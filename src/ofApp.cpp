#include "ofApp.h"
int miliNext[5]{0,0,0,0,0};
int milidiff = 1000;
int SliderCounter = 0;

vector<ofFbo *> myfbo;
vector<ofxQuadWarp *> mywarper;
vector<int> x;
vector<int> y;
vector<int> w;
vector<int> h;
ofImage kariImage[15];
int mynum = 15; //切り取る領域の数
int nowKey;
int humanBeatCounter = 0;

ofVboMesh mesh;




//ofImage entireImage = NULL; バグ

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    ofSetBackgroundAuto(false);
    ofSetFrameRate(30);
    ofSetVerticalSync( true );
    ofEnableSmoothing();
    
    //画面の混色の設定を加算合成にする
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    //キャプチャするムービーのサイズを指定
    camWidth = ofGetWidth()/3; //3
    camHeight = (2*camWidth)/3; //2
    
    //カメラの初期化
    for(int i = 0 ; i < camNUM; i++){
        vidGrabber[i].setVerbose(true);
        vidGrabber[i].setDeviceID(i);
        vidGrabber[i].initGrabber(camWidth, camHeight);
        // vidGrabber[i].setDeviceID(i);
        
    }
    //カメラのFBOの準備
    for(int i = 0;i<camNUM;i++){
        DrawFlg[i] = false;//フラグの初期化
        RecFlg[i] = false;//フラグの初期化
        counter[i] = 0;
    }
    

    
    //強制フルスク
    //ofToggleFullscreen();
    
    display = false;
    drawLine = true;
    apple.load("apple.jpg");//写真の読み込み
    
   
    
    int blankX = 20; //余白を作るとバグる、なぜ？もしかして領域の幅が何らかの倍数ににならないとうまくいかない？
    int blankY = 200; //縦方向の余白
    int width = ofGetWidth()-blankX*7;
    int height = ofGetHeight()-blankY*2;
    //printf("%d,%d", width/5,height);
    
    
    for(int i=0; i<5; i++)
        for(int j=0; j<1; j++){
            for(int k=0; k<4; k++){
                
                if(k!=3){
                        x.push_back(width/5*i+width/20*k+blankX*(i+1));
                        y.push_back(height*j+blankY*(j+1));
                        w.push_back(width/20);
                        h.push_back(height);
                }
            
            //print("%d,%d,%d,%d",)
            }
        }
    
    
    
    for(int i = 0; i < mynum; i ++){
        
        ofxQuadWarp kariWarper;
        mywarper.push_back(new ofxQuadWarp);
        
        ofFbo kariFbo;
        myfbo.push_back(new ofFbo);
        
        myfbo[i]->allocate(w[i], h[i]);
        mywarper[i]->setSourceRect(ofRectangle(0, 0, w[i], h[i]));
        mywarper[i]->setTopLeftCornerPosition(ofPoint(x[i], y[i]));
        mywarper[i]->setTopRightCornerPosition(ofPoint(x[i] + w[i], y[i]));
        mywarper[i]->setBottomLeftCornerPosition(ofPoint(x[i], y[i] + h[i]));
        mywarper[i]->setBottomRightCornerPosition(ofPoint(x[i] + w[i], y[i] + h[i]));
        mywarper[i]->setup();
        
        //グリッジ
        effectGlitch.myGlitch[i].setup(myfbo[i]);
    }
    

}

//--------------------------------------------------------------
void ofApp::update(){
    //カメラ映像のupdate
    for(int i = 0 ; i < camNUM; i++){
        vidGrabber[i].update();
    }
    
    
    
    if(ofGetFrameNum()){
        return;
    }
    
}

void ofApp::DrawManyCircle(int num){
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    for(int i=0; i<200; i++){//円のランダム表示
        int r = ofRandom(10);
        ofDrawEllipse(ofRandom(x[num], x[num]+w[num]), ofRandom(y[num], y[num]+h[num]), r, r);
        //ofDrawEllipse(ofRandom(x1, x2), ofRandom(y1, y2), r, r);
    }
}

void ofApp::DrawColorfulRect(int num){
    ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
    ofDrawRectangle(x[num], y[num], w[num], h[num]);
}

