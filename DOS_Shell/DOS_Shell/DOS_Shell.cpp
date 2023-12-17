#include <iostream>
#include <string>
#include "Shell.h"

using namespace std;

int main()
{
    system("cls");
    bool running = true;
    Shell* newDosShell = new Shell();
    newDosShell->PrintAuthorInfo();
    string command;
    while (running)
    {
        command = "";
        newDosShell->DisplayCurrentPath();
        getline(cin,command);

        newDosShell->ExecuteCommand(command);

        
    }
}