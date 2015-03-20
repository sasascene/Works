//
//  SceneD.cpp
//  MultiScene
//
//  Created by sasascene on 2014/12/13.
//
//

#include "SceneD.h"

const int SceneD::WIDTH;
const int SceneD::HEIGHT;
const int SceneD::NUM_PERTICLES;

void SceneD::setup(){
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
    
    step = 5;

}

void SceneD::update(){
    updateVertex();
}

void SceneD::draw(){
    ofBackground(0);
    drawObject();
    
}

// 頂点情報の更新
void SceneD::updateVertex(){
    
    // 頂点情報の初期化
    clearVertex();
    
    triangulation.reset();
    
//    int step = 1 + ofNoise(_noiseSeed)*30;
//    
//    float r1 = 200;
//    for(int i = 0; i < 360; i += step){
//        float rn1 = r1 + ofNoise(_noiseSeed) * 5 + pMagnitude[20]*3;
//        float radi = ofDegToRad(i);
//        float x = rn1 * cos(radi);
//        float y = rn1 * sin(radi);
//        myVerts1[i/step] = ofVec3f(x, y, 0);
//        _noiseSeed += 0.01;
//        
//        if(ofRandom(1) > 0.6){
//            triangulation.addPoint(ofPoint(x, y, 0));
//        }
//    }
//    
//    float r2 = 150;
//    for(int i = 0; i < 720; i += step){
//        float rn2 = r2 + ofNoise(_noiseSeed) * 10  + pMagnitude[30]*3;
//        float radi = ofDegToRad(i);
//        float x = rn2 * cos(radi);
//        float y = rn2 * sin(radi);
//        myVerts2[i/step] = ofVec3f(x, y, 0);
//        _noiseSeed += 0.01;
//        
//        if(ofRandom(1) > 0.7){
//            triangulation.addPoint(ofPoint(x, y, 0));
//        }
//    }
//    
//    float r3 = 100 + pMagnitude[16];
//    for(int i = 0; i < 360; i += step){
//        float rn3 = r3 + ofNoise(_noiseSeed) * 10  + pMagnitude[40]*3;
//        float radi = ofDegToRad(i);
//        float x = rn3 * cos(radi);
//        float y = rn3 * sin(radi);
//        myVerts3[i/step] = ofVec3f(x, y, 0);
//        _noiseSeed += 0.01;
//        
//        if(ofRandom(1) > 0.8){
//            triangulation.addPoint(ofPoint(x, y, 0));
//        }
//    }
//    
//    float r4 = 50;
//    for(int i = 0; i < 360; i += step){
//        float rn4 = r4 + ofNoise(_noiseSeed) * 3 + pMagnitude[60]*3;
//        float radi = ofDegToRad(i);
//        float x = rn4 * cos(radi);
//        float y = rn4 * sin(radi);
//        myVerts4[i/step] = ofVec3f(x, y, 0);
//        _noiseSeed += 0.01;
//        
//        if(ofRandom(1) > 0.4){
//            triangulation.addPoint(ofPoint(x, y, 0));
//        }
//    }
//    
    // 頂点情報の更新
    myVbo1.updateVertexData(myVerts1, NUM_PERTICLES);
    myVbo2.updateVertexData(myVerts2, NUM_PERTICLES);
    myVbo3.updateVertexData(myVerts3, NUM_PERTICLES);
    myVbo4.updateVertexData(myVerts4, NUM_PERTICLES);
}

