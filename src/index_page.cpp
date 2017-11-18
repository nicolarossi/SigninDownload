#include <kore/kore.h>
#include <kore/http.h>
#include "parse_parameter.h"
#include "serve_asset.h"
#include "cindexpage.h"

extern "C" int index_page(struct http_request *);

int validate_and_serve_download(struct http_request *req);

extern "C" int index_page(struct http_request *req) {
    debug("Requesting [%s]",req->path);
    if (req->method == HTTP_METHOD_GET) {
        int rv;
        bool bad_parsing = false;

        http_populate_get(req);
        PARSE_STRING_PARAMETER(hash_email, rv);

        if (rv) { /**/
            // Try to validate the hash_email provided
            if (validate_and_serve_download(req) == KORE_RESULT_OK) {
                return KORE_RESULT_OK;
            }
        }

        // NOTE: a GET / is redirected to GET /index.html

        // In other case return the index page
        serve_asset(req);

    } else if (req->method == HTTP_METHOD_POST) {
        http_populate_post(req);
        int parsing_success;
        PARSE_STRING_PARAMETER(name,parsing_success);
        PARSE_STRING_PARAMETER(surname,parsing_success);
        PARSE_STRING_PARAMETER(email,parsing_success);

        if (parsing_success) {
            std::string url;
            singledownload::cindexpage c;

            c.generate_hash_url(email,url);

            if (c.insert_into_db(name,surname,email,url)) {
                act("Save [%s] in DB",email.c_str());
            } else {
                char text[256];
                sprintf(text,"Internal error [%s:%d]",__FILE__,__LINE__);
                http_response(req,500,text,strlen(text));
                err("ERROR IN SAVE IN DB ");
            }
            if (c.send_email(name,surname,email)) {
                /**/
                act("Mail send to [%s] with URL [%s]",email.c_str(),url.c_str());
            } else {
                char text[256];
                sprintf(text,"Internal error [%s:%d]",__FILE__,__LINE__);
                http_response(req,500,text,strlen(text));
                err("ERROR IN SENDING EMAIL ");
            }

            char text[]="Please check your email";
            http_response(req,200,text,strlen(text));
        } else {
            char text[256];
            sprintf(text,"Internal error [%s:%d]",__FILE__,__LINE__);
            http_response(req,500,text,strlen(text));
            err("ERROR IN SOME PARSING");
            return KORE_RESULT_OK;
        }
    }

    return (KORE_RESULT_OK);
}
