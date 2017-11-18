/*
 * identify_content_type.cpp
 *
 *  Created on: 03 feb 2017
 *      Author: nop
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include <http.h>
#include <kore.h>
#include "log.h"
}
#include <fstream>
#include "identify_content_type.h"

using namespace std;

bool ends_with(string const& radix, string const &ending) {
    if (radix.length() >= ending.length()) {
        return (0
                == radix.compare(radix.length() - ending.length(),
                        ending.length(), ending));
    } else {
        return false;
    }
}

const char*identify_content_type(string const&filename, char*buff, int len) {
    if (ends_with(filename, ".html")) {
        return "text/html";
    }
    if (ends_with(filename, ".css")) {
        return "text/css";
    }
    if (ends_with(filename, ".js") || ends_with(filename, ".map")) {
        return "application/javascript; charset=utf-8";
    }
    if (ends_with(filename, ".png")) {
        return "image/png";
    }
    if (ends_with(filename, ".jpg")) {
        return "image/jpg";
    }
    if (ends_with(filename, ".jpeg")) {
        return "image/jpeg";
    }

    if (ends_with(filename, ".eot")) {
        return "application/octet-stream";
    }
    if (ends_with(filename, ".svg")) {
        return "image/svg+xml";
    }

    if (ends_with(filename, ".ttf")) {
        return "application/x-font-ttf";
    }

    if (ends_with(filename, ".woff")) {
        return "application/font-woff";
    }

    if (ends_with(filename, ".woff2")) {
        return "application/octet-stream";
    }

    if (ends_with(filename, ".jpeg")) {
        return "application/font-woff";
    }

    if (ends_with(filename, ".ico")) {
        return "image/x-icon";
    }

    /*    if (ends_with(filename,".woff")) {
     return "";
     }
     if (ends_with(filename,".woff2")) {
     return "";
     }*/

    /* TODO implementare mimetype -b nomefile ??? */
    warn("Richiesto di identificare un tipo sconosciuto [%s]",
            filename.c_str());
    return "text/html";
}

