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
//    Passenger pass3("Mary");
    
    // Button on each floor to request a lift going upwards
    FloorButtonUp *floorButtonsUp[3];
    
    
    // construct and initialise floorButtonsUp
    for(int i = 0; i < 3; i++){
        floorButtonsUp[i] = new FloorButtonUp("ButtonUp");
        floorButtonsUp[i]->position = i;
        floorButtonsUp[i]->pushed = 0;
        
    }
    
    
    for(int i = 0; i < 3; i++){
        
        // initialise signals 0 - 9
        floorButtonUpSignal[0 + i*3].write(-1); // initialise signals
        floorButtonUpSignal[1 + i*3].write(-1); // initialise signals
        floorButtonUpSignal[2 + i*3].write(-1); // initialise signals
        
        
        floorButtonsUp[i]->requestUpFloor(floorButtonUpSignal[0 + i]); // connect ButtonUp with floorButtonUpSignal
        floorButtonsUp[i]->requestUpFloor(floorButtonUpSignal[3 + i]);
        floorButtonsUp[i]->requestUpFloor(floorButtonUpSignal[6 + i]);
        

        pass1.requestUpFloor[i](floorButtonUpSignal[0 + i]); // connect 0 - 0, 1 - 1, 2 - 2
        pass2.requestUpFloor[i](floorButtonUpSignal[3 + i]); // connect 0 - 3, 1 - 4, 2 - 5
//      pass3.requestUpFloor[i](floorButtonUpSignal[6 + i]); // connect 0 - 6, 1 - 7, 2 - 8
    }
    
    sc_start(15, SC_SEC);
    return 0;
}