#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofLogToFile("logOFtes.txt", true);
    
    myStatus.setup();
    myModel.setup(&myStatus);
    ofSetFrameRate(30);
    ofLog() << myStatus.currentMovie ;
    currentMovie.setPixelFormat(OF_PIXELS_RGB);
    decodeMode = OF_QTKIT_DECODE_PIXELS_AND_TEXTURE;
    currentMovie.loadMovie( "movies/"+myStatus.currentMovie, decodeMode);

    currentMovie.setLoopState(OF_LOOP_NONE);
	 currentMovie.play();
        movieLoaded=true;
    currentMovie.setSynchronousSeeking(false);
    myComm.setup( &myStatus );
    
    ofAddListener(httpUtils.newResponseEvent,this,&testApp::newResponse);
	httpUtils.start();
    getRemoteMovie();
    
    
    current_note_value=0;
    // print the available output ports to the console
	midiOut.listPorts(); // via instance
	//ofxMidiOut::listPorts(); // via static too	
	// connect
	midiOut.openPort(0);	// by number
	//midiOut.openPort("IAC Driver Pure Data In");	// by name
	//midiOut.openVirtualPort("ofxMidiOut");		// open a virtual port
    
    circlesize=0;
    verdana30.loadFont("verdana.ttf", 100, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);

    verdana_small.loadFont("verdana.ttf",20,true,true);
        ofSetCircleResolution(100);
    
    sender.setup("127.0.0.1", 12001);
    //getRemoteStatus();
    
}

//--------------------------------------------------------------
void testApp::update(){
    if(movieLoaded==true){
        currentMovie.update();
        if(myStatus.bikeSpeed==0)
            currentMovie.setPaused(true);
        else
            currentMovie.setPaused(false);
    }
    if(myStatus.arduinoConnected && ofGetFrameNum()%3==0)
        myComm.readData();
    
    if(currentMovie.getPosition() >0.99 || circlesize>=800){
        setNextMovie();
    }
    
    if(ofGetFrameNum()%1==0)           sendMidiChange();
    
    if(ofGetFrameNum()%1500==0)        myComm.sendToMotor();
    if(ofGetFrameNum()%1503==0)        myComm.sendToMotor();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 0);
    ofSetHexColor(0xFFFFFF);
    if(movieLoaded) currentMovie.draw(0,0);

    if((currentMovie.getDuration()-currentMovie.getPositionInSeconds())<5){
        myStatus.transitionMode=true;
        //ofLog()<< "transition "<< circlesize;
    }
    if(ofGetFrameNum()%25==0){
        //ofLog() << ofGetFrameRate() << "\n";
        //ofLog() << myStatus.bikeSpeed << "\n";
        //ofLog() << currentMovie.getPositionInSeconds() << " of " << currentMovie.getDuration() << " \n ";
    }
    if(myStatus.transitionMode==true){
        drawTransition();
        
    }    
}

void testApp::drawTransition(){

    if(ofGetFrameNum()%40 <20){
        verdana30.drawString("JUMPING!", 300, 300);
        transitioncounter+=1;        
    }

    if(transitioncounter>40){
        ofSetColor(0, 0, 0);
        ofCircle(640, 360, circlesize);
        
        if(circlesize<800){
            circlesize+=24;
        }
    }
    
}


void testApp::setNextMovie(){
    movieLoaded=false;
    myModel.advanceMovie();
    currentMovie.stop();
    ofLog() <<"Antes de closemovie" << myStatus.currentMovie << "\n";
    //currentMovie.closeMovie();
    ofLog() <<"fin -- " << myStatus.currentMovie << "\n";
    //myStatus.currentMovie= myModel.getCurrentMovie();
    
    currentMovie.loadMovie("movies/"+myStatus.currentMovie,decodeMode);
    //currentMovie.setLoopState(OF_LOOP_NONE);
    //currentMovie.setSynchronousSeeking(false);
    movieLoaded=true;
    currentMovie.play();
    //currentMovie.setPosition(0.70);
    myStatus.transitionMode=false;
    circlesize=0;
    transitioncounter=0;
}

void testApp::newResponse(ofxHttpResponse & response){
	responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
    ofLog() << response.responseBody << "\n";
    int remoteSpeed=ofToInt(response.responseBody);
    
    if(myStatus.remoteStatus==0 && remoteSpeed==1 ){ //turn on the motor
        myStatus.motorStatus=true;
        myComm.sendToMotor();
    }
    if(myStatus.remoteStatus==1 && remoteSpeed==0 ) {//turn off the motor
        myStatus.motorStatus=false;
        myComm.sendToMotor();
    }
    myStatus.remoteStatus=remoteSpeed;
}

void testApp::drawBannerInfo(){
    ofRect(800, 0, 480, 200);
    verdana30.drawString("info general!", 800, 50);
    
}

void testApp::getRemoteMovie(){
    ofxHttpForm form;
	form.action = "http://transeuropeslow.fact.co.uk/getSpeed";
	form.method = OFX_HTTP_GET;
	form.addFormField("number", ofToString(myStatus.bikeSpeed ) );
	httpUtils.addForm(form);
}
//--------------------------------------------------------------
void testApp::keyPressed(int key){ 
    
    
    if (key == OF_KEY_LEFT){
        myStatus.motorStatus=true;
        myComm.sendToMotor();
        ofLog() << "key left";
    }    
    else if (key == OF_KEY_RIGHT){
        ofLog() << "key right";
                myStatus.motorStatus=false;
        myComm.sendToMotor();
    }
    else if (key == OF_KEY_UP){
        sendMidiNote();
    }
    
    else{
        if(myStatus.bikeSpeed>0)
            myStatus.bikeSpeed=0;
        else
            myStatus.bikeSpeed=1;        
    }
}

void testApp::sendMidiNote(){
        midiOut.sendNoteOn(1, myStatus.currentCity,  current_note_value);
    }

void testApp::sendMidiChange(){
    int sendNote=myStatus.bikeSpeed*50;
    //if(sendNote != current_note_value){
        //midiOut.sendNoteOn(1, myStatus.currentCity,  current_note_value);
        if (current_note_value>sendNote && current_note_value>0) current_note_value-=1;
        if(current_note_value<0) current_note_value=0;
        if (current_note_value<sendNote ) current_note_value+=1;
        //if(ofGetFrameNum()%25==0)
        //    ofLog() << current_note_value << "\n";
        if(current_note_value==0) current_note_value=1;
        midiOut.sendControlChange(1, 8, current_note_value);
    //}
}


void testApp::getRemoteStatus(){
    
    std::string url = "http://transeuropeslow.fact.co.uk/getStatus";
	
    
	// Now parse the JSON
	bool parsingSuccessful = result.open(url);
    
	if (parsingSuccessful) {
        //result.getMemberNames();
		ofLog() <<       result.size();
		//ofLog() << result.getMemberNames() << endl;
        ofLog() << result["speed"] ;
        
	} else {
		ofLog()  << "Failed to parse JSON" << endl;
	}


}

void testApp::oscSendEOV(){    
    ofxOscMessage m;
    m.setAddress("/video");
    m.addStringArg(myStatus.currentMovie);
    sender.sendMessage(m);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    currentMovie.setPosition(0.90);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    ofLog() << msg.message;
    //midiOut.sendNoteOn(1, myStatus.currentCity,  current_note_value);
    oscSendEOV();
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}