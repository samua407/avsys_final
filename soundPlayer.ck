//instantiate a SinOscillator called 'osc'
SinOsc osc; // => dac;

//initiate a reverb called 'r'
PRCRev r;

//initiate a gain called 'g'
Gain g;

//set reverb value to .03
.03 => r.mix;

//set gain value to .5
.5 => g.gain;

// create our OSC receiver
OscRecv recv;

// use port 4567
7771 => recv.port;

// start listening (launch thread)
recv.listen();

// create an address in the receiver, store in new variable
// expects message to come from /playtone address
// expects message to be a float (therefore f)
// when message is received, store contents to oe of type OscEvent
recv.event( "/playtone, i, s" ) @=> OscEvent oe;

// infinite event loop
while ( true )
{
    // wait for event to arrive
    oe => now;
    
    // grab the next message from the queue. 
    while ( oe.nextMsg() != 0 )
    { 
        
        <<< "received!" >>>;
        
        //create a float called velocity.
        int velocity;
        
        //reverb will be velocity, modified to work within reverb parameters
        float reverb;
        string color;
        

        
        
        // getFloat fetches the expected float (as indicated by "f")
        oe.getInt() => velocity;
        <<< velocity >>> ;
        
        velocity * .02 => reverb;
        reverb => r.mix;
        <<< reverb >>>;
        
        oe.getString() => color; 
        <<< color >>> ;
        
        // set play pointer to beginning
        
        //500 => osc.freq;
        //color => osc.freq;
        
        if(color == "pink"){
           //262 => osc.freq;
           131 => osc.freq;
        }
        
        else if(color == "blue"){
            //311 => osc.freq;
            156 => osc.freq;
        }
    

       
        else if(color == "red"){
           //440 => osc.freq;
           220 => osc.freq;
        };

    

        
        //hook up the oscillator to a reverb (start playing)
        r => g => dac;
        osc => r;
        
        //play for 200ms
        //when you can get xPossDiff in here, make ms = to xPosDiff
        //200::ms => now;
        200::ms => now;
        
        //disconnect the oscillator from reverb (stop playing)
        osc =< r;
        r =< dac;
        g =< dac;
        
    }
}
