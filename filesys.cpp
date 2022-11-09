#include "filesys.h"
//#include "sdisk.h"
#include "sdisk.h"


Filesys::Filesys(string diskname, int numberofblocks, int blocksize):Sdisk(diskname, numberofblocks, blocksize){
  // need to set the root size then set the fat size

  // check if there is a file system on the disk already
  string buffer;
  getblock(1, buffer);
  if (buffer[0] == '#'){ // means the disk is not formatted
    buildfs();
    fssynch();
  }
  else{ // disk has been formatted already so read it in
    readfs();
  }
}

// might need to change the string block input to buffer since thats what he did in the notes
int Filesys::addblock(string file, string buffer){
  int allocate = fat[0];
  if (allocate <= 0){
    cout << "No space on disk!";
    return 0;
  }

  int blockid = getfirstblock(file);
  if (blockid == 0){
    // update the root
    for (int i = 0; i < filename.size(); i++){
      firstblock[i] = allocate;
      break;
    }
  }
  else{
    // update fat... find the end of file
    while (fat[blockid] != 0){
      blockid = fat[blockid];
    }
    // fat[blockid] = 0;
    fat[blockid] = allocate;
  }
  fat[0] = fat[fat[0]];
  fat[allocate] = 0;
  fssynch();

  putblock(allocate, buffer);

  return allocate;
}

//##############################################################################

int Filesys::delblock(string file, int blocknumber){
  bool flag = fbcheck(file, blocknumber);
  if (!flag)
    return 0;
  int b = getfirstblock(file);
  if (b == blocknumber){
    for (int i = 0; i <= filename.size(); i++){
      if (filename[i] == file){
        firstblock[i] = fat[firstblock[i]];
        break;
      }
    }
  }
  else{
    while (fat[b] != blocknumber){
      b = fat[b];
    }
    fat[b] = fat[blocknumber];
    fat[blocknumber] = fat[0];
    fat[0] = blocknumber;
    return 1;
  }
  return 0; // JUST ADDED
}

//##############################################################################

int Filesys::nextblock(string file, int blocknumber){
  if (fbcheck(file, blocknumber))
    return fat[blocknumber];

  else
    return -1;
}

//##############################################################################

int Filesys::readblock(string file, int blocknumber, string& buffer){
  if (fbcheck(file, blocknumber)){
    getblock(blocknumber, buffer);
    return 1;
  }
  return 0;
}

//##############################################################################

int Filesys::writeblock(string file, int blocknumber, string buffer){
  if (fbcheck(file, blocknumber)){
    putblock(blocknumber, buffer);
    return 1;
  }
  return 0;
}

//##############################################################################    14 14

bool Filesys::fbcheck(string file, int blocknumber){
  int b = getfirstblock(file);
  if (b == -1)
    return false;

  while (b != 0){
    if (b == blocknumber){
      return true;
    }
    b = fat[b];
  }
  return false;
}

//##############################################################################

int Filesys::fsclose(){
  // do nothing
  return 1;
}

//##############################################################################

int Filesys::newfile(string file){
  // create empty file
  // -1 means file already exists
  // 0 no room left
  // 1 success

  // check if file already exists
  // do this by checking each entry in the filename vector and seeing if == to input file 
  for (int i = 0; i < filename.size(); i++){
    if (filename[i] == file){
      return -1; // if true, return -1 for FILE ALREADY EXISTS
    }
  }

  // see if there are some xxxxxx in the filename vector
  // do this in order to confirm whether or not there is an open entry 
  // because XXXXXX denotes empty space for file to be put in its place
  for (int i = 0; i < filename.size(); i++){ // loop thru each entry in filename vector to find first XXXXXX (open entry)
    if (filename[i] == "xxxxxx"){
      // know we have an entry to put the file at
      filename[i] = file; // set the open entry equal to the inputted file name (from XXXXXX to file)
      firstblock[i] = 0;  //set firstblock (parallel vector of filename) equal to 0 [why zero: a zero in the block is an empty block]
      fssynch(); // need to save the root directory after changes
      return 1; // SUCCESS
    }
    return 0; // otherwise there is no space so return 0
  }
  return 0; // JUST ADDED
}

//##############################################################################

