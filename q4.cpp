#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;
string working_directory = "Files";
string path = "Files";

#ifdef _linux_ 
#include <unistd.h>
    void MyMkDir(const char* path){
		mkdir(path, 0666);
	}
#elif _WIN32
#include <direct.h>
    void MyMkDir(const char* path) {
        _mkdir(path);
    }
#else

#endif


void WriteToFile(experimental::filesystem::path path)
{
    ofstream myFile_Handler;
    // File Open
    myFile_Handler.open(path.c_str());
    
    myFile_Handler << "Hello from argument3" << endl;

    // File Close
    myFile_Handler.close();
}

void ReadFromFile(experimental::filesystem::path path)
{
    ifstream myFile_Handler;
    string myLine;

    myFile_Handler.open(path.c_str());
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

void create_dir(std::experimental::filesystem::path dir_path)
{
    if(false == std::experimental::filesystem::is_directory(dir_path)){
    	if(false == std::experimental::filesystem::create_directory(dir_path))
		cout << "directory creation failed" << endl;
//		exit(1);
    }
}

int main(int argc, char** argv)
{
    if (argc < 2){
    	printf("missing argument\r\n");
	    exit(1);
    }
    experimental::filesystem::path working_dir = experimental::filesystem::current_path();
    working_dir /= working_directory;
    
    create_dir(working_dir);
    
    experimental::filesystem::path path = working_dir;
    path /= "argument2.txt";
    if(!strcmp("create", argv[1]))
    {
	    WriteToFile(path);
    }
    if(!strcmp("read", argv[1]))
    {
    	ReadFromFile(path);
    }
    
    std::cout << "Press enter to exit" << std::endl;
    
    return 0;
}