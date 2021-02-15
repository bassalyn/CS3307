/* By Bradley Assaly-Nesrallah (250779140)

This is the mymv program which moves a file to a differnt
name or location using the rename function or
using dump and remove functions if there is an Error


September 3, 2019
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>                 //includes libraries
#include <fstream>
#include <unistd.h>

#include "filemanager.h"          //includes header

using namespace std;              //uses namespace std

int main(int argc, char* argv[]){         //command line arguments
  if (argc == 1) {                      //warns user in no args
    cout << "Please enter arguments for this utility function." << endl;
  }
  if (argc == 2) {                    //warns user if one arg
    cout << "Please enter a second argument for this utility function." << endl;
  }
  if (argc == 3) {                  //if two args moves first file to second arg
    try{
      filemanager source = filemanager(argv[1]);    //creates filemanger obj for arg1
      source.Rename(argv[2]);                     //renames file to second arg using rename function
      if (source.getError_num() != 0 && S_ISREG(source.getType())){  //if didnt work and regular file
        fstream outfile (argv[2]);                  //creates fstream object
        source.Dump(outfile);                   //dumps to outfile
        source.Remove();                        //removes original object
        outfile.close();                        //closes outfile
      }
    }catch (std::exception &e){
      cout << e.what() << endl;                 //handles exceptions and prints info to user
    }
  }
  if (argc > 3) {                             //warns user if more than two args
    cout << "Please enter a two arguments for this utility function." << endl;
  }
  return 0;
}
