#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "BeatGenerator.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    void DrawManyCircle(int x1, int x2, int y1, int y2);
    
    bool display;
    bool drawLine;
    ofImage apple;
    
    vector<ofImage *> img;
    vector<ofFbo *> fbo;
    vector<ofxQuadWarp *> warper;
    
    vector<int> lx;
    vector<int> ly;
    vector<int> ww;
    vector<int> hh;
    int mouseCount;
    
    //擬似心拍用変数
    float BPM = 80;
    float margin = 0.2;
    int flct = 0.3;
    BeatGenerator bg;
    
};
