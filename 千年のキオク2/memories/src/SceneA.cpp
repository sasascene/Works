//
//  SceneA.cpp
//  MultiScene
//
//  Created by sasascene on 2014/12/13.
//
//

#include "SceneA.h"

const int SceneA::WIDTH;
const int SceneA::HEIGHT;
const int SceneA::NUM_PERTICLES;

void SceneA::setup(){
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

void SceneA::update(){
    updateVertex();
}

void SceneA::draw(){
    ofBackground(0);
    drawObject();
    
}

// 頂点情報の更新
void SceneA::updateVertex(){
    
    // 頂点情報の初期化
    clearVertex();
    
    int step = 5;
    
    float r1 = 200;
    for(int i = 0; i < 360; i += step){
        float rn1 = r1 + ofNoise(_noiseSeed) * 5;
        float radi = ofDegToRad(i);
        float x = rn1 * cos(radi);
        float y = rn1 * sin(radi);
        myVerts1[i/step] = ofVec3f(x, y, 0);
        _noiseSeed += 0.01;
    }
    
    float r2 = 150;
    for(int i = 0; i < 720; i += step){
        float rn2 = r2 + ofNoise(_noiseSeed) * 10;
        float radi = ofDegToRad(i);
        float x = rn2 * cos(radi);
        float y = rn2 * sin(radi);
        myVerts2[i/step] = ofVec3f(x, y, 0);
        _noiseSeed += 0.01;
    }
    
    float r3 = 100 + pMagnitude[16];
    for(int i = 0; i < 360; i += step){
        float radi = ofDegToRad(i);
        float x = r3 * cos(radi);
        float y = r3 * sin(radi);
        myVerts3[i/step] = ofVec3f(x, y, 0);
        _noiseSeed += 0.01;
    }
    
    float r4 = 50;
    for(int i = 0; i < 360; i += step){
        float rn4 = r4 + ofNoise(_noiseSeed) * 3;
        float radi = ofDegToRad(i);
        float x = rn4 * cos(radi);
        float y = rn4 * sin(radi);
        myVerts4[i/step] = ofVec3f(x, y, 0);
        _noiseSeed += 0.01;
    }
    
    // 頂点情報の更新
    myVbo1.updateVertexData(myVerts1, NUM_PERTICLES);
    myVbo2.updateVertexData(myVerts2, NUM_PERTICLES);
    myVbo3.updateVertexData(myVerts3, NUM_PERTICLES);
    myVbo4.updateVertexData(myVerts4, NUM_PERTICLES);
}

// オブジェクト描画
void SceneA::drawObject(){
    
    cam.begin();
    
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    
    // 外側から描画
    // 1列目
    ofPushMatrix();
        ofSetColor(pMagnitude[20]*10, pMagnitude[20]*10, pMagnitude[20]*10, 250);
        ofSetLineWidth(2);
        ofRotateZ(ofGetElapsedTimeMillis() * 0.02);
        myVbo1.draw(GL_LINES, 0, 360/5);
    ofPopMatrix();
    
    // 2列目
    ofPushMatrix();
        ofSetColor(pMagnitude[30]*30, pMagnitude[30]*30, pMagnitude[30]*30, 250);
        ofSetLineWidth(2);
        ofRotateZ(ofGetElapsedTimeMillis() * -0.02);
        myVbo2.draw(GL_LINE_LOOP, 0, 360/5);
        ofSetColor(pMagnitude[40]*30, pMagnitude[40]*30, pMagnitude[40]*30, 250);
        glPointSize(pMagnitude[40]*5);
        myVbo2.draw(GL_POINTS, 360/5, 360/5);
    ofPopMatrix();
    
    // 3列目
    ofPushMatrix();
        ofSetColor(pMagnitude[20]*10, pMagnitude[20]*10, pMagnitude[20]*10, 250);
        ofSetLineWidth(*pLevel);
        ofRotateZ(ofGetElapsedTimeMillis() * 0.04);
        myVbo3.draw(GL_LINES, 0, 360/5);
    ofPopMatrix();
    
    // 4列目
    ofPushMatrix();
        ofSetColor(pMagnitude[50]*10, pMagnitude[50]*10, pMagnitude[50]*10, 250);
        ofSetLineWidth(pMagnitude[50]);
        ofRotateZ(ofGetElapsedTimeMillis() * -0.02);
        myVbo4.draw(GL_LINE_LOOP, 0, 360/5);
    ofPopMatrix();
    
    cam.end();
    
}

// 座標情報のクリア
void SceneA::clearVertex(){
    
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