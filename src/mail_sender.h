/*
 * mail_sender.h
 *
 *  Created on: 19 Nov 2017
 *      Author: nop
 */

#ifndef SRC_MAIL_SENDER_H_
#define SRC_MAIL_SENDER_H_
#include <curl/curl.h>
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include "log.h"

typedef struct upload_status {
        int lines_read;
} upload_status_t;
namespace singledownload {
    extern "C" {
        size_t _payload_source(void *ptr, size_t size,
                size_t nmemb, void *userp);
    }
    class mail_sender {
                friend size_t _payload_source(void *ptr, size_t size,
                        size_t nmemb, void *userp);

             std::vector<std::string> payload_text;
            /**/
            upload_status_t upload_status = { 0 };
         //   std::string url_smtp;

            // TODO extern "C"


            void _init_payload_text(std::string const&from,
                    std::string const&to, std::stringstream &body);
            mail_sender() ;

        public:
            virtual ~mail_sender();
            bool send(std::string const& url_smtp_server, std::string const& from, std::string const& to,
                    std::vector<std::string> const&cc, std::stringstream &body);

            static mail_sender& get_instance() {
                static mail_sender instance;
                return instance;
            }



             std::vector<std::string>& get_payload_text()  {
                return payload_text;
            }
    };

} /* namespace singledownload */

#endif /* SRC_MAIL_SENDER_H_ */
