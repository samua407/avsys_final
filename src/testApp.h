#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBlobTracker.h"
#include "ofxOsc.h"
#include "note.h"


class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void mousePressed(int x, int y, int button);
    
    ofVideoGrabber movie;
    
    ofxCvColorImage rgb,hsb;
    ofxCvGrayscaleImage hue, hue2,sat,bri,filtered, filtered2;
    ofxCvContourFinder contours, c2;
    
    ofxBlobTracker  tracker;
    
    int findHue;
    int orange;
    int blue;
    
    int w, h;
    int defineHue;
    
    ofPoint pos;
    ofPoint newPos;
    
    float posSpeed;
    
};
