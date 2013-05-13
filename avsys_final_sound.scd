//  for use with QSCInterface.h
//  Created by MarkDavid Hosale on 13-04-06.

(r = Routine({

    "Booting SUPERCOLLIDER".postln;

    s = Server.local ;

    while { s.serverRunning.not }{

        "Waiting for Server.".postln;

        10.wait; // give server time to boot 1-10 seconds depending on machine

        s.boot;

        s.doWhenBooted({

            //-------------------Initialize Sound----------------------//

            "Initialize Sound...".postln;

//            SynthDef(\mysynth, { | modfreq = 20.0, vol = 1.0 |
              SynthDef(\playTone, { | modfreq = 20.0, vol = 1.0 |
                var sampler, bufnum = 2;
                var env = Env.perc(0.001, 0.75, 1, -1);
                var gen = EnvGen.kr(env,doneAction: 2);

                // create the OSC sender in the server (SendTrig sends OSC messages when it's triggered)
                SendTrig.kr(Impulse.kr(10), 0, gen);
                SendTrig.kr(Done.kr(gen), 1);

                    Out.ar(out, SinOsc.ar(220,SinOsc.ar(modfreq, mul:2pi))* gen);

            }).send(s);

            //-------------------OSC RESPONDER:: OF->SC ----------------------//

            "OSC Responder loading...".postln;

            // register comm for listening to openframeworks
            OSCresponderNode(  nil,'/scresponder',{ arg time,responder,msg;

                // [time, responder, msg].postln;

                switch( msg[1],
                    'startsynth', {
                        var thisStarImplosion = Synth(\implosion);
                        thisStarImplosion.set(\modfreq, msg[2]);
                    }
                );

            }).add;


     //-------------------OSC RESPONDER:: SC->OF ----------------------//
           /* ~openframeworks = NetAddr("127.0.0.1", 57130); //this is for sending to OpenFrameworks

            OSCresponderNode(nil,'/tr',{ arg time,responder,msg;

                // [time, responder, msg].postln;

                switch( msg[2],

                    0, {// env done
                        ~openframeworks.sendMsg('/synthdone', 1);
                    },

                    //synth follower
                    1, {
                        ~openframeworks.sendMsg('/synth-follow', msg[3].asFloat);
                    }
                );

            }).add;

            ~openframeworks.sendMsg('/scbooted', 1);//tell the brain about it

            "Booted!".postln;
        });*/

        10.wait; // give server time to boot 1-10 seconds depending on machine
    };
}).play;

)  