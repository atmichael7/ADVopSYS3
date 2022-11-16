#include "sdisk.cpp"
#include "filesys.cpp"


int main()
{
  cout << "A - ";
          // # of blocks , blocksize
  Sdisk disk1("disk1",256,128);
  cout << "A1 - ";
  Filesys fsys("disk1",256,128);
  cout << "B - ";
  fsys.newfile("file1");
  cout << "C1 - ";
  fsys.newfile("file2");
  cout << "C2 - ";
  string bfile1;
  string bfile2;
  for (int i=1; i<=1024; i++)
     {
       bfile1+="1";
     }
  cout << "D - ";

  vector<string> blocks = block(bfile1,128);

  cout << "E - "; // segmentation fault after E

  int blocknumber=0;

  for (int i=0; i< blocks.size(); i++)
     {
       blocknumber=fsys.addblock("file1",blocks[i]);
     }

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

  for (int i=0; i< blocks.size(); i++)
     {
       blocknumber=fsys.addblock("file2",blocks[i]);
     }

  cout << "G2 - ";

  fsys.delblock("file2",blocknumber);

  cout << "G3 - ";

}
