//
// Created by lahmer on 2/21/17.
//

#ifndef FILESERVER_FILE_H
#define FILESERVER_FILE_H


#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <fstream>

class File {
public:
    struct FileChunk{
        unsigned int segmentNumber;
        std::shared_ptr<File> file;
        unsigned char* buff;
        FileChunk(){
            buff = NULL;
        }
    };


    File(const boost::filesystem::path& p, unsigned int segmentSize);
    std::string getFileURL();
    void loadSegments();
private:
    void log(const std::string&  );
private:
    bool areLoaded;
    unsigned int fileSize;
    unsigned int segmentSize;


    boost::filesystem::path path;
    unsigned int lastSegment;
    std::map<int,File::FileChunk> chunks;
    std::ifstream file;
};


#endif //FILESERVER_FILE_H
