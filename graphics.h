#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

//@Code By: Jesus Jose Navarrete Baca OMI 2013 (ID = 654173AF PARRAL)
//@ENTREGA 7405 DPTO 10

#include <windows.h>
#include <iostream>

using namespace std;

void printWait(const char * ,int);

char hline = 205, vline = 186, topr = 187, downr = 188, downl = 200, topl = 201;
void printLine(int);
void printLine();
void setCursor(int,int);
int getRow();
int getColumn();
int getRowT();
int getColumnT();
void square_Logon();


void tileLogon(){
    printLine(2);
    cout<<endl;
    setCursor(getRow(),getColumnT()/2-15);
    cout<<"SIMULADOR DE CONTROL ATM BASICO"<<endl<<endl;
    printLine(2);
    setCursor(getRowT()-8,0);
    printLine(2);
    cout<<endl;
    setCursor(getRow(),getColumnT()/2-15);
    cout<<"SIMULADOR DE CONTROL ATM BASICO"<<endl<<endl;
    printLine(2);
    square_Logon();
}
void square_Logon(){
    setCursor(getRowT()/2-6,getColumnT()/2-30);
    cout<<topl;
    for(int x=0; x<60; ++x){
        cout<<hline;
    }
    cout<<topr;
    setCursor(getRowT()/2+6,getColumnT()/2-30);
    cout<<downl;
    for(int x=0; x<60; ++x){
        cout<<hline;
    }
    cout<<downr;
    setCursor(getRowT()/2-5,getColumnT()/2-30);
    for(int x=0; x<11; ++x){
        cout<<vline<<endl;
        setCursor(getRow(),getColumnT()/2-30);
    }
    setCursor(getRowT()/2-5,getColumnT()/2+31);
    for(int x=0; x<11; ++x){
        cout<<vline<<endl;
        setCursor(getRow(),getColumnT()/2+31);
    }
    setCursor(getRowT()/2-4,getColumnT()/2-25);
}

void setCursor( int row, int column){
  COORD mycoord;
  mycoord.X = column;
  mycoord.Y = row;
  SetConsoleCursorPosition(
    GetStdHandle( STD_OUTPUT_HANDLE ),mycoord);
  }

int getColumn(){
  CONSOLE_SCREEN_BUFFER_INFO controlbase;

  if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&controlbase))
    return -1;
  return controlbase.dwCursorPosition.X;
  }

int getRow(){
  CONSOLE_SCREEN_BUFFER_INFO controlbase;
  if (!GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&controlbase))
    return -1;
  return controlbase.dwCursorPosition.Y;
  }

void defineBackgroundColor(void){
   system("color 1F");
   SetConsoleTitle("ATM @CheCheSwap");
}

  int getRowT(void){
   CONSOLE_SCREEN_BUFFER_INFO driver;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &driver);
   return driver.srWindow.Bottom - driver.srWindow.Top + 1;
  }

  int getColumnT(void){
    CONSOLE_SCREEN_BUFFER_INFO driver;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&driver);
    return driver.srWindow.Right-driver.srWindow.Left+1;
  }

void printLine(){
    for(int x=0; x<getColumnT(); ++x){
        cout<<hline;
    }
}
void printLine(int n){
    for(int x=0; x<n; ++x){
        for(int y=0; y<getColumnT(); ++y){
            cout<<hline;
        }
    }
}
void init_sheet_WNDPROC(){

    defineBackgroundColor();
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0);

    /*HWND console = GetConsoleWindow(); //Alternative With CBAR
    ShowWindow(console,SW_MAXIMIZE);
    */
}

#endif // GRAPHICS_H_INCLUDED
