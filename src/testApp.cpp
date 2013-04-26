#include "testApp.h"
#include "note.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);
    
    w = 320;
    h = 240;
    pink = 178; //ORANGE NOW. CHANGE TO CORRECT VALUE
    blue = 105;
    green = 10; //CHANGE TO CORRECT VALUE
    red = 70; //CHANGE TO CORRECT VALUE
    
    movie.initGrabber(w, h, true);
    
    //reserve memory for cv images
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filteredPink.allocate(w, h);
    filteredRed.allocate(w, h);
    filteredBlue.allocate(w, h);
    filteredGreen.allocate(w, h);
 

}

//--------------------------------------------------------------
void testApp::update(){
    
    movie.update();
    if (movie.isFrameNew()) {
        
        //copy webcam pixels to rgb image
        rgb.setFromPixels(movie.getPixels(), w, h);
        
        //mirror horizontal
        rgb.mirror(false, true);
        
        //duplicate rgb
        hsb = rgb;
        
        //convert to hsb
        hsb.convertRgbToHsv();
        
        //store the three channels as grayscale images
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        
///////////////////////////////
//////////color tracking begins
///////////////////////////////
        
        //PINK COLOR TRACKING
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filteredPink.getPixels()[i] = ofInRange(hue.getPixels()[i],pink-5,pink+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contoursPink.findContours(filteredPink, 50, w*h, 1, false);
        
        //smooth + send
        pinkNote.colorVelSmooth();
        pinkNote.sendColorVel("pink");
        
        
        
        //BLUE COLOR TRACKING
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filteredBlue.getPixels()[i] = ofInRange(hue.getPixels()[i],blue-5,blue+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contoursBlue.findContours(filteredBlue, 50, w*h/2, 1, false);
        
        //find velocity
        blueNote.colorVelSmooth();
        blueNote.sendColorVel("blue");
        
        
        
        //GREEN COLOR TRACKING
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filteredGreen.getPixels()[i] = ofInRange(hue.getPixels()[i],green-5,green+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contoursGreen.findContours(filteredGreen, 50, w*h, 1, false);
        
        //find velocity
        greenNote.colorVelSmooth();
        greenNote.sendColorVel("green");
        
        
        
        //RED COLOR TRACKING
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filteredRed.getPixels()[i] = ofInRange(hue.getPixels()[i],red-5,red+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contoursRed.findContours(filteredRed, 50, w*h/2, 1, false);
        
        //find velocity
        redNote.colorVelSmooth();
        redNote.colorVel("red");
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255,255);
    
    
    
////////find velocity using class
    pinkNote.colorVel(contoursPink);
    blueNote.colorVel(contoursBlue);
    greenNote.colorVel(contoursGreen);
    redNote.colorVel(contoursRed);

    
///////draw RGB Image
    rgb.draw(w/2,2);
   
///////draw Contour Images
    contoursPink.draw(0,240);
    ofDrawBitmapString("Pink countours (above)", 5, 490);
    ofDrawBitmapString(&"Velocity: " + [ redNote.velocitySmoothed], 5, 505); //PRINT SMOOTHED VELOCITY
    
    contoursBlue.draw(w,240);
    ofDrawBitmapString("Blue contours (above)", w+5, 490);
    ofDrawBitmapString(&"Velocity: " [ blueNote.velocitySmoothed], w+5, 505); //PRINT SMOOTHED VELOCITY
    
    contoursGreen.draw(0, 500);
    ofDrawBitmapString("Green contours (above)", 5, 750);
    ofDrawBitmapString(&"Velocity: " [ greenNote.velocitySmoothed], 5, 765); //PRINT SMOOTHED VELOCITY
    
    contoursRed.draw(w, 500);
    ofDrawBitmapString("Red contours (above)", w+5, 750);
    ofDrawBitmapString(&"Velocity: "[ redNote.velocitySmoothed], w+5, 765); //PRINT SMOOTHED VELOCITY
    
    ofSetColor(255, 0, 0);
    ofFill();
    
    


    

    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    
}
