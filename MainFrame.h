//---------------------------------------------------------------------------

#ifndef MainFrameH
#define MainFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Edge.hpp>
#include <WebView2.hpp>
#include <Winapi.ActiveX.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.GIFImg.hpp>
//------------------------------------

class TBrowserFrame : public TFrame
{
__published:	// IDE-managed Components
	TEdgeBrowser *EdgeBrowser;

	TPanel *Progress;
	TImage *imgProgress;
	void __fastcall EdgeBrowserContentLoading(TCustomEdgeBrowser *Sender, bool IsErrorPage,
          TUInt64 NavigationID);
	void __fastcall EdgeBrowserCreateWebViewCompleted(TCustomEdgeBrowser *Sender, HRESULT AResult);
	void __fastcall EdgeBrowserExecuteScript(TCustomEdgeBrowser *Sender, HRESULT AResult,
          const UnicodeString AResultObjectAsJson);
	void __fastcall EdgeBrowserFrameNavigationCompleted(TCustomEdgeBrowser *Sender,
          bool IsSuccess, TOleEnum WebErrorStatus);
	void __fastcall EdgeBrowserFrameNavigationStarting(TCustomEdgeBrowser *Sender, TNavigationStartingEventArgs *Args);
	void __fastcall EdgeBrowserHistoryChanged(TCustomEdgeBrowser *Sender);
	void __fastcall EdgeBrowserNavigationCompleted(TCustomEdgeBrowser *Sender, bool IsSuccess,
          TOleEnum WebErrorStatus);
	void __fastcall EdgeBrowserNavigationStarting(TCustomEdgeBrowser *Sender, TNavigationStartingEventArgs *Args);
	void __fastcall EdgeBrowserNewWindowRequested(TCustomEdgeBrowser *Sender, TNewWindowRequestedEventArgs *Args);
	void __fastcall EdgeBrowserPermissionRequested(TCustomEdgeBrowser *Sender, TPermissionRequestedEventArgs *Args);
	void __fastcall EdgeBrowserProcessFailed(TCustomEdgeBrowser *Sender, TOleEnum ProcessFailedKind);
	void __fastcall EdgeBrowserScriptDialogOpening(TCustomEdgeBrowser *Sender, TScriptDialogOpeningEventArgs *Args);
	void __fastcall EdgeBrowserDocumentTitleChanged(TCustomEdgeBrowser *Sender, const UnicodeString ADocumentTitle);
	void __fastcall EdgeBrowserContainsFullScreenElementChanged(TCustomEdgeBrowser *Sender,
          bool ContainsFullScreenElement);
	void __fastcall EdgeBrowserWebResourceRequested(TCustomEdgeBrowser *Sender, TWebResourceRequestedEventArgs *Args);
	void __fastcall FrameClick(TObject *Sender);
	void __fastcall imgProgressClick(TObject *Sender);
	void __fastcall ProgressClick(TObject *Sender);









private:	// User declarations
public:		// User declarations
	__fastcall TBrowserFrame(TComponent* Owner);
	void CreateBrowser(String newTitle,String loadUrl);
	void Close();



TTabSheet* TabSheet;
String url;


};
//---------------------------------------------------------------------------
extern PACKAGE TBrowserFrame *BrowserFrame;
//---------------------------------------------------------------------------
#endif