void ofApp::DrawBlueRect(int num){
    ofSetColor(ofRandom(0), ofRandom(0), ofRandom(255));
    ofDrawRectangle(x[num], y[num], w[num]*3, h[num]*3);
}
//--------------------------------------------------------------
void ofApp::draw(){
    //この中にマッピングされる側のコードを書く
    ofBackground(0);
    //フェードのためにフィルターを重ねる
    //if(entireImage!=NULL)entireImage->draw(0,0);
    ofSetColor(0, 0, 0, 0); //半透明の黒（背景色）
    ofRect(0, 0, ofGetWidth(), ofGetHeight()); //画面と同じ大きさの四角形を描画
    

    //カメラの映像を描画
    ofSetColor(0xffffff);
    for(int i = 0 ; i < camNUM; i++){
        if(i>=3){
            vidGrabber[i].draw((i-3)*camWidth,camHeight);
        }
        vidGrabber[i].draw(i*camWidth,0);
    }

    
    //ここの条件をOSCが送られてきた時にすればOK
    int mili = ofGetElapsedTimeMillis();//起動してからの時間を取得

    
    //白色エフェクト
    if(nowKey == 'm'){
        ofSetColor(255);
        SliderCounter++;
        
        int p = 10;
        int p2 = SliderCounter/20;
        if(p > p2) p = p - p2;
        else p = 1;
        
        int sliderCount = SliderCounter%(10*p);
        if(sliderCount > 8*p){
            ofDrawRectangle(x[0], y[0], w[0]*3, h[0]);
        } else if(sliderCount > 6*p){
            ofDrawRectangle(x[3], y[3], w[3]*3, h[3]);
        } else if(sliderCount > 4*p){
            ofDrawRectangle(x[6], y[6], w[3]*3, h[3]);
        } else if(sliderCount > 2*p){
            ofDrawRectangle(x[9], y[9], w[3]*3, h[3]);
        } else {
            ofDrawRectangle(x[12], y[12], w[3]*3, h[3]);
        }
        
    } else {
        SliderCounter = 0;
    }
    
    //枠を付ける,y軸がうまくいってない気がする
    ofSetColor(0,150);
    for(int i=0; i<mynum; i++){
        ofDrawRectangle(x[i]-2,y[i]-2,4,y[i]+h[i]);
        ofDrawRectangle(x[i]-2,y[i]-2,x[i]+w[i],4);
        ofDrawRectangle(x[i]+w[i]-2,y[i]-2,4,y[i]+h[i]);
        ofDrawRectangle(x[i]-2,y[i]+h[i]-2,x[i]+w[i],4);
    }
    
    for(int i=0; i<mynum; i++){
        //kariImage.push_back(new ofImage);
        kariImage[i].grabScreen(x[i], y[i], w[i], h[i]);
        //kariImage[i]->saveImage("test3.png");
    }
    	
    
    //entireImage->grabScreen(0, 0, ofGetWidth(), ofGetHeight());
    
    //ここまで
    ofSetColor(100);
    ofNoFill();
    
    ofSetColor(255, 255, 255);
    ofFill();
    
    if (display) {
        ofBackground(0);
        
        for(int i=0;i<mynum;i++){
            myfbo[i]->begin();
            kariImage[i].draw(0, 0);
            myfbo[i]->end();
        
            
            
            ofMatrix4x4 mat = mywarper[i]->getMatrix();
        
            glPushMatrix();
            glMultMatrixf(mat.getPtr());
        {
            effectGlitch.myGlitch[i].generateFx();
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
    //vector<ofImage*>().swap(kariImage);   //←swap技法による解放
    
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
        for (int i=0; i<mynum; i++) {
            mywarper[i]->toggleShow();
            
        }
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
    
    
    //入力keyをnowKeyに格納
    KeyNum(key);
    
    //Glitchのエフェクトの開始
    effectGlitch.EffectStart(key);
    
    
    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //Glitchのエフェクトの停止
    effectGlitch.EffectStop(key);
        
    
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
//--------------------------------------------------------------
void ofApp::KeyNum(int key){
    nowKey = key;
    
}

