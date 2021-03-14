#include "ofxTidalReceiver.h"

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

        if (name == "cycle") {
          cycle = msg.getArgAsFloat(i + 1);
          break;
        }

        switch (typeStr[i + 1]) {
        case 'i':
          replace(name, (float)msg.getArgAsInt(i + 1));
          break;
        case 'f':
          replace(name, msg.getArgAsFloat(i + 1));
          break;
        }
      }
    }
  }
}

void ofxTidalReceiver::add(const std::string &name) { add(name, 0.0f); }

void ofxTidalReceiver::add(const std::string &name, const float &value) {
  values.push_back(std::make_pair(name, value));
}

float ofxTidalReceiver::get(const std::string &name) {
  for (auto &v : values) {
    if (v.first == name) {
      return v.second;
    }
  }
  return 0.0f;
}

float ofxTidalReceiver::getCycle() { return cycle; }

void ofxTidalReceiver::replace(const std::string &name, const float &value) {
  for (auto &v : values) {
    if (v.first == name) {
      v.second = value;
      break;
    }
  }
}
