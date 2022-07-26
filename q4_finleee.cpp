#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <direct.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

void WriteToFile()
{
    ofstream myFile_Handler;

    // File Open
    myFile_Handler.open("argument2.txt");
    myFile_Handler << "Hello  from *argument3*" << endl;

    // File Close
    myFile_Handler.close();
}
void ReadFromFile()
{
    ifstream myFile_Handler;
    string myLine;

    myFile_Handler.open("argument2.txt");
    if (myFile_Handler.is_open())
    {
        // Keep reading the file
        while (getline(myFile_Handler, myLine))
        {
            // print the line on the standard output
            cout << myLine << endl;
        }
        // File Close
        myFile_Handler.close();
    }
    else
    {
        cout << "Unable to open the file!";
    }
}
void create_dir()
{
    if (_mkdir("Files") == -1)
        cout << "directory not opened" << endl;

    else
        cout << "Directory created";
}
int main(int argc, char** argv)
{
    create_dir();
    if (_chdir("Files") == -1)
        cout << "directory not changed" << endl;

    else
        cout << "Directory entered";
    WriteToFile();
    ReadFromFile();
    
	std::cout << "Press enter to exit" << std::endl;
	
    return 0;
}