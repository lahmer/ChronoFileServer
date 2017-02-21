//
// Created by lahmer on 2/21/17.
//

#include <boost/filesystem/operations.hpp>
#include <dirent.h>
#include "FileServer.h"

FileServer::FileServer(const std::string &directory) {
    boost::filesystem::path p(directory);
    path= p;
    if(boost::filesystem::exists(p) && boost::filesystem::is_directory(p)){
        payloadSize = 255;
        loadDirectory();
    } else{
        std::cout<<p << "   isn't valid directory"<<std::endl;
    }

}

void FileServer::loadDirectory() {

    std::vector<boost::filesystem::path> v;
    DIR* dir = opendir(path.string().c_str());
    struct dirent *epdf;
    while (epdf = readdir(dir)){
        if(strcmp(epdf->d_name,".") == 0)
            continue;
        if(strcmp(epdf->d_name,"..") == 0)
            continue;
        boost::filesystem::path pth(path.string() +std::string("/") +std::string(epdf->d_name));
        if(boost::filesystem::is_directory(pth))
            continue;
        v.push_back(pth);
    }
    //now we create a file object for each one of them
    for(auto it : v){
        std::shared_ptr<File> file;
        file.reset(new File(it,payloadSize));
        this->fileList[it.string()] = file;
    }
    return;
}

std::shared_ptr<File> FileServer::getFile(const std::string &file) {
    return this->fileList[file];
}
