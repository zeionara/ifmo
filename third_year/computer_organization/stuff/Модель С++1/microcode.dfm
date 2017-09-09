object Form1: TForm1
  Left = 289
  Top = 208
  Width = 768
  Height = 452
  Caption = '98'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 56
    Top = 96
    Width = 93
    Height = 13
    Caption = '15    PCH. PCL    0 '
  end
  object Label4: TLabel
    Left = 256
    Top = 112
    Width = 77
    Height = 13
    Caption = '7        Data      0'
  end
  object Label5: TLabel
    Left = 376
    Top = 112
    Width = 84
    Height = 13
    Caption = '7       SFR          0'
  end
  object Label6: TLabel
    Left = 592
    Top = 96
    Width = 76
    Height = 13
    Caption = '7      Xdata      0'
  end
  object Label7: TLabel
    Left = 376
    Top = 152
    Width = 81
    Height = 13
    Caption = '7         ACC       0'
  end
  object Label8: TLabel
    Left = 496
    Top = 240
    Width = 74
    Height = 13
    Caption = '7      Wrk        0'
  end
  object Label9: TLabel
    Left = 496
    Top = 192
    Width = 74
    Height = 13
    Caption = '7      Wrk1      0'
  end
  object Label10: TLabel
    Left = 48
    Top = 184
    Width = 101
    Height = 13
    Caption = ' '#1088#1077#1075#1080#1089#1090#1088'  '#1082#1086#1084#1072#1085#1076' IR'
  end
  object Label13: TLabel
    Left = 312
    Top = 80
    Width = 112
    Height = 13
    Caption = #1055' '#1040' '#1052' '#1071' '#1058' '#1068'        RAM '
  end
  object Label14: TLabel
    Left = 376
    Top = 192
    Width = 82
    Height = 13
    Caption = '7         B            0'
  end
  object Label16: TLabel
    Left = 592
    Top = 144
    Width = 77
    Height = 13
    Caption = '15  DPH. DPL 0'
  end
  object Label17: TLabel
    Left = 256
    Top = 152
    Width = 31
    Height = 13
    Caption = 'R0-R7'
  end
  object Label18: TLabel
    Left = 376
    Top = 288
    Width = 82
    Height = 13
    Caption = 'C,ac,F0,rs,ov,0,P'
  end
  object Label19: TLabel
    Left = 344
    Top = 304
    Width = 25
    Height = 13
    Caption = 'PSW'
  end
  object Label20: TLabel
    Left = 256
    Top = 200
    Width = 28
    Height = 13
    Caption = 'Stack'
  end
  object Label21: TLabel
    Left = 48
    Top = 160
    Width = 131
    Height = 13
    Caption = #1041' '#1051' '#1054' '#1050'   '#1091#1087#1088#1072#1074#1083#1077#1085#1080#1103' (CU)'
  end
  object Label22: TLabel
    Left = 160
    Top = 248
    Width = 66
    Height = 13
    Caption = #1082#1086#1076#1080#1088#1086#1074#1072#1085#1080#1077
  end
  object Label23: TLabel
    Left = 32
    Top = 112
    Width = 14
    Height = 13
    Caption = 'PC'
  end
  object Label24: TLabel
    Left = 552
    Top = 168
    Width = 30
    Height = 13
    Caption = 'DPTR'
  end
  object Label2: TLabel
    Left = 48
    Top = 48
    Width = 148
    Height = 13
    Caption = #1087#1088#1086#1075#1088#1072#1084#1084#1085#1072#1103' '#1087#1072#1084#1103#1090#1100'  CODE '
  end
  object Label1: TLabel
    Left = 160
    Top = 240
    Width = 55
    Height = 13
    Caption = #1088#1072#1079#1088#1077#1096#1080#1090#1100
  end
  object Label26: TLabel
    Left = 696
    Top = 264
    Width = 13
    Height = 13
    Caption = 'P3'
  end
  object Label27: TLabel
    Left = 600
    Top = 328
    Width = 97
    Height = 13
    Caption = #1084#1072#1089#1082#1080' '#1087#1088#1077#1088#1099#1074#1072#1085#1080#1081
  end
  object Label28: TLabel
    Left = 584
    Top = 344
    Width = 3
    Height = 13
  end
  object Label25: TLabel
    Left = 608
    Top = 360
    Width = 78
    Height = 13
    Caption = 'EX1    EX0    EA'
  end
  object Label29: TLabel
    Left = 600
    Top = 304
    Width = 66
    Height = 13
    Caption = 'INT1      INT0'
  end
  object ProgCnt: TEdit
    Left = 56
    Top = 112
    Width = 89
    Height = 21
    TabOrder = 0
  end
  object Button1: TButton
    Left = 160
    Top = 112
    Width = 49
    Height = 25
    Caption = 'C'#1073#1088#1086#1089
    TabOrder = 1
    OnClick = Button1Click
  end
  object Edit6: TEdit
    Left = 376
    Top = 208
    Width = 81
    Height = 21
    TabOrder = 2
  end
  object Work: TEdit
    Left = 496
    Top = 256
    Width = 73
    Height = 21
    TabOrder = 3
  end
  object Work1: TEdit
    Left = 496
    Top = 208
    Width = 73
    Height = 21
    TabOrder = 4
  end
  object Instr: TEdit
    Left = 56
    Top = 200
    Width = 97
    Height = 21
    TabOrder = 5
  end
  object Button2: TButton
    Left = 160
    Top = 200
    Width = 65
    Height = 25
    Caption = ' '#1042#1099#1087#1086#1083#1085#1080#1090#1100
    TabOrder = 6
    OnClick = Button2Click
  end
  object Acu: TEdit
    Left = 376
    Top = 168
    Width = 81
    Height = 21
    TabOrder = 7
  end
  object Edit15: TEdit
    Left = 592
    Top = 160
    Width = 81
    Height = 21
    TabOrder = 8
  end
  object ComboBox2: TComboBox
    Left = 256
    Top = 168
    Width = 73
    Height = 21
    ItemHeight = 13
    TabOrder = 9
    Items.Strings = (
      'R0'
      'R1'
      'R2'
      'R3'
      'R4'
      'R5'
      'R6'
      'R7')
  end
  object CheckBox1: TCheckBox
    Left = 136
    Top = 232
    Width = 17
    Height = 25
    Caption = 'CheckBox1'
    TabOrder = 10
    OnClick = CheckBox1Click
  end
  object ComboBox3: TComboBox
    Left = 592
    Top = 112
    Width = 97
    Height = 21
    ItemHeight = 13
    TabOrder = 11
  end
  object ComboBox4: TComboBox
    Left = 376
    Top = 128
    Width = 89
    Height = 21
    ItemHeight = 13
    TabOrder = 12
  end
  object ComboBox5: TComboBox
    Left = 256
    Top = 128
    Width = 73
    Height = 21
    ItemHeight = 13
    TabOrder = 13
  end
  object Edit1: TEdit
    Left = 376
    Top = 304
    Width = 81
    Height = 21
    TabOrder = 14
  end
  object Button7: TButton
    Left = 56
    Top = 352
    Width = 129
    Height = 25
    Caption = #1057#1086#1079#1076#1072#1090#1100' '#1092#1072#1081#1083#1099'  MaxPlus'
    TabOrder = 15
    OnClick = Button7Click
  end
  object Edit2: TEdit
    Left = 592
    Top = 256
    Width = 89
    Height = 21
    TabOrder = 16
  end
  object Button3: TButton
    Left = 608
    Top = 280
    Width = 17
    Height = 17
    Caption = '3'
    TabOrder = 17
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 640
    Top = 280
    Width = 17
    Height = 17
    Caption = '2'
    TabOrder = 18
    OnClick = Button4Click
  end
  object CheckBox2: TCheckBox
    Left = 608
    Top = 344
    Width = 17
    Height = 17
    Caption = 'CheckBox2'
    TabOrder = 19
    OnClick = CheckBox2Click
  end
  object CheckBox3: TCheckBox
    Left = 640
    Top = 344
    Width = 17
    Height = 17
    Caption = 'CheckBox3'
    TabOrder = 20
    OnClick = CheckBox3Click
  end
  object CheckBox4: TCheckBox
    Left = 672
    Top = 344
    Width = 17
    Height = 17
    Caption = 'CheckBox4'
    TabOrder = 21
    OnClick = CheckBox4Click
  end
  object ComboBox1: TComboBox
    Left = 56
    Top = 64
    Width = 97
    Height = 21
    ItemHeight = 13
    TabOrder = 22
  end
  object ComboBox6: TComboBox
    Left = 256
    Top = 216
    Width = 73
    Height = 21
    ItemHeight = 13
    TabOrder = 23
  end
  object OpenDialog1: TOpenDialog
    Left = 680
    Top = 24
  end
end
