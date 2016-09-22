#include "ofApp.h"
int miliNext = 0;
int milidiff = 500;


vector<ofFbo *> myfbo;
vector<ofxQuadWarp *> mywarper;
vector<int> x;
vector<int> y;
vector<int> w;
vector<int> h;

ofImage entireImage;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    ofSetBackgroundAuto(false);
    ofSetFrameRate( 60 );
    ofSetVerticalSync( true );
    ofEnableSmoothing();
    
    display = false;
    drawLine = true;
    apple.load("apple.jpg");//写真の読み込み
    
    bg = *new BeatGenerator(BPM/60.0*1000 + (0.5 - flct)*BPM*margin/60*1000, flct);
    
    x.push_back(250);
    y.push_back(30);
    w.push_back(400);
    h.push_back(200);
    
    x.push_back(30);
    y.push_back(30);
    w.push_back(200);
    h.push_back(200);
    
    
    x.push_back(300);
    y.push_back(250);
    w.push_back(200);
    h.push_back(200);
    
    
    for(int i = 0; i < 3; i ++){
        
        ofxQuadWarp kariWarper;
        mywarper.push_back(new ofxQuadWarp);
        
        ofFbo kariFbo;
        myfbo.push_back(new ofFbo);
        
        myfbo[i]->allocate(w[i], h[i]);
        mywarper[i]->setSourceRect(ofRectangle(0, 0, w[i], h[i]));
        mywarper[i]->setTopLeftCornerPosition(ofPoint(x[i], 300+y[i]));
        mywarper[i]->setTopRightCornerPosition(ofPoint(x[i] + w[i], 300+y[i]));
        mywarper[i]->setBottomLeftCornerPosition(ofPoint(x[i], 300 + y[i] + h[i]));
        mywarper[i]->setBottomRightCornerPosition(ofPoint(x[i] + w[i], 300 + y[i] + h[i]));
        mywarper[i]->setup();
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(ofGetFrameNum()){
        return;
    }
}

