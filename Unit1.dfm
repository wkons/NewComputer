object Form1: TForm1
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = '   3. '#1053#1054#1042#1067#1049' '#1055#1056#1048#1053#1062#1048#1055' '#1042#1067#1063#1048#1057#1051#1045#1053#1048#1049
  ClientHeight = 565
  ClientWidth = 823
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox1: TPaintBox
    Left = 11
    Top = 15
    Width = 800
    Height = 500
    OnClick = PaintBox1Click
  end
  object Button1: TButton
    Left = 11
    Top = 529
    Width = 103
    Height = 25
    Caption = #1055#1072#1091#1079#1072
    TabOrder = 0
    OnClick = Button1Click
  end
  object CheckBox1: TCheckBox
    Left = 588
    Top = 533
    Width = 221
    Height = 17
    Caption = #1055#1086#1076#1072#1074#1072#1090#1100' '#1085#1072' '#1074#1093#1086#1076#1099' '#1089#1083#1091#1095#1072#1081#1085#1099#1077' '#1076#1072#1085#1085#1099#1077
    Checked = True
    State = cbChecked
    TabOrder = 1
  end
  object Button2: TButton
    Left = 120
    Top = 529
    Width = 109
    Height = 25
    Caption = #1057#1073#1088#1086#1089#1080#1090#1100' '#1089#1077#1090#1100
    TabOrder = 2
    OnClick = Button2Click
  end
  object CheckBox2: TCheckBox
    Left = 466
    Top = 533
    Width = 116
    Height = 17
    Caption = #1058#1091#1088#1073#1086'-'#1088#1077#1078#1080#1084
    TabOrder = 3
  end
  object Timer1: TTimer
    Interval = 33
    OnTimer = Timer1Timer
    Left = 32
    Top = 36
  end
end
