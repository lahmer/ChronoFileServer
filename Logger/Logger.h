//
// Created by lahmer on 2/21/17.
//

#ifndef FILESERVER_LOGGER_H
#define FILESERVER_LOGGER_H

#include <blackhole/attribute.hpp>
#include <blackhole/attributes.hpp>
#include <blackhole/config/json.hpp>
#include <blackhole/extensions/facade.hpp>
#include <blackhole/extensions/writer.hpp>
#include <blackhole/registry.hpp>
#include <blackhole/root.hpp>

using namespace blackhole;

/// As always specify severity enumeration.
enum severity {
    debug   = 0,
    info    = 1,
    warning = 2,
    error   = 3
};


class Logger {
public :
    static void InitializeLogger();
};


#endif //FILESERVER_LOGGER_H
