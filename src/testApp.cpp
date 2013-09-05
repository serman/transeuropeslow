#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    myStatus.setup();
    myModel.setup(&myStatus);
    ofSetFrameRate(30);
    if(myStatus.logmode)        ofLogToFile("logOFtes.txt", true);
    ofSetFullscreen(myStatus.fullscreen);
    
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
    //getRemoteMovie();
    //getRemoteSpeed();
    
    
    current_note_value=0;
    // print the available output ports to the console
    if(myStatus.midienabled){
        	midiOut.listPorts(); // via instance
	//ofxMidiOut::listPorts(); // via static too	
	// connect
	midiOut.openPort(0);	// by number
	//midiOut.openPort("IAC Driver Pure Data In");	// by name
	//midiOut.openVirtualPort("ofxMidiOut");		// open a virtual port
    }
    circlesize=0;
    if( myStatus.CITY != "mad" ){
    verdana30.loadFont("AlteHaasGroteskBold.ttf", 170, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);
    }
    else{ //Madrid
        verdana30.loadFont("AlteHaasGroteskBold.ttf", 25, true, true);

    }
    if( myStatus.CITY != "mad" ){
        verdana_small.loadFont("verdana.ttf",17,true,true);
    }
    else verdana_small.loadFont("verdana.ttf",10,true,true);
    
    ofSetCircleResolution(100);
    
    sender.setup("127.0.0.1", 12001);
    //getRemoteStatus();
        if(movieLoaded) currentMovie.draw(0,0);
        ofBackground(40, 40, 40);
}

