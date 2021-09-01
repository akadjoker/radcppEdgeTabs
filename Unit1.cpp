//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <windows.h>
#include <string.h>
#include <iostream>
#include <string.h>         // Required for: strcmp(), strstr(), strcpy(), strncpy() [Used in TextReplace()], sscanf() [Used in LoadBMFont()]
#include <stdarg.h>         // Required for: va_list, va_start(), vsprintf(), va_end() [Used in TextFormat()]
#include <ctype.h>          // Requried for: toupper(), tolower() [Used in TextToUpper(), TextToLower()]
#include <string>
#include <IdURI.hpp>
#include <System.StrUtils.hpp>
#include <System.SysUtils.hpp>
#include <System.AnsiStrings.hpp>
#include <System.IOUtils.hpp>

#include <memory>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include "ULogResources.h"
#include "Uads.h"

TStringList *strList;
TStringList *adsList;
TMainForm *MainForm;
THintWindow *HintWnd;
TabEdgeItem* currentTabEdge=NULL;

static int PagesIndex=100;
bool FBlockImages=false;



bool ShouldBlockURI(String Uri)
{
#ifdef __clang__
	std::unique_ptr<TIdURI> URI(new TIdURI(Uri));
#else
	std::auto_ptr<TIdURI> URI(new TIdURI(Uri));
#endif
	// For no particular reason, block Google's main English sites
	String Host = URI->Host.LowerCase();
	if (EndsStr(L"yahoo.com", Host) || EndsStr(L"yahoo.co.uk", Host))
		return true;
	return false;
}
void trace(String msg)
{

}

void ActivateHintNOW(String Txt, TPoint Pt)
{
	if (Txt.Length())
	{
		TRect Rect = HintWnd->CalcHintRect(Screen->Width, Txt, NULL);
		Rect.Left = Rect.Left + Pt.X;
		Rect.Right = Rect.Right + Pt.X;
		Rect.Top = Rect.Top + Pt.Y;
		Rect.Bottom = Rect.Bottom + Pt.Y;
		HintWnd->ActivateHint(Rect, Txt);
	}
}


bool FindString(String Substring, String  Text)
{
int  offset=0;
int  count=0;

wchar_t* txt = Text.w_str();
std::wstring ws = txt;
std::string str( ws.begin(), ws.end() );

wchar_t* txt2 = Substring.w_str();
std::wstring ws2 = txt2;
std::string str2( ws2.begin(), ws2.end() );


if (str.find(str2) != std::string::npos)
{
return true;
}
return false;
}

int Occurrences(String Substring, String  Text)
{
int count=0;
  int last=1;
  for (int i=1;i<=Text.Length();i++)
  {
	  char value = Text[i];

	  for (int j=last;j<=Substring.Length();j++)
	  {
		if (value==Substring[j])
		{
			 count+=1;
//			 MainForm->Memo1->Lines->Add(String().sprintf(L"match %c",			 Substring[j]));
             last=j;
			continue;
        }
	  }
  }

  return count;
}


bool block(String url)
{
	  // MainForm->Memo1->Lines->Add(url);

       if (!MainForm->BlockAds->Checked) return false;


	for (auto host :adsList)
	{

  //	std::auto_ptr<TIdURI> URI(new TIdURI(url));
  //	String Host = URI->Host.LowerCase();


	int compare =   Occurrences(LowerCase(url),LowerCase( host)); //CompareText(LowerCase(str),LowerCase(url));
 //  MainForm->Memo1->Lines->Add(String().sprintf(L" url %s Host: %s    %d %d", url.c_str(),host.c_str(),compare,host.Length()));





	  //	if (CompareText(LowerCase(str),LowerCase(url))>=str.Length()-1)

	   if  (ContainsText(url,host))
	 //  if (AnsiStrLComp(str.c_str(),url.c_str(),str.Length()-1))
	// if (compare>=host.Length()-1)
	   {
		   trace("BLOCK ->"+url+" : "+host);
		 //  ActivateHintNOW(String().sprintf(L"Add Block  %s Host: %s ", url.c_str(),host.c_str()),
		 //  MainForm->ClientToScreen(Point(MainForm->Width / 2-(MainForm->Width/2),-GetSystemMetrics(SM_CYCAPTION) -GetSystemMetrics(SM_CYCAPTION))));

		   return true  ;
	   }


	}
	return false;
}

void addLink(String url)
{
   //	 if (!FormLogRes->Visible) return;
	 int index;
	 if (!strList->Find(url,index))
	 {
				 strList->Add(url);
		         trace(url);

	 }
}
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner)
{
HintWnd = new THintWindow(this);

 






}

