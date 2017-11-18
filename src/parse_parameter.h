#ifndef PARSE_PARAMETER_H
extern "C" {
#include <http.h>
#include <kore.h>
#include <log.h>
}
#include <string>
#include <sstream>

#define PARSE_INTEGER_PARAMETER(PAR,rv)\
    int PAR; \
    if (http_argument_get_int32(req, #PAR ,&PAR)==KORE_RESULT_OK) {;\
        debug( "%s Parameter %s:%d [%d]",#PAR,__FILE__,__LINE__,PAR);\
        rv=1;\
    } else {\
        std::stringstream ss;\
        ss<< ""<<#PAR <<" is not validated ";\
        std::string m=ss.str();\
        err(m.c_str());\
        rv=0;\
    }

#define PARSE_DOUBLE_PARAMETER(PAR,rv)\
    double PAR; \
    char*  PAR ## _tmp ; \
    if (http_argument_get_string(req, #PAR ,&(PAR ## _tmp))==KORE_RESULT_OK) {;\
        debug( "%s Parameter %s:%d [%s]",#PAR,__FILE__,__LINE__,PAR ## _tmp );\
        PAR=atof(PAR ## _tmp);\
        rv=1; \
    } else {\
        std::stringstream ss;\
        ss<< ""<<#PAR <<" is not validated ";\
        std::string m=ss.str();\
        err(m.c_str());\
        rv=0;\
    }

#define PARSE_STRING_PARAMETER(PAR,rv) \
    char*  PAR ## _tmp ; \
    std::string PAR;\
    if (http_argument_get_string(req, #PAR ,&(PAR ## _tmp))==KORE_RESULT_OK) {;\
        debug( "%s Parameter %s:%d [%s]",#PAR,__FILE__,__LINE__,PAR ## _tmp );\
        PAR=std::string(PAR ## _tmp);\
        rv=1; \
    } else {\
        std::stringstream ss;\
        ss<< ""<< #PAR <<" is not validated ";\
        std::string m=ss.str();\
        err(m.c_str());\
        rv=0;\
    }

// TODO delete PAR ## _tmp



#define PARSE_CHAR_STRING_PARAMETER(PAR,rv)\
    char*  PAR ;\
    if (http_argument_get_string(req, #PAR ,&PAR )==KORE_RESULT_OK) {;\
        debug( "%s Parameter %s:%d [%s]",#PAR,__FILE__,__LINE__,PAR );\
        rv=1; \
    } else {\
        std::stringstream ss;\
        ss<< ""<< #PAR <<" is not validated ";\
        std::string m=ss.str();\
        err(m.c_str());\
        rv=0;\
    }



#endif
