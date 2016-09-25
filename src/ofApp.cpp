#include "ofApp.h"
int miliNext[5]{0,0,0,0,0};
int milidiff = 1000;


vector<ofFbo *> myfbo;
vector<ofxQuadWarp *> mywarper;
vector<int> x;
vector<int> y;
vector<int> w;
vector<int> h;
ofImage kariImage[15];
int mynum = 15; //切り取る領域の数


ofVboMesh mesh;

//RandomWalker
static const int NUM = 500;
vector<RandomWalkerAkimoto*> walker;
vector<RandomWalkerAkimoto*> walker2;
vector<RandomWalkerAkimoto*> walker3;
vector<RandomWalkerAkimoto*> walker4;
vector<RandomWalkerAkimoto*> walker5;
Akimoto akimoto = *new Akimoto();

//ofImage entireImage = NULL; バグ

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255);
    ofSetBackgroundAuto(false);
    ofSetFrameRate( 60 );
    ofSetVerticalSync( true );
    ofEnableSmoothing();
    
    //OSC
    receiver.setup(PORT);
    
    
    //強制フルスク
    //ofToggleFullscreen();
    
    display = false;
    drawLine = true;
    apple.load("apple.jpg");//写真の読み込み
    
    //BeatGeneratorSetup
    for(int i=0; i<5; i++){
        bg[i] = *new BeatGenerator(BPM/60.0*1000 + (0.5 - flct)*BPM*margin/60*1000, flct);
        BPM += 4;
    }
    
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
        myGlitch[i].setup(myfbo[i]);
    }
    
    
    //AkimotoSetup
    
    for(int i=0; i<NUM; i++)
        walker.push_back(new RandomWalkerAkimoto(x[0],y[0],w[0]*3,h[0]));
    for(int i=0; i<NUM; i++)
        walker2.push_back(new RandomWalkerAkimoto(x[6],y[6],w[0]*3,h[0]));
    for(int i=0; i<NUM; i++)
        walker3.push_back(new RandomWalkerAkimoto(x[3],y[3],w[0]*3,h[0]));
    for(int i=0; i<NUM; i++)
        walker4.push_back(new RandomWalkerAkimoto(x[9],y[9],w[0]*3,h[0]));
    for(int i=0; i<NUM; i++)
        walker5.push_back(new RandomWalkerAkimoto(x[12],y[12],w[0]*3,h[0]));
    
    //akimoto.particles = new Particles(10,x[1],y[1],w[1],h[1]);
    //akimoto.PerlinNoiseSetup(x[6],y[6],w[6]*3,h[6]);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //OSCの受信
    while (receiver.hasWaitingMessages()) {
        //心拍情報の受信
        ofxOscMessage OscBeat;
        receiver.getNextMessage(&OscBeat);
        
        if (OscBeat.getAddress() == "/Beat") {
            for(int i = 0; i < 7 ; i++){
                 beat_detect[i] =  OscBeat.getArgAsInt32(i);
            }
        }
        //FFTの解析データの受信
        ofxOscMessage OscFFT;
        receiver.getNextMessage(&OscFFT);
        
        if (OscFFT.getAddress() == "/Fft") {
            lowValue = OscFFT.getArgAsFloat(0);
            midValue = OscFFT.getArgAsFloat(1);
            highValue = OscFFT.getArgAsFloat(2);
            }

        
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
    /*
    //複数の円の表示
    DrawManyCircle(10); //0-20の番号を入れる
    
    //ランダムな色の表示
    DrawColorfulRect(3);
    
     //perlin
     akimoto.PerlinNoiseUpdate();
     akimoto.PerlinNoiseDraw();
     
    
    */
    //粒子の上行
    
    
    
    
    /*
    DrawBlueRect(0);
    DrawBlueRect(3);
    DrawBlueRect(6);
    DrawBlueRect(9);
    DrawBlueRect(12);
    */
     
    //ここの条件をOSCが送られてきた時にすればOK
    int mili = ofGetElapsedTimeMillis();//起動してからの時間を取得
    for(int i=0; i<5; i++){
        if(bg[i].autoBeat(mili, BPM, margin)){
        //DrawManyCircle(0, 0, 0, 0);
            miliNext[i] = mili + milidiff;
        //for(int i=0; i<NUM; i++)
        //walker[i]->Reset();
        }
        
        if(mili < miliNext[i]){
            float fade = 1-(float)(miliNext[i]-mili)/(float)milidiff;
            //printf("fade = %f",fade);
            if(i == 0)akimoto.RandomWalkerUp(walker, OF_PRIMITIVE_LINES,10,miliNext[i]-mili, milidiff);
            if(i==1)akimoto.RandomWalkerUp(walker2, OF_PRIMITIVE_POINTS,5,miliNext[i]-mili, milidiff);
            if(i==2)akimoto.RandomWalkerUp(walker3, OF_PRIMITIVE_TRIANGLES,10,miliNext[i]-mili, milidiff);
            if(i==3)akimoto.RandomWalkerUp(walker4, OF_PRIMITIVE_POINTS,10,miliNext[i]-mili, milidiff);
            if(i==4)akimoto.RandomWalkerUp(walker5, OF_PRIMITIVE_POINTS,20, miliNext[i]-mili, milidiff);
            
            
        }
    }
    
    //ちゃんとフェードさせるならクラスか配列を作る必要あり
    
    
    
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
            myGlitch[i].generateFx();
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
    
    
    //グリッジ
    if (key == '1') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
            cout << "グリッジ！！" << endl;
        }
    }
    if (key == '2') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_GLOW			, true);
        }
    }
    if (key == '3') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SHAKER			, true);
        }
    }
    if (key == '4') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
        }
    }
    if (key == '5') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_TWIST			, true);
        }
    }
    if (key == '6') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_OUTLINE		, true);
        }
    }
    if (key == '7') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_NOISE			, true);
        }
    }
    if (key == '8') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SLITSCAN		, true);
        }
    }
    if (key == '9') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SWELL			, true);
        }
    }
    if (key == '0') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_INVERT			, true);
        }
    }
    
    
    if (key == 'q') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);        }
    }
    if (key == 'w') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
        }
    }
    if (key == 'e') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
        }
    }
    if (key == 'r') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
        }
    }
    if (key == 't') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
        }
    }
    if (key == 'y') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
        }
    }
    if (key == 'u') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);        }
    }

    
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == '1') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
        }
    }
    if (key == '2') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_GLOW			, false);
        }
    }
    if (key == '3') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SHAKER			, false);
        }
    }
    if (key == '4') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
        }
    }
    if (key == '5') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_TWIST			, false);
        }
    }
    if (key == '6') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_OUTLINE		, false);
        }
    }
    if (key == '7') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_NOISE			, false);
        }
    }
    if (key == '8') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SLITSCAN		, false);
        }
    }
    if (key == '9') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SWELL			, false);
        }
    }
    if (key == '0') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_INVERT			, false);
        }
    }
    
    
    if (key == 'q') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);        }
    }
    if (key == 'w') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
        }
    }
    if (key == 'e') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
        }
    }
    if (key == 'r') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
        }
    }
    if (key == 't') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
        }
    }
    if (key == 'y') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
        }
    }
    if (key == 'u') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);        }
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
