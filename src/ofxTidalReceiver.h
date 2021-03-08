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

//---------------------------------------------------------------

ofxTidalReceiver::ofxTidalReceiver() {}

bool ofxTidalReceiver::setup(const int &port = 7788) { return setup(port); }
bool ofxTidalReceiver::setup(const int &port = 7788,
                             const std::string &path = "/dirt/play") {

  const bool listening = osc.setup(port);
  this->path = path;
  return listening;
}

void ofxTidalReceiver::update() {
  while (osc.hasWaitingMessages()) {
    ofxOscMessage msg;
    osc.getNextMessage(msg);
    if (msg.getAddress() == path) {
      // a str like 'ifs' for 'i'nt, 'f'loat, 's'tring
      const auto typeStr = msg.getTypeString();
      // i+=2 because every other arg *should* be the name
      for (std::size_t i = 0; i < typeStr.length(); i += 2) {
        const auto name = msg.getArgAsString(i);
        switch (typeStr[i + 1]) {
        case 'i':
          getValueByName<int>(name)->setValue(msg.getArgAsInt(i + 1));
          break;
        case 'f':
          getValueByName<float>(name)->setValue(msg.getArgAsFloat(i + 1));
          break;
        }
      }
    }
  }
}

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
