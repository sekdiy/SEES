#include "Passenger.h"
#include "FloorBtnUp.h"
#include <systemc>
using namespace sc_core;

int sc_main (int argc, char * argv[]) {

    // Signals
    sc_signal<int> floorButtonUpSignal[3];

    // Passengers
    Passenger pass1("Peter");
    //Passenger pass2("Paul");
    //Passenger pass3("Mary");

    // FloorButtons
    FloorButtonUp fbu("ButtonUp");
    fbu.requestUpFloor[0](floorButtonUpSignal[0]);
    pass1.requestUpFloor[0](floorButtonUpSignal[0]);
    //pass2.requestUpFloor(floorButtonUpSignal);
    //pass3.requestUpFloor(floorButtonUpSignal);

    sc_start(7, SC_SEC);
    return 0;
}

