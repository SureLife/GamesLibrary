#include "mainwindow.h"
#include <windows.h>
#include <iostream>
#include "ui_mainwindow.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

LPWSTR launchGame(LPWSTR gameSelected) {
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;
    DWORD dwThreadId = 0;
    ZeroMemory( &si, sizeof(si) );
    ZeroMemory( &pi, sizeof(pi) );
    BOOL bCreateProcess = NULL;
    bCreateProcess =CreateProcess(
                gameSelected,
                NULL,
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi);
    if(bCreateProcess == FALSE) {
        cout<<"Create Process Failed & Error No - "<<GetLastError()<<endl;
    }
    cout<<"Create Process Success"<<endl;
    cout<<"Process ID - "<<pi.dwProcessId<<endl;
    cout<<"Thread ID - "<<pi.dwThreadId<<endl;
    cout<<"GetProcessID - "<<(GetProcessId(pi.hProcess))<<endl;
    cout<<"GetThreadID - "<<(GetThreadId(pi.hThread))<<endl;

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

}

void MainWindow::on_pushButton_clicked()
{
    char text[] = "C:\\Users\\GamesLibrary\\Documents\\CollapsingWorlds\\CollapsingWorlds.exe";
    wchar_t wtext[150];
    mbstowcs(wtext, text, strlen(text)+1);
    LPWSTR game = wtext;
    label.raise();
    launchGame(game);
}

void MainWindow::on_pushButton_2_clicked()
{
    char text[] = "C:\\Users\\GamesLibrary\\Documents\\BlasteroidFinal\\BlasteroidCommand.exe";
    wchar_t wtext[150];
    mbstowcs(wtext, text, strlen(text)+1);
    LPWSTR game = wtext;

    launchGame(game);
}
