/* By Bradley Assaly-Nesrallah (250779140)

This is the myrm program which uses the filemanager
class remove function to remove a gien file

September 3, 2019
*/


#include <iostream>                       //include library
#include <fstream>

#include "filemanager.h"                //include header


using namespace std;                    //include namespace

int main(int argc, char* argv[]){       //command line arguments
  if (argc == 1) {                    //warns user no arg
    cout << "Please enter arguments for this utility function." << endl;
  }

  if (argc >=2) {                         //if one arg or more removes files
    for (int i=1; i < argc; i++){
      try{
      filemanager source = filemanager(argv[i]);  //creates filemanager object
      source.Remove();                          //calls remove function
    }catch (std::exception &e){             //handles exceptions and prints for user
        cout << e.what() << endl;
      }
    }
  }
  return 0;
}
