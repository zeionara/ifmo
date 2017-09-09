//---------------------------------------------------------------------------

#ifndef modelirH
#define modelirH
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
        TLabel *Label6;
        TLabel *Label7;
        TEdit *Work;
        TLabel *Label8;
        TEdit *Instr;
        TLabel *Label10;
        TButton *Button2;
        TEdit *Acu;
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
        TLabel *Label23;
        TLabel *Label24;
        TEdit *Edit1;
        TLabel *Label1;
        TButton *Button7;
        TOpenDialog *OpenDialog1;
        TEdit *Edit2;
        TLabel *Port3;
        TButton *Button3;
        TButton *Button4;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TLabel *Label28;
        TLabel *Label25;
        TLabel *Label29;
        TCheckBox *CheckBox4;
        TComboBox *ComboBox6;
        TEdit *Edit7;
        TEdit *Edit6;
        TLabel *Label12;
        TEdit *Edit9;
        TLabel *Label14;
        TLabel *Label30;
        TLabel *Label5;
        TLabel *Label9;
        TLabel *Label27;
        TEdit *Edit8;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TButton *Button10;
        TCheckBox *CheckBox7;
        TLabel *Label2;
        TButton *Button13;
        TEdit *Edit3;
        TEdit *Edit4;
        TCheckBox *CheckBox8;
        TLabel *Label11;
        TCheckBox *CheckBox9;
        TLabel *Label15;
        TLabel *Label31;
        TLabel *Label13;
        TLabel *Label32;
        TEdit *Edit5;
        TEdit *Edit11;
        TLabel *Port0;
        TEdit *Edit10;
        TLabel *Port1;
        TLabel *Port2;
        TButton *Button5;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        //void __fastcall ComboBox1DblClick(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall CheckBox4Click(TObject *Sender);
        void __fastcall Edit7DblClick(TObject *Sender);
        void __fastcall Edit6DblClick(TObject *Sender);
        void __fastcall Edit9DblClick(TObject *Sender);
        void __fastcall Button10Click(TObject *Sender);
        void __fastcall Button13Click(TObject *Sender);
        void __fastcall Edit2DblClick(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
private:	// User declarations

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void __fastcall MicroCodMem(char *ss);
        void __fastcall PSWC(char *simv);
        unsigned char __fastcall CodMop(char *ss,char *sss);
        void __fastcall clear_mema(void);
        void __fastcall StateMCU(void);
        void __fastcall Reg(char i);
        void __fastcall Stack(int i);
        void __fastcall bitreg(unsigned char var);
        void  __fastcall TakeCode(char *stpole,char *stmo);
        char __fastcall adress(char *ss);
        void __fastcall GoToInt(void);
        void __fastcall ClearInt(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
