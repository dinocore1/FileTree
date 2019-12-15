#pragma once

typedef uint32_t blockptr_t;

struct Block {
    uint8_t data[4096];
};

struct INode {
    uint32_t size;
    uint16_t link_count;
    blockptr_t block[60];
};

class DataFile {
public:
    DataFile(const string& filePath);
    ~DataFile();

    int open();

    const string mFilePath;

private:
    FILE* mFD;
};
