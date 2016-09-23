//
//  MyOSC.cpp
//  BeatMapping
//
//  Created by 諸星智也 on 2016/09/23.
//
//

#include "MyOSC.hpp"
#include "ofMain.h"

//--------------------------------------------------------------
void MyOSC::setup(){
    //指定したポートで接続
    receiver.setup(PORT);
    
    //受信してくる変数の初期化
    
}
//--------------------------------------------------------------
void MyOSC::update(){
    //現在順番待ちのOSCメッセージがある間は受信を続ける
    while (receiver.hasWaitingMessages()) {
        //次のメッセージを取得
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        //以下は送信側の設定あとに記述
        
    }
}
