#include "shell.h"
#include "filesys.h"
#include "block.h"

Shell::Shell(string diskname, int numberofblocks, int blocksize):Filesys(diskname, numberofblocks, blocksize){
    
}

int Shell::add(string file, string buffer){ // adds new file using buffer as data
    int code = newfile(file);

    if (code == 1){
        vector<string> blocks = block(buffer, getblocksize());
        for (int i = 0; i < blocks.size(); i++){
            code = addblock(file, blocks[i]);
        }
        return 1; // success 
    }

    return 0; // failed to create new file
}


int Shell::del(string file){
    while (getfirstblock(file) != 0){
        delblock(file, getfirstblock(file));
    }
    // now that data is deleted in the file, need to clear the filename of it 
    rmfile(file);
    return 1;
}


// retrieve a files information
int Shell::type(string file){
    string buffer;
    int block = getfirstblock(file);
    while (block != 0){
        string b;
        readblock(file, block, b);
        buffer += b;
        block = nextblock(file, block); // may be a mistake here (block)
    }

    // need to print it out 
    for (int i = 0; i <= buffer.length(); i++){
        cout << buffer[i];
    }

    cout << endl;

    return 1;
}




int Shell::dir(){
    vector<string> flist = ls();
    for (int i = 0; i < flist.size(); i++){
        cout << flist[i] << endl;
    }
    return 1;
}


int Shell::copy(string file1, string file2){
    // check if files exist 

    // then copy the contents of the first file into buffer 

    // write the buffer out to the second file 

    return 1;
}