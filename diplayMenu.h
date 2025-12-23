#ifndef MENU_H
#define MENU_H
#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
using std::cout;

void SetStdinEcho(bool enable = true)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );

#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}
void adminMenu()
{
    cout<<"Admin Menu\n";
    cout<<"1: Create New Elf\n";
    cout<<"2: Change exisiting elf password if nedded\n";
    cout<<"3: Disable elf Account\n";
    cout<<"4: See Raports\n";
    cout<<"5: Exit\n";
}
void elfMenu()
{
    cout << "Elf Menu\n";
    cout << "1. Assign Gift\n";              
    cout << "2. List Children with Gifts\n";
    cout << "3. Search Child\n";
    cout << "4. Search Gift\n";
    cout << "5. Remove Gift\n";
    cout << "6. Reports\n";
    cout << "0. Exit\n";

}

#endif