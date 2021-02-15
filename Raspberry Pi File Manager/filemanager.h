/* By Bradley Assaly-Nesrallah (250779140)

This is the header file for the filemanager class
defines the prototypes for the class

September 3, 2019
*/

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>                      //include vector string
#include <string>

class filemanager{

   public:                              //protoypes public functions
     filemanager(std::string filename);  //constructor

     ~filemanager();                  //destructor

     std::string getName();

     std::string getOwnerStr();        //getters

     std::string getGroupStr();

     std::string getPermissions();

     std::string getAcess_time();

     std::string getModification_time();

     std::string getStatus_change_time();

     int getType();

     int getSize();

     int getOwnerID();

     int getGroupID();

     int getBlock_size();

     int getError_num();

     std::string getError_string();

     std::vector<filemanager> getChildren();

     void setName(std::string newName);    //setter

     void Dump(std::fstream &filestream);   //function prototypes

     void Rename(std::string newName);     //dump, rename, remove, compare, expand

     void Remove();

     void Compare(filemanager file);

     void Expand();

   private:                             //declaring private variables encapsulation
     std::string Name, OwnerStr, Permissions, Access_time, Modification_time;
     std::string Status_change_time, GroupStr;
     int Type, Size, OwnerID, GroupID, Block_size, Error_num;
     std::vector<filemanager> Children;


};

#endif
