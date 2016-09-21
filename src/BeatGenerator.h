//
//  BeatGenerator.h
//  HeartBeatController
//
//  Created by 秋元和久 on 2016/09/20.



class BeatGenerator {
    
public:
    bool autoBeat(int mili, float BPM, float margin);
    BeatGenerator(){};
    BeatGenerator(int nxt, float x){nextTime = nxt; flct = x;};
private:
    int nextTime;
    float flct; //ゆらぎ
    void intermittentChaos(); //間欠カオス
};

