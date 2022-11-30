#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <iostream>
#include "filesys.h"
#include "block.h"

using namespace std; 

class Table: public Filesys{
    public:
        Table(string diskname, int numberofblocks, int blocksize, string flatfile, string indexfile);
        int build_table(string inputfile);
        int search(string value); // calls index_search and returns block other than 0

    private: 
        int index_search(string value);
        string flatfile;
        string indexfile;
};

#endif