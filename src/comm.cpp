//
//  comm.cpp
//  tes_hsk
//
//  Created by Sergio Galan on 8/12/13.
//
//

#include "comm.h"
void comm::setup(systemStatus * status){
    myStatus=status;
    mySerial.enumerateDevices();
    myStatus->arduinoConnected = mySerial.setup(0, 4800);
    
}

void comm::readData(){
    int mySpeed=0;
    int seq=0;
    int rawData=0;
    int rawData2=0;
    int typeofMsg=0;
    unsigned char value[8];
    
    if(mySerial.available() >7){
        mySerial.readBytes(value,8);
        typeofMsg=value[0];
        seq= (value[1] << 8) +value[2];
        mySpeed = value[3];
        rawData= (value[4] << 8) +value[5];
        rawData2= (value[6] << 8) +value[7];
        
/**     unsigned short type= * (unsigned short *) value;
        unsigned short speed=* (unsigned short *) (value+2);
        unsigned short seq= *(unsigned short *)(value+4);
        unsigned short rawvalue = *(unsigned short *)(value+6);
        

        int type=  ((int)(value[1]&0xFF) << 8) + ((int)(value[0]&0xFF) << 0);
        int speed=((int)(value[3]&0xFF) << 8) + ((int)(value[2]&0xFF) << 0);;
        int seq= ((int)(value[5]&0xFF) << 8) + ((int)(value[4]&0xFF) << 0);
        unsigned char rawvalue = value[7];
        **/
        
        myStatus->bikeSpeed=mySpeed;
        mySerial.flush();
        //printf("%x %x ", value[0], value[4] );
        //cout << value;
        cout << seq<< " : " << myStatus->bikeSpeed << " valor leido "<< rawData  << " valor leido2 "<< rawData2 <<" \n";
        
    }
    
}

void comm::sendToMotor(){
    if(myStatus->arduinoConnected==false )
        return;
    if(myStatus->motorStatus){
        mySerial.writeByte(1);
        //cout << "sending 1";
    }
    else
        mySerial.writeByte(0);
    
}