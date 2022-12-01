
#include <stdio.h>
#include <iostream>
#include "table.h"
using namespace std;

Table::Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile):Filesys(diskname, numberofblocks, blocksize){
    this->flatfile = flatfile;
    this->indexfile = indexfile;
}


int Table::build_table(string inputfile){
    // build the flatfile and the index file 
    newfile(indexfile);
    newfile(flatfile);
    ifstream infile; 
    infile.open(inputfile.c_str());
    ostringstream outstream; 
    string rec;
    getline(infile, rec);

    while (infile.good()){
        string date = rec.substr(0, 5);
        vector<string> blocks = block(rec, getblocksize());
        int b = addblock(flatfile, blocks[0]);
        outstream << date << " " << b << " ";
        getline(infile, rec);
    } // process each line in the infile 
    outstream << "88888" << " ";

    string buffer = outstream.str();
    vector<string> blocks = block(buffer, getblocksize());

    for (int i = 0; i < blocks.size(); i++){
        addblock(indexfile, blocks[i]);
    }

    return 1;
}

int Table::search(string value){
    int block = index_search(value);
    if (block == 0){
        // record not found
        cout << "Record not found!/n";
        return 0;
    }
    else{
        // did find the desired record 
        // so get the record
        string buffer;
        int error = readblock(flatfile, block, buffer);
        cout << buffer << endl;
    }
    return 1;
}

//######################################################################
//#####                                                            #####
//#####     PRIVATE FUNCTIONS FOR TABLE CLASS                      #####
//#####                                                            #####
//######################################################################

int Table::index_search(string value){
    // read in the entire index file and put into buffer
    string buffer;
    int block = getfirstblock(indexfile);

    // check if there are things associated with the firstblock of indexfile
    // if there isn't then need to build tables
    if (block == -1){
        cout << "Table not built, building table from data.txt\n";
        build_table("data.txt");
        cout << "Table built, now try searching again.\n";
        return 1;
    }

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