void TMainForm::navigate(String URL,bool past)
{
   try
{


	if (past)
	{
		edtAddress->Text=URL;

	}

   if (!StartsText(L"http", URL))
		URL = L"http://" + URL;


	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		 TempNewTab->EdgeBrowser->Navigate(URL);
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}

}
void TMainForm::add(String url)
{
 std::string str ((char*)url.data());
  char buffer[20];
  std::size_t length = str.copy(buffer,15);
  buffer[length]='\0';
  std::string title(buffer);

  TabEdgeItem* TempNewTab  = new TabEdgeItem(Pages);
  TempNewTab->PageControl = Pages;
  TempNewTab->Caption=*buffer;
  TempNewTab->Tag=(PagesIndex++)+Pages->PageCount;
  TempNewTab->createBrowser(url,url);

  Pages->TabIndex++;
}

//---------------------------------------------------------------------------

__fastcall TabEdgeItem::TabEdgeItem(TComponent* Owner)
	: TTabSheet(Owner)
{
 isMobile=false;
}
void TabEdgeItem::setMobileUserAgent()
{
 isMobile=true;
}
void TabEdgeItem::setDesktopUserAgent()
{
  isMobile=false;
}

void TabEdgeItem::Close()
{
BrowserFrame->Close();
}




void TabEdgeItem::createBrowser(String url,String title)
{

BrowserFrame = new TBrowserFrame(this);
BrowserFrame->Parent =this;
BrowserFrame->Visible=true;
BrowserFrame->Align =alClient;
BrowserFrame->TabSheet=this;
BrowserFrame->url=url;
BrowserFrame->CreateBrowser(title,url);
EdgeBrowser=BrowserFrame->EdgeBrowser;
BrowserFrame->Show();

}


void __fastcall TMainForm::SpeedButton10Click(TObject *Sender)
{
add(edtAddress->Text);

}
//---------------------------------------------------------------------------



void __fastcall TMainForm::add2Click(TObject *Sender)
{
 Close();

}
//---------------------------------------------------------------------------



void __fastcall TMainForm::SpeedButton9Click(TObject *Sender)
{

	String URL = edtAddress->Text;
   if (!StartsText(L"http", URL))
		URL = L"http://" + URL;
   /*
	  EdgeBrowser->Navigate(URL);
	  return;
			  */
try
{




	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->Navigate(URL);
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}



}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
FBlockImages=mShowImages->Checked;






strList  = new TStringList();
adsList = new TStringList();
adsList->LoadFromFile("data/ads.txt");



}
//---------------------------------------------------------------------------




void __fastcall TMainForm::SpeedButton8Click(TObject *Sender)
{

try
{

	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;
	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		if (TempNewTab->EdgeBrowser->CanGoBack)		TempNewTab->EdgeBrowser->GoBack();
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}



}
//---------------------------------------------------------------------------










void __fastcall TMainForm::edtAddressKeyPress(TObject *Sender, System::WideChar &Key)

{
	if (Key == 13)
    {
        Key = 0;
		navigate(edtAddress->Text);

	}
}
//---------------------------------------------------------------------------







// xstring(798): candidate constructor not viable: no known conversion from 'System::WideChar *' (aka 'wchar_t *') to 'const std::basic_string<char, std::char_traits<char>, std::allocator<char> >::_Myt' (aka 'const basic_string<char, std::char_traits<char>, std::allocator<char> >') for 1st argument

