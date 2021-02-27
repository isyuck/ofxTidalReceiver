#pragma once

#include "ofMain.h"

// don't forget to include the addon!
#include "ofxTidalReceiver.h"

class ofApp : public ofBaseApp {

public:
  void setup();
  void update();
  void draw();

  // create an object 'tidal' of type ofxTidalReceiver,
  // this is what will receive OSC messages.
  ofxTidalReceiver tidal;
};
