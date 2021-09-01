//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ULogResources.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLogRes *FormLogRes;
//---------------------------------------------------------------------------
__fastcall TFormLogRes::TFormLogRes(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormLogRes::Button2Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormLogRes::Button1Click(TObject *Sender)
{
Memo1->Lines->Clear();
}
//---------------------------------------------------------------------------
