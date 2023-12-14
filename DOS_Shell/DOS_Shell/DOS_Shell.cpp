#include <iostream>
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
        cin >> command;

        newDosShell->ExecuteCommand(command);


    }
}