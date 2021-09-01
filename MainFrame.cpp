//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <System.SysUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.IOUtils.hpp>
//#include <System.AnsiStrings.hpp>
#include "MainFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBrowserFrame *BrowserFrame;
#include "Unit1.h"
#include "ULogResources.h"

extern bool FBlockImages;
//---------------------------------------------------------------------------
__fastcall TBrowserFrame::TBrowserFrame(TComponent* Owner)
	: TFrame(Owner)
{
//TabSheet=(TTabSheet*)Owner;
}


//---------------------------------------------------------------------------

void TBrowserFrame::CreateBrowser(String newTitle,String loadUrl)
{
   url=loadUrl;

//EdgeBrowser->SetBrowserExecutableFolder("I:\WebView2.FixedVersionRuntime.92.0.902.84.x64");
//EdgeBrowser->BrowserExecutableFolder = TPath::GetDirectoryName("I:\\WebView2.FixedVersionRuntime.92.0.902.84.x64");
EdgeBrowser->CreateWebView();



 String URL = loadUrl;
   if (!StartsText(L"http", URL))
		URL = L"http://" + URL;
	EdgeBrowser->Navigate(URL);


}
void TBrowserFrame::Close()
{
 EdgeBrowser->CloseWebView();
 EdgeBrowser->CloseBrowserProcess();
}


void __fastcall TBrowserFrame::EdgeBrowserContentLoading(TCustomEdgeBrowser *Sender, bool IsErrorPage, TUInt64 NavigationID)
{
			   //
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserCreateWebViewCompleted(TCustomEdgeBrowser *Sender,
          HRESULT AResult)
{
   if (SUCCEEDED(AResult))
    {


		Sender->AddWebResourceRequestedFilter('*', COREWEBVIEW2_WEB_RESOURCE_CONTEXT_ALL);
    }
    else
    {
        if (AResult == HResultFromWin32(ERROR_FILE_NOT_FOUND))
            Application->MessageBox(L"Could not find Edge installation. "
                "Do you have a version installed that''s compatible with this WebView2 SDK version?",
                L"Edge initialisation error", MB_OK | MB_ICONERROR);
        else if (AResult == E_FAIL)
            Application->MessageBox(L"Failed to initialise Edge loader",
                L"Edge initialisation error", MB_OK | MB_ICONERROR);
        else
            try
            {
                OleCheck(AResult);
            }
            catch (Exception &e)
            {
                String msg;
                msg.sprintf(L"Failed to initialise Edge: %s", e.Message.c_str());
                Application->MessageBox(
                    msg.c_str(),
                    L"Edge initialisation error", MB_OK | MB_ICONERROR);
            }
	}
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserExecuteScript(TCustomEdgeBrowser *Sender, HRESULT AResult, const UnicodeString AResultObjectAsJson)

{
 //
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserFrameNavigationCompleted(TCustomEdgeBrowser *Sender,bool IsSuccess, TOleEnum WebErrorStatus)
{
	//
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserFrameNavigationStarting(TCustomEdgeBrowser *Sender, TNavigationStartingEventArgs *Args)
{
	Progress->Visible=true;
   //	Sender->AddWebResourceRequestedFilter('*', COREWEBVIEW2_WEB_RESOURCE_CONTEXT_ALL);

	WideChar *Uri;

	 if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)))
	 {

	   addLink(Uri);

	 }

	if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)) && 	 block(Uri))
	{
		Args->ArgsInterface->Set_Cancel(TRUE);
	}





	Args->ArgsInterface->Set_Cancel(TRUE);
	CoTaskMemFree(Uri);
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserHistoryChanged(TCustomEdgeBrowser *Sender)

