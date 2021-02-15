/* By Bradley Assaly-Nesrallah (250779140)

This is the mycat file which uses the filemanager
class and dump function to display the contents of
one of more arguments

September 3, 2019
*/

#include <iostream>
#include <fstream>       //include libraries

#include "filemanager.h"   //include header


using namespace std;        //using namespace for std

int main(int argc, char* argv[]){        //command line arguments
  if (argc == 1) {                      //handles if one arg, prints warning
    cout << "Please enter arguments for this utility function." << endl;
  }

  if (argc >=2) {                    //if greater or equal to one arg prints using cat
    for (int i=1; i < argc; i++){
      try{                                      //handles exceptions
        fstream outfile ("dumpfile", ios::out);     //creates fstream for dump
        filemanager source = filemanager(argv[i]);    //creates filemanager object
        source.Dump(outfile);                      //dumps from file to fstream
        outfile.seekp(0);                         //sets position to beginning
        outfile.close();
        cout << ifstream("dumpfile").rdbuf();     //prints contents of fstream
        remove("dumpfile");                      //removes the fstream temp file
      }catch (std::exception &e){               //catches and prints exceptions to notiy user
        cout << e.what() << endl;
      }
    }
  }

  return 0;
}
