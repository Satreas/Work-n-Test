//---------------------------------------------------------------------------
#include <windows.h>
#include <vcl.h>
#include <fstream.h>
#include <mmsystem.hpp>
#pragma hdrstop
#include "TheGame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "sButton"
#pragma link "acPNG"
#pragma resource "*.dfm"
TmainForm *mainForm;
//Main-Inint-----------------------------------------------------------------
__fastcall TmainForm::TmainForm(TComponent* Owner)
        : TForm(Owner)
{
        defaultMs = 3;
        P1.moveSpeed = P1.moveSpeed = defaultMs;
        P1.canDash = P2.canDash = false;
        P1.alJump = P2.alJump = true;
        P1.jDir = P2.jDir = true;
        P1.isOnGround = P2.isOnGround = true;
        P1.jSpeed = P2.jSpeed = 10;
        jTop = 0;
        sHeight = 323;
        cHeight = 160;
        floor = 238;
        GameWindows->ActivePageIndex = 0;
}


void __fastcall TmainForm::mButtonStartClick(TObject *Sender)
{
        GameWindows->ActivePageIndex = 1;
        mButtonStart->Caption = "Continue";
        mainForm->SetFocusedControl(mButtonStart);
        mButtonStart->Visible = false;
        mButtonExit->Visible = false;
}

//Menu-Buttons---------------------------------------------------------------

void __fastcall TmainForm::aMenuExecute(TObject *Sender)
{
        GameWindows->ActivePageIndex = 0;
        mButtonStart->Visible = true;
        mButtonExit->Visible = true;
}

void __fastcall TmainForm::mButtonExitClick(TObject *Sender)
{
        mainForm->Close();
}
//Controls-------------------------------------------------------------------

void __fastcall TmainForm::FormKeyPress(TObject *Sender, char &Key)
{
        //ShowMessage(IntToStr(Key));
        switch(Key)
        {
         case 'a':{                                          // A button press
                  if (dashRegP1->Enabled == true) P1.moveSpeed*=2;
                  mLeft->Enabled = true; break;
                 }
         case 'd':{                                         // D button press
                   if (dashRegP1->Enabled == true) P1.moveSpeed*=2;
                   mRight->Enabled = true; break;
                  }
         case 's':{                                         // S button press
                   Player1_img->Height=cHeight;
                  }
         case 'w':if(P1.alJump==true)                       // W button press
                   {
                    P1.jDir=true; P1.moveSpeed *= 1.5;
                    JumpH->Enabled = true; break;
                   }
        }
}

void __fastcall TmainForm::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        //ShowMessage(IntToStr(Key));
        switch(Key)
        {
         case 'A':{                                          //A button up
                  mLeft->Enabled = false; P1.moveSpeed = defaultMs;
                  dashRegP1->Enabled = true; break;
                 }
         case 'D':{                                          //D button up
                  mRight->Enabled = false; P1.moveSpeed = defaultMs;
                  dashRegP1->Enabled = true; break;
                 }
         case 'S':{                                          // S button up
                   Player1_img->Height=sHeight;
                  }
         case 'W':{P1.jDir=false; break;}                    //W button up
        }
}

//Player1-Stats--------------------------------------------------------------

void __fastcall TmainForm::JumpHTimer(TObject *Sender)
{
        P1.alJump = false;
        P1.isOnGround = false;
        if (Player1_img->Top > jTop && P1.jDir==true)
         Player1_img->Top-=P1.jSpeed;
        if (Player1_img->Top <= jTop)
         P1.jDir=false;
        if (P1.jDir == false)
         {
          Player1_img->Top+=P1.jSpeed*0.8;
          if (Player1_img->Top >= floor)
           {
            P1.alJump=true;
            P1.isOnGround=true;
            P1.moveSpeed = defaultMs;
            JumpH->Enabled = false;
           }
         }
}

void __fastcall TmainForm::mLeftTimer(TObject *Sender)
{
        Player1_img->Left-=P1.moveSpeed;
}

void __fastcall TmainForm::mRightTimer(TObject *Sender)
{
        Player1_img->Left+=P1.moveSpeed;
}

void __fastcall TmainForm::dashRegP1Timer(TObject *Sender)
{
        dashRegP1->Enabled = false;
}

//Player2-Stats--------------------------------------------------------------
