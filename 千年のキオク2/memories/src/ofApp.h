#pragma once

#include "ofMain.h"

#include "ofxOsc.h"
#include "ofxSyphon.h"
#include "sound_input.h"
#include "BaseScene.h"

#include "Scene0.h"
#include "SceneA.h"
#include "SceneB.h"
#include "SceneC.h"
#include "SceneD.h"
#include "SceneE.h"
#include "SceneF.h"

// listen on port 12345
#define PORT 12345

#define BUFFER_SIZE 1024
#define NUM_WINDOWS 80

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // OSC
    ofxOscReceiver receiver;
    
    // パターン切替関連
    int currentPattern;
    
    // シーン切替関連
    vector <BaseScene *> scenes;
    int currentScene;
    int pictureIndex;
    
    // シーン選択
    void selectScene();
    
    // サウンド関連
    void sound_init();
    void sound_get();
    void audioReceived  (float * input, int bufferSize, int nChannels);
    float * left;
    float * right;
    float gain;
    float level;
    float timeline_array[257][2];
    int  bufferCounter;
    fft  myfft;
    float phase[BUFFER_SIZE];
    float power[BUFFER_SIZE];
    float freq[NUM_WINDOWS][BUFFER_SIZE/2];
    float freq_phase[NUM_WINDOWS][BUFFER_SIZE/2];
    float magnitude[BUFFER_SIZE];
    
    // Syphon関連
    ofxSyphonServer server;
    
private:
    ofTrueTypeFont font;
    
};
