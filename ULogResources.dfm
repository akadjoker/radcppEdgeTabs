object FormLogRes: TFormLogRes
  Left = 0
  Top = 0
  Caption = 'Resources Watcher'
  ClientHeight = 488
  ClientWidth = 711
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 447
    Width = 711
    Height = 41
    Align = alBottom
    TabOrder = 0
    ExplicitLeft = 400
    ExplicitTop = 120
    ExplicitWidth = 185
    object Button1: TButton
      Left = 536
      Top = 5
      Width = 75
      Height = 25
      Caption = 'Clear'
      TabOrder = 0
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 617
      Top = 5
      Width = 75
      Height = 25
      Caption = 'Close'
      TabOrder = 1
      OnClick = Button2Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 711
    Height = 447
    Align = alClient
    Caption = 'Panel2'
    TabOrder = 1
    ExplicitLeft = 424
    ExplicitTop = 176
    ExplicitWidth = 185
    ExplicitHeight = 41
    object Memo1: TMemo
      Left = 1
      Top = 1
      Width = 709
      Height = 445
      Align = alClient
      Lines.Strings = (
        '')
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
end
