//
//  note.h
//  avsys_final2
//
//  Created by Alexandra Samuel on 4/25/13.
//
//

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBlobTracker.h"
#include "ofxOsc.h"




class note: {
    
public:
    
    //methods
    
    void colorVel(ofxCvContourFinder);
    void colorVelSmooth();
    void sendColorVel(string);

    
    //constructor
    
    note();
    
    //variables

    //color
    
    
    //velocity
    int posDiffX;
    int posDiffY;
    int velocity;
    int velocitySmoothed = 0;
    ofPoint pos;
    ofVec3f v1;

    //message
    string activeColor;
    int slowYourRoll = 0;
    ofxOscSender sender;
    
};