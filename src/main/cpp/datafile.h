#ifndef DATAFILE_H
#define DATAFILE_H


class DataFile {
public:
    DataFile(const string& filePath);
    ~DataFile();

    int open();

    const string mFilePath;

private:
    FILE* mFD;
};

#endif // DATAFILE_H