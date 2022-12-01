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
    if (getfirstblock(file) == -1){
        // getfirstblock returned -1 meaning file does not exist in the vector 
        cout << "File does not exist.\n";
        return 0;
    }

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
    if (block == -1){
        cout << "File does not exist.\n";
        return 0;
    }

    while (block != 0){ // pull data from each block until it reaches 0 EOF
        string b;
        readblock(file, block, b);
        buffer += b;
        block = nextblock(file, block); // may be a mistake here (block)
    }

    // need to print it out 
    for (int i = 0; i <= buffer.length(); i++){
        cout << buffer[i];
    }

    cout << endl; // create some space for the $

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
	int code = getfirstblock(file1);
	if (code == -1){
        cout << "Error code: A\n";
		return 0; // file 1 does not have any blocks associated with it, cannot proceed
	}

    // at this point the file2 does not exist that we want to copy to, so create one 
	if (newfile(file2) == 0){
        cout << "Error code: C\n";
		return 0;   // not enough space in the ROOT for a new file to be created, should be outputted in respective functions 
	}

    code = getfirstblock(file2);
	if (code == -1){
        cout << "Error code: B\n";
		return 0; // file 2 (exists) does not have any blocks associated with it, cannot proceed
	}

	int currBlock = getfirstblock(file1); // first block
	while (currBlock != 0){
		string b;
		getblock(currBlock, b); // shouldn't this be currBlock??????????????????????rather than 0??????????????????????????????????
		int flag = addblock(file2, b);
		if (flag == 1){
			cout << "Not enough space to copy, terminating.\n";
			del(file2);
			return 0;
		}
		currBlock = nextblock(file1, currBlock);
	}
    cout << "Successfully copied " << file1 << " to " << file2 << ".\n";
	return 1; // success 
}