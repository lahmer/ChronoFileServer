//
// Created by lahmer on 2/21/17.
//

#include <iostream>
#include "Logger/Logger.h"
#include "FileServer/File.h"
#include "FileServer/FileServer.h"

int main(){
    //Logger::InitializeLogger();
    //boost::filesystem::path p("/home/lahmer/main.py");
    //File file(p,250);
    //file.loadSegments();
    FileServer server("/home/lahmer/Desktop/temp");
    std::shared_ptr<File> file = server.getFile("/home/lahmer/Desktop/temp/bestRoute-0-ghBW_HighCon_0.top");
    for (int i = 0; i < file->getChunkListSize();++i) {
        std::cout<<file->getChunk(i)->buff;
    }
    std::cout<<"Hello, World!"<<std::endl;
    return 0;
}