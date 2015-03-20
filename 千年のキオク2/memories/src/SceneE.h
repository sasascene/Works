//
//  SceneE.h
//  MultiScene
//
//  Created by sasascene on 2014/12/13.
//
//

#ifndef __MultiScene__SceneE__
#define __MultiScene__SceneE__

#pragma once
#include "ofMain.h"
#include "BaseScene.h"
#include "ofxDelaunay.h"

// BaseSceneを継承したSceneE

class SceneE : public BaseScene {
    
public:
    void setup();
    void update();
    void draw();
    
    // 視点、ライト
    ofEasyCam cam;
    ofLight light;
    
    static const int WIDTH = 200;
    static const int HEIGHT = 200;
    static const int NUM_PERTICLES = WIDTH * HEIGHT;
    
    // ノイズの種
    float _noiseSeed;
    
    int step;
    
    // 頂点バッファオブジェクト
    ofVbo myVbo1;
    ofVbo myVbo2;
    ofVbo myVbo3;
    ofVbo myVbo4;
    // 頂点座標
    ofVec3f myVerts1[NUM_PERTICLES];
    ofVec3f myVerts2[NUM_PERTICLES];
    ofVec3f myVerts3[NUM_PERTICLES];
    ofVec3f myVerts4[NUM_PERTICLES];
    // 色情報
    ofFloatColor myColor[NUM_PERTICLES];
    
    // 頂点情報の更新
    void updateVertex();
    // オブジェクト描画
    void drawObject();
    // 座標情報のクリア
    void clearVertex();
    
    // ドロネー
    ofxDelaunay triangulation;
};

#endif /* defined(__MultiScene__SceneE__) */