int Filesys::rmfile(string file){
    // remove file that is empty
    // -1 file diskname
    // 0 file not empty
    // 1 success

    // search for the file that the user wants to remove
    for (int i = 0; i < filename.size(); i++){
      if (filename[i] == file){ // found the desired file that wants to be removed 
        if (firstblock[i] == 0){
          // found the file and its firstblock is empty
          // which means that the file is empty and has no blocks associated with it except its first block in the parallel vector 
          filename[i] = "XXXXXX"; // thus can set the filename to XXXXXX since we don't need to worry about any blocks
          fssynch();  // synch the changes with the root 
          return 1; // return 1 for success
        }
        // firstblock is not zero thus not empty
        // thus any other function curious can use this as a condition checker when deleting the blocks to ensure that it wont leave any open blocks 
        return 0;
      }
      // file does not exist
      return -1;
    }
    return 0; // JUST ADDED
}

//##############################################################################

int Filesys::getfirstblock(string file){
  // -1 file does not exist  if the first block is zero
  // return firstblock number of the file

  // go through the list of all the files in order to find the desired file 
  for (int i = 0; i < filename.size(); i++){
    if (filename[i] == file){
      // found file so return its first block
      // return the index of the first block i because filename and firstblock are parallel vectors, each holding relevant info about eachother 
      return firstblock[i];
    }
  }
  // could not find the file after the loop, thus does not exist
  return -1;
}

//##############################################################################

int Filesys::readfs(){          
  string buffer1, buffer2;  // initialize buffers
  getblock(1, buffer1);     // Sdisk function to get the first block for the ROOT and place it into buffer1 pass by reference
  // PERHAPS PUT INITIALIZER VALUES OUT HERE?
  for (int i = 0; i < fatsize; i++){ // go through fat and put it all into buffer2
    string b;
    getblock(i+2, b); // getblock info and put info into b for passby reference
    buffer2 += b;     // add on the block into the end of buffer2
  }

  // initialize instream 1 and 2 to get the proper strings from the buffers
  istringstream instream1;
  istringstream instream2;
  // convert buffers into acceptable strings in case something went wonky 
  instream1.str(buffer1);
  instream2.str(buffer2);

  // just in case something went wonky with the filename or firstblock parallel vectors clear them out to be populated after
  filename.clear();
  firstblock.clear();
  // PERHAPS ALSO INITIALIZE THE F AND B OUT HERE?
  for (int i = 0; i < rootsize; i++){
    string f;
    int b;
    instream1 >> f >> b;
    filename.push_back(f);
    firstblock.push_back(b);
  }

  for (int i = 0; i < getnumberofblocks(); i++){
    int k;
    instream2 >> k;
    fat.push_back(k);
  }
  return 1;
}

//##############################################################################
// PRIVATE FUNCTIONS FROM THE HEADER FILE
//##############################################################################

int rootsize;           // maximum number of entries in ROOT
int fatsize;            // number of blocks occupied by FAT
vector<string> filename;   // filenames in ROOT
vector<int> firstblock; // firstblocks in ROOT
vector<int> fat;             // FAT

// builds the file system
int Filesys::buildfs(){
  for (int i = 0; i < rootsize; i++){
    filename.push_back("XXXXXX");
    firstblock.push_back(0);
  } // after the loop the root has been built

  // populate the index 0 through fatsize+2 of the FAT
  fat.push_back(2+fatsize);
  fat.push_back(-1);
  for (int i = 0; i < fatsize; i++){
    fat.push_back(-1);
  }

  // now populate the rest of the FAT so start at the index 2+fatsize
  for (int i = 2+fatsize; i < getnumberofblocks(); i++){
    fat.push_back(i+1);
  }

  // so the tailend isnt pointing to something that doesnt exist in the space
  fat[fat.size()-1] = 0;

  return 1; // success
}



// writes the FAT and ROOT to the sdisk
int Filesys::fssynch(){
  // synch file system
  // call this whenever modifying any part of the FAT or the root
  ostringstream outstream1, outstream2;
  for (int i = 0; i < firstblock.size(); i++){
    outstream2 << fat[i] << " "; // writing to FAT
  }

  string buffer1 = outstream1.str();
  string buffer2 = outstream2.str();

  vector <string> blocks1 = block(buffer1, getblocksize());
  vector <string> blocks2 = block(buffer2, getblocksize());

  putblock(1, blocks1[0]); // putting root into the index 1

  for (int i = 0; i < blocks2.size(); i++){
    putblock(fatsize=2+i, blocks2[i]);
  }
  return 1;
}