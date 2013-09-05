#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "ofxXmlSettings.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
	
    ofxXmlSettings settings;
    
    int w=1280;
    int h = 720;
    std:string ciudad=settings.getValue("settings:city", "hsk");
    if (ciudad=="lvp"){
        w=1360;
        h=768;
    }
    if (ciudad=="mad"){
        w=1024;
        h=768;
    }
    ofSetupOpenGL(&window, w,h, OF_WINDOW);			// <-------- setup the GL context
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
