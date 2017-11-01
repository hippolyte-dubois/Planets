#include "ofApp.h"
#include <random>

//--------------------------------------------------------------
void ofApp::setup(){
    
    // Aubio Setup
    int nOutputs = 0;
    int nInputs = 2;
    
    // setup onset object
    onset.setup();
    ofAddListener(onset.gotOnset, this, &ofApp::onsetEvent);
    
    // setup pitch object
    pitch.setup();
    
    // setup beat object
    beat.setup();
    ofAddListener(beat.gotBeat, this, &ofApp::beatEvent);
    
    // setup mel bands object
    bands.setup();
    
    ofSoundStreamListDevices();
    //mic.setDeviceID(0);
    //mic.setup(nOutputs, nInputs, 44100, 256, 4);
    ofSoundStreamSetup(nOutputs, nInputs);
    
    ofEnableDepthTest();
    ofSetVerticalSync(true);
    cam.setDistance(160);
    
    ofBackground(5);
    ofDisableAntiAliasing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    t = 0;
    circle_res = 250;
    r_onset = 0;
    r_beat = 0;
    
    gotOnset = false;
    gotBeat = false;
}

void ofApp::exit(){
    //mic.stop();
    //mic.close();
    ofSoundStreamStop();
    ofSoundStreamClose();
}

//--------------------------------------------------------------
void ofApp::update(){
    onset.setThreshold(onsetThreshold);
    t+= .1F;
    if(r_onset > 0)
        r_onset -= 0.5;
    if(r_beat > 0)
        r_beat -= 0.5;
    if(gotOnset)
        gotOnset = false;
    if(gotBeat)
        gotBeat = false;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPolyline c1, c2, c3, c4;
    
    cam.begin();
    
    node_global.rotate(.1, ofVec3f(.01,-.02,1));
    node_global.transformGL();
    
    node_inner_circle.rotate(-.25, ofVec3f(0,0,1));
    node_inner_circle.transformGL();
    
    node_sphere.rotate(1, ofVec3f(.8, .9, .1));
    node_sphere.transformGL();
    
    ofSetColor(150);
    ofNoFill();
    ofDrawIcoSphere(30);
    ofFill();
    ofDrawIcoSphere(5);
    node_sphere.restoreTransformGL();
    
    for(int i = 0; i < circle_res; i++){
        addVertices(c1, .1F, .5F, 50 + r_beat, 30 + r_onset, i);
        addVertices(c2, .02F, .1F, 80 + r_beat, 10 + r_onset, i);
        addVertices(c3, .03F, .08F, 80 + r_beat, 8 + r_onset, i);
        addVertices(c4, .05F, .2F, 90 + r_beat, 5 + r_onset, i);
    }
    
    c1.close();
    c2.close();
    c3.close();
    c4.close();
    
    c1.draw();
    c1.getSmoothed(2,0.5).draw();
    c4.draw();
    c4.getSmoothed(2,0.5).draw();
    node_inner_circle.restoreTransformGL();
    c2.draw();
    c2.getSmoothed(2,0.5).draw();
    node_global.restoreTransformGL();
    c3.draw();
    c3.getSmoothed(2,0.5).draw();
    cam.end();
}

void ofApp::addVertices(ofPolyline &c, float dT, float dI, float r, float amp, int i){
    c.addVertex(cos(i * TWO_PI/circle_res) * r,
                sin(i * TWO_PI/circle_res) * r,
                ofMap(ofNoise(i * dI, t * dT), 0, 1, -amp, amp));
    ofFill();
    ofDrawIcoSphere(cos(i * TWO_PI / 4) * r,
                    sin(i * TWO_PI / 4) * r,
                    ofMap(ofNoise(i * dI, t * dT), 0, 1, -amp, amp),
                    ofNoise(t + (double) rand() / RAND_MAX) * (100 / (2 * r)));
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    // compute onset detection
    onset.audioIn(input, bufferSize, nChannels);
    // compute pitch detection
    pitch.audioIn(input, bufferSize, nChannels);
    // compute beat location
    beat.audioIn(input, bufferSize, nChannels);
    // compute bands
    bands.audioIn(input, bufferSize, nChannels);
}

void audioOut(){
}

//----
void ofApp::onsetEvent(float & time) {
    ofLog() << "got onset at " << time << " s";
    r_onset = 10;
    gotOnset = true;
}

//----
void ofApp::beatEvent(float & time) {
    ofLog() << "got beat at " << time << " s";
    r_beat = 15;
    gotBeat = true;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
