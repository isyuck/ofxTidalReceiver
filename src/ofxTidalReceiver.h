#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxTidalValue.h"

class ofxTidalReceiver {
public:
  ofxTidalReceiver();
  bool setup(const int &port);
  bool setup(const int &port, const std::string &path);
  // check for new messages
  void update();
  // add a new value with name & default
  template <typename T> void add(const std::string &name, const T &value);
  // get a value by it's name
  template <typename T> T get(const std::string &name);

private:
  // find a value with name, replace it's value with value
  template <typename T>
  void updateValue(const std::string &name, const T value);

  ofxOscReceiver osc;
  std::string path;
  std::vector<ofxTidalValue *> values;
};

// templated methods have to live in .h

template <typename T>
void ofxTidalReceiver::add(const std::string &name, const T &value) {
  values.push_back(new ofxTidalValue_t<T>(name, value));
}

template <typename T> T ofxTidalReceiver::get(const std::string &name) {
  for (const auto &v : values) {
    if (name == v->getName()) {
      ofxTidalValue *tb = v;
      ofxTidalValue_t<T> *td = nullptr;
      td = dynamic_cast<ofxTidalValue_t<T> *>(tb);
      return td->getValue();
    }
  }
  return NULL;
}

template <typename T>
void ofxTidalReceiver::updateValue(const std::string &name, const T value) {
  for (const auto &v : values) {
    if (name == v->getName()) {
      ofxTidalValue *tb = v;
      ofxTidalValue_t<T> *td = nullptr;
      td = dynamic_cast<ofxTidalValue_t<T> *>(tb);
      td->setValue(value);
      return;
    }
  }
}
