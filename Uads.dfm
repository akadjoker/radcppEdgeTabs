object FormAds: TFormAds
  Left = 0
  Top = 0
  Caption = 'FormAds'
  ClientHeight = 539
  ClientWidth = 912
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 912
    Height = 498
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 416
    ExplicitTop = 56
    ExplicitWidth = 185
    ExplicitHeight = 41
    object ListAds: TListBox
      Left = 1
      Top = 1
      Width = 910
      Height = 496
      Align = alClient
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListAdsClick
      ExplicitLeft = 312
      ExplicitTop = 88
      ExplicitWidth = 121
      ExplicitHeight = 97
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 498
    Width = 912
    Height = 41
    Align = alBottom
    TabOrder = 1
    ExplicitLeft = 288
    ExplicitTop = 104
    ExplicitWidth = 185
    object Edit1: TEdit
      Left = 1
      Top = 6
      Width = 280
      Height = 21
      TabOrder = 0
    end
    object Button1: TButton
      Left = 824
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Close'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 287
      Top = 5
      Width = 75
      Height = 25
      Caption = 'Add'
      TabOrder = 2
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 368
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Delete'
      TabOrder = 3
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 449
      Top = 6
      Width = 75
      Height = 25
      Caption = 'Update'
      TabOrder = 4
      OnClick = Button4Click
    end
  end
end
