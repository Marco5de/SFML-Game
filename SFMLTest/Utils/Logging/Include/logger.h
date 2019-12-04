//
// Created by marco on 03.12.19.
//

//based on https://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505

#ifndef SFMLTEST_LOGGER_H
#define SFMLTEST_LOGGER_H


#include "log.h"

//#define LOGGING_FILE

//todo overwrite operator << instead of function call

#ifdef LOGGING_FILE
    static logging::logger<logging::file_log_policy> log_inst("output.log");
#else
    static logging::logger<logging::console_log_policy> log_inst("output.log");
#endif


#ifdef LOGGING_LEVEL_1

    #define LOG log_inst.print<logging::logmsg_type::debug>
    #define LOG_ERR log_inst.print<logging::logmsg_type::error>
    #define LOG_WARN log_inst.print<logging::logmsg_type::warning>

#else

    #define LOG(...)
    #define LOG_ERR(...)
    #define LOG_WARN(...)

#endif

#ifdef LOGGING_LEVEL_2

    #define ELOG log_inst.print<logging::logmsg_type::debug>
    #define ELOG_ERR log_inst.print<logging::logmsg_type::error>
    #define ELOG_WARN log_inst.print<logging::logmsg_type::warning>

#else

    #define ELOG(...)
    #define ELOG_ERR(...)
    #define ELOG_WARN(...)

#endif
#endif //SFMLTEST_LOGGER_H
