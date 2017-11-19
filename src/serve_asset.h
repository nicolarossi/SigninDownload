#include <string.h>
#include "identify_content_type.h"

extern "C" int serve_asset(struct http_request *req);

int _internal_serve_file(struct http_request*req, std::string const &DIR);
