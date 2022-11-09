#include "sdisk.h"

Sdisk::Sdisk(string diskname, int numberofblocks, int blocksize){
  this->diskname = diskname;
  this->numberofblocks = numberofblocks;
  this->blocksize = blocksize;

  ifstream infile;
  infile.open(diskname);

  if (infile.fail()){
    infile.close();
    ofstream outdisk;
    outdisk.open(diskname.c_str());
    for (int i = 0; i < numberofblocks * blocksize; i++){
      outdisk.put('#');
    }
    cout << "\nFile does not exist, created new file '" << diskname.c_str() << "'\n";
  }

  else{
    char c;
    int counter;
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

  for (int i = 0; i < blocksize; i++){
    iofile.get(c);
    buffer.push_back(c);
  }
  return 1;
}


int Sdisk::putblock(int blocknumber, string buffer){
  fstream iofile;
  iofile.open(diskname.c_str(), ios::in | ios::out);
  if (blocknumber < 0 || blocknumber >= numberofblocks){
    cout << "Block does not exist";
    return 0;
  }

  iofile.seekp(blocksize * blocknumber);
  for (int i = 0; i < blocksize; i++){
    iofile.put(buffer.at(i));
  }
  return 1;
}


int Sdisk::getnumberofblocks(){
  return numberofblocks;
}

int Sdisk::getblocksize(){
  return blocksize;
}


vector<string> block(string buffer, int b)
{
  // blocks the buffer into a list of blocks of size b

  vector<string> blocks;
  int numberofblocks=0;

  if (buffer.length() % b == 0){ 
    numberofblocks= buffer.length()/b;
  }
  else{ 
    numberofblocks= buffer.length()/b +1;
  }

  string tempblock;

  for (int i=0; i<numberofblocks; i++){ 
    tempblock=buffer.substr(b*i,b);
    blocks.push_back(tempblock);
  }

  int lastblock=blocks.size()-1;

  for (int i=blocks[lastblock].length(); i<b; i++){ 
    blocks[lastblock]+="#";
  }

  return blocks;
}



