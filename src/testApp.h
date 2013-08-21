#pragma once

#include "ofMain.h"
#include "systemStatus.h"
#include "model.h"
#include "comm.h"
#include "ofxHttpUtils.h"
#include "ofxMidi.h"
#include "ofxJSONElement.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void drawBanner(int t);
        void getRemoteMovie();
    void getRemoteSpeed();
        void newResponse(ofxHttpResponse & response);
        void sendMidiNote();
        void oscSendEOV();
    
    void getRemoteStatus();
    void drawTransition();
    int circlesize;
    int transitioncounter=0;
    		ofTrueTypeFont	verdana30;
    ofTrueTypeFont verdana_small;
    void sendMidiChange();
    void drawBannerInfo();;
        void readData();
        void setNextMovie();
        ofQTKitPlayer 		currentMovie;
        ofQTKitDecodeMode decodeMode;
        systemStatus        myStatus;
        model   myModel;
        comm myComm;
    
        ofxJSONElement result;
    
        ofxHttpUtils httpUtils;
        ofxMidiOut midiOut;
        ofxOscSender sender;
    
        int counter;
        string responseStr;
        string requestStr;
        string action_url;
        int current_note_value;
        bool movieLoaded;
		
};
