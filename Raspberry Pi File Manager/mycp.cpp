/* By Bradley Assaly-Nesrallah (250779140)

This is the mycpp which uses filemanager to copy a given file
to a new name or location using the dump function

September 3, 2019
*/


#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>             //include libraries
#include <fstream>
#include <unistd.h>

#include "filemanager.h"      //include header files

using namespace std;           //uses namespace std

int main(int argc, char* argv[]){       //command line arguemnets
  if (argc == 1) {               //prints warning if no args
    cout << "Please enter arguments for this utility function." << endl;
  }
  if (argc == 2) {                //prints warning if only one arg
    cout << "Please enter a second argument for this utility function." << endl;
  }
  if (argc == 3) {            //if two args copies first to second
    try{
      filemanager source = filemanager(argv[1]);   //creates filemanager object
      if (source.getError_num() == 0 && S_ISREG(source.getType())){  //if no error and regular file
        fstream outfile (argv[2], ios::out);    //creates outfile object
        source.Dump(outfile);                 //uses dump to copy to new file location
        outfile.close();                    //closes file
      }
    }catch (std::exception &e){              //catches exception and prints info to user
      cout << e.what() << endl;
    }
  }
  if (argc > 3) {                //prints warning if more than two args
    cout << "Please enter two arguments for this utility function." << endl;
  }
  return 0;
}
