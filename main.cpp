#include "sdisk.cpp"
#include "filesys.cpp"


int main()
{
  cout << "A \n";
  Sdisk disk1("disk1",256,128);
  cout << "A1 \n";
  Filesys fsys("disk1",256,128);
  cout << "B \n";
  fsys.newfile("file1");
  fsys.newfile("file2");
  cout << "C \n";
  string bfile1;
  string bfile2;
  cout << "D \n";
  for (int i=1; i<=1024; i++)
     {
       bfile1+="1";
     }


  //    vector<string> block(string buffer, int b);

  vector<string> blocks = block(bfile1,128);

  int blocknumber=0;

  for (int i=0; i< blocks.size(); i++)
     {
       blocknumber=fsys.addblock("file1",blocks[i]);
     }

  fsys.delblock("file1",fsys.getfirstblock("file1"));

  for (int i=1; i<=2048; i++)
     {
       bfile2+="2";
     }

  blocks=block(bfile2,128);

  for (int i=0; i< blocks.size(); i++)
     {
       blocknumber=fsys.addblock("file2",blocks[i]);
     }

  fsys.delblock("file2",blocknumber);

}
