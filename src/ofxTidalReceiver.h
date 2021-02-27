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
  // find a value using it's name, and return a pointer to it
  template <typename T>
  ofxTidalValue_t<T> *getValueByName(const std::string &name);

  // store all of the values
  std::vector<ofxTidalValue *> values;
  ofxOscReceiver osc;
  std::string path;
};

// templated methods have to live in .h

template <typename T>
void ofxTidalReceiver::add(const std::string &name, const T &value) {
  values.push_back(new ofxTidalValue_t<T>(name, value));
}

template <typename T> T ofxTidalReceiver::get(const std::string &name) {
  return getValueByName<T>(name)->getValue();
}

template <typename T>
ofxTidalValue_t<T> *ofxTidalReceiver::getValueByName(const std::string &name) {
  for (const auto &v : values) {
    if (name == v->getName()) {
      ofxTidalValue *tb = v;            // t base
      ofxTidalValue_t<T> *td = nullptr; // t derived
      td = dynamic_cast<ofxTidalValue_t<T> *>(tb);
      return td;
    }
  }
  return NULL;
}
