/* By Bradley Assaly-Nesrallah (250779140)

This is the mystat file which uses the filemanager
class to display information about a given file,
uses the getters to retrieve the information for
the file

September 3, 2019
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>             //include libraries
#include <fstream>
#include <unistd.h>

#include "filemanager.h"      //include header


using namespace std;            //using namespace std

int main(int argc, char* argv[]){         //command line arguments
  if (argc != 2) {                      //warns user if not one arg
    cout << "Please enter one argument for this utility function." << endl;
  }

  if (argc == 2) {        //prints information for one arg file
    try{
      filemanager source = filemanager(argv[1]);        //creates filemanger object
      cout << "File Name: " << source.getName() << endl;    //prints info using getters
      if (S_ISREG(source.getType())){
        cout << "File Type: Regular"  << endl;        //prints file type
      }else if (S_ISDIR(source.getType())){
        cout << "File Type: Directory"  << endl;
      }else{
        cout << "File Type: Link"  << endl;
      }
      cout << "Size :" << source.getSize() << endl;   //prints size
      cout << "Owner :" << source.getOwnerStr() << endl;
      cout << "Group Name: " << source.getGroupStr() << endl;   //prints ownser and group string
      cout << "Permissions :" << source.getPermissions() << endl;   //prints permission as string
      cout << "Access time :" << source.getAcess_time();
      cout << "Modification time: " << source.getModification_time();     //prints times as strings
      cout << "Status change time :" << source.getStatus_change_time();
      cout << "Block Size :" << source.getBlock_size() << endl;
      if (S_ISDIR(source.getType())){                         //expands children for directorie s
        source.Expand();
      }
      cout << "Children :" << (source.getChildren().size()-2) << endl;      //prints children number and error number 
      cout << "Error number :" << source.getError_num() << endl;
    }catch (std::exception &e){         //handles exception and prints warning to user
      cout << e.what() << endl;
    }
  }
  return 0;
}
