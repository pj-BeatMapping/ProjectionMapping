//
//  Glitch.hpp
//  ProjectionMapping
//
//  Created by 諸星智也 on 2016/11/09.
//
//

#ifndef Glitch_hpp
#define Glitch_hpp

#include "ofMain.h"
#include "ofxPostGlitch.h"

class Glitch {
    
public:
    //グリッジ用
    ofxPostGlitch myGlitch[15];
    void EffectStart(int key); //エフェクトの開始
    void EffectStop(int key); //エフェクトの停止

    
    
};

#endif /* Glitch_hpp */
