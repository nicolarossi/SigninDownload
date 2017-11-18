/*
 * cindexpage.h
 *
 *  Created on: 18 Nov 2017
 *      Author: nop
 */

#ifndef SRC_CINDEXPAGE_H_
#define SRC_CINDEXPAGE_H_
#include <string>
using namespace std;
namespace singledownload {

    class cindexpage {
        public:
            cindexpage();

            void generate_hash_url(std::string const & email,std::string &hash);
            bool insert_into_db(std::string const & name,std::string const & surname,std::string const & email,
                    std::string & hash);

            bool send_email(std::string const & name,std::string const & surname,std::string const & email);
            virtual ~cindexpage();
    };

} /* namespace singledownload */

#endif /* SRC_CINDEXPAGE_H_ */
