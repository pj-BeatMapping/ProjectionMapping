//
//  Akimoto.cpp
//  BeatMapping
//
//  Created by 秋元和久 on 2016/09/23.
//
//

#include "Akimoto.h"

Akimoto::Akimoto(){
    //RandomWalker
    //mesh.setMode(OF_PRIMITIVE_POINTS);
    //mesh.setMode(OF_PRIMITIVE_LINES);
    

}

Spectrum::Spectrum(){}

Spectrum::Spectrum(int _x, int _y, int _w, int _h){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Spectrum::draw(int milidiff, int milimax){
    //10段
    int num = 10;
    int blank = 5;//余白
    
    int spWidth = w-blank*2;
    int spHeight = (h-(num+2)*blank)/10;
    
    int upDownHeight;
    
    float rate = (float)milidiff/(float)milimax;
    
    rate *= rate;
    if(0 < rate && rate < 1){
        if(rate > 0.5){ //1~0.5は上にあがる
            rate = (-rate+1.0)*2.0;
        } else { //0.5~0は下がる
            rate = (rate)*2.0;
        }
    } else rate = 1;
    //printf("why %d",int(num*rate));
    ofSetColor(255);
    for(int i=0; i<int(num*rate); i++){
        //ofDrawRectangle(x, y, w, h);
        ofDrawRectangle(x+blank,y+h-(spHeight*(i+1)+blank*(i+1)),spWidth,spHeight);
    
    }
    
}

Compo::Compo(){}

Compo::Compo(int _x, int _y, int _w, int _h){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Compo::draw(int milidiff, int milimax){
    //5段
    int num = 5;
    int blank = w-h/5;//余白
    
    int spWidth = h/5;
    int spHeight = h/5;
    
    int upDownHeight;
    
    float rate = (float)milidiff/(float)milimax;
    
    rate *= rate;
    if(0 < rate && rate < 1){
        if(rate > 0.5){ //1~0.5は上にあがる
            rate = (-rate+1.0)*2.0;
        } else { //0.5~0は下がる
            rate = (rate)*2.0;
        }
    } else rate = 1;
    
    //printf("why %d",int(num*rate));
    ofSetColor(255);
    for(int i=0; i<int(num*rate); i++){
        //ofDrawRectangle(x, y, w, h);
        ofEllipse(x+w/2, y+h-(h/10+h/5*i), w/2, h/5);
        
    }
    
}

void Compo::draw(int milidiff, int milimax, float lowVal, float midVal, float highVal){
    //5段
    int num = 5;
    int blank = w-h/5;//余白
    
    int spWidth = h/5;
    int spHeight = h/5;
    
    int upDownHeight;
    
    float rate = (float)milidiff/(float)milimax;
    
    rate *= rate;
    if(0 < rate && rate < 1){
        if(rate > 0.5){ //1~0.5は上にあがる
            rate = (-rate+1.0)*2.0;
        } else { //0.5~0は下がる
            rate = (rate)*2.0;
        }
    } else rate = 1;
    
    //printf("why %d",int(num*rate));
    ofSetColor(255);
    for(int i=0; i<int(num*rate); i++){
        //ofDrawRectangle(x, y, w, h);
        //ofEllipse(x+w/2, y+h-(h/10+h/5*i), w/2, h/5);
        ofSetColor(lowVal, midVal, highVal,50);
        ofFill();
        ofCircle(x+w/2, y+h-(h/10+h/5*i), lowVal);
        ofCircle(x+w/2, y+h-(h/10+h/5*i), midVal);
        ofCircle(x+w/2, y+h-(h/10+h/5*i), highVal);
    }
    
}

void Compo::tripleDraw(int milidiff, int milimax){
    //5段
    int num = 5;
    int blank = w-h/5;//余白
    
    int spWidth = h/5;
    int spHeight = h/5;
    
    int upDownHeight;
    
    float rate = (float)milidiff/(float)milimax;
    
    rate *= rate;
    if(0 < rate && rate < 1){
        if(rate > 0.5){ //1~0.5は上にあがる
            rate = (-rate+1.0)*2.0;
        } else { //0.5~0は下がる
            rate = (rate)*2.0;
        }
    } else rate = 1;
    
    //printf("why %d",int(num*rate));
    ofSetColor(255);
    for(int i=0; i<int(num*rate); i++){
        //ofDrawRectangle(x, y, w, h);
        //ofEllipse(x+w/2, y+h-(h/10+h/5*i), w/2, h/5);
        ofSetColor(255, 255, 255, 50);
        ofFill();
        ofCircle(x+w/2, y+h-(h/10+h/5*i), 30);
        ofCircle(x+w/2, y+h-(h/10+h/5*i), 100);
        ofCircle(x+w/2, y+h-(h/10+h/5*i), 50);
    }
    
}


void Compo::tripleDraw(int milidiff, int milimax, float lowVal, float midVal, float highVal){
    //5段
    int num = 5;
    int blank = w-h/5;//余白
    
    int spWidth = h/5;
    int spHeight = h/5;
    
    //printf("why %d",int(num*rate));
    ofSetColor(255);
    for(int i=0; i<num; i++){
        //ofDrawRectangle(x, y, w, h);
        //ofEllipse(x+w/2, y+h-(h/10+h/5*i), w/2, h/5);
        ofSetColor(lowVal, midVal, highVal,50);
        ofFill();
        ofCircle(x+w/2, y+h-(h/10+h/5*i), lowVal);
        ofCircle(x+w/2, y+h-(h/10+h/5*i), midVal);
        ofCircle(x+w/2, y+h-(h/10+h/5*i), highVal);
    }
    
}

//RandomWalker
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

void RandomWalkerAkimoto::Reset(){
    //初期位置を画面中心に
    
    position.x = x + w/2.0;
    position.y = y + h;
    
    //移動確率をランダムに
    left = ofRandom(5, 20.0);
    right = ofRandom(5, 20.0);
    top = ofRandom(0, 30.0);
    bottom = ofRandom(0, 0.0);
}

void RandomWalkerAkimoto::Draw(){
    //上下左右同じ確率でランダムに移動
    
    int diff = ofRandom(-top, bottom);
    position.x += ofRandom(-left, right);
    position.y += diff;
    
    float rate = (float)(diff+top)/(float)(top+bottom);
    //printf("%f",rate);
    ofSetColor(255.0*(rate/2.0),255.0*(rate/2.0),255.0,100);
    
    
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

void RandomWalkerAkimoto::UpDownDraw(int milidiff, int milimax){
    //上下左右同じ確率でランダムに移動
    
    int diff = ofRandom(-top, bottom);
    position.x += ofRandom(-left, right);
    position.y += diff;
    
    float rate = (float)(diff+top)/(float)(top+bottom);
    //printf("%f",rate);
    ofSetColor(255.0*(rate/2.0),255.0*(rate/2.0),255.0,100);
    
    int upDownHeight;
    
    rate = (float)milidiff/(float)milimax;
    
    rate *= rate;
    if(0 < rate && rate < 1){
        if(rate > 0.5){ //1~0.5は上にあがる
            upDownHeight = (-rate+1.0)*2.0*(h);
        } else { //0.5~0は下がる
        upDownHeight = (rate)*2.0*(h);
        }
    }
    
    // 画面からはみ出たら、反対側から出現
    if (position.x < x) {
        position.x = x+w;
    }
    if (position.x > x+w) {
        position.x = x;
    }
    if (position.y < y+h-upDownHeight) {
        position.y = y+h;
    }
    if (position.y > y+h) {
        position.y = y+h-upDownHeight;
    }
}

void Akimoto::RandomWalkerUp(vector<RandomWalkerAkimoto*> walker, ofPrimitiveMode mode){
    mesh.setMode(mode);
    mesh.clear();
    ofSetColor(255,255,255,100);
    glPointSize(5);
    for (int i = 0; i < walker.size(); i++) {
        walker[i]->Draw();
        ofVec3f pos = ofVec3f(walker[i]->position.x,
                              walker[i]->position.y,
                              0);
        mesh.addVertex(pos);
    }
    mesh.draw();
}

void Akimoto::RandomWalkerUp(vector<RandomWalkerAkimoto*> walker, ofPrimitiveMode mode, int size){
    mesh.setMode(mode);
    mesh.clear();
    ofSetColor(255,255,255,100);
    glPointSize(size);
    for (int i = 0; i < walker.size(); i++) {
        
        walker[i]->Draw();
        ofVec3f pos = ofVec3f(walker[i]->position.x,
                              walker[i]->position.y,
                              0);
        mesh.addVertex(pos);
    }
    mesh.draw();
}

void Akimoto::RandomWalkerUp(vector<RandomWalkerAkimoto*> walker, ofPrimitiveMode mode, int size, int milidiff, int milimax){
    mesh.setMode(mode);
    mesh.clear();
    ofSetColor(255,255,255,100);
    glPointSize(size);
    for (int i = 0; i < walker.size(); i++) {
        
        walker[i]->UpDownDraw(milidiff, milimax);
        ofVec3f pos = ofVec3f(walker[i]->position.x,
                              walker[i]->position.y,
                              0);
        mesh.addVertex(pos);
    }
    mesh.draw();
}

Particles::Particles(int _maxParticles, int _x, int _y, int _w, int _h){
    maxParticles = _maxParticles;
    numParticles = 0;
    friction = 0.01;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}

void Particles::resetForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec2f(0, 0);
    }
}

void Particles::addForce(int count, ofVec2f force){
    forces[count] += force;
}

void Particles::addDampingForce(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] -= velocitys[i] * friction;
    }
}

