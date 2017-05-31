
#include "ieee1888Main.h"


IEEE1888Main::IEEE1888Main() {
}

IEEE1888Main::~IEEE1888Main() {
}
ieee1888_transport* IEEE1888Main::makeFetchLatestContext(std::vector<std::string>& pointIds) {
    int count=pointIds.size();
    ieee1888_transport* rq_transport=ieee1888_mk_transport();
    ieee1888_header* rq_header=ieee1888_mk_header();
    ieee1888_query* rq_query=ieee1888_mk_query();
    ieee1888_key* rq_key=ieee1888_mk_key_array(count);
    for(int i=0;i<count;++i){
        rq_key[i].id=ieee1888_mk_string(pointIds[i].c_str());
        rq_key[i].attrName=ieee1888_mk_attrNameType("time");
        rq_key[i].select=ieee1888_mk_selectType("maximum");
    }
    rq_query->id=ieee1888_mk_new_uuid();
    rq_query->type=ieee1888_mk_queryType("storage");
    rq_query->key=rq_key;
    rq_query->n_key=count;
    rq_header->query=rq_query;
    rq_transport->header=rq_header;
    return rq_transport;
}
ieee1888_body* IEEE1888Main::doFetch(ieee1888_transport* rq_transport, std::string& from) {
    int err;
    ieee1888_transport* rs_transport=ieee1888_client_query(rq_transport,from.c_str(),0,&err);
    ieee1888_destroy_objects((ieee1888_object*)rq_transport);
    free(rq_transport);
    ieee1888_body* failed=NULL;
    if(rs_transport==NULL){
        return failed;
    }

    ieee1888_header* rs_header=rs_transport->header;
    if(rs_header==NULL){
        ieee1888_destroy_objects((ieee1888_object*)rs_transport);
        free(rs_transport);
        return failed;
    }

    if(rs_header->OK==NULL){
        if(rs_header->error==NULL){
            // std::cout << "FATAL: neither OK nor error was put in the response.\n";
        }
        ieee1888_destroy_objects((ieee1888_object*)rs_transport);
        free(rs_transport);
        return failed;
    }
    return rs_transport->body;

    // ieee1888_destroy_objects((ieee1888_object*)rs_transport);
    // free(rs_transport);
    // return IEEE1888_FETCH_SUCCESS;
}
void IEEE1888Main::destroy(ieee1888_object* obj) {
    ieee1888_destroy_objects(obj);
    free(obj);
}
