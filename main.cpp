#include "sdisk.cpp"
#include "filesys.cpp"
// #include "block.cpp"


int main()
{
          // # of blocks , blocksize
  Sdisk disk1("disk1",256,128);
  Filesys fsys("disk1",256,128);
  
  fsys.newfile("file1");
  fsys.newfile("file2");
  string bfile1;
  string bfile2;
  for (int i=1; i<=1024; i++)
     {
       bfile1+="1";
     }

  vector<string> blocks = block(bfile1,128);
  // vector is filled with 8 blocks of size 128 1's
  //cout << "BLOCKS.size()=" << blocks.size() << endl;
  
  //for (int i = 0; i <= blocks.size()-1; i++){
  //  cout << "\ni=" << i << " - " << blocks[i]; 
  //}
  // if the loop doesnt have -1 after blocks.size() it will segment fault for reading out of range 

  
  int blocknumber=0;

  // add block to put info into block
  for (int i=0; i<=blocks.size()-1; i++)
     {
        //cout << "\nYES - " << i;
       blocknumber=fsys.addblock("file1",blocks[i]); // cant make it past i = 0
       cout << "i=" << i << " | alloc: " << blocknumber << endl;
       //cout << "YES - " << i;
     }

  /*

  cout << "F - ";

  fsys.delblock("file1",fsys.getfirstblock("file1"));

  cout << "F1 - ";

  for (int i=1; i<=2048; i++)
     {
       bfile2+="2";
     }

  cout << "G - ";

  blocks=block(bfile2,128);

  cout << "G1 - ";

  for (int i=0; i< blocks.size()-1; i++)
     {
       blocknumber=fsys.addblock("file2",blocks[i]);
     }

  cout << "G2 - ";

  fsys.delblock("file2",blocknumber);

  cout << "G3 - ";

  */
  

}
