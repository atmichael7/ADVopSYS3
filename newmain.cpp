#include <iostream>
#include <string>
#include <stdio.h>
//#include "block.cpp"
#include "sdisk.cpp"
#include "filesys.cpp"
#include "shell.cpp"
#include "table.cpp"

using namespace std;





int main()
{
    string s, command = "go", op1, op2;
    Sdisk disk1("disk1",256,128);
    Filesys fsys("disk1",256,128);
    Shell shell("disk1", 256, 128);
    Table table("disk1", 256, 128, "flat1", "index1");


while (command != "quit")
     {
       command.clear();
       op1.clear();
       op2.clear();
       cout << "$";
       getline(cin,s);
       int firstblank=s.find(' ');
       if (firstblank < s.length()) s[firstblank]='#';
       int secondblank=s.find(' ');
       command=s.substr(0,firstblank);
       if (firstblank < s.length())
         op1=s.substr(firstblank+1,secondblank-firstblank-1);
       if (secondblank < s.length())
         op2=s.substr(secondblank+1);
       if (command=="dir")
          {
            // use the ls function
            shell.dir();
           }
       if (command=="add")
          {
            // The variable op1 is the new file and op2 is the file data
            shell.add(op1, op2);
           }
       if (command=="del")
          {
            // The variable op1 is the file
            shell.del(op1);
           }
       if (command=="type")
          {
            // The variable op1 is the file
            shell.type(op1);
        
           }
       if (command=="copy")
          {
            // The variable op1 is the source file and the variable op2 is the destination file.
            shell.copy(op1, op2);
           }
       if (command=="search")
          {
            // This is the command for Project 4
            // The variable op1 is the date
            //shell.search(op1);
            table.search(op1);
           }
      }

    return 0;
}