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
    void Reset();
    void UpDownDraw(int milidiff, int milimax);
    
    ofVec2f position;
    float left, right, top, bottom;
    int x, y ,w, h;
};

class Particles {
public:
    Particles(int maxParticles, int _x, int _y, int _w, int _h);
    void update();
    void draw();
    void addParticle(ofVec2f position,
                     ofVec2f velocity = ofVec2f(0, 0),
                     ofColor color = 0xffffff);
    void resetForce();
    void addForce(int count, ofVec2f force);
    void addDampingForce();
    void resetOffWalls();
    void updatePos();
    
    int maxParticles;
    float pointSize;
    
    int numParticles;
    deque<ofVec2f> positions;
    deque<ofVec2f> velocitys;
    deque<ofVec2f> forces;
    deque<ofColor> colors;
    float friction;
    
    ofVboMesh mesh;
    
    int x,y,w,h;
};

class Spectrum{
public:
    Spectrum();
    Spectrum(int _x, int _y, int _w, int _h);
    void draw(int milidiff, int milimax);
    int x,y,w,h;
};

class Compo{
public:
    Compo();
    Compo(int _x, int _y, int _w, int _h);
    void draw(int milidiff, int milimax);
    void draw(int milidiff, int milimax, float lowVal, float midVal, float highVal);
    void tripleDraw(int milidiff, int milimax);
    void tripleDraw(int milidiff, int milimax, float lowVal, float midVal, float highVal);
    int x,y,w,h;
};

class Akimoto {
    
public:
    Akimoto();
    
    //RandomWalker
    void RandomWalkerUp(vector<RandomWalkerAkimoto*> walker, ofPrimitiveMode mode);
    void RandomWalkerUp(vector<RandomWalkerAkimoto*> walker, ofPrimitiveMode mode, int size);
    void RandomWalkerUp(vector<RandomWalkerAkimoto*> walker, ofPrimitiveMode mode, int size, int milidiff, int milimax);
    ofVboMesh mesh;
    
    
    ofImage myImage;
    unsigned char * pixels;
    
    int particleNum;
    Particles *particles;
    
    int perlinWidth;
    int perlinHeight;
    
    //PerlinNoise
    void PerlinNoiseSetup(int _x, int _y, int _w, int _h);
    void PerlinNoiseUpdate();
    void PerlinNoiseDraw();

private:
};

