//
//  systemStatus.cpp
//  tes_hsk
//
//  Created by Sergio Galan on 8/11/13.
//
//
#include <string>
#include "systemStatus.h"
#include "ofxXmlSettings.h"

void systemStatus::setup(){
    motorStatus=false;
    bikeSpeed=0;
    remoteUsers=0;
    transitionMode=false;
    transitionMode2=false;
    arduinoConnected=true;
    httpServer=true;
    videoAvailable=false;
    standalone=true;
    printHUD=false;
    firstFrame=true;
    setNextMovie=false;
    currentMovie="lvp-barrio2.mpg";
    currentCity=MADRID;
    ofxXmlSettings settings;
    
    if(!settings.loadFile("settings.xml"))
        ofLog() <<" SETTINGS FILE NOT FOUND"     ;
    CITY=settings.getValue("settings:city", "");
    ofLog() <<" current city is " << CITY;

    
}