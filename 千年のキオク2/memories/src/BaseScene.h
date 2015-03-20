//
//  BaseScene.h
//  MultiScene
//
//  Created by sasascene on 2014/12/13.
//
//

#ifndef __MultiScene__BaseScene__
#define __MultiScene__BaseScene__

#pragma once

#include "ofMain.h"

// 全てのシーンの雛形

class BaseScene {

public:
    
    //仮想関数 (virtual) として定義する
    virtual void setup(){};
    virtual void update(){};
    virtual void draw(){};
    virtual void keyPressed (int key){};
    virtual void keyReleased(int key){};
    virtual void mouseMoved(int x, int y ){};
    virtual void mouseDragged(int x, int y, int button){};
    virtual void mousePressed(int x, int y, int button){};
    virtual void mouseReleased(int x, int y, int button){};
    virtual void windowResized(int w, int h){};
    
    // サウンド
    float *pLevel;
    float *pMagnitude;
    float *pLeft;
    float *pRight;
    
    // コントローラ
    int *pKnob;
    int *pFader;
    int *pSolo;
    int *pMute;
    int *pRec;
    
    // 画像インデックス
    int *pPictureIndex;
    
    // 画像コレクション
    vector<ofImage> images;
    
    // 描画パラメータ
    int *pPointSize;
    int *pLineWeight;
    
    // ノイズ
    float noiseSeed;
    float perlinNoise;
    
    // 座標情報のクリア
    virtual void clearVertex(){};
};

#endif /* defined(__MultiScene__BaseScene__) */
