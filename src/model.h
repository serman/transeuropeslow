//
//  model.h
//  tes_hsk
//
//  Created by Sergio Galan on 8/12/13.
//
//

#ifndef __tes_hsk__model__
#define __tes_hsk__model__

#include <iostream>
#include "systemStatus.h"
#include "ofMain.h"

#define NUMBER_OF_MOVIES 41

class model{
public:
    void setup(systemStatus *);
    void advanceMovie();
    void setThisMovie(std::string moviename);
    void setThisMovie(int movienumber );
    string getCurrentMovie();
    //vector<string> sequence;
    const char* sequence[NUMBER_OF_MOVIES]={
        "mad-huerto.mp4", //0
        "mad-boeticher1.mp4", //1
        "mad-arganzuela-rampa.mp4", //2
        "mad-calleIndustrial.mp4", //3
        "mad-casademcapocoches.mp4",//4
        "mad-ecobulevar.mp4",//5
        "mad-ensanche1.mp4",//6
        "mad-ensanche2.mp4",//7
        "mad-fabricasVillaverde.mp4", //8
        "mad-hexagonos.mp4", //9
        "mad-parquetematicoretro.mp4", //10
        "mad-VallecasPueblo.mp4" , //11
        "mad-ViasTren.mp4" ,    //12
        "lvp-anfield2.mp4", //13
        "lvp-anfield1.mp4", //14
        "lvp-barrio2.mp4", //15
        "lvp-callenorte.mp4",//16
        "lvp-centroprivado.mp4",//17
        "lvp-grafiti.mp4", //18
        "lvp-jamaica1.mp4", //19
        "lvp-pub-abandonado.mp4", //20
        "lvp-rumbo-al-norte.mp4", //21
        "lvp-tabacalera1.mp4", //22
        "lvp-tabacalera2.mp4", //23
        "lvp-parque1.mp4", //24
        "lvp-zonabonita.mp4", //25
        "lvp-tabacalera-almacen.mp4", //26
        "hsk-edificioBarcoNaranja.mp4", // 27 -
        "hsk-edificioDecorado.mp4", // 28 -
        "hsk-gentrificacion.mp4", //29 -
        "hsk-bosqueBonito.mp4",  //30 -
        "hsk-grafiti1.mp4",    //-31
        "hsk-casasAbandonadas.mp4",  //-32
        "hsk-ladrilloRojoPuerto.mp4",  //33 - 
        "hsk-poligonoFiesta.mp4",  // 34 -
        "hsk-restaurantDay.mp4", // 35 -
        "hsk-casasVias.mp4", // 36 -
        "hsk-super1.mp4", // 37 -
        "hsk-centroPeriferico.mp4", // 38 -
        "hsk-super2.mp4", // 39 -
        "hsk-cuevaCarbonGruas.mp4" // 40 -
  
    };
    int order[NUMBER_OF_MOVIES] ={0,35,16,28,1,36,18,31,2,22,3,34,24,5,13,32,6,37,19,29,7,23,15,8,33,9,10,40,26,38,27,25,11,17,12,39,14,20,4,30,21}; // 14 se repite
    systemStatus *myStatus;
    int sequenceNext;
};

#endif /* defined(__tes_hsk__model__) */