// オブジェクト描画
void SceneD::drawObject(){
    
//    // ドロネー
//    cam.begin();
//    
//    glEnable(GL_POINT_SMOOTH);
//    glEnable(GL_LINE_SMOOTH);
//    
//    ofBackground(0);
//    
//    ofNoFill();
//    
//    ofPushMatrix();
//        glLineWidth(1);
//        ofSetColor(pMagnitude[50]*7, pMagnitude[50]*7, pMagnitude[50]*8, 170);
//        triangulation.triangulate();
//        triangulation.draw();
//    ofPopMatrix();
//    
//    cam.end();
    
    
    step = 5;
    
    cam.begin();
    
    ofFill();
    
    // ベースの円
    ofPushMatrix();
    ofRotateZ(ofGetElapsedTimeMillis() * -0.02);
    float rMag1 = 50;
    float color = 10 + abs(100 * sin(ofGetElapsedTimeMillis() * 0.002));
    for(int i = 0; i < 360 * pMagnitude[5] * 0.005; i += step){
        
        ofSetColor(color, color, color, 200);
        
        ofPushMatrix();
            ofRotateZ(i);
            ofTranslate(-25, rMag1);
            ofRect(0, 0, 50, 5);
        ofPopMatrix();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateZ(ofGetElapsedTimeMillis() * 0.03);
    float rMag2 = 80;
    for(int i = 0; i < 360 * pMagnitude[10] * 0.02; i += step){
        
        ofSetColor(color, color, color, 200);
        
        ofPushMatrix();
        ofRotateZ(i);
        ofTranslate(-25, rMag2);
        ofRect(0, 0, 50, 5);
        ofPopMatrix();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateZ(ofGetElapsedTimeMillis() * -0.04);
    float rMag3 = 110;
    for(int i = 0; i < 360 * pMagnitude[15] * 0.05; i += step){
        
        ofSetColor(color, color, color, 200);
        
        ofPushMatrix();
        ofRotateZ(i);
        ofTranslate(-25, rMag3);
        ofRect(0, 0, 50, 5);
        ofPopMatrix();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateZ(ofGetElapsedTimeMillis() * 0.08);
    float rMag4 = 140;
    for(int i = 0; i < 360 * pMagnitude[30] * 0.5; i += step){
        
        ofSetColor(color, color, color, 200);
        
        ofPushMatrix();
        ofRotateZ(i);
        ofTranslate(-25, rMag4);
        ofRect(0, 0, 50, 5);
        ofPopMatrix();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofRotateZ(ofGetElapsedTimeMillis() * -0.12);
    float rMag5 = 170;
    for(int i = 0; i < 360 * pMagnitude[40] * 0.5; i += step){
        
        ofSetColor(color, color, color, 200);
        
        ofPushMatrix();
        ofRotateZ(i);
        ofTranslate(-25, rMag5);
        ofRect(0, 0, 50, 5);
        ofPopMatrix();
    }
    ofPopMatrix();
    
    // 動く部分
    ofTranslate(0, 0, 10);
    ofPushMatrix();
        ofRotateZ(ofGetElapsedTimeMillis() * 0.02);
        ofSetColor(100, 100, 100 + pMagnitude[20]*100, 200);
        ofNoFill();
        ofSetLineWidth(1);
    
        ofPushMatrix();
            ofTranslate(-10, rMag1);
            float rectWidth = 260;
            ofTranslate(0, -rectWidth/3);
            ofRect(0, 0, 4,  rectWidth);
        ofPopMatrix();
    ofPopMatrix();
    
    cam.end();
    
//    // FFT のサークル
//    cam.begin();
//    
//    float r2 = 100;
//    int eq = 0;
//    
//    ofRotateZ(ofGetElapsedTimeMillis() * -0.02);
//    
//    ofPushStyle();
//    ofFill();
//    for(int i = 0; i < 360; i += 18){
//        
//        ofSetColor(pMagnitude[20]*10, pMagnitude[30]*10, pMagnitude[50]*10, 200);
//        ofPushMatrix();
//            ofRotateZ(i);
//            ofTranslate(-10, r2);
//            float fftRectWidth = pMagnitude[(eq+1)];
//            if(fftRectWidth > 40){
//                fftRectWidth = 40;
//            }
//            ofRect(0, 0, 20, fftRectWidth);
//        ofPopMatrix();
//        
//        eq++;
//    }
//    ofPopStyle();
//    
//    cam.end();
//    
//    // FFT のサークル
//    cam.begin();
//    
//    float r3 = 150;
//    
//    ofRotateZ(ofGetElapsedTimeMillis() * 0.02);
//    
//    ofPushStyle();
//    ofFill();
//    for(int i = 0; i < 360; i += 18){
//        
//        ofSetColor(pMagnitude[20]*10, pMagnitude[30]*10, pMagnitude[50]*10, 200);
//        ofPushMatrix();
//        ofRotateZ(i);
//        ofTranslate(-10, r3);
//        float fftRectWidth = pMagnitude[(eq+1)];
//        if(fftRectWidth > 40){
//            fftRectWidth = 40;
//        }
//        ofRect(0, 0, 20, fftRectWidth);
//        ofPopMatrix();
//        
//        eq++;
//    }
//    ofPopStyle();
//    
//    cam.end();
    
}

// 座標情報のクリア
void SceneD::clearVertex(){
    
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