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
        File::FileChunk chunk;
        chunk.segmentNumber = this->lastSegment++;

        chunk.buff = new unsigned char[this->segmentSize];
        for(int i = 0 ; i < this->segmentSize && index< content.size();i++,index++){
            chunk.buff[i] = (unsigned char) content.c_str()[index];
            std::cout<<i<<std::endl;
        }
        std::cout<<"Here"<<std::endl;
        this->chunks[lastSegment++] = chunk;
    }
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
