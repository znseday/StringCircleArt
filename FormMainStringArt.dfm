object frmMainStringArt: TfrmMainStringArt
  Left = 0
  Top = 0
  Caption = 'StringArt (by TsynikinSA)'
  ClientHeight = 502
  ClientWidth = 944
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnlLeft: TPanel
    Left = 0
    Top = 0
    Width = 944
    Height = 502
    Align = alClient
    TabOrder = 0
    object GaugeMain: TGauge
      Left = 18
      Top = 425
      Width = 318
      Height = 19
      ForeColor = clGreen
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Font.Quality = fqNonAntialiased
      ParentFont = False
      Progress = 0
    end
    object Label6: TLabel
      Left = 18
      Top = 452
      Width = 92
      Height = 13
      Caption = #1058#1077#1082#1091#1097#1072#1103#1103' '#1086#1096#1080#1073#1082#1072
    end
    object Label17: TLabel
      Left = 18
      Top = 476
      Width = 109
      Height = 13
      Caption = #1055#1088#1077#1076#1099#1076#1091#1097#1072#1103' '#1086#1096#1080#1073#1082#1072
    end
    object pnlImgSrc: TPanel
      Left = 12
      Top = 10
      Width = 308
      Height = 308
      BevelKind = bkSoft
      BevelOuter = bvNone
      TabOrder = 0
      object imgSrc: TImage
        Left = 0
        Top = 0
        Width = 304
        Height = 304
        Align = alClient
        ExplicitLeft = 2
        ExplicitTop = 2
        ExplicitWidth = 289
        ExplicitHeight = 263
      end
    end
    object btnGo: TButton
      Left = 14
      Top = 377
      Width = 187
      Height = 42
      Caption = #1047#1072#1087#1091#1089#1082
      Enabled = False
      TabOrder = 1
      OnClick = btnGoClick
    end
    object pnlImgArt: TPanel
      Left = 326
      Top = 10
      Width = 308
      Height = 308
      BevelKind = bkSoft
      BevelOuter = bvNone
      TabOrder = 2
      object imgArt: TImage
        Left = 0
        Top = 0
        Width = 304
        Height = 304
        Align = alClient
        ExplicitLeft = 72
        ExplicitTop = 16
        ExplicitWidth = 351
        ExplicitHeight = 351
      end
    end
    object GroupBox1: TGroupBox
      Left = 342
      Top = 324
      Width = 593
      Height = 161
      Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080
      TabOrder = 3
      object Label1: TLabel
        Left = 12
        Top = 80
        Width = 79
        Height = 13
        Caption = #1050#1086#1083'-'#1074#1086' '#1075#1074#1086#1079#1076#1077#1081
      end
      object Label2: TLabel
        Left = 12
        Top = 107
        Width = 80
        Height = 13
        Caption = #1069#1092#1092' '#1088#1072#1076#1080#1091#1089', %'
      end
      object Label3: TLabel
        Left = 12
        Top = 134
        Width = 75
        Height = 13
        Caption = #1071#1088#1082#1086#1089#1090#1100' '#1083#1080#1085#1080#1080
      end
      object Label4: TLabel
        Left = 220
        Top = 24
        Width = 58
        Height = 13
        Caption = #1052#1072#1082#1089' '#1085#1080#1090#1077#1081
      end
      object Label5: TLabel
        Left = 345
        Top = 24
        Width = 83
        Height = 13
        Caption = #1052#1072#1082#1089' '#1074#1088#1077#1084#1103', '#1084#1080#1085
      end
      object Label7: TLabel
        Left = 179
        Top = 53
        Width = 115
        Height = 13
        Caption = #1056#1077#1072#1083#1100#1085#1099#1081' '#1076#1080#1072#1084#1077#1090#1088', '#1084#1084
      end
      object Label8: TLabel
        Left = 12
        Top = 24
        Width = 70
        Height = 13
        Caption = #1064#1080#1088#1080#1085#1072', '#1087#1080#1082#1089
      end
      object Label9: TLabel
        Left = 12
        Top = 53
        Width = 67
        Height = 13
        Caption = #1042#1099#1089#1086#1090#1072', '#1087#1080#1082#1089
      end
      object Label10: TLabel
        Left = 179
        Top = 80
        Width = 112
        Height = 13
        Caption = #1050#1086#1101#1092#1092' '#1088#1072#1076' '#1079#1072#1090#1077#1085#1077#1085#1080#1103
      end
      object Label11: TLabel
        Left = 180
        Top = 107
        Width = 114
        Height = 13
        Caption = #1058#1086#1083#1097#1080#1085#1072' '#1075#1074#1086#1079#1076#1080#1082#1072', '#1084#1084
      end
      object Label12: TLabel
        Left = 287
        Top = 137
        Width = 73
        Height = 13
        Caption = #1059#1089#1080#1083#1077#1085#1080#1103' '#1074' 3D'
      end
      object Label13: TLabel
        Left = 408
        Top = 137
        Width = 45
        Height = 13
        Caption = #1058#1086#1083#1097#1080#1085#1072
      end
      object Label14: TLabel
        Left = 356
        Top = 53
        Width = 72
        Height = 13
        Caption = 'kConstDimming'
      end
      object Label15: TLabel
        Left = 180
        Top = 134
        Width = 19
        Height = 13
        Caption = #1044#1091#1075
      end
      object Label16: TLabel
        Left = 423
        Top = 110
        Width = 21
        Height = 13
        Caption = #1064#1072#1075
      end
      object EditNailsCount: TEdit
        Left = 98
        Top = 77
        Width = 65
        Height = 21
        NumbersOnly = True
        TabOrder = 0
        Text = '256'
      end
      object EditReff: TEdit
        Left = 98
        Top = 104
        Width = 65
        Height = 21
        TabOrder = 1
        Text = '95'
        OnKeyPress = EditReffKeyPress
      end
      object EditColorVal: TEdit
        Left = 98
        Top = 131
        Width = 65
        Height = 21
        TabOrder = 2
        Text = '0,04'
        OnKeyPress = EditColorValKeyPress
      end
      object EditMaxStrings: TEdit
        Left = 284
        Top = 21
        Width = 39
        Height = 21
        NumbersOnly = True
        TabOrder = 3
        Text = '10000'
      end
      object EditMaxTime: TEdit
        Left = 434
        Top = 21
        Width = 45
        Height = 21
        TabOrder = 4
        Text = '480'
        OnKeyPress = EditMaxTimeKeyPress
      end
      object EditRealD: TEdit
        Left = 300
        Top = 50
        Width = 49
        Height = 21
        NumbersOnly = True
        TabOrder = 5
        Text = '415'
      end
      object EditWidth: TEdit
        Left = 98
        Top = 21
        Width = 65
        Height = 21
        NumbersOnly = True
        TabOrder = 6
        Text = '280'
      end
      object EditHeight: TEdit
        Left = 98
        Top = 50
        Width = 65
        Height = 21
        NumbersOnly = True
        TabOrder = 7
        Text = '280'
      end
      object chbAutoWidth: TCheckBox
        Left = 170
        Top = 23
        Width = 47
        Height = 17
        Caption = 'Auto'
        TabOrder = 8
      end
      object EditRadCoeff: TEdit
        Left = 300
        Top = 77
        Width = 49
        Height = 21
        TabOrder = 9
        Text = '0,00245'
        OnKeyPress = EditRadCoeffKeyPress
      end
      object GroupBox2: TGroupBox
        Left = 485
        Top = 7
        Width = 105
        Height = 68
        Caption = #1052#1086#1076#1077#1083#1100' '#1103#1088#1082#1086#1089#1090#1080
        TabOrder = 10
        object rbL: TRadioButton
          Left = 16
          Top = 19
          Width = 34
          Height = 17
          Caption = 'L'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object rbI: TRadioButton
          Left = 56
          Top = 19
          Width = 113
          Height = 17
          Caption = 'I'
          TabOrder = 1
        end
        object rbY: TRadioButton
          Left = 16
          Top = 42
          Width = 25
          Height = 17
          Caption = 'Y'
          TabOrder = 2
        end
        object rbV: TRadioButton
          Left = 56
          Top = 42
          Width = 113
          Height = 17
          Caption = 'V'
          TabOrder = 3
        end
      end
      object EditNailWidth: TEdit
        Left = 300
        Top = 104
        Width = 49
        Height = 21
        TabOrder = 11
        Text = '2'
        OnKeyPress = EditNailWidthKeyPress
      end
      object GroupBox3: TGroupBox
        Left = 485
        Top = 76
        Width = 103
        Height = 54
        Caption = #1060#1091#1085#1082#1094#1080#1103' '#1086#1096#1080#1073#1082#1080
        TabOrder = 12
        object rbErrorFunc_df2: TRadioButton
          Left = 11
          Top = 20
          Width = 70
          Height = 17
          Caption = 'df2'
          Checked = True
          TabOrder = 0
          TabStop = True
        end
        object rbErrorFunc_df4: TRadioButton
          Left = 51
          Top = 20
          Width = 70
          Height = 17
          Caption = 'df4'
          TabOrder = 1
        end
      end
      object EditCoeffGainIn3D: TEdit
        Left = 366
        Top = 134
        Width = 36
        Height = 21
        TabOrder = 13
        Text = '5'
        OnKeyPress = EditCoeffGainIn3DKeyPress
      end
      object EditLineWidthIn3D: TEdit
        Left = 456
        Top = 134
        Width = 28
        Height = 21
        TabOrder = 14
        Text = '1'
        OnKeyPress = EditLineWidthIn3DKeyPress
      end
      object chbIsRadDimming: TCheckBox
        Left = 356
        Top = 79
        Width = 41
        Height = 17
        Caption = #1042#1082#1083
        Checked = True
        State = cbChecked
        TabOrder = 15
      end
      object Edit_kConstDimming: TEdit
        Left = 434
        Top = 50
        Width = 31
        Height = 21
        TabOrder = 16
        Text = '1'
        OnKeyPress = Edit_kConstDimmingKeyPress
      end
      object chbArcs: TCheckBox
        Left = 405
        Top = 75
        Width = 73
        Height = 17
        Caption = #1057' '#1076#1091#1075#1072#1084#1080
        TabOrder = 17
      end
      object EditArcsCount: TEdit
        Left = 205
        Top = 131
        Width = 45
        Height = 21
        NumbersOnly = True
        TabOrder = 18
        Text = '63'
      end
      object chbNotIdealIn3D: TCheckBox
        Left = 492
        Top = 136
        Width = 98
        Height = 17
        Caption = #1053#1077#1080#1076#1077#1072#1083#1100#1085#1086#1089#1090#1100
        Checked = True
        State = cbChecked
        TabOrder = 19
      end
      object Edit_dArcs: TEdit
        Left = 448
        Top = 107
        Width = 35
        Height = 21
        NumbersOnly = True
        TabOrder = 20
        Text = '1'
      end
      object chbOnlyClockwise: TCheckBox
        Left = 405
        Top = 90
        Width = 73
        Height = 17
        Caption = #1055#1086' '#1095#1072#1089#1086#1074#1086#1081
        TabOrder = 21
      end
    end
    object Memo: TMemo
      Left = 640
      Top = 10
      Width = 295
      Height = 308
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 4
    end
    object EditCurErr: TEdit
      Left = 133
      Top = 449
      Width = 68
      Height = 21
      ReadOnly = True
      TabOrder = 5
      Text = '0'
    end
    object btnGoTo3D: TButton
      Left = 207
      Top = 396
      Width = 129
      Height = 23
      Caption = #1055#1086#1082#1072#1079#1072#1090#1100' '#1074' 3D'
      TabOrder = 6
      OnClick = btnGoTo3DClick
    end
    object btnOpen: TButton
      Left = 14
      Top = 330
      Width = 322
      Height = 41
      Action = ActionFileOpen
      TabOrder = 7
    end
    object btnTest: TButton
      Left = 248
      Top = 471
      Width = 88
      Height = 25
      Caption = 'Test'
      TabOrder = 8
      Visible = False
      OnClick = btnTestClick
    end
    object EditLastErr: TEdit
      Left = 133
      Top = 473
      Width = 68
      Height = 21
      ReadOnly = True
      TabOrder = 9
      Text = '0'
    end
    object chbMiniArcs: TCheckBox
      Left = 208
      Top = 378
      Width = 97
      Height = 17
      Caption = #1052#1080#1085#1080' '#1093#1086#1088#1076#1099
      Checked = True
      State = cbChecked
      TabOrder = 10
    end
    object chbCrisConst: TCheckBox
      Left = 207
      Top = 452
      Width = 61
      Height = 17
      Caption = 'CrisConst'
      TabOrder = 11
    end
    object pnlColorBG: TPanel
      Left = 274
      Top = 451
      Width = 62
      Height = 17
      Color = clWhite
      ParentBackground = False
      TabOrder = 12
      OnClick = pnlColorBGClick
    end
  end
  object ActionList: TActionList
    Left = 520
    Top = 48
    object ActionFileOpen: TAction
      Caption = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083
      ShortCut = 16463
      OnExecute = ActionFileOpenExecute
    end
    object ActionHelpAbout: TAction
      Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
    end
    object ActionModelDefPos: TAction
      Caption = #1057#1090#1072#1088#1090#1086#1074#1072#1103' '#1087#1086#1079#1080#1094#1080#1103
    end
    object ActionModelReDraw: TAction
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100'/'#1087#1077#1088#1077#1088#1080#1089#1086#1074#1072#1090#1100' 3d'
      OnExecute = ActionModelReDrawExecute
    end
  end
  object dlgOpen: TOpenPictureDialog
    Filter = 
      'All (*.png;*.jpg;*.jpeg;*.bmp)|*.png;*.jpg;*.jpeg;*.bmp|Portable' +
      ' Network Graphics (*.png)|*.png|JPEG Image File (*.jpg)|*.jpg|JP' +
      'EG Image File (*.jpeg)|*.jpeg|Bitmaps (*.bmp)|*.bmp'
    Options = [ofReadOnly, ofOverwritePrompt, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 464
    Top = 48
  end
  object ColorDialog: TColorDialog
    Options = [cdFullOpen]
    Left = 518
    Top = 122
  end
end
