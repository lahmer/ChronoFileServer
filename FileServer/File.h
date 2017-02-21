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
        std::string buff;
        FileChunk(){
            buff = "";
        }
    };


    File(const boost::filesystem::path& p, unsigned int segmentSize);
    std::string getFileURL();
    std::shared_ptr<FileChunk> getChunk(unsigned int index );
    unsigned int getChunkListSize();
private:
    void loadSegments();
    void log(const std::string&);
private:
    bool areLoaded;
    unsigned int fileSize;
public:
    unsigned int getFileSize() const;

private:
    unsigned int segmentSize;


    boost::filesystem::path path;
    unsigned int lastSegment;
    std::vector<std::shared_ptr<File::FileChunk>> chunks;
    std::ifstream file;
};


#endif //FILESERVER_FILE_H
