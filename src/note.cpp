

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxBlobTracker.h"
#include "ofxOsc.h"
#include "note.h"

note::note(){
//    posDiffX = 0;
//    int posDiffY;
//    int velocity;
    velocitySmoothed = 10;

//    ofVec3f v1;

//    //message
//    string activeColor;
//    int slowYourRoll = 0;
}

//------------
int note::colorVel(ofxCvContourFinder &contours, string activeColor){
    
    for (int i=0; i<contours.nBlobs; i++) {
        
        pos.x = contours.blobs[i].centroid.x;
        pos.y = contours.blobs[i].centroid.y;
                
        posDiffX = (v1.x - pos.x);
        posDiffY = (v1.y - pos.y);
        velocity = sqrt( powf(posDiffX,2) + powf(posDiffY,2));
        
        if (velocity < 50){
               
            velocitySmoothed = 0.98 * velocitySmoothed + 0.02 * velocity;
            //return velocitySmoothed;

        }
        
        v1.set(pos.x, pos.y);
        
    }
    
    //cout << velocitySmoothed << endl;
    
    //return 0;
    
}


//------------
//void note::sendColorVel(string activeColor){

//    //if the movement on the x axis of the colored blob is greater than 1 unit (in either direction), then:
//    if(velocitySmoothed > 5){
//        
//        //SEND to OSC the activeColor and posDiffX (velocity on the x axis) (i know theres a way to calculate velocity of vx + vy)
//        
//        if (slowYourRoll % 20 == 0){
//            
//            ofxOscMessage x;
//            x.setAddress("/playtone");
//            x.addFloatArg(velocity);
//            x.addStringArg(activeColor);
//            sender.sendMessage(x);
//            cout << "message sent" << endl;
//            //ofSleepMillis(200);
//        }
//        slowYourRoll++;
//        cout << activeColor << endl;
//
//    }


//}

