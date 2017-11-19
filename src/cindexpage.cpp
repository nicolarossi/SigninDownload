/*
 * cindexpage.cpp
 *
 *  Created on: 18 Nov 2017
 *      Author: nop
 */

#include "cindexpage.h"

#include <stdio.h>
#include <string.h>

/**/
#include "configuration.h"
#include "mail_sender.h"
#include "log.h"

namespace singledownload {

    cindexpage::cindexpage() {
        // TODO Auto-generated constructor stub

    }

    void cindexpage::generate_hash_url(const std::string& email,
            std::string& hash) {
        // TODO
        hash = "hash_" + email;
    }

    bool cindexpage::insert_into_db(const std::string& name,
            const std::string& surname, const std::string& email,
            std::string& hash) {
        // TODO
        return true;
    }


    /**/
    bool cindexpage::send_email(
            const std::string& name,
            const std::string& surname, const std::string& email,
            const std::string& hash) {

        configuration &conf=configuration::get_instance();

        stringstream ss=conf.get_mail_body(name,surname,hash);

       return mail_sender::get_instance().send(
               conf.mail_server_address,
               conf.FROM,email,
               conf.CC,
               ss
       );


    }

    cindexpage::~cindexpage() {
        // TODO Auto-generated destructor stub
    }

} /* namespace singledownload */
