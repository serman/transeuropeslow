//
//  comm.h
//  tes_hsk
//
//  Created by Sergio Galan on 8/12/13.
//
//

#ifndef __tes_hsk__comm__
#define __tes_hsk__comm__

#include <iostream>
#include "systemStatus.h"
#include "ofMain.h"

class comm{
public:
    void setup( systemStatus * );
    void readData();
    void sendToMotor();
    void closeSerial();

    ofSerial mySerial;
    systemStatus *myStatus;

};

#endif /* defined(__tes_hsk__comm__) */