{
 //
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserNavigationCompleted(TCustomEdgeBrowser *Sender,  bool IsSuccess, TOleEnum WebErrorStatus)
{
 Progress->Visible=false;

// TabSheet->Caption


}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserNavigationStarting(TCustomEdgeBrowser *Sender, TNavigationStartingEventArgs *Args)
{
Progress->Visible=true;
TGIFImage* image =(TGIFImage*) imgProgress->Picture->Graphic;
if (image)
{
image->Animate=true;
}

	WideChar *Uri;


	if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)) && 	 block(Uri))
	{
		Args->ArgsInterface->Set_Cancel(TRUE);
	}  else
	{
	   addLink(Uri);
	}


	CoTaskMemFree(Uri);
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserNewWindowRequested(TCustomEdgeBrowser *Sender,TNewWindowRequestedEventArgs *Args)
{
  //
	 Args->ArgsInterface->Set_Handled(true);
	 WideChar *Uri;



	  //	about:blank#blocked


	 if (SUCCEEDED(Args->ArgsInterface->Get_uri(Uri)) )
	 {
	 if (ContainsText(Uri,"about:blank"))
	 {
		CoTaskMemFree(Uri);
	    return;
	 }


	 if (!block(Uri))
	 {

			 MainForm->add(Uri);
		   //	 addLink(Uri);
	 }

			CoTaskMemFree(Uri);
	 }



}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserPermissionRequested(TCustomEdgeBrowser *Sender,TPermissionRequestedEventArgs *Args)
{
   //
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserProcessFailed(TCustomEdgeBrowser *Sender,
          TOleEnum ProcessFailedKind)
{
 if (ProcessFailedKind == COREWEBVIEW2_PROCESS_FAILED_KIND_BROWSER_PROCESS_EXITED)
    {
        int button = Application->MessageBox(
            L"Browser process exited unexpectedly. Recreate webview?",
            L"Browser process exited",
            MB_YESNO | MB_ICONQUESTION);
        if (button == IDYES)
            EdgeBrowser->ReinitializeWebView();
    }
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserScriptDialogOpening(TCustomEdgeBrowser *Sender,
          TScriptDialogOpeningEventArgs *Args)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserDocumentTitleChanged(TCustomEdgeBrowser *Sender,
		  const UnicodeString ADocumentTitle)
{
if (!this->Visible) return;



// StrLCopy(szBuffer, ADocumentTitle.t_str(), 10);
// Application->MessageBox(WideString(szBuffer).c_bstr(), L"StrLCopy example", MB_OKCANCEL);
//TabSheet->Caption=WideString(szBuffer).c_bstr();
TabSheet->Hint=ADocumentTitle;
MainForm->Caption=ADocumentTitle;
MainForm->edtAddress->Text=EdgeBrowser->LocationURL;




wchar_t* txt = ADocumentTitle.t_str();
std::wstring ws = txt;
std::string str( ws.begin(), ws.end() );
char buffer[11];

int size=str.size();//ADocumentTitle.Length();

for (int i=0;i<=10;i++)
{
buffer[i]='\0';
}


if (size>10)
{
 size=10;
}

std::size_t length = str.copy(buffer,size);

TabSheet->Caption=buffer;
TabSheet->Hint=ADocumentTitle;
MainForm->Caption=ADocumentTitle;

MainForm->edtAddress->Text=EdgeBrowser->LocationURL;

}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserContainsFullScreenElementChanged(TCustomEdgeBrowser *Sender,
          bool ContainsFullScreenElement)
{
if (ContainsFullScreenElement)
    {
		MainForm->BorderStyle = bsNone;
	  	MainForm->WindowState = wsMaximized;
    }
    else
    {
		MainForm->WindowState = wsNormal;
		MainForm->BorderStyle = bsSizeable;
	}
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::EdgeBrowserWebResourceRequested(TCustomEdgeBrowser *Sender,
          TWebResourceRequestedEventArgs *Args)
{



//_di_ICoreWebView2WebResourceResponse Response;
_di_ICoreWebView2WebResourceRequest Request;
	  /*
        static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_ALL = System::Int8(0x0);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_DOCUMENT = System::Int8(0x1);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_STYLESHEET = System::Int8(0x2);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE = System::Int8(0x3);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_MEDIA = System::Int8(0x4);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_FONT = System::Int8(0x5);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_SCRIPT = System::Int8(0x6);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_XML_HTTP_REQUEST = System::Int8(0x7);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_FETCH = System::Int8(0x8);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_TEXT_TRACK = System::Int8(0x9);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_EVENT_SOURCE = System::Int8(0xa);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_WEBSOCKET = System::Int8(0xb);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_MANIFEST = System::Int8(0xc);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_SIGNED_EXCHANGE = System::Int8(0xd);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_PING = System::Int8(0xe);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_CSP_VIOLATION_REPORT = System::Int8(0xf);
static const System::Int8 COREWEBVIEW2_WEB_RESOURCE_CONTEXT_OTHER = System::Int8(0x10);
	  */

 COREWEBVIEW2_WEB_RESOURCE_CONTEXT ResourceContext;




	if (SUCCEEDED(  Args->ArgsInterface->Get_ResourceContext(ResourceContext)))
		{

		int id=(int)ResourceContext;


          trace(String().sprintf(L"RESOURCE  id:%d",id));

			if (ResourceContext == COREWEBVIEW2_WEB_RESOURCE_CONTEXT_MEDIA)
			{

						if (SUCCEEDED(Args->ArgsInterface->Get_Request(Request)))
						{
							WideChar *Uri;
							 Request->Get_uri(Uri) ;


							 trace(String().sprintf(L"MEDIA %s  ",Uri));


							 if (Uri) CoTaskMemFree(Uri);

						}



			}

			if (ResourceContext == COREWEBVIEW2_WEB_RESOURCE_CONTEXT_SCRIPT)
			{

						if (SUCCEEDED(Args->ArgsInterface->Get_Request(Request)))
						{
										WideChar *Uri;
							 Request->Get_uri(Uri) ;
							// if (AnsiEndsText(Uri,".js"))
							 {
							 trace(String().sprintf(L"SCRIPT %s ",Uri));
							 }



						 //	if (block(Uri))
							{

							}


							  if (Uri) CoTaskMemFree(Uri);

						}

					

			}

				if (ResourceContext == COREWEBVIEW2_WEB_RESOURCE_CONTEXT_XML_HTTP_REQUEST)
			{

						if (SUCCEEDED(Args->ArgsInterface->Get_Request(Request)))
						{
									WideChar *Uri;
							 Request->Get_uri(Uri) ;

                             	if (block(Uri))
							{

							}

							 if (ContainsText(Uri,".m3u8"))
							 {
							  trace(String().sprintf(L"REQUEST %s ",Uri));
							 }
							  if (Uri) CoTaskMemFree(Uri);

						}



			}

					if (ResourceContext == COREWEBVIEW2_WEB_RESOURCE_CONTEXT_FETCH)
			{

						if (SUCCEEDED(Args->ArgsInterface->Get_Request(Request)))
						{
							WideChar *Uri;
							 Request->Get_uri(Uri) ;

                             	if (block(Uri))
							{

							}

						  //	 trace(String().sprintf(L"FETCH %s ",Uri));
							 if (ContainsText(Uri,".m3u8"))
							 {
								 trace(String().sprintf(L"FETCH %s ",Uri));
							 }


						if (Uri) CoTaskMemFree(Uri);
						}



			}

        }



	if (FBlockImages)
	{

		if (SUCCEEDED(
			Args->ArgsInterface->Get_ResourceContext(ResourceContext)))
		{
			// Ensure that the type is image
			if (ResourceContext != COREWEBVIEW2_WEB_RESOURCE_CONTEXT_IMAGE)
				return;
			// Override the response with an empty one to block the image.
			// If Set_Response is not called, the request will continue as normal.
			_di_ICoreWebView2WebResourceResponse Response;
			if (SUCCEEDED(EdgeBrowser->EnvironmentInterface->CreateWebResourceResponse(
				NULL, 403 , (wchar_t *)L"Blocked", (wchar_t *)L"", Response)))
				Args->ArgsInterface->Set_Response(Response);
		}
	}


}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::FrameClick(TObject *Sender)
{
Progress->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::imgProgressClick(TObject *Sender)
{
 Progress->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TBrowserFrame::ProgressClick(TObject *Sender)
{
Progress->Visible=false;
}
//---------------------------------------------------------------------------

