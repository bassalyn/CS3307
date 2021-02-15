/* By Bradley Assaly-Nesrallah (250779140)

This is the mydiff file which uses the filemanager class
to compare two different files using the compare function

September 3, 2019
*/


#include <iostream>                 //includes libraries
#include <fstream>

#include "filemanager.h"            //includes header


using namespace std;                //uses namespace stf

int main(int argc, char* argv[]){       //command line arguments
  if (argc != 3) {                      //if not exactly two args prints warning
    cout << "Please enter two arguments for this utility function." << endl;
  }

  if (argc ==3) {         //if two args compares the files for equivalence
    try{
      filemanager file1 = filemanager(argv[1]);     //makes two filemanger objects
      filemanager file2 = filemanager(argv[2]);
      file1.Compare(file2);                       //calls compare function
    }catch (std::exception &e){                     //handles exceptions prints info to user
      cout << e.what() << endl;
    }
  }
  return 0;
}
