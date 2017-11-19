/*
 * cindexpage.cpp
 *
 *  Created on: 18 Nov 2017
 *      Author: nop
 */

#include "cindexpage.h"

namespace singledownload {

    cindexpage::cindexpage() {
        // TODO Auto-generated constructor stub

    }

    void cindexpage::generate_hash_url(const std::string& email,
            std::string& hash) {
        // TODO
        hash="hash_"+email;
    }

    bool cindexpage::insert_into_db(const std::string& name,
            const std::string& surname, const std::string& email,
            std::string& hash) {
        // TODO
        return true;
    }

    bool cindexpage::send_email(const std::string& name,
            const std::string& surname, const std::string& email) {
        // TODO
        //https://curl.haxx.se/libcurl/c/smtp-mail.html
        return true;
    }

    cindexpage::~cindexpage() {
        // TODO Auto-generated destructor stub
    }

} /* namespace singledownload */
