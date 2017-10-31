#pragma once

#include "ofMain.h"
#include "ofxAubio.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void exit();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut();
    
    void onsetEvent(float & time);
    void beatEvent(float & time);
    
private:
    bool gotOnset, gotBeat;
    ofxAubioOnset onset;
    ofxAubioPitch pitch;
    ofxAubioBeat beat;
    ofxAubioMelBands bands;
    
    ofEasyCam cam;
    double t;
    ofNode node_global, node_sphere, node_inner_circle;
    int circle_res;
    float onsetThreshold = 0.3;
    
    float r_inc;
    
    void addVertices(ofPolyline &c, float dT, float dI, float r, float amp, int i);
};
