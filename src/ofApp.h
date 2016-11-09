#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"
#include "ofxPostGlitch.h"
#include "Glitch.hpp"

#define camNUM 4

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mousePressed(int x, int y, int button);

    void DrawManyCircle(int num);
    void DrawColorfulRect(int num);
    void DrawBlueRect(int num);
    void KeyNum(int key);
    
    
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
    
    void FboUpdate(int camera);//FBO格納用の関数
    void FboDraw(int camera);//FBOの描画用の関数
    void stop(int number); //描画の停止用関数
    
    ofVideoGrabber vidGrabber[camNUM];//カメラのインスタンス
    int camWidth , camHeight;//カメラの表示高さと幅
    vector<ofFbo *> camFbo[camNUM];
    
    
    bool RecFlg[camNUM];
    bool DrawFlg[camNUM];
    int counter[camNUM];
  
    //グリッチエフェクト
    Glitch effectGlitch;

    
    
};