void __fastcall TMainForm::SpeedButton7Click(TObject *Sender)
{


try
{

 edtAddress->Text="www.google.pt";
	String URL = edtAddress->Text;
   if (!StartsText(L"http", URL))
		URL = L"http://" + URL;


	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {


	 TempNewTab->EdgeBrowser->Navigate(URL);
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}



}
//---------------------------------------------------------------------------


void __fastcall TMainForm::PopupMenu11Click(TObject *Sender)
{
 TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;
  TempNewTab->Close();
  delete TempNewTab;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::CloseTool1Click(TObject *Sender)
{

CloseTool1->Checked=!CloseTool1->Checked;

PanelBar->Enabled=CloseTool1->Checked;
PanelBar->Visible=CloseTool1->Checked;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::PagesChange(TObject *Sender)
{


try
{
  TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

Caption=IntToStr(Pages->PageCount)+" "+IntToStr(Pages->TabIndex)+" "+IntToStr(TempNewTab->Tag);


	if (TempNewTab)
	{
	  if(	 TempNewTab->EdgeBrowser)
	  {
			 Caption=  TempNewTab->EdgeBrowser->DocumentTitle;
			 edtAddress->Text=TempNewTab->EdgeBrowser->LocationURL;
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton6Click(TObject *Sender)
{

try
{

	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;
	if (TempNewTab)
	{
	  if(	 TempNewTab->EdgeBrowser)
	  {

	   TempNewTab->EdgeBrowser->GoForward();
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormActivate(TObject *Sender)
{


 edtAddress->Text="www.google.pt";

	String URL = edtAddress->Text;
   if (!StartsText(L"http", URL))
		URL = L"http://" + URL;
add(URL);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::SpeedButton1Click(TObject *Sender)
{


try
{


	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	TempNewTab->SetFocus();
	  if(	  TempNewTab->EdgeBrowser)
	  {

	  TempNewTab->EdgeBrowser->SetFocus();
	  TempNewTab->EdgeBrowser->Refresh();
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Back1Click(TObject *Sender)
{
SpeedButton8Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Home1Click(TObject *Sender)
{
SpeedButton7Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ForwordClick(TObject *Sender)
{
SpeedButton6Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Stop1Click(TObject *Sender)
{
SpeedButton2Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Reload1Click(TObject *Sender)
{
SpeedButton1Click(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SpeedButton2Click(TObject *Sender)
{

try
{




	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->Stop();
	  }


	}



} catch (const char* msg)
{
	ShowMessage(msg);
}

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N252Click(TObject *Sender)
{
try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->SizeRatio = 0.5f;
		 			  // A couple of ways present themselves to get the bounding dimensions of the WebView2 browser control.
			// One uses the WebView2 interface, one uses VCL control methods
		#define ONE_POSSIBLE_WAY
		#ifdef ONE_POSSIBLE_WAY
			tagRECT Bounds;
					  TempNewTab->EdgeBrowser->ControllerInterface->Get_Bounds(Bounds);
			String Msg = String().sprintf(L"Left:\t%d\nTop:\t%d\nRight:\t%d\nBottom:\t%d\n",
				Bounds.left, Bounds.top, Bounds.right, Bounds.bottom);

			Width=Bounds.right;
            Height=Bounds.bottom;
		   //	Application->MessageBox(Msg.c_str(), L"WebView Bounds", MB_OK | MB_ICONINFORMATION);
		#else
			TRect Bounds = EdgeBrowser->BoundsRect;
			TSize Size = Bounds.Size;
			Bounds.Location = 		  TempNewTab->EdgeBrowser->ClientToScreen(Bounds.Location);
			Bounds.Size = Size;
			String Msg = String().sprintf(L"Left:\t%d\nTop:\t%d\nRight:\t%d\nBottom:\t%d\n",
				Bounds.Left, Bounds.Top, Bounds.Right, Bounds.Bottom);
			Application->MessageBox(Msg.c_str(), L"WebView Bounds", MB_OK | MB_ICONINFORMATION);
		#endif

	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N502Click(TObject *Sender)
{
try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->SizeRatio = 0.7071f;
	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N752Click(TObject *Sender)
{
try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->SizeRatio = 0.806f;
	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N1001Click(TObject *Sender)
{
try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->SizeRatio = 1;
	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N501Click(TObject *Sender)
{
   try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->ZoomFactor = 0.5;
	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N1002Click(TObject *Sender)
{
   try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->ZoomFactor = 1.0;
	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N1501Click(TObject *Sender)
{
   try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->ZoomFactor = 1.5;
	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N2001Click(TObject *Sender)
{
   try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->ZoomFactor = 2.0;
	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N251Click(TObject *Sender)
{
   try
{
	TabEdgeItem* TempNewTab=(TabEdgeItem*)Pages->Pages[Pages->TabIndex] ;

	if (TempNewTab)
	{
	  if(	  TempNewTab->EdgeBrowser)
	  {
		  TempNewTab->EdgeBrowser->ZoomFactor = 0.2;


		


	  }


	}

} catch (const char* msg)
{
	ShowMessage(msg);
}
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::WatchResources1Click(TObject *Sender)
{
FormLogRes->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
strList->SaveToFile("data/readlinks.txt");
delete strList;
delete adsList;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Favorites2Click(TObject *Sender)
{

navigate("www.cam4.pt",true);


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::chartubate1Click(TObject *Sender)
{

navigate("https://pt.chaturbate.com",true);

}
//---------------------------------------------------------------------------



void __fastcall TMainForm::youtube1Click(TObject *Sender)
{


navigate("https://www.youtube.com",true);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::kickass1Click(TObject *Sender)
{
navigate("https://kickasstorrents.to",true);


}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit1Click(TObject *Sender)
{
  FormAds->Show();
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mShowImagesClick(TObject *Sender)
{
mShowImages->Checked=!mShowImages->Checked;

FBlockImages=mShowImages->Checked;

}
//---------------------------------------------------------------------------




void __fastcall TMainForm::duckduckgo1Click(TObject *Sender)
{

navigate("https://duckduckgo.com/",true);
}
//---------------------------------------------------------------------------

