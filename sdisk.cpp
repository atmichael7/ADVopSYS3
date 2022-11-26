#include "sdisk.h"

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize){
  this->diskname = diskname;
  this->numberofblocks = numberofblocks;
  this->blocksize = blocksize;

  ifstream infile;
  infile.open(diskname.c_str());

  if (infile.fail()){
    infile.close();
    ofstream outdisk;
    outdisk.open(diskname.c_str());
    for (int i = 0; i < numberofblocks * blocksize; i++){
      outdisk.put('#');
    }
    cout << "\nDisk does not exist, created new disk '" << diskname << "'\n";
  }

  else{
    char c;
    int counter = 0;  // Should this be 0 or 1?
    infile.get(c);
    while (infile.good()){
      counter++;
      infile.get(c);
    }

    if (counter == numberofblocks * blocksize)
      cout << "\nDisk format: OK\n";
    else
      cout << "\nDisk format: FAIL\n";
  }
  return;
}

int Sdisk::getblock(int blocknumber, string& buffer){
  fstream iofile;
  iofile.open(diskname.c_str(), ios::in | ios::out);
  iofile.seekg(blocknumber * blocksize);
  buffer.clear();
  char c;

  for (int i = 0; i < blocksize; i++){  // Potentially i = 1??? Not likely though
    iofile.get(c);
    buffer.push_back(c);
  }
  return 1;
}

int Sdisk::putblock(int blocknumber, string buffer){ 
  fstream iofile;
  iofile.open(diskname.c_str(), ios::in | ios::out);
  if (blocknumber < 0 || blocknumber >= numberofblocks){
    cout << "Block out of range!";
    return 0;
  }

  // Ensure that the buffer is == blocksize, or something wonky might be going on
  if (buffer.size() != blocksize){
    if (buffer.size() > blocksize){
      cout << "WARNING: Buffer is greater than blocksize\n";
    }
    else if (buffer.size() < blocksize){
      cout << "WARNING: Buffer is less than blocksize\n";
    }
    else{
      cout << "WARNING: Buffer size inconsistency\n";
    }
    cout << "\nWARNING: UNKNOWN ERROR RAISED IN BUFFER SIZE\n";
  }

  iofile.seekp(blocksize * blocknumber);
  for (int i = 0; i < blocksize; i++){
    iofile.put(buffer.at(i));
  }
  iofile.close();
  return 1;
}

int Sdisk::getnumberofblocks(){ return numberofblocks; }
int Sdisk::getblocksize(){ return blocksize; }
