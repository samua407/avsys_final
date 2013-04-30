//
//  note.h
//  avsys_final2
//
//  Created by Alexandra Samuel on 4/25/13.
//
//

#pragma once


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBlobTracker.h"
#include "ofxOsc.h"



//class superSmartOfImage : public ofImage {
//    
//  // all of ofImage
//    
//    void mySuperFunction(){
//        
//    }
//    
//};


class note   {
    
public:
    
    //methods
    
    //ofxCvColorImage img;
    
    int colorVel(ofxCvContourFinder &_cont, string activeColor);

    
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
    ofxOscSender sender;
    
};