#pragma once

#include "ofMain.h"
#include "ofxSuperCollider.h"

/*------------------------------------------------------------------------------
 * The below SynthDefs must be loaded into SuperCollider before execution.
 * copy+paste the lot and hit enter...
 *------------------------------------------------------------------------------
 
 SynthDef(\fx_comb, { |inbus = 0, outbus = 0, wet = 0.5, delaytime = 0.1, decaytime = 1.0, fade = 0.5|
	var in, out;
 
	in = In.ar(inbus, 2);
	out = CombN.ar(in, 2.0, delaytime, decaytime);
 
	out = (wet * out) + ((1 - wet) * in);
	Out.ar(outbus, out);
 }).store;
 
 SynthDef(\sine_harmonic, { |outbus = 0, freq = 200, amp = 0.1, gate = 1, pan = 0|
	var data, env;
 
	amp = Lag.kr(amp, 0.4);
 
	// generate, degrade, filter, echo
	data = SinOsc.ar(freq, 0, amp);
	data = Latch.ar(data, Impulse.ar(Rand(1000, 35000)));
	data = LPF.ar(data, 1000);
	data = Pan2.ar(data, pan);
	data = data + CombN.ar(data, 0.5, 0.3, 15.0, 0.3);
 
	// envelope
	env = EnvGen.kr(Env.asr(0.5, 1.0, 1.0), gate: gate, doneAction: 2);
	data = data * env;
 
	data = [ data[0], data[1] * Select.kr(IRand(0, 3), [ 1, 1, -1 ]) ];
 
	Out.ar(outbus, data);
 }).store;
 
 SynthDef(\playbuf_1, { |bufnum = 0, outbus = 0, amp = 0.5, loop = 0, pan = 0, rate = 1.0|
	var data;
	data = PlayBuf.ar(1, bufnum, BufRateScale.kr(bufnum) * rate, 0, 0, loop);
	FreeSelfWhenDone.kr(data);
	Out.ar(outbus, Pan2.ar(data, pan, amp));
 }).store;
 
 
 *--------------------------------------------------------------------------------*/

class ofApp : public ofBaseApp
{
    
public:
    ~ofApp();
    void setup();
    void update();
    void draw();
    void stop();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    ofxSCSynth	*synth;
    
    ofxSCSynth	*playbuf;
    ofxSCBus	*bus;
    ofxSCSynth	*delay;
    ofxSCBuffer	*buffer;
    
};
