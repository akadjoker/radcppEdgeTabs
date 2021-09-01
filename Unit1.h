//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <System.StrUtils.hpp>

#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Menus.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "MainFrame.h"
#include <Vcl.Edge.hpp>
#include <WebView2.hpp>
#include <Winapi.ActiveX.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TImageList *ImageList1;
	TPanel *PanelBar;
	TSpeedButton *SpeedButton6;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8;
	TSpeedButton *SpeedButton9;
	TSpeedButton *SpeedButton10;
	TMenuItem *File1;
	TMenuItem *add2;
	TSpeedButton *SpeedButton1;
	TEdit *edtAddress;
	TPopupMenu *PopupMenu1;
	TMenuItem *PopupMenu11;
	TMenuItem *Navigation1;
	TMenuItem *Hack1;
	TMenuItem *Window1;
	TMenuItem *CloseTool1;
	TMenuItem *Back1;
	TMenuItem *Home1;
	TMenuItem *Forword;
	TMenuItem *Stop1;
	TMenuItem *Reload1;
	TPageControl *Pages;
	TSpeedButton *SpeedButton2;
	TMenuItem *Zoom1;
	TMenuItem *N252;
	TMenuItem *N502;
	TMenuItem *N752;
	TMenuItem *N1001;
	TMenuItem *Zoom3;
	TMenuItem *N2;
	TMenuItem *N501;
	TMenuItem *N1002;
	TMenuItem *N1501;
	TMenuItem *N2001;
	TMenuItem *N251;
	TMenuItem *InjectJava1;
	TMenuItem *WatchResources1;
	TMenuItem *Favorites1;
	TMenuItem *youtube1;
	TMenuItem *kickass1;
	TMenuItem *N1;
	TMenuItem *BlockAds;
	TMenuItem *Edit1;
	TMenuItem *Ads1;
	TMenuItem *mShowImages;
	TSplitter *Splitter2;
	TMenuItem *duckduckgo1;
	void __fastcall SpeedButton10Click(TObject *Sender);
	void __fastcall add2Click(TObject *Sender);
	void __fastcall SpeedButton9Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SpeedButton8Click(TObject *Sender);
	void __fastcall edtAddressKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall SpeedButton7Click(TObject *Sender);
	void __fastcall PopupMenu11Click(TObject *Sender);
	void __fastcall CloseTool1Click(TObject *Sender);
	void __fastcall PagesChange(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall Back1Click(TObject *Sender);
	void __fastcall Home1Click(TObject *Sender);
	void __fastcall ForwordClick(TObject *Sender);
	void __fastcall Stop1Click(TObject *Sender);
	void __fastcall Reload1Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall N252Click(TObject *Sender);
	void __fastcall N502Click(TObject *Sender);
	void __fastcall N752Click(TObject *Sender);
	void __fastcall N1001Click(TObject *Sender);
	void __fastcall N501Click(TObject *Sender);
	void __fastcall N1002Click(TObject *Sender);
	void __fastcall N1501Click(TObject *Sender);
	void __fastcall N2001Click(TObject *Sender);
	void __fastcall N251Click(TObject *Sender);
	void __fastcall WatchResources1Click(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Favorites2Click(TObject *Sender);
	void __fastcall chartubate1Click(TObject *Sender);
	void __fastcall youtube1Click(TObject *Sender);
	void __fastcall kickass1Click(TObject *Sender);
	void __fastcall Edit1Click(TObject *Sender);
	void __fastcall mShowImagesClick(TObject *Sender);
	void __fastcall duckduckgo1Click(TObject *Sender);










private:	// User declarations
public:		// User declarations
	__fastcall TMainForm(TComponent* Owner);


	void add(String url);
	void navigate(String url,bool past=false);
};

class TabEdgeItem : public TTabSheet
{

__published:	// IDE-managed Components
	TBrowserFrame *BrowserFrame;
	TEdgeBrowser *EdgeBrowser;

private:	// User declarations
public:		// User declarations
	__fastcall TabEdgeItem(TComponent* Owner);
   void createBrowser(String url,String title);
   void Close();
   void setMobileUserAgent();
   void setDesktopUserAgent();
   bool isMobile;



};

//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;


//---------------------------------------------------------------------------
bool ShouldBlockURI(String Uri);
bool block(String url);
void trace(String url);
void addLink(String url);
void ActivateHintNOW(String Txt, TPoint Pt);


#endif
