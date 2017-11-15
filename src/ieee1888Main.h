#ifndef IEEE1888MAIN_H
#define IEEE1888MAIN_H

#include "nan.h"
extern "C" {
#include "ieee1888.h"
}

class KeyValMap {
    public:
        std::string key;
        std::string value;
        KeyValMap(std::string, std::string);
};

class IEEE1888Main {
    public:

        static ieee1888_transport* makeFetchLatestContext(std::vector<std::string>& pointId);
        static ieee1888_body* doFetch(ieee1888_transport*, std::string& from);
        static void destroy(ieee1888_object* obj);
    private:
        IEEE1888Main();
        ~IEEE1888Main();
};

#endif