void ofApp::DrawManyCircle(int x1, int x2, int y1, int y2){
    for(int i=0; i<200; i++){//円のランダム表示
        int r = ofRandom(10);
        ofDrawEllipse(ofRandom(250, 650), ofRandom(30, 230), r, r);
        //ofDrawEllipse(ofRandom(x1, x2), ofRandom(y1, y2), r, r);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //この中にマッピングされる側のコードを書く
    ofBackground(0);
    //フェードのためにフィルターを重ねる
    entireImage.draw(0,0);
    ofSetColor(0, 0, 0, 10); //半透明の黒（背景色）
    ofRect(0, 0, ofGetWidth(), ofGetHeight()); //画面と同じ大きさの四角形を描画

    
    //ここの条件をOSCが送られてきた時にすればOK
    int mili = ofGetElapsedTimeMillis();//起動してからの時間を取得
    if(bg.autoBeat(mili, BPM, margin)){
        //DrawManyCircle(0, 0, 0, 0);
        miliNext = mili + milidiff;
    }
    
    //ちゃんとフェードさせるならクラスか配列を作る必要あり
    if(mili < miliNext){
        float fade = 1-(mili-miliNext)/milidiff;
        printf("fade = %f",fade);
        
        //複数の円の表示
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
        DrawManyCircle(0, 0, 0, 0);
        
        //ランダムな色の表示
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
        ofDrawRectangle(30, 30, 200, 200);
        
        //画像表示
        ofSetColor(255, 255, 255);
        apple.draw(300, 250,200,200);
        
    }
    
    vector<ofImage*> kariImage;
    for(int i=0; i<3; i++){
        kariImage.push_back(new ofImage);
        kariImage[i]->grabScreen(x[i], y[i], w[i], h[i]);
        kariImage[i]->saveImage("test3.png");
    }
    
    
    entireImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    //ここまで
    ofSetColor(100);
    ofNoFill();
    
    for (int i=0; i<img.size(); i++) {
        img[i]->grabScreen(lx[i], ly[i], ww[i], hh[i]);
        if(i == 1)img[i]->saveImage("test2.png");
        
        //ofImage bar;
        
        //bar.grabScreen(0,0,ofGetScreenWidth(), ofGetScreenHeight());
        //bar.saveImage("bar.png");
        if(drawLine){
            ofDrawRectangle(lx[i], ly[i], ww[i], hh[i]);
            ofDrawRectangle(250, 30, 400, 200);
        }
    }
    
    ofSetColor(255, 255, 255);
    ofFill();
    
    if (display) {
        ofBackground(0);
        
        for(int i=0;i<3;i++){
            myfbo[i]->begin();
            kariImage[i]->draw(0, 0);
            myfbo[i]->end();
        
            ofMatrix4x4 mat = mywarper[i]->getMatrix();
        
            glPushMatrix();
            glMultMatrixf(mat.getPtr());
        {
            myfbo[i]->draw(0, 0);
        }
            glPopMatrix();
        
            ofSetColor(100, 100, 100);
            ofSetLineWidth(2);
            mywarper[i]->draw();
            
            ofSetColor(255,255,255);
        }
        
        
        
        for (int i=0; i<img.size(); i++) {
            
            fbo[i]->begin();
            img[i]->draw(0, 0);
            fbo[i]->end();
            
            ofMatrix4x4 mat = warper[i]->getMatrix();
            
            glPushMatrix();
            glMultMatrixf(mat.getPtr());
            {
                fbo[i]->draw(0, 0);
            }
            glPopMatrix();
            
            ofSetColor(100, 100, 100);
            ofSetLineWidth(2);
            warper[i]->draw();
            
            ofSetColor(0,0,0);
        }
    }
    

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'a' ){//切り取った領域の表示
        if (display) {
            display = false;
        }else{
            display = true;
        }
        
    }
    
    if( key == 's' ){//切り取った領域の
        for (int i=0; i<img.size(); i++) {
            warper[i]->toggleShow();
            
        }
        mywarper[0]->toggleShow();
        mywarper[1]->toggleShow();
        mywarper[2]->toggleShow();
        if (drawLine) {
            drawLine = false;
        }else{
            drawLine = true;
        }
    }
    
    if (key == 'f')
    {
        ofToggleFullscreen();
    }
    
    if(key == 'd'){//領域を一つずつ消す、領域がないのに消すとエラー
        lx.pop_back();
        ly.pop_back();
        ww.pop_back();
        hh.pop_back();
        delete img[img.size()-1];
        img.pop_back();
        delete fbo[fbo.size()-1];
        fbo.pop_back();
        delete warper[warper.size()-1];
        warper.pop_back();
        
        mouseCount -= 3;
    }
    
    if (key == 'D') {//領域を全部消す
        lx.clear();
        ly.clear();
        ww.clear();
        hh.clear();
        for (int i=0; i<img.size(); i++) {
            delete img[i];
            delete fbo[i];
            delete warper[i];
        }
        img.clear();
        fbo.clear();
        warper.clear();
        
        mouseCount = 0;
    }
    
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){//一度目のクリックで左上、二度目で右上、三度目で右下を指定、領域を認識できるかは今の所運
    if (!display) {
        if (mouseCount % 3 == 0) {
            lx.push_back(mouseX);
            ly.push_back(mouseY);
            ww.push_back(0);
            hh.push_back(0);
        }else if(mouseCount % 3 == 1){
            ww[mouseCount/3] = mouseX - lx[mouseCount/3];
            if (mouseX - lx[mouseCount/3] < 0) {
                lx[mouseCount/3] += ww[mouseCount/3];
                ww[mouseCount/3] *= -1;
            }
        }else{
            hh[mouseCount/3] = mouseY - ly[mouseCount/3];
            if (mouseY - ly[mouseCount/3] < 0) {
                ly[mouseCount/3] += hh[mouseCount/3];
                hh[mouseCount/3] *= -1;
            }
            
            img.push_back(new ofImage);
            img[mouseCount/3]->grabScreen(lx[mouseCount/3], ly[mouseCount/3], ww[mouseCount/3], hh[mouseCount/3]);
            
            
            ofxQuadWarp kariWarper;
            warper.push_back(new ofxQuadWarp);
            
            ofFbo kariFbo;
            fbo.push_back(new ofFbo);
            
            fbo[mouseCount/3]->allocate(ww[mouseCount/3], hh[mouseCount/3]);
            warper[mouseCount/3]->setSourceRect(ofRectangle(0, 0, ww[mouseCount/3], hh[mouseCount/3]));
            warper[mouseCount/3]->setTopLeftCornerPosition(ofPoint(lx[mouseCount/3], ly[mouseCount/3]));
            warper[mouseCount/3]->setTopRightCornerPosition(ofPoint(lx[mouseCount/3] + ww[mouseCount/3], ly[mouseCount/3]));
            warper[mouseCount/3]->setBottomLeftCornerPosition(ofPoint(lx[mouseCount/3], ly[mouseCount/3] + hh[mouseCount/3]));
            warper[mouseCount/3]->setBottomRightCornerPosition(ofPoint(lx[mouseCount/3] + ww[mouseCount/3], ly[mouseCount/3] + hh[mouseCount/3]));
            warper[mouseCount/3]->setup();
            
        }
        mouseCount++;
    }
    
    
}
