//
//  systemStatus.h
//  tes_hsk
//
//  Created by Sergio Galan on 8/11/13.
//
//

#ifndef __tes_hsk__systemStatus__
#define __tes_hsk__systemStatus__

#include <iostream>

#define MADRID 36
#define LIVERPOOL 37
#define HELSINKI 38

class systemStatus{
    public:
        void setup();
        void setMotorTimer();
    
        bool motorStatus;
        int bikeSpeed;
        int remoteUsers;
        bool transitionMode;
        bool transitionMode2;
        bool arduinoConnected;
        bool httpServer;
        bool videoAvailable;
        bool standalone;
        bool printHUD;
        bool firstFrame;
        bool setNextMovie;
        int currentCity;
        std::string currentMovie;
        std::string CITY; // mad hsk lvp
        int remoteStatus;
        int bannerTmpWidth=0;
        std::string    liverpoolMovie="";
        bool logmode;
    bool midienabled;
    bool offline;
    int arduinoport;
    bool fullscreen;
    bool fastmode;
    int nextAutoTurnOff=1000; 

};
#endif /* defined(__tes_hsk__systemStatus__) */
