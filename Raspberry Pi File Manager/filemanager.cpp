/* By Bradley Assaly-Nesrallah (250779140)

This is the cpp file for the filemanager class
contains the filemanager class used to manage a file
constructor, destructor, getters, setters, and functions
to operate on a given file and stores its key info

September 3, 2019
*/

#include <sys/stat.h>  //include system files and libraries
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>  //in traditional c++ include order
#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <cstdio>
#include <unistd.h>
#include <vector>
#include <string>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <time.h>

#include "filemanager.h"     //include header file


using namespace std;        //using namespace for std

     filemanager::filemanager(string filename){  //constructor
        Name = filename;                        //sets name
        struct stat sb;                         //struct stat to get attributes
        const char *name = filename.c_str();    //converts name to char *
        if (!name) {                            //if null name throws error
          throw std::runtime_error("Could not open file");
          exit(EXIT_FAILURE);
        }

        ifstream file;
        file.open(filename);                    //checks if file exists
        if (!file){
          throw std::runtime_error("Could not open file");  //throws error if file DNE
          exit(EXIT_FAILURE);
        }

        int status = stat(name,&sb); //fills stat object and record if error
          Type = sb.st_mode;
          Size = sb.st_size;        //uses stat obj to fill attributes
          OwnerID = sb.st_uid;
          struct passwd *pwd;       //uses pwd struct to get string of owner
          pwd = getpwuid(OwnerID);
          OwnerStr = pwd->pw_name;
          GroupID = sb.st_gid;
          struct group *grp;          //uses grp struct to get string of group name
          grp = getgrgid(GroupID);
          GroupStr = grp->gr_name;
          Permissions = "";            //for permissions uses macros to get each
          if (Type & S_IRUSR){         //value for USR,GRP,OTH, records value
            Permissions.append("r");   //in string attribute for easy access
          }else{
              Permissions.append("_");
          }
          if (Type & S_IWUSR){
            Permissions.append("w");
          }else{
              Permissions.append("_");
          }
          if (Type & S_IXUSR){
            Permissions.append("x");
          }else{
              Permissions.append("_");
          }
          if (Type & S_IRGRP){
            Permissions.append("r");
          }else{
              Permissions.append("_");
          }
          if (Type & S_IWGRP){
            Permissions.append("w");
          }else{
              Permissions.append("_");
          }
          if (Type & S_IXGRP){
            Permissions.append("x");
          }else{
              Permissions.append("_");
          }
          if (Type & S_IROTH){
            Permissions.append("r");
          }else{
              Permissions.append("_");
          }
          if (Type & S_IWOTH){
            Permissions.append("w");
          }else{
              Permissions.append("_");
          }
          if (Type & S_IXOTH){
            Permissions.append("x");
          }else{
              Permissions.append("_");
          }
          Access_time = ctime(&sb.st_atime);       //converts time to string stores
          Modification_time = ctime(&sb.st_mtime);
          Status_change_time = ctime(&sb.st_ctime);  //stores time as string
          Block_size = sb.st_blksize;               //stores blocksize
          if (status == 0){                        //if stat fine sets Error to 0
            Error_num = 0;
          }else {
            Error_num = errno;                   //otherwise stores errno
          }
          vector<filemanager> children;          //creates vector for children
          Children = children;
     }

     filemanager::~filemanager(){            //destructor for class
     }

     string filemanager::getName(){         //getter for attribute
       return Name;
     }

     string filemanager::getOwnerStr(){    //getter for attribute
       return OwnerStr;
     }

     string filemanager::getGroupStr(){   //getter for attribute
      return GroupStr;
    }

     string filemanager::getPermissions(){   //getter for attribute
       return Permissions;
     }

     string filemanager::getAcess_time(){   //getter for attribute
       return Access_time;
     }

     string filemanager::getModification_time(){    //getter for attribute
       return Modification_time;
     }

     string filemanager::getStatus_change_time(){   //getter for attribute
       return Status_change_time;
     }

     int filemanager::getType(){   //getter for attribute
       return Type;
     }

     int filemanager::getSize(){   //getter for attribute
       return Size;
     }

     int filemanager::getOwnerID(){   //getter for attribute
       return OwnerID;
     }

     int filemanager::getGroupID(){   //getter for attribute
       return GroupID;
     }

     int filemanager::getBlock_size(){   //getter for attribute
       return Block_size;
     }

     int filemanager::getError_num(){   //getter for attribute
       return Error_num;
     }

     string filemanager::getError_string(){   //getter calls strerror to get str
       return strerror(Error_num);
     }

     vector<filemanager> filemanager::getChildren(){    //getter for attribute
       return Children;
     }

     void filemanager::setName(string newName){   //setter sets name attribute
       Name = newName;
     }

     /* Name: Dump

     Description: takes a filestream and dumps named file to it, uses fstream
     read, write, flush, close and sets error num appropriately

     Parameters: outfile an address to a fstream

     Return: void
     */

     void filemanager::Dump(fstream &outfile){
        if S_ISREG(Type){               //uses macro to check if regular file
          ifstream infile (Name);          //if so opens ifstream
          while (!infile.eof()){
            char* buffer = new char[Block_size];   //creates buffer using size
            infile.read(buffer,Block_size);       //reads to buffer using blocksize
            outfile.write(buffer,Block_size);     //writes to buffer using blocksize
            outfile.flush();                //flushes buffer
            delete[] buffer;
          }
          infile.close();                 //closes infile
               //deletes the buffer
        }else{
          Error_num = ENOTSUP;            //if not regular file sets error ENOTSUP
        }
        if (errno != 0){                 //if errno nonzero sets Error num
          Error_num = errno;
        }else{
          Error_num = 0;                //if successful sets Error num to 0
        }
      }

      /* Name: Rename

      Description: takes a string and renames the file using rename function
      and return error num as appropriate

      Parameters: a string for the new name of the file

      Return: void
      */

      void filemanager::Rename(string newName){
          const char *name = Name.c_str();       //converts name att to char*
          const char *newname = newName.c_str(); //converts newname to char*
          Error_num = rename(name, newname);     //sets error num 0 if succes error otherwise
          setName(newName);                   //uses setter to set new name
          if (Error_num != 0){                //if error occured display error to user
            cout << getError_string() << endl;
          }
      }

      /* Name: Remove

      Description: remove the file using the unlink function and returns error
      number as appropriate

      Parameters: none

      Return: void
      */

      void filemanager::Remove(){
        const char *name = Name.c_str();  //conerts name to char *
        Error_num = unlink(name);       //uses unlink function and store errnum
        if (Error_num != 0){           //if error displays string to user
          cout << getError_string() << endl;
        }
      }

      /* Name: Compare

      Description: takes a file and compares to current object and lets user
      know, also sets error num appropriately

      Parameters: a filemanager object

      Return: void
      */

      void filemanager::Compare(filemanager file){
        if (getSize() != file.getSize()){    //if files different size lets user know
          cout << "The two files compared were not the same." << endl;
          return;
        }
        fstream file1 (Name);               //opens up fstream for object file
        fstream file2 (file.getName());     //opens fstream for parameter file
        bool samefile = true;              //boolean for equivalence
        while (!file1.eof()){              // while first file not done
          char buffer1[getBlock_size()];
          char buffer2[getBlock_size()];       //creates buffers
          file1.read(buffer1 ,getBlock_size());
          file2.read(buffer2 ,getBlock_size());  //reads to buffers blocksize
          if (strcmp(buffer1, buffer2)){        //compares buffers
            samefile = false;
          }
        }
        file1.close();                      //closes the files
        file2.close();
        if (samefile) {                 //depending on boolean lets reader know if same
          cout << "The two files compared were the same." << endl;
        }else{
          cout << "The two files compared were not the same." << endl;
        }
        if (errno != 0){            //checks errno, if nonzero sets and lets user know
          cout << getError_string() << endl;
          Error_num = errno;
        }else{
          Error_num = 0;            //if successful sets error num to 0
        }
      }

      /* Name: Expand

      Description: fills a files children vector by looking at contents of Directory
      if the file is a directory and sets error num appropriately

      Parameters: void

      Return: void
      */

      void filemanager::Expand(){
        if S_ISDIR(Type){                   //checks if file is directory
          const char *name = Name.c_str();   //converts name to char *
          DIR* dir = opendir(name);         //opens directory
          struct dirent * ent;               //makes dirent struct
          while ((ent = readdir(dir))!= NULL){  //goes through directories
            string path = Name;               //reads directory and gets path
            if (path.back() != '/'){
              path.append("/");
            }
            path.append(ent->d_name);
            filemanager file = filemanager(path);  //creates filemanger object
            Children.push_back(file);          //adds each filemanger object to vector
          }
          closedir(dir);                      //closes directory
          if (errno != 0){                    //if errno nonezero sets error num
              Error_num = errno;
              cout << getError_string() << endl;   //prints error string to user

          }
        }else if (!S_ISDIR(Type)){            //if not a directory
          Error_num = ENOTSUP;                //sets error num to ENOTSUP and prints
          cout << getError_string() << endl;
        }
      }
