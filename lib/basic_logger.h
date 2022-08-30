#ifndef BASIC_LOGGER_H
#define BASIC_LOGGER_H
#include <iostream>


#define MODULE_NAME "GR-GRAND"
#define LOGV(...) \
  __android_log_print(ANDROID_LOG_VERBOSE, MODULE_NAME, __VA_ARGS__)
#define LOGD(...) \
  __android_log_print(ANDROID_LOG_DEBUG, MODULE_NAME, __VA_ARGS__)
#define LOGI(...) \
  __android_log_print(ANDROID_LOG_INFO, MODULE_NAME, __VA_ARGS__)
#define LOGW(...) \
  __android_log_print(ANDROID_LOG_WARN, MODULE_NAME, __VA_ARGS__)
#define LOGE(...) \
  __android_log_print(ANDROID_LOG_ERROR, MODULE_NAME, __VA_ARGS__)
#define LOGF(...) \
  __android_log_print(ANDROID_LOG_FATAL, MODULE_NAME, __VA_ARGS__)

#define GR_DEBUG(name, msg) LOGD(name,msg)
#define GR_INFO(name, msg) LOGI(name,msg)
#define GR_NOTICE(name, msg) LOGW(name,msg)
#define GR_WARN(name, msg) LOGW(name,msg)
#define GR_ERROR(name, msg) LOGE(name,msg)
#define GR_ALERT(name, msg) LOGE(name,msg)
#define GR_CRIT(name, msg) LOGE(name,msg)
#define GR_FATAL(name, msg) LOGF(name,msg)
#define GR_EMERG(name, msg) LOGF(name,msg)
#define GR_ERRORIF(name, cond, msg) if((cond)) LOGE(name,msg)
#define GR_ASSERT(name, cond, msg) if(!(cond)) LOGE(name,msg) assert(cond)
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