void Particles::resetOffWalls(){
    float minx = 0;
    float miny = 0;
    float maxx = w;
    float maxy = h;
    //printf("%f, %f, %f, %f\n", minx,miny,maxx,maxy);
    
    for(int i = 0; i < positions.size(); i++){
        if (positions[i].x > maxx){
            positions[i].x = minx;
        }
        if (positions[i].y > maxy){
            positions[i].y = miny;
        }
        if (positions[i].x < minx){
            positions[i].x = maxx;
        }
        if (positions[i].y < miny){
            positions[i].y = maxy;
        }
    }
}

void Particles::updatePos(){
    for(int i = 0; i < positions.size(); i++){
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
    }
}

void Particles::update(){
    for(int i = 0; i < positions.size(); i++){
        forces[i] = ofVec2f(0, 0);
        forces[i] -= velocitys[i] * friction;
        velocitys[i] += forces[i];
        positions[i] += velocitys[i];
    }
}

void Particles::draw(){
    mesh.clear();
    for (int i = 0; i < positions.size(); i++) {
        mesh.addVertex(ofVec3f(x+positions[i].x, y+positions[i].y));
        mesh.addColor(ofFloatColor(1.0,1.0,1.0));
    }
    mesh.draw();
}

void Particles::addParticle(ofVec2f _position, ofVec2f _velocity, ofColor _color){
    positions.push_back(_position);
    velocitys.push_back(_velocity);
    colors.push_back(_color);
    forces.push_back(ofVec2f(0, 0));
    numParticles++;
    
    if (positions.size() > maxParticles) {
        positions.pop_front();
        colors.pop_front();
        velocitys.pop_front();
        forces.pop_front();
        numParticles--;
    }
}

