//
//  Glitch.cpp
//  ProjectionMapping
//
//  Created by 諸星智也 on 2016/11/09.
//
//

#include "Glitch.hpp"

//--------------------------------------------------------------------------
void Glitch::EffectStart(int key)
{
    //グリッジ
    if (key == 'z') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
            //cout << "グリッジ！！" << endl;
        }
    }
    if (key == 'q') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_GLOW			, true);
        }
    }
    if (key == 'w') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SHAKER			, true);
        }
    }
    if (key == 'e') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
        }
    }
    if (key == 'r') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_TWIST			, true);
        }
    }
    if (key == 't') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_OUTLINE		, true);
        }
    }
    if (key == 'y') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_NOISE			, true);
        }
    }
    if (key == 'u') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SLITSCAN		, true);
        }
    }
    if (key == 'i') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SWELL			, true);
        }
    }
    if (key == 'o') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_INVERT			, true);
        }
    }
    
    
    if (key == 'p') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);        }
    }
    if (key == 'z') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
        }
    }
    if (key == 'x') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
        }
    }
    if (key == 'c') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
        }
    }
    if (key == 'v') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
        }
    }
    if (key == 'b') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
        }
    }
    if (key == 'n') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);        }
    }

}

//--------------------------------------------------------------------------
void Glitch::EffectStop(int key)
{
    //グリッジ
    if (key == 'z') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
            //cout << "グリッジ！！" << endl;
        }
    }
    if (key == 'q') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_GLOW			, false);
        }
    }
    if (key == 'w') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SHAKER			, false);
        }
    }
    if (key == 'e') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
        }
    }
    if (key == 'r') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_TWIST			, false);
        }
    }
    if (key == 't') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_OUTLINE		, false);
        }
    }
    if (key == 'y') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_NOISE			, false);
        }
    }
    if (key == 'u') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SLITSCAN		, false);
        }
    }
    if (key == 'i') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_SWELL			, false);
        }
    }
    if (key == 'o') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_INVERT			, false);
        }
    }
    
    
    if (key == 'p') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
        }
    }
    if (key == 'z') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
        }
    }
    if (key == 'x') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
        }
    }
    if (key == 'c') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
        }
    }
    if (key == 'v') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
        }
    }
    if (key == 'b') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
        }
    }
    if (key == 'n') {
        for(int i = 0 ; i < 15;i++){
            myGlitch[i].setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);
        }
    }
}


