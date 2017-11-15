#include <nan.h>
#include "ieee1888Main.h"
void fetch(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // v8::Isolate *isolate = info.GetIsolate();
  if (info.Length() <2 || !info[0]->IsObject()) {
    Nan::ThrowTypeError("Wrong arguments or wrong length");
    return;
  }
  v8::Local<v8::Object> ret=Nan::New<v8::Object>();
  v8::Local<v8::Array> opt=v8::Local<v8::Array>::Cast(info[0]);
  // v8::Local<v8::Array> optKeys = opt->GetOwnPropertyNames();
  std::vector<std::string> pointIds;
  std::string from(*v8::String::Utf8Value(info[1]));
  for (int i = 0; i < opt->Length(); ++i) {
      v8::Local<v8::Value> key = opt->Get(i);
      pointIds.push_back(std::string(*v8::String::Utf8Value(key)));
  }
  ieee1888_body* rs_body=IEEE1888Main::doFetch(IEEE1888Main::makeFetchLatestContext(pointIds),from);
  if(rs_body==NULL){
    Nan::ThrowError("network error occured");
    return;
  }
  ieee1888_point* rs_point=rs_body->point;
  if(rs_body->n_point<=0 || rs_point==NULL){
      IEEE1888Main::destroy((ieee1888_object*)rs_body);
      Nan::ThrowError("rs body empty");
      return;
  }
  for (int i=0; i<rs_body->n_point; ++i){
      v8::Local<v8::Value> id=Nan::New(rs_point[i].id).ToLocalChecked();
      if (!ret->Has(id))
          ret->Set(id, Nan::New<v8::Array>());
      v8::Local<v8::Array> ary=v8::Local<v8::Array>::Cast(ret->Get(id));
      int tail=ary->Length();
      ieee1888_value* rs_value=rs_point[i].value;
      int rs_n_value=rs_point[i].n_value;
      if(rs_n_value>0 && rs_value!=NULL){
          ieee1888_value* target_value=&rs_value[rs_n_value-1];
          v8::Local<v8::Object> valObj=Nan::New<v8::Object>();
          valObj->Set(Nan::New("time").ToLocalChecked(), Nan::New(target_value->time).ToLocalChecked());
          valObj->Set(Nan::New("content").ToLocalChecked(), Nan::New(target_value->content).ToLocalChecked());
          ary->Set(tail, valObj);
      }
  }
  IEEE1888Main::destroy((ieee1888_object*)rs_body);
  info.GetReturnValue().Set(ret);

}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("fetch").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(fetch)->GetFunction());
}

NODE_MODULE(ieee1888, Init)
