#include "Passenger.h"
#include "FloorBtnUp.h"
#include <systemc>
using namespace sc_core;

int sc_main (int argc, char * argv[]) {

    // Signals
    sc_signal<int> floorButtonUpSignal[3];
    
    
    // initialise signals
    for(int i = 0; i < 3; i++)
        floorButtonUpSignal[i].write(-1);
    
    // Passengers
    Passenger pass1("Peter");
    //Passenger pass2("Paul");
    //Passenger pass3("Mary");

    // FloorButtons
    FloorButtonUp fbu0("ButtonUp0");
    FloorButtonUp fbu1("ButtonUp1");
    FloorButtonUp fbu2("ButtonUp2");
    fbu0.position = 0;
    fbu1.position = 1;
    fbu2.position = 2;
    
    fbu0.requestUpFloor(floorButtonUpSignal[0]);
    fbu1.requestUpFloor(floorButtonUpSignal[1]);
    fbu2.requestUpFloor(floorButtonUpSignal[2]);
    
    pass1.requestUpFloor[0](floorButtonUpSignal[0]);
    pass1.requestUpFloor[1](floorButtonUpSignal[1]);
    pass1.requestUpFloor[2](floorButtonUpSignal[2]);
    /*
    pass2.requestUpFloor[0](floorButtonUpSignal[0]);
    pass2.requestUpFloor[1](floorButtonUpSignal[1]);
    pass2.requestUpFloor[2](floorButtonUpSignal[2]);
    */
    //pass2.requestUpFloor(floorButtonUpSignal);
    //pass3.requestUpFloor(floorButtonUpSignal);

    sc_start(70, SC_SEC);
    return 0;
}

