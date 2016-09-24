//
//  Morohoshi.hpp
//  ProjectionMapping
//
//  Created by Ë´∏ÊòüÊô∫‰πü on 2016/09/24.
//
//

#include "ofMain.h"
#include "ofxPostGlitch.h"
class Morohoshi {
    
public:
    void setup();
    void update();
    void draw();
    void PostGlitch();
    void keyPressed (int key);
    void keyReleased (int key);
    
    //グリッジ用のインスタンス
    ofxPostGlitch myGlitch;
};
