//---------------------------------------------------------------------------

#ifndef ULogResourcesH
#define ULogResourcesH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFormLogRes : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TMemo *Memo1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFormLogRes(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormLogRes *FormLogRes;
//---------------------------------------------------------------------------
#endif
