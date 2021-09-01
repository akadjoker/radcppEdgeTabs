//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Uads.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormAds *FormAds;

extern TStringList *adsList;
//---------------------------------------------------------------------------
__fastcall TFormAds::TFormAds(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormAds::Button1Click(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormAds::FormShow(TObject *Sender)
{

ListAds->Items->LoadFromFile("data/ads.txt");

}
//---------------------------------------------------------------------------
void __fastcall TFormAds::FormClose(TObject *Sender, TCloseAction &Action)
{
ListAds->Items->SaveToFile("data/ads.txt");
adsList->Clear();
adsList->LoadFromFile("data/ads.txt");
}
//---------------------------------------------------------------------------
void __fastcall TFormAds::ListAdsClick(TObject *Sender)
{
if (ListAds->ItemIndex<0) return;
String add = ListAds->Items->Strings[ListAds->ItemIndex];
Edit1->Text=add;
Caption = IntToStr(ListAds->ItemIndex)+ " "+add;

}
//---------------------------------------------------------------------------
void __fastcall TFormAds::Button4Click(TObject *Sender)
{
ListAds->Items->SaveToFile("data/ads.txt");
adsList->Clear();
adsList->LoadFromFile("data/ads.txt");
}
//---------------------------------------------------------------------------
void __fastcall TFormAds::Button3Click(TObject *Sender)
{
if (ListAds->ItemIndex<0) return;
String add = ListAds->Items->Strings[ListAds->ItemIndex];
int BIndex = ListAds->Items->IndexOf(add);
if (BIndex > -1)
	ListAds->Items->Delete(BIndex);

}
//---------------------------------------------------------------------------
void __fastcall TFormAds::Button2Click(TObject *Sender)
{
ListAds->Items->Append(Edit1->Text);
}
//---------------------------------------------------------------------------
