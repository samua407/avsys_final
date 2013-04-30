#include "testApp.h"
#include "note.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofBackground(0,0,0);
    
    //set width and height of each image
    w = 320;
    h = 240;
    
    //set the hue values for each color
    pink = 178; //ORANGE NOW. CHANGE TO CORRECT VALUE
    blue = 105;
    green = 10; //CHANGE TO CORRECT VALUE
    red = 70; //CHANGE TO CORRECT VALUE
    
    //start the video feed
    movie.initGrabber(w, h, true);
    
    //reserve memory for cv images, otherwise they wont work!
    rgb.allocate(w, h);
    hsb.allocate(w, h);
    hue.allocate(w, h);
    sat.allocate(w, h);
    bri.allocate(w, h);
    filteredPink.allocate(w, h);
    filteredRed.allocate(w, h);
    filteredBlue.allocate(w, h);
    filteredGreen.allocate(w, h);
    
    // open an outgoing connection to HOST:PORT
	sender.setup(HOST, PORT);
    //sender.setup("127.0.0.1", 2468);
 

}

//--------------------------------------------------------------
void testApp::update(){
    
    //next frame of movie
    movie.update();
    
    //if there is a new frame,
    if (movie.isFrameNew()) {
        
        //copy webcam pixels to rgb image
        rgb.setFromPixels(movie.getPixels(), w, h);
        
        //mirror horizontal so it makes sense
        rgb.mirror(false, true);
        
        //clone the rgb image into the hsb image
        hsb = rgb;
        
        //convert the hsb image to Hsv values, so we can get hue, saturation, and brightness
        hsb.convertRgbToHsv();
        
        //store the three channels of the Hsv into their own contrast masks (grayscale images)
        hsb.convertToGrayscalePlanarImages(hue, sat, bri);
        
        
///////////////////////////////
//////////color tracking begins
///////////////////////////////
        
        //PINK COLOR TRACKING
        //filter image based on the hue value we're looking for
        //looping through every pixel in the contour mask of pink hue, and pulling out pink values.
        //storing them in the filteredPink array
        for (int i=0; i<w*h; i++) {
            filteredPink.getPixels()[i] = ofInRange(hue.getPixels()[i],pink-5,pink+5);
        }
        
        //run the contour finder on the filtered image to create blobs from points that are in proximity of each other
        contoursPink.findContours(filteredPink, 50, w*h, 1, false);
                
        //calculate velocity of color, smooth velocity, and send to OSC with color name
        pinkNote.colorVel(contoursPink, "pink");
//        pinkNote.sendColorVel("pink");
        
        
        
        //BLUE COLOR TRACKING
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filteredBlue.getPixels()[i] = ofInRange(hue.getPixels()[i],blue-5,blue+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contoursBlue.findContours(filteredBlue, 50, w*h/2, 1, false);
        
        //calculate velocity of color, smooth velocity, and send to OSC with color name
        blueNote.colorVel(contoursBlue, "blue");
        //blueNote.sendColorVel("blue");
        
        
        
        //GREEN COLOR TRACKING
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filteredGreen.getPixels()[i] = ofInRange(hue.getPixels()[i],green-5,green+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contoursGreen.findContours(filteredGreen, 50, w*h, 1, false);
        
        //calculate velocity of color, smooth velocity, and send to OSC with color name
        greenNote.colorVel(contoursGreen, "green");
//        greenNote.sendColorVel("green");
        
        
        
        //RED COLOR TRACKING
        //filter image based on the hue value were looking for
        for (int i=0; i<w*h; i++) {
            filteredRed.getPixels()[i] = ofInRange(hue.getPixels()[i],red-5,red+5);
        }
        
        //run the contour finder on the filtered image to find blobs with a certain hue
        contoursRed.findContours(filteredRed, 50, w*h/2, 1, false);
        
        //calculate velocity of color, smooth velocity, and send to OSC with color name
        redNote.colorVel(contoursRed, "red");
        
        
//        redNote.sendColorVel("red");

    }

    
////////////////
//SEND MESSAGE
///////////////
    
    cout << greenNote.velocitySmoothed << endl;
    
//    //if the movement on the x axis of the colored blob is greater than 1 unit (in either direction), then:
//    if(velocitySmoothed > 5){
//        
//        //SEND to OSC the activeColor and posDiffX (velocity on the x axis) (i know theres a way to calculate velocity of vx + vy)
//        
//        if (slowYourRoll % 20 == 0){
//            ofxOscMessage x;
//            x.setAddress("/playtone");
//            x.addIntArg(velocitySmoothed);
//            ///x.addStringArg(activeColor);
//            sender.sendMessage(x);
//            cout << velocitySmoothed << " sent." << endl;
//        }
//        slowYourRoll++;
    
        
//    }

}

//--------------------------------------------------------------
void testApp::draw(){
    ofSetColor(255,255,255);
    
///////draw the original RGB Image (camera, mirrored)
    rgb.draw(w/2,2);
   
///////draw Contour Images
    contoursPink.draw(0,240);
    ofDrawBitmapString("Pink countours (above)", 5, 490);
   // ofDrawBitmapString(&"Velocity: " + [ redNote.velocitySmoothed], 5, 505); //PRINT SMOOTHED VELOCITY
    
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
