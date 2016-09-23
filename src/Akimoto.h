//
//  Akimoto.h
//  BeatMapping
//
//  Created by 秋元和久 on 2016/09/23.
//
//
#include "ofMain.h"



class RandomWalkerAkimoto {
    
public:
    
    RandomWalkerAkimoto(int _x, int _y, int _w, int _h);
    void update();
    void Draw();
    
    ofVec2f position;
    float left, right, top, bottom;
    int x, y ,w, h;
};

class Akimoto {
    
public:
    ofVboMesh mesh;
    
    //RandomWalker
    void RandomWalkerUp(vector<RandomWalkerAkimoto*> walker);
    Akimoto();
    
private:
};