/*
 * configuration.h
 *
 *  Created on: 18 Nov 2017
 *      Author: nop
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_
#include <string>
#include <sstream>
#include <vector>

using namespace std;

namespace singledownload {

    class configuration {
        private:
            configuration();
        public:
            std::string HTML_DIR{"./html/"};
            std::string FROM{"nicola.rossi@gmail.com"};
            std::vector<std::string> CC={"nicola.rossi+cc@gmail.com"};
            std::string MAIL_BODY{""};
            std::string mail_server_address{"smtps://smtp.gmail.com:587"};


            static configuration &get_instance() {
                static configuration instance;
                return instance;
            }

             stringstream  get_mail_body(
                    string const&name,
                    string const&surname,
                    string const&hash
            ){
                stringstream ss;

                ss<<"Hello "<<name<<","<<endl;

                ss<<" click here to download your happiness"<<endl;
                ss<<" http://127.0.0.1:8888/index.html?hash="<<hash<<endl;

                ss<<" Bye bye "<<endl;

                return ss;
            }
    };

} /* namespace singledownload */

#endif /* SRC_CONFIGURATION_H_ */
