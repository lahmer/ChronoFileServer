//
// Created by lahmer on 2/21/17.
//

#include <sstream>
#include "File.h"
#include "boost/filesystem.hpp"
void File::log(const std::string & msg) {
    std::cout<<msg<<std::endl;
}

std::string File::getFileURL() {
    return std::string(path.string());
}

void File::loadSegments() {
    std::stringstream str;
    file.open(path.string());

    while(str<< file.rdbuf());

    //start segmenting the file
    std::string content(str.str());
    int index = 0;
    while(index < content.size()){
        std::shared_ptr<File::FileChunk> chunk;
        chunk.reset(new FileChunk());
        chunk->segmentNumber = this->lastSegment++;

        for(int i = 0 ; i < this->segmentSize && index< content.size();i++,index++){
            chunk->buff.push_back(content.c_str()[i]);
        }
        this->chunks.push_back(chunk);
        //std::cout<<chunks[lastSegment-1]->buff<<std::endl;
    }

    areLoaded = true;
}

File::File(const boost::filesystem::path &p, unsigned int segmentSize) {
    //we now check the existence of the file
    this->path = p;
    if(!boost::filesystem::exists(p)){
        log("file ****"+p.string() +"**** doesnt exists");
        std::terminate();
    }if(!boost::filesystem::is_regular(p)){
        log("The path***"+p.string()+" is a directory");
        std::terminate();
    }
    this->fileSize = (unsigned int) boost::filesystem::file_size(p);
    lastSegment = 0;
    areLoaded = false;
    this->segmentSize = segmentSize;
}

unsigned int File::getFileSize() const {
    return fileSize;
}

std::shared_ptr<File::FileChunk> File::getChunk(unsigned int index) {
    if(index< 0)
        return nullptr;
    if(index >= lastSegment)
        return nullptr;
    if(!areLoaded)
        loadSegments();
    areLoaded = true;
    return this->chunks.at(index);
}

unsigned int File::getChunkListSize() {
    if(! areLoaded)
        loadSegments();
    areLoaded = true;
    return (unsigned int) this->chunks.size();
}