//--------------------------------------------------------------
void testApp::update(){
    myStatus.setMotorTimer();
    if(movieLoaded==true){
        currentMovie.update();
        if(myStatus.bikeSpeed==0)
            currentMovie.setPaused(true);
        else
            currentMovie.setPaused(false);
    }
    if(myStatus.arduinoConnected && ofGetFrameNum()%1==0)
        myComm.readData();
    
    if(currentMovie.getPosition() >0.99 || circlesize>=900){
        setNextMovie();
    }
    if(myStatus.midienabled){
        if(ofGetFrameNum()%1==0)           sendMidiChange();
    }
    if(ofGetFrameNum()%1300==0)        myComm.sendToMotor();
    if(ofGetFrameNum()%1303==0)        myComm.sendToMotor();
    if(ofGetFrameNum()%220==0 && !myStatus.offline) {
        if ( myStatus.CITY=="hsk" ) getRemoteMovie();
        getRemoteSpeed(); //cada 4 segs aprox
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    //ofSetHexColor(0x000000);
    //ofRect(40,40,192,157);
    ofSetHexColor(0x000000);
    ofRect(40+36+36,40,48,16);

    ofSetHexColor(0x000000);
    ofRect(40+36,40+16,48+36+36,16);

    ofSetHexColor(0xFFFFFF);
    if(myStatus.CITY=="hsk") {
        if(movieLoaded) currentMovie.draw(0,0);
    }
    else if(myStatus.CITY=="lvp") {
        if(movieLoaded) currentMovie.draw(0,0,1360,768);
    }
    else if(myStatus.CITY=="mad") {
        if(movieLoaded) currentMovie.draw(20,72,222,125);
    }
    if((currentMovie.getDuration()-currentMovie.getPositionInSeconds())<5){
        myStatus.transitionMode=true;
        //ofLog()<< "transition "<< circlesize;
    }
    if(ofGetFrameNum()%25==0){
        //ofLog() << ofGetFrameRate() << "\n";
        //ofLog() << myStatus.bikeSpeed << "\n";
        //ofLog() << currentMovie.getPositionInSeconds() << " of " << currentMovie.getDuration() << " \n ";
    }
    if(ofGetFrameNum()%1800 < 400){
        drawBanner(ofGetFrameNum()%1800);
    }
    if(myStatus.transitionMode==true){
        drawTransition();
        
    }
    ofSetColor(255,255,255,200);
    if(myStatus.currentCity==MADRID)
        verdana_small.drawString("madrid",    112,70);
    else if(myStatus.currentCity==LIVERPOOL)
        verdana_small.drawString("helsinki", 111,70);
    else if(myStatus.currentCity==HELSINKI)
        verdana_small.drawString("liverpool",  109,70);
    
}

void testApp::drawTransition(){

    if(ofGetFrameNum()%40 <20){
        ofSetColor(255,255,255,200);
        if(myStatus.CITY!="mad")
            verdana30.drawString("JUMPING!", 70, 350);
        else // en madrid:
            verdana30.drawString("JUMPING!", 60, 120);
        transitioncounter+=1;        
    }

    if(transitioncounter>44){
        ofSetColor(0, 0, 0);
        if(myStatus.CITY!="mad")
            ofCircle(640, 360, circlesize);
        else //mad
            ofCircle(120, 130, circlesize/5);
        if(circlesize<900){
            circlesize+=24;
        }
    }
    
}

void testApp::drawBanner(int t){ //tiempo de 1 a 300 en fps en segs /25
    int w=1280;
    int h= 720;
    if (myStatus.CITY!="hsk"){
        w = 1360 ;
        h = 768  ;
    }
    ofSetColor(60, 60, 60, 60);
    ofRect(0,h-myStatus.bannerTmpWidth,w,myStatus.bannerTmpWidth);
    
    if(myStatus.bannerTmpWidth<80 && t<349)
        myStatus.bannerTmpWidth+=2;

    
    else if(t>349 && myStatus.bannerTmpWidth>0 ){
        myStatus.bannerTmpWidth-=2;
    }
    if (myStatus.bannerTmpWidth>77){
        ofSetColor(255);
        verdana_small.drawString("To read about what you see on this video, type http://tes.fact.co.uk on your mobile phone", 70, h-33);
    }
    
}

void testApp::setNextMovie(){
    movieLoaded=false;
    myModel.advanceMovie();
    currentMovie.stop();
//ofLog() <<"Antes de closemovie" << myStatus.currentMovie << "\n";
    //currentMovie.closeMovie();
//    ofLog() <<"fin -- " << myStatus.currentMovie << "\n";
    //myStatus.currentMovie= myModel.getCurrentMovie();
    
    currentMovie.loadMovie("movies/"+myStatus.currentMovie,decodeMode);
    //currentMovie.setLoopState(OF_LOOP_NONE);
    //currentMovie.setSynchronousSeeking(false);

    currentMovie.play();
    currentMovie.setPosition(0.01);
    movieLoaded=true;
    
    if(myStatus.fastmode) currentMovie.setPosition(0.75);
    myStatus.transitionMode=false;
    circlesize=0;
    transitioncounter=0;
}

void testApp::newResponse(ofxHttpResponse & response){
    if(ofIsStringInString( response.url, "getSpeed") ){

        responseStr = ofToString(response.status) + ": " + (string)response.responseBody;

        int remoteSpeed=ofToInt(response.responseBody);
                    cout<< "es speed " << remoteSpeed;
        if(remoteSpeed>=1 ){ //turn on the motor
            myStatus.motorStatus=true;
            myComm.sendToMotor();
            myStatus.nextAutoTurnOff=ofGetFrameNum()+1000;
                ofLog() << "motor remoto encendido" << "\n";
        }
        if( remoteSpeed==0 ) {//turn off the motor
            myStatus.motorStatus=false;
            myComm.sendToMotor();
            ofLog() << "motor remoto pagado" << "\n";
        }
        myStatus.remoteStatus=remoteSpeed;
    
    }else{ // nos est‡ llegando la pelicula
        myStatus.liverpoolMovie=ofToString(response.responseBody);      
        
    }
}

void testApp::drawBannerInfo(){
    ofRect(800, 0, 480, 200);
    verdana30.drawString("info general!", 800, 50);
    
}

void testApp::getRemoteSpeed(){
    ofxHttpForm form;
    if(myStatus.CITY=="hsk"){
        form.action = "http://transeuropeslow.fact.co.uk/getSpeedLiverpool";
        	form.addFormField("number", ofToString(myStatus.bikeSpeed ) );
    }
    else{
        form.action = "http://127.0.0.1/getSpeedHsk";
        form.addFormField("motor", ofToString(myStatus.motorStatus) );
        form.addFormField("speed", ofToString(myStatus.bikeSpeed ) );
        form.addFormField("arduino", ofToString(myStatus.arduinoConnected ) );
        
        vector<string> result=ofSplitString(myStatus.currentMovie,".mp4");
        form.addFormField("movie", ofToString(result[0]));
    }
    
    form.method = OFX_HTTP_GET;
    httpUtils.addForm(form);
}

void testApp::getRemoteMovie(){
    ofxHttpForm form;
    if(myStatus.CITY=="hsk") form.action = "http://transeuropeslow.fact.co.uk/getMovieLiverpool";
    else return;
	form.method = OFX_HTTP_GET;
	form.addFormField("hsk_movie", myStatus.currentMovie );
	httpUtils.addForm(form);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){ 
    
    
    if (key == OF_KEY_LEFT){
        myStatus.motorStatus=true;
        myStatus.nextAutoTurnOff=ofGetFrameNum()+1000;
        myComm.sendToMotor();
        ofLog() << "key left";
    }    
    else if (key == OF_KEY_RIGHT){
        ofLog() << "key right";
                myStatus.motorStatus=false;
        myComm.sendToMotor();
    }
    else if (key == OF_KEY_UP){
       // sendMidiNote();
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
    
  /**
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
	} **/


}

void testApp::oscSendEOV(){    
    ofxOscMessage m;
    m.setAddress("/video");
    vector<string> result=ofSplitString(myStatus.currentMovie,".mp4");
    ofLog() << result[0] ;
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
    midiOut.sendNoteOn(1, myStatus.currentCity,  current_note_value);
    oscSendEOV();
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}