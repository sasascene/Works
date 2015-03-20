//
//  Scene0.cpp
//  MultiScene
//
//  Created by sasascene on 2014/12/13.
//
//

#include "Scene0.h"

const int Scene0::WIDTH;
const int Scene0::HEIGHT;
const int Scene0::NUM_PERTICLES;

void Scene0::setup(){
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
    step = 10;

}

void Scene0::update(){
    updateVertex();
}

void Scene0::draw(){
    ofBackground(0);
    drawObject();
    
}

// 頂点情報の更新
void Scene0::updateVertex(){
    
    // 頂点情報の初期化
    clearVertex();
    
}

// オブジェクト描画
void Scene0::drawObject(){
    
    cam.begin();
    
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    
    ofNoFill();
    
    // 縦表示
    ofRotateZ(90);
    ofTranslate(-4 * ofGetWidth(), 0, -4000);
    
    // 描画
    ofPushStyle();
        ofPushMatrix();
            ofSetLineWidth(1);
            ofSetColor(pMagnitude[50]*10, pMagnitude[50]*10, pMagnitude[50]*10, 250);
            ofBeginShape();
            for (unsigned int i = 0; i < 1024; i+=1){
                ofVertex(i*10, -pLeft[i]*3000);
                ofVertex(i*10, -pRight[i]*3000);
            }
            ofEndShape(false);
        ofPopMatrix();
    ofPopStyle();
    
    cam.end();
    
}

// 座標情報のクリア
void Scene0::clearVertex(){
    
}