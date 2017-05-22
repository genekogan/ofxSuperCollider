#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup()
{
    //--------------------------------------------------------------
    // Create a SuperCollider synth with default parameters
    // and spawn it on the server.
    //--------------------------------------------------------------
    synth = new ofxSCSynth("sine_harmonic");
    synth->create();
    
    //--------------------------------------------------------------
    // Load up a buffer with a sound file, and route its playback
    // to an fx unit via a 2-channel audio bus.
    //--------------------------------------------------------------
    buffer = new ofxSCBuffer();
    buffer->read(ofToDataPath("bell.aif", true));
    
    bus = new ofxSCBus(2);
    
    playbuf = new ofxSCSynth("playbuf_1");
    playbuf->set("bufnum", buffer->index);
    playbuf->set("outbus", bus->index);
    playbuf->create();
    
    delay = new ofxSCSynth("fx_delay");
    delay->set("wet", 0.4);
    delay->set("delaytime", 0.4);
    delay->set("decaytime", 4);
    delay->set("inbus", bus->index);
    delay->set("outbus", 0);
    delay->addToTail();
    delay->create();
    
    //--------------------------------------------------------------
    // Drawing setup
    //--------------------------------------------------------------
    ofBackground(0, 20, 50);
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------

void ofApp::update()
{
}

//--------------------------------------------------------------

ofApp::~ofApp()
{
    //--------------------------------------------------------------
    // Free synths and buffers when we're done - otherwise
    // they'll hang about on SC server, occupying CPU and memory.
    //--------------------------------------------------------------
    synth->free();
    delay->free();
    buffer->free();
    bus->free();
}

//--------------------------------------------------------------

void ofApp::draw()
{
    ofEnableAlphaBlending();
    ofSetColor(0, 20, 50, 2);
    ofFill();
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key)
{
    
}

//--------------------------------------------------------------

void ofApp::keyReleased(int key)
{
    
}

//--------------------------------------------------------------

void ofApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------

void ofApp::mouseDragged(int x, int y, int button)
{
    //--------------------------------------------------------------
    // Modulate synth params based on mouse position.
    //--------------------------------------------------------------
    
    if (button == 0)
    {
        synth->set("freq", x + 40);
        synth->set("amp", 1.0f - (float) y / ofGetHeight());
        synth->set("pan", (float) x / ofGetHeight() - 0.5f);
        
        ofSetColor(255, 255, 255, 100);
        ofCircle(x, y, 10 * (1.0 - (float) y / ofGetHeight()));
    }
}

//--------------------------------------------------------------

void ofApp::mousePressed(int x, int y, int button)
{
    //--------------------------------------------------------------
    // Trigger stuff. Press right mouse button for bells.
    //--------------------------------------------------------------
    
    if (button == 0)
    {
        this->mouseDragged(x, y, button);
        synth->set("amp", 0.8f);
    }
    else if (button == 2)
    {
        playbuf->set("rate", 2.0f * x / ofGetWidth());
        playbuf->create();
        
        ofSetColor(255, 255, 0, 200);
        ofTriangle(x, y - 10, x + 10, y + 10, x - 10, y + 10);
    }
}

//--------------------------------------------------------------

void ofApp::mouseReleased(int x, int y, int button)
{
    synth->set("amp", 0.1f);
}

//--------------------------------------------------------------

void ofApp::windowResized(int w, int h)
{
    
}

