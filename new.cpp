
#include <stdio.h>
#include <iostream>
using namespace std;


int Table::indexsearch(string value){
    // read in the entire index file and put into buffer
    string buffer;
    int block = getfirstblock(indexfile);

    while (block != 0){
        // read block in
        string b;
        int error = readblock(indexfile, block, b);
        buffer += b;
        block = nextblock(indexfile, block);
    }

    istringstream instream;
    string s; 
    int b;
    instream.str(buffer);
    instream >> s >> b;

    while (s != "88888"){
        // means have an index record 
        if (s == value){
            return b;
        }
        instream >> s >> b;
    }
    // haven't found record so return 0
    return 0; 
}









int search(string value){
    int block = indexsearch(value);
    if (block == 0){
        // record not found
        cout << "Record not found!/n";
        return 0;
    }
    else{
        // did find the desired record 
        // so get the record
        string buffer;
        int error = readblock(flatfile, block, buffer){
            cout << buffer;
        }
    }
    return 1;
}