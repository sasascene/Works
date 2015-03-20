#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // 描画設定
    ofSetFrameRate(60);
    ofBackground(0);
    
    // Syphonサーバの設定
    server.setName("openFrameworks");
    
    // フルスクリーン
    //ofSetFullscreen(true);
    
    // カーソルの非表示
    ofHideCursor();
    
    // OSC
    receiver.setup(PORT);
    
    // 0
    BaseScene *s0 = new Scene0();
    s0->setup();
    scenes.push_back(s0);
    // A
    BaseScene *sa = new SceneA();
    sa->setup();
    scenes.push_back(sa);
    // B
    BaseScene *sb = new SceneB();
    sb->setup();
    scenes.push_back(sb);
    // C
    BaseScene *sc = new SceneC();
    sc->setup();
    scenes.push_back(sc);
    // D
    BaseScene *sd = new SceneD();
    sd->setup();
    scenes.push_back(sd);
    // E
    BaseScene *se = new SceneE();
    se->setup();
    scenes.push_back(se);
    // F
    BaseScene *sf = new SceneF();
    sf->setup();
    scenes.push_back(sf);

    
    // 初期パターン、シーンの指定
    currentPattern = 0;
    currentScene = 0;
    pictureIndex = 0;
    
    // サウンドの初期設定
    gain = 4;
    sound_init();
    
    //  load font
    font.loadFont("Arial.ttf", 10);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    // サウンド取得
    try{
        sound_get();
    }catch (...){
        
    }
    
    selectScene();
    
    // 現在のシーンに音量とスペクトルを渡す
    scenes[currentScene]->pLevel = &level;
    scenes[currentScene]->pMagnitude = magnitude;
    scenes[currentScene]->pLeft = left;
    scenes[currentScene]->pRight = right;
    
//    // 現在のシーンにコントローラを渡す
//    scenes[currentScene]->pKnob = knob;
//    scenes[currentScene]->pFader = fader;
//    scenes[currentScene]->pSolo = solo;
//    scenes[currentScene]->pMute = mute;
//    scenes[currentScene]->pRec = rec;
    
//    // 描画パラメータを渡す
//    scenes[currentScene]->pPointSize = &fader[7];
//    scenes[currentScene]->pLineWeight = &fader[6];
    
    // 現在のシーンを更新
    scenes[currentScene]->update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // 現在のシーンを描画
    scenes[currentScene]->draw();
    
    // Syhonへ送信
    server.publishScreen();
    
    // パラメータの表示
    for(int i = 0; i < 510; i += 10){
        ofSetColor(180, 180, 180);
        font.drawString(ofToString(i), 20, 100 + i);
        font.drawString(ofToString(magnitude[i]), 50, 100 + i);
    }

}

void ofApp::selectScene(){
    
    currentPattern = ofRandom(5);
    
    switch (currentPattern) {
            // 通常パターン
        case 0:
            if(magnitude[490] > 1){
                currentScene = 0;
            }
            if(magnitude[20] > 3){
                currentScene = 3;
                if(magnitude[30] > 2){
                    currentScene = 4;
                }
            }
            break;
            
        case 1:
            if(magnitude[490] > 1){
                currentScene = 0;
            }
            if(magnitude[10] > 3){
                currentScene = 6;
                if(magnitude[50] > 2){
                    currentScene = 2;
                }
            }
            break;
            
        case 2:
            if(magnitude[490] > 1){
                currentScene = 0;
            }
            if(magnitude[10] > 3){
                currentScene = 2;
                if(magnitude[50] > 2){
                    currentScene = 5;
                }
            }
            break;
            
        case 3:
            if(magnitude[490] > 1){
                currentScene = 0;
            }
            if(magnitude[90] > 2){
                currentScene = 6;
                if(magnitude[30] > 2){
                    currentScene = 2;
                }
            }
            break;
            
        case 4:
            if(magnitude[490] > 1){
                currentScene = 0;
            }
            if(magnitude[20] > 2){
                currentScene = 6;
                if(magnitude[80] > 1){
                    currentScene = 1;
                }
            }
            
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case '1':
            currentScene = 0;
            break;
        case '2':
            currentScene = 1;
            break;
        case '3':
            currentScene = 2;
            break;
        case '4':
            currentScene = 3;
            break;
        case '5':
            currentScene = 4;
            break;
        case '6':
            currentScene = 5;
            break;
        case '7':
            currentScene = 6;
            break;
        case 'r':
            scenes[currentScene]->clearVertex();
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

// サウンド初期設定
void ofApp::sound_init(){
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // BUFFER_SIZE samples per buffer
    // 4 num buffers (latency)
    
    ofSoundStreamSetup(0,2,this, 44100,BUFFER_SIZE, 4);
    left = new float[BUFFER_SIZE];
    right = new float[BUFFER_SIZE];
    
    for (int i = 0; i < NUM_WINDOWS; i++)
    {
        for (int j = 0; j < BUFFER_SIZE/2; j++)
        {
            freq[i][j] = 0;
        }
    }
}

// サウンド取得
void ofApp::sound_get(){
    static int index=0;
    float avg_power = 0.0f;
    
    if(index < 80)
        index += 1;
    else
        index = 0;
    
    /* do the FFT */
    myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
    
    /* start from 1 because mag[0] = DC component */
    /* and discard the upper half of the buffer */
    level = 0;
    for(int j=1; j < BUFFER_SIZE/2; j++) {
        freq[index][j] = magnitude[j]*gain*3;
        level += magnitude[j];
        magnitude[j] *= gain*2;
    }
    level = level*gain;
}

// サウンド取得時イベント
void ofApp::audioReceived(float * input, int bufferSize, int nChannels){
    // samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        left[i] = input[i*2];
        right[i] = input[i*2+1];
    }
    bufferCounter++;
}

