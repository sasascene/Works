//
//  SceneF.cpp
//  MultiScene
//
//  Created by sasascene on 2014/12/13.
//
//

#include "SceneF.h"

const int SceneF::WIDTH;
const int SceneF::HEIGHT;
const int SceneF::NUM_PERTICLES;

void SceneF::setup(){
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // 視点の初期設定
    cam.setDistance(500);
    
    // ライトの初期設定
    light.enable();
    light.setSpotlight();
    light.setPosition(200, 2000, 5000);
    light.setAmbientColor(ofFloatColor(0.3, 0.3, 0.3, 0.5));
    light.setDiffuseColor(ofFloatColor(0.5, 0.5, 0.8, 0.5));
    light.setSpecularColor(ofFloatColor(0.8, 0.8, 0.8, 0.5));
    
    myVbo1.setVertexData(myVerts1, NUM_PERTICLES, GL_DYNAMIC_DRAW);
    myVbo2.setVertexData(myVerts2, NUM_PERTICLES, GL_DYNAMIC_DRAW);
    myVbo3.setVertexData(myVerts3, NUM_PERTICLES, GL_DYNAMIC_DRAW);
    myVbo4.setVertexData(myVerts4, NUM_PERTICLES, GL_DYNAMIC_DRAW);
    
    _noiseSeed = ofRandom(0.1);


}

void SceneF::update(){
    updateVertex();
}

void SceneF::draw(){
    ofBackground(0);
    drawObject();
    
}

// 頂点情報の更新
void SceneF::updateVertex(){
    
    // 頂点情報の初期化
    clearVertex();
    
}

// オブジェクト描画
void SceneF::drawObject(){
    
    cam.begin();
    
    // ベースの円
    float r = 50;
    float color = 10 + abs(100 * sin(ofGetElapsedTimeMillis() * 0.002));
    for(int i = 0; i < 360; i += 1){
        
        ofSetColor(color, color, color, 200);
        
        ofPushMatrix();
        ofRotateZ(i);
        ofTranslate(-25, r);
        ofRect(0, 0, 50, 10);
        ofPopMatrix();
    }
    
    cam.end();
    
    cam.begin();
    
    // 動く部分
    ofTranslate(0, 0, 10);
    ofPushMatrix();
        ofRotateZ(ofGetElapsedTimeMillis() * 0.02);
        ofSetColor(100, 100, 100 + pMagnitude[20]*100, 200);
        ofNoFill();
        ofSetLineWidth(1);
        ofPushMatrix();
            ofTranslate(-10, r);
            float rectWidth = 20 + pMagnitude[20] * 10;
            ofTranslate(0, -rectWidth/3);
            ofRect(0, 0, 20,  rectWidth);
        ofPopMatrix();
    ofPopMatrix();
    
    cam.end();
    
    // FFT のサークル
    cam.begin();

    float rMag = 60 + pMagnitude[50] * 10;
    if(rMag > 200){
        rMag = 200;
    }
    int eq = 0;
    
    ofFill();
    
    ofRotateZ(ofGetElapsedTimeMillis() * 0.02);
    
    for(int i = 0; i < 360; i += 18){
        
        ofSetColor(pMagnitude[20]*10, pMagnitude[30]*10, pMagnitude[80]*10, 200);
        
        ofPushMatrix();
        ofRotateZ(i);
        ofTranslate(-25, rMag);
        ofRect(0, 0, 50, pMagnitude[(eq+5)*3] * 3);
        ofPopMatrix();
        
        eq++;
    }

    cam.end();
    
}

// 座標情報のクリア
void SceneF::clearVertex(){
    
    for(int i = 0; i < NUM_PERTICLES; i++){
        myVerts1[i] = ofVec3f(0, 0, 0);
        myVerts2[i] = ofVec3f(0, 0, 0);
        myVerts3[i] = ofVec3f(0, 0, 0);
        myVerts4[i] = ofVec3f(0, 0, 0);
    }
    
    // 頂点情報の更新
    myVbo1.updateVertexData(myVerts1, NUM_PERTICLES);
    myVbo2.updateVertexData(myVerts2, NUM_PERTICLES);
    myVbo3.updateVertexData(myVerts3, NUM_PERTICLES);
    myVbo4.updateVertexData(myVerts4, NUM_PERTICLES);
}