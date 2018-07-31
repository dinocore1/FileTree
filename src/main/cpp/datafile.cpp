
#include "pch.h"

DataFile::DataFile(const string& filePath)
 : mFilePath(filePath), mFD(NULL)
{
}

DataFile::~DataFile()
{
    if(mFD != NULL) {
        fclose(mFD);
        mFD = NULL;
    }
}

int DataFile::open()
{
    const char* filename = mFilePath.c_str();

    if((mFD = fopen(filename, "r")) != NULL) {
        //file already exists;
        fclose(mFD);
        mFD = fopen(filename, "a+b");
    } else {
        //init file
        mFD = fopen(filename, "w+b");
        
    }



}