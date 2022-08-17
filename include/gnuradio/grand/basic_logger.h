#ifndef BASIC_LOGGER_H
#define BASIC_LOGGER_H
#include <iostream>
#define GR_DEBUG(name, msg) std::cout<<"DEBUG: "<<msg<<std::endl
#define GR_INFO(name, msg) std::cout<<"INFO: "<<msg<<std::endl
#define GR_NOTICE(name, msg) std::cout<<"NOTICE: "<<msg<<std::endl
#define GR_WARN(name, msg) std::cerr<<"WARN: "<<msg<<std::endl
#define GR_ERROR(name, msg) std::cerr<<"ERROR: "<<msg<<std::endl
#define GR_ALERT(name, msg) std::cerr<<"ERROR: "<<msg<<std::endl
#define GR_CRIT(name, msg) std::cerr<<"ERROR: "<<msg<<std::endl
#define GR_FATAL(name, msg) std::cerr<<"FATAL: "<<msg<<std::endl
#define GR_EMERG(name, msg) std::cerr<<"EMERG: "<<msg<<std::endl
#define GR_ERRORIF(name, cond, msg) if((cond)) std::cerr<<"ERROR: "<<msg<<std::endl
#define GR_ASSERT(name, cond, msg) if(!(cond)) std::cerr<<"ERROR: "<<msg<<std::endl; assert(cond)
#define GR_LOG_DEBUG(logger, msg) std::cout<<"DEBUG: "<<msg<<std::endl
#define GR_LOG_INFO(logger, msg) std::cout<<"INFO: "<<msg<<std::endl
#define GR_LOG_NOTICE(logger, msg) std::cout<<"NOTICE: "<<msg<<std::endl
#define GR_LOG_WARN(logger, msg) std::cerr<<"WARN: "<<msg<<std::endl
#define GR_LOG_ERROR(logger, msg) std::cerr<<"ERROR: "<<msg<<std::endl
#define GR_LOG_ALERT(logger, msg) std::cerr<<"ALERT: "<<msg<<std::endl
#define GR_LOG_CRIT(logger, msg) std::cerr<<"CRIT: "<<msg<<std::endl
#define GR_LOG_FATAL(logger, msg) std::cerr<<"FATAL: "<<msg<<std::endl
#define GR_LOG_EMERG(logger, msg) std::cerr<<"EMERG: "<<msg<<std::endl
#define GR_LOG_ERRORIF(logger, cond, msg) if((cond)) std::cerr<<"ERROR: "<<msg<<std::endl
#define GR_LOG_ASSERT(logger, cond, msg) std::cerr<<"ERROR: "<<msg<<std::endl; assert(cond)
#endif