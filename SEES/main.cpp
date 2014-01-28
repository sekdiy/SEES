#include "Passenger.h"
#include "FloorBtnUp.h"
#include <systemc>
using namespace sc_core;

int sc_main (int argc, char * argv[]) {

    // Signals
    sc_signal<int> floorButtonUpSignal[9];
    
    // Passengers
    Passenger pass1("Peter");
    Passenger pass2("Paul");
    Passenger pass3("Mary");

    // FloorButtons
    FloorButtonUp fbu0("ButtonUp0");
    FloorButtonUp fbu1("ButtonUp1");
    FloorButtonUp fbu2("ButtonUp2");
    fbu0.position = 0;
    fbu1.position = 1;
    fbu2.position = 2;
    
    for(int i = 0; i < 3; i++){
        floorButtonUpSignal[i].write(-1); // initialise signals
        fbu0.requestUpFloor(floorButtonUpSignal[0 + i*3]); // connect with floorButtonUpSignal 0, 3, 6
        fbu1.requestUpFloor(floorButtonUpSignal[1 + i*3]); // connect with floorButtonUpSignal 1, 4, 7
        fbu2.requestUpFloor(floorButtonUpSignal[2 + i*3]); // connect with floorButtonUpSignal 2, 5, 8
        
        pass1.requestUpFloor[i](floorButtonUpSignal[0 + i]); // connect 0 - 0, 1 - 1, 2 - 2
        pass2.requestUpFloor[i](floorButtonUpSignal[3 + i]); // connect 0 - 3, 1 - 4, 2 - 5
        pass3.requestUpFloor[i](floorButtonUpSignal[6 + i]); // connect 0 - 6, 1 - 7, 2 - 8
    }

    sc_start(10, SC_SEC);
    return 0;
}

