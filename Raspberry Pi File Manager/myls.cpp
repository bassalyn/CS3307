/* By Bradley Assaly-Nesrallah (250779140)

This is the myls which shows displays the file or
the elements of a directory using the Expand function
also contains a -l option for long display format

September 3, 2019
*/


#include <sys/types.h>    //include libraries
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>

#include "filemanager.h"  // include header

using namespace std;      //uses std namespace

int main(int argc, char* argv[]){     //command line arguments

  if (argc == 1) {                  //if no command line prints current dir
    DIR *dir;
    struct dirent *ent;             //creates dirent struct
    char cwd[PATH_MAX];             //creates var for current path
    getcwd(cwd, sizeof(cwd));       //gets current working directory
    if ((dir = opendir (cwd)) != NULL) {  //for each element in cwd
      int count = 0;                         //counter to skip first two outputs
      while ((ent = readdir (dir)) != NULL) {
        if (count >=2){
          cout << ent->d_name << endl;            //prints directory elements name
        }
        count++;                          //increments counter
      }
      closedir (dir);                       //closes directory
    }
  }
  if (argc ==2) {                       //if one argument
    try{
    filemanager source = filemanager(argv[1]);  //creates filemanger object for arg
    if (S_ISDIR(source.getType())){             //checks if directory
      source.Expand();                          //calls expand function
      for (int i = 2; i<source.getChildren().size();i++){
        cout << source.getChildren().at(i).getName() << endl; //prints names of children of object
      }

    }else{
      cout << source.getName() << endl;         //otherwise just prints name of arg
    }
    }catch (std::exception &e){                 //handles exceptions and prints what it was
      cout << e.what() << endl;
    }
  }

  if (argc == 3){
    string code = argv[1];          //if two arguments, ie option and arg
    if (code.compare("-l")==0){    //if option is -l proceed
      try{
        filemanager source = filemanager(argv[2]);  //creates filemanager object
        if (S_ISDIR(source.getType())){           //if isdirectory
          source.Expand();                        //calls expand to populate children
          for (int i = 2; i<source.getChildren().size();i++){
            if (S_ISREG(source.getChildren().at(i).getType())){      //prints filetype using macros
              cout << "-";
            }else if (S_ISDIR(source.getChildren().at(i).getType())){
              cout << "d";
            }else if (S_ISLNK(source.getChildren().at(i).getType())) {
              cout << "l";
            }
            cout << source.getChildren().at(i).getPermissions();   //prints permission
            cout << " ";
            if (S_ISREG(source.getChildren().at(i).getType())){
              cout << "1";
            }else{
              cout << source.getChildren().at(i).getChildren().size();  //prints number of children
            }
            cout << " ";
            cout << source.getChildren().at(i).getOwnerStr();             //prints owner string
            int space1 = (12 - source.getChildren().at(i).getOwnerStr().size());
            for (int i = 0; i < space1; i++){                         //standardizes the spaces
              cout << " ";
            }
            cout << source.getChildren().at(i).getGroupStr();         //prints the group name
            int space2 = (12 - source.getChildren().at(i).getGroupStr().size());
            for (int i = 0; i < space2; i++){                       //standardizes the spaces
              cout << " ";
            }
            cout << source.getChildren().at(i).getSize();          //prints the sizr
            int digits = 0;
            int num = source.getChildren().at(i).getSize();
            while (num){                                        //gets digits to standardize the spaces
              num /= 10;
              digits ++;
            }
            int space3 = (8 - digits);                  //standardizes the spaces
            for (int i = 0; i < space3; i++){
              cout << " ";
            }
            cout << source.getChildren().at(i).getName();     //prints the name
            int space4 = (20 - source.getChildren().at(i).getName().length());
            for (int i = 0; i < space4; i++){            //standardizes the output
              cout << " ";
            }
            cout << source.getChildren().at(i).getModification_time();  //prints modification time
            }
        }else{
          cout << "-";
          cout << source.getPermissions();         //if not directory prints files info
          cout << " ";
          if (S_ISREG(source.getType())){        //prints permissions and type
            cout << "1";
          }
          cout << " ";
          cout << source.getOwnerStr();          //prints owner string
          int space1 = (12 - source.getOwnerStr().size());  //standardizes spaces
          for (int i = 0; i < space1; i++){
            cout << " ";
          }
          cout << source.getGroupStr();              //prints group string
          int space2 = (12 - source.getGroupStr().size());
          for (int i = 0; i < space2; i++){         //standardizes spaces
            cout << " ";
          }
          cout << source.getSize();                   //prints blocksize
          int digits = 0;
          int num = source.getSize();            //gets digits of size
          while (num){
            num /= 10;
            digits ++;
          }
          int space3 = (8 - digits);            //standadrizes spaces
          for (int i = 0; i < space3; i++){
            cout << " ";
          }
          cout << source.getName();                     //prints file name
          int space4 = (20 - source.getName().length());    //standardizes name and spaces
          for (int i = 0; i < space4; i++){
            cout << " ";
          }
          cout << source.getModification_time();     //prints modification time
          }
        }catch (std::exception &e){             //handles exceptions and prints
          cout << e.what() << endl;
        }
      }else{                                  //if option isnt -l lets user know
        cout << "Please enter a valid option for this utility (ie '-l')." <<endl;
      }
    }
    if (argc>3){                                    //if too many args lets user know
      cout << "Please enter one argument (and/or and option) for this utility function." << endl;
    }
  return 0;
}
