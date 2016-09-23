//
//  MyOSC.hpp
//  BeatMapping
//
//  Created by 諸星智也 on 2016/09/23.
//
//

#ifndef MyOSC_hpp
#define MyOSC_hpp

#include "ofxOsc.h"

#define PORT 8000 //ポート番号を設定

class MyOSC{
    
public:
    void setup();
    void update();
    void draw();
    
    //受信用もインスタンス
    ofxOscReceiver receiver;
    
    //受信してくるもののフォーマットをここに記述
    
    
};

#endif