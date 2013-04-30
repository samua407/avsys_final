#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBlobTracker.h"
#include "ofxOsc.h"
#include "note.h"

#define HOST "localhost"
#define PORT 12345



class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void mousePressed(int x, int y, int button);
    
    ofVideoGrabber movie;
    
    ofxCvColorImage rgb,hsb;
    ofxCvGrayscaleImage hue, sat,bri,filteredPink, filteredBlue, filteredGreen, filteredRed;
    ofxCvContourFinder contoursPink, contoursBlue, contoursGreen, contoursRed;
    
    ofxBlobTracker  tracker;
    
    int findHue;
    int pink;
    int blue;
    int green;
    int red;
    
    int w, h;
    int defineHue;
    
    ofPoint posPink;
    ofPoint newPinkPos;
    float posPinkSpeed;
    
    //declare new objects
    note pinkNote;
    note blueNote;
    note greenNote;
    note redNote;

    //message
    ofxOscSender sender;
    int slowYourRoll = 0;
    int velocitySmoothed;


};
