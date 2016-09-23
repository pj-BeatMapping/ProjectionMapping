//
//  Akimoto.cpp
//  BeatMapping
//
//  Created by 秋元和久 on 2016/09/23.
//
//

#include "Akimoto.h"

RandomWalkerAkimoto::RandomWalkerAkimoto(int _x, int _y, int _w, int _h){
    //初期位置を画面中心に
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    
    position.x = x + w/2.0;
    position.y = y + h;
    
    //移動確率をランダムに
    left = ofRandom(3, 5.0);
    right = ofRandom(3, 5.0);
    top = ofRandom(5, 30.0);
    bottom = ofRandom(5, 10.0);
}

void RandomWalkerAkimoto::Draw(){
    //上下左右同じ確率でランダムに移動
    position.x += ofRandom(-left, right);
    position.y += ofRandom(-top, bottom);
    
    
    // 画面からはみ出たら、反対側から出現
    if (position.x < x) {
        position.x = x+w;
    }
    if (position.x > x+w) {
        position.x = x;
    }
    if (position.y < y) {
        position.y = y+h;
    }
    if (position.y > y+h) {
        position.y = y+h;
    }
    
    
}

Akimoto::Akimoto(){
    mesh.setMode(OF_PRIMITIVE_POINTS);
}

void Akimoto::RandomWalkerUp(vector<RandomWalkerAkimoto*> walker){
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    mesh.clear();
    ofSetColor(255,255,255,100);
    glPointSize(2);
    for (int i = 0; i < walker.size(); i++) {
        walker[i]->Draw();
        ofVec3f pos = ofVec3f(walker[i]->position.x,
                              walker[i]->position.y,
                              0);
        mesh.addVertex(pos);
    }
    mesh.draw();
}