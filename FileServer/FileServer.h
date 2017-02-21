//
// Created by lahmer on 2/21/17.
//

#ifndef FILESERVER_FILESERVER_H
#define FILESERVER_FILESERVER_H


#include <string>
#include <map>
#include "File.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>

class FileServer {
public:
    FileServer(const std::string& directory);
    std::shared_ptr<File> getFile(const std::string& file);
private:
    void loadDirectory();

private:
    boost::filesystem::path path;
    std::map<std::string,std::shared_ptr<File>> fileList;
    unsigned int payloadSize;
};


#endif //FILESERVER_FILESERVER_H
