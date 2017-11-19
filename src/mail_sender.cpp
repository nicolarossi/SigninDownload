/*
 * mail_sender.cpp
 *
 *  Created on: 19 Nov 2017
 *      Author: nop
 */

#include <iostream>
#include <sstream>
#include "mail_sender.h"
using namespace std;

namespace singledownload {

    mail_sender::mail_sender(){

    }
    mail_sender::~mail_sender() {
        // TODO Auto-generated destructor stub
    }


    extern "C" {
        size_t _payload_source(void *ptr, size_t size, size_t nmemb,
                void *userp) {

            upload_status_t *upload_ctx = (struct upload_status *) userp;

            if ((size == 0) || (nmemb == 0) || ((size * nmemb) < 1)) {
                return 0;
            }

            if (static_cast<size_t>(upload_ctx->lines_read) < mail_sender::get_instance().get_payload_text().size()) {

                vector<string> &v=mail_sender::get_instance().get_payload_text();
                std::string data =v[upload_ctx->lines_read];
                data += "\r\n";
                size_t len = data.size();
                memcpy(ptr, data.c_str(), len);
                upload_ctx->lines_read++;
                return len;
            } else {
                return 0;
            }
        }
    };


    void mail_sender::_init_payload_text(string const&from, string const&to, stringstream &body) {
        payload_text.clear();

        payload_text.emplace_back(string("From: ")+from);
        payload_text.emplace_back(string("To: ")+to);
        payload_text.emplace_back("Subject: Ciao ");

        string row;
        while(std::getline(body, row, '\n')) {
            payload_text.emplace_back(row);
        }
    }

    bool mail_sender::send(string const& url_smtp_server,string const& from, string const& to,
            vector<string> const&cc, stringstream &body) {
        // TODO
        //https://curl.haxx.se/libcurl/c/smtp-mail.html
        //https://support.google.com/a/answer/176600?hl=it
        CURL *curl;
        CURLcode res = CURLE_OK;
        struct curl_slist *recipients = NULL;
        struct upload_status upload_ctx;

        act(" Try to send an email to [%s] ", to.c_str());

        upload_ctx.lines_read = 0;

        curl = curl_easy_init();
        if (curl) {
            /* Set username and password */
            curl_easy_setopt(curl, CURLOPT_USERNAME, "nicola.rossi@gmail.com");
            curl_easy_setopt(curl, CURLOPT_PASSWORD, "");

            curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); /* TODO review in production environment*/
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0); /* TODO review in production environment*/

            curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
            /* This is the URL for your mailserver */

            debug("using url [%s]", url_smtp_server.c_str());
            curl_easy_setopt(curl, CURLOPT_URL, url_smtp_server.c_str());

            /* Note that this option isn't strictly required, omitting it will result
             * in libcurl sending the MAIL FROM command with empty sender data. All
             * autoresponses should have an empty reverse-path, and should be directed
             * to the address in the reverse-path which triggered them. Otherwise,
             * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
             * details.
             */
            curl_easy_setopt(curl, CURLOPT_MAIL_FROM,from.c_str());

            debug("from [%s]", from.c_str());

            /*
             *  Create the payload_source vector
             * */

            /* Add two recipients, in this particular case they correspond to the
             * To: and Cc: addressees in the header, but they could be any kind of
             * recipient. */
            recipients = curl_slist_append(recipients, to.c_str());

            for (auto const& recip: cc ) {
                debug(" CC : [%s]",recip.c_str());
                recipients = curl_slist_append(recipients,
                        recip.c_str());
            }
            curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

            /* We're using a callback function to specify the payload (the headers and
             * body of the message). You could just use the CURLOPT_READDATA option to
             * specify a FILE pointer to read from. */

            _init_payload_text(from,to,body);


            curl_easy_setopt(curl, CURLOPT_READFUNCTION,_payload_source);
            curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

            debug("/* Send the message */");
            res = curl_easy_perform(curl);

            debug("res =%d", res);

            /* Check for errors */
            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n",
                        curl_easy_strerror(res));
            }

            /* Free the list of recipients */
            curl_slist_free_all(recipients);

            /* curl won't send the QUIT command until you call cleanup, so you should
             * be able to re-use this connection for additional messages (setting
             * CURLOPT_MAIL_FROM and CURLOPT_MAIL_RCPT as required, and calling
             * curl_easy_perform() again. It may not be a good idea to keep the
             * connection open for a very long time though (more than a few minutes
             * may result in the server timing out the connection), and you do want to
             * clean up in the end.
             */
            curl_easy_cleanup(curl);
        }

        return ((int) res == CURLE_OK);
    }
} /* namespace singledownload */
