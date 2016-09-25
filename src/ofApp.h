#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "BeatGenerator.h"
#include "Akimoto.h"
#include "ofxOsc.h"
#include "Morohoshi.hpp"

#define PORT 8000//自分のポート番号

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    void DrawManyCircle(int num);
    void DrawColorfulRect(int num);
    void DrawBlueRect(int num);
    
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
    BeatGenerator bg[5];
    
    //OSC
    ofxOscReceiver receiver;
    //受信した心拍情報
    int beat_detect[7];
    //受信したFFT情報
    float lowValue,midValue,highValue;
    
    Morohoshi morohoshi;
    
    
};
