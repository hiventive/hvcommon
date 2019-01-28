/**
* Main log call
* l - level
* m - message
*/
#define HV_LOG(l,m) _HV_LOG_##l(m)


/**
* Specialized log calls
* Levels and their effects are listed in https://github.com/muflihun/easyloggingpp and in README.md
*/
#define _HV_LOG_GLOBAL(m) //TODO
#define _HV_LOG_TRACE(m) //TODO
#define _HV_LOG_DEBUG(m) //TODO
#define _HV_LOG_FATAL(m) //TODO
#define _HV_LOG_ERROR(m) //TODO
#define _HV_LOG_WARNING(m) //TODO
#define _HV_LOG_INFO(m) //TODO
#define _HV_LOG_VERBOSE(m) //TODO
//#define _HV_LOG_UNKNOWN(m) //Je ne sais pas à quoi ça sert dans easylogging, probablement pas utile


