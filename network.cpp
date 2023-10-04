#include "myhead.h"

#include <cpr/cpr.h>

std::tuple<int, std::string> net_GETNew(std::string url) {
    auto rep = cpr::Get(cpr::Url{url});
    return std::make_tuple((int)rep.error.code, rep.text);
}

std::tuple<int, std::string> net_GET(std::string url) {
    return net_GETNew(domainName + url);
}
