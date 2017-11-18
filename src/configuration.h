/*
 * configuration.h
 *
 *  Created on: 18 Nov 2017
 *      Author: nop
 */

#ifndef SRC_CONFIGURATION_H_
#define SRC_CONFIGURATION_H_
#include <string>

namespace singledownload {

    class configuration {
        private:
            configuration();
        public:
            std::string HTML_DIR{"./html/"};

            static configuration &get() {
                static configuration instance;
                return instance;
            }
    };

} /* namespace singledownload */

#endif /* SRC_CONFIGURATION_H_ */
