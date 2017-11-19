/*
 * serve_asset.cpp
 *
 *  Created on: 03 feb 2017
 *      Author: nop
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>


extern "C" {
#include <http.h>
#include <kore.h>
#include "log.h"
}
#include <boost/filesystem.hpp>

#include "serve_asset.h"
#include "configuration.h"

namespace fs = boost::filesystem;
using namespace std;

using namespace singledownload;


// NOTE: a GET / is redirected to GET /index.html
extern "C" int serve_asset(struct http_request *req) {
    http_populate_get(req);
    int rv;

    //--- TODO Management if-modified-since

    //--- TODO In the configuration file -> Hardening req->path
    rv = 1;

    if (rv) {
        string filename ;

        if (string("/") != req->path ){
            filename = configuration::get().HTML_DIR + req->path;
        } else {
            filename = configuration::get().HTML_DIR + "index.html";
        }

        return _internal_serve_file(req,filename);

    } else {
        http_response_header(req, "location", "URL_TO_REDIRECT");
        http_response(req, 302, NULL, 0);
        return KORE_RESULT_ERROR;
    }
}


int _internal_serve_file(struct http_request*req, std::string const &filename) {

    fs::path lib_path(filename);

    if ( ( ! fs::exists(lib_path)) || ( ! fs::is_regular_file(lib_path))) {
        err("Error  [%s] file not present or it is directory ", filename.c_str());
        http_response(req, 404, NULL, 0);
        return KORE_RESULT_ERROR;
    }
    stringstream sout;

    /* Read template */
    ifstream ifs(filename, ios::binary | ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    if (pos <= 0) {
        err("Error reading file [%s]", filename.c_str());
        http_response(req, 404, NULL, 0);
        return KORE_RESULT_ERROR;
    }
    // What happens if the OS supports really big files.
    // It may be larger than 32 bits?
    // This will silently truncate the value/
    int length = pos;

    // Manuall memory management.
    char *pChars = new char[length + 1];
    ifs.seekg(0, ios::beg);
    ifs.read(pChars, length);

    pChars[length] = 0;
    ifs.close();

    http_response_header(req, "content-type",
            identify_content_type(filename, pChars, length));
    http_response(req, 200, pChars, length);
    delete[] pChars;
    return (KORE_RESULT_OK);
}

