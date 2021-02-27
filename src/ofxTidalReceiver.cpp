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
    osc.getNextMessage(&msg);
    if (msg.getAddress() == path) {
      // a str like 'ifs' for 'i'nt, 'f'loat, 's'tring
      const auto typeStr = msg.getTypeString();
      // i+=2 because every other arg *should* be the name
      for (std::size_t i = 0; i < typeStr.length(); i += 2) {
        const auto name = msg.getArgAsString(i);
        switch (typeStr[i + 1]) {
        case 'i':
          updateValue(name, msg.getArgAsInt(i + 1));
          break;
        case 'f':
          updateValue(name, msg.getArgAsFloat(i + 1));
          break;
        }
      }
    }
  }
}
