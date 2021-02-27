#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // listen for messages with the address "/play", on port 5060
  tidal.setup(5060, "/play");

  // add "opacity" to the list of values to store, and set
  // it's default to 255.0 (it will be 255.0 until a new
  // message is received)
  tidal.add("opacity", 255.0f);
  tidal.add("posX", 150.0f);
  tidal.add("posY", 150.0f);
  tidal.add("scale", 100);

  // you can add as many values as you like, currently only
  // of type float or int.

  ofBackground(ofColor::white);
}

//--------------------------------------------------------------
void ofApp::update() {
  // check for new messages
  tidal.update();
}

//--------------------------------------------------------------
void ofApp::draw() {

  // use tidal.get to store the value of "opacity" in a
  // variable called opacity. currently you have to pass
  // the type of your value when calling tidal.get, in
  // this case it is a float, so we do <float>.
  float opacity = tidal.get<float>("opacity");

  // set the color to a nice blue, and use opacity to
  // control the opacity of future shapes.
  ofSetColor(ofColor::blue, opacity);

  // again use tidal.get, this time to construct an
  // ofVec2f of x "posX", and y "posY". we still use
  // <float> here because ofVec2f is just two floats.
  ofVec2f pos = ofVec2f(tidal.get<float>("posX"), tidal.get<float>("posY"));

  // use our pos and another tidal.get to draw a circle
  // at position = pos, with size = scale.
  ofDrawCircle(pos, tidal.get<int>("scale"));
}
