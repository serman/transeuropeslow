//
//  model.cpp
//  tes_hsk
//
//  Created by Sergio Galan on 8/12/13.
//
//

#include "model.h"

void model::setup(systemStatus * status){
    myStatus=status;
    //sequence={"mad-huerto.mp4", "mad-boeticher1.mp4", "mad-arganzuela-rampa.mp4","mad-calleIndustrial.mp4","mad-casademcapocoches.mp4","mad-ecobulevar.mp4","mad-ensanche1.mp4"};
    sequenceNext=10;
    myStatus->currentMovie = getCurrentMovie();
    
    
}

void model::advanceMovie(){
    sequenceNext++;
    if ( sequenceNext >= NUMBER_OF_MOVIES-1 ){
        sequenceNext=0;
    }
    myStatus->currentMovie=sequence[ order[sequenceNext] ];
    
    if(ofIsStringInString( sequence[ order[sequenceNext] ], "mad-") )
        myStatus->currentCity = MADRID;
    else if (ofIsStringInString( sequence[ order[sequenceNext] ], "liv-") )
        myStatus->currentCity = LIVERPOOL;
    
    if (ofIsStringInString( sequence[ order[sequenceNext] ], "boeticher") )
        myStatus->currentCity = HELSINKI;
    
    if (ofIsStringInString( sequence[ order[sequenceNext] ], "calleIndustrial") )
        myStatus->currentCity = HELSINKI;
    ofSendMessage("changed");
}

string model::getCurrentMovie(){
    return sequence[order[sequenceNext]];
    
}