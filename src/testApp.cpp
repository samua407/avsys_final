#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);
    
    w = 320;
    h = 240;
    orange = 178;
    blue = 105;
    
    movie.initGrabber(w, h, true);
    
    //reserve memory for cv images
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filtered.allocate(w, h);
    filtered2.allocate(w, h);
 

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
        
        
        //color tracking begins
        
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filtered.getPixels()[i] = ofInRange(hue.getPixels()[i],orange-5,orange+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contours.findContours(filtered, 50, w*h, 1, false);
        
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filtered2.getPixels()[i] = ofInRange(hue.getPixels()[i],blue-5,blue+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        c2.findContours(filtered2, 50, w*h/2, 1, false);
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255,255);
    
    rgb.draw(0,0);
    contours.draw(0,480);
    c2.draw(400,480);
    
    ofSetColor(255, 0, 0);
    ofFill();
    
    //draw red circles for found blobs
    for (int i=0; i<contours.nBlobs; i++) {
        
        ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 20);
        pos.x = contours.blobs[i].centroid.x;
        pos.y = contours.blobs[i].centroid.y;
        
        posSpeed = newPos.x - pos.x;
        
        //draw xPos
        string xposition = "xPos: "+ofToString(pos.x, 15);
        ofDrawBitmapString(xposition, 100, 100);
        
        //draw yPos
        string yposition = "yPos: "+ofToString(pos.y, 15);
        ofDrawBitmapString(yposition, 100, 125);
    }
    
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    
}