void Akimoto::PerlinNoiseSetup(int _x, int _y, int _w, int _h){
    
    perlinWidth = _w;
    perlinHeight = _h;
    
    myImage.allocate(perlinWidth, perlinHeight, OF_IMAGE_GRAYSCALE);
    pixels = myImage.getPixels();
    
    float scaleX = ofRandom(3.0, 10.0);
    float scaleY = ofRandom(3.0, 10.0);
    for (int j = 0; j < perlinHeight; j++) {
        for (int i = 0; i < perlinWidth; i++) {
            float noiseX = ofMap(i, 0, perlinWidth, 0, scaleX);
            float noiseY = ofMap(j, 0, perlinHeight, 0, scaleY);
            int noiseVal = ofNoise(noiseX, noiseY) * 255;
            pixels[j * perlinWidth + i] = noiseVal;
        }
    }
    myImage.update();
    
    particleNum = 400;
    particles = new Particles(particleNum, _x, _y, _w, _h);
    particles->friction = 0.015;
    
    for (int i = 0; i < particleNum; i++) {
        ofVec3f position = ofVec3f(ofRandom(perlinWidth), ofRandom(perlinHeight));
        particles->addParticle(position);
    }

}

void Akimoto::PerlinNoiseUpdate(){
    float speed = 0.1;
    particles->resetForce();
    for (int i = 0; i < particleNum; i++) {
        int val = pixels[int(particles->positions[i].y) * perlinWidth + int(particles->positions[i].x)];
        int angle = ofMap(val, 0, 255, 0, PI*2.0);
        ofVec3f force;
        force.x = cos(angle) * speed;
        force.y = sin(angle) * speed;
        particles->addForce(i, force);
    }
    particles->addDampingForce();
    particles->updatePos();
    particles->resetOffWalls();
}

void Akimoto::PerlinNoiseDraw(){
    ofSetColor(50);
    myImage.draw(particles->x, particles->y);
    
    ofSetColor(255);
    particles->draw();
}
