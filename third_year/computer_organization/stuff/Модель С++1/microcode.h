//---------------------------------------------------------------------------

#ifndef microcodeH
#define microcodeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *ProgCnt;
        TLabel *Label3;
        TButton *Button1;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *Edit6;
        TLabel *Label7;
        TEdit *Work;
        TLabel *Label8;
        TEdit *Work1;
        TLabel *Label9;
        TEdit *Instr;
        TLabel *Label10;
        TButton *Button2;
        TLabel *Label13;
        TEdit *Acu;
        TLabel *Label14;
        TEdit *Edit15;
        TLabel *Label16;
        TComboBox *ComboBox2;
        TLabel *Label17;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TCheckBox *CheckBox1;
        TLabel *Label22;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TComboBox *ComboBox5;
        TLabel *Label23;
        TLabel *Label24;
        TEdit *Edit1;
        TLabel *Label2;
        TLabel *Label1;
        TButton *Button7;
        TOpenDialog *OpenDialog1;
        TEdit *Edit2;
        TLabel *Label26;
        TButton *Button3;
        TButton *Button4;
        TLabel *Label27;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TLabel *Label28;
        TLabel *Label25;
        TLabel *Label29;
        TCheckBox *CheckBox4;
        TComboBox *ComboBox1;
        TComboBox *ComboBox6;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        //void __fastcall ComboBox1DblClick(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
       // void __fastcall Codmema1(void);
       // void __fastcall Codmema2(void);
        //void __fastcall Codmema3(void);
        //void __fastcall Codmema4(void);
        //void __fastcall Codmema5(void);
        void __fastcall MicroCodMem(char *ss);
        void __fastcall PSWC(char *simv);
        unsigned char __fastcall CodMop(char *ss,char *sss);
        //void __fastcall TakeCode(char * stpole, char * stmo);
        void __fastcall clear_mema(void);
        void __fastcall StateMCU(void);

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
