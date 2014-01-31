#include "Passenger.h"
#include "FloorBtn.h"
#include "Control.h"
#include <systemc>
using namespace sc_core;

int sc_main (int argc, char * argv[]) {
    
    // Signals
    sc_signal<int> floorButtonPassengerInteraction[3];
    sc_signal<int> floorCtrlUwInteraction[3];
    sc_signal<int> floorCtrlDwInteraction[3];
    
    // Control
    Control ctrl("Main_Control");
    
    // Passengers
    Passenger pass1("Peter");
    Passenger pass2("Paul");
    Passenger pass3("Mary");
    
    // Button on each floor to request a lift going upwards
    FloorButton buttons("FloorButtons");
    
    for(int i = 0; i < 3; i++){
        
        // initialise signals
        floorButtonPassengerInteraction[i].write(-1);
        
        // bind ports
        buttons.requests[i](floorButtonPassengerInteraction[i]);
        buttons.pushedUp[i](floorCtrlUwInteraction[i]);
        buttons.pushedDown[i](floorCtrlDwInteraction[i]);
        //
        ctrl.uwRequests[i](floorCtrlUwInteraction[i]);
        ctrl.dwRequests[i](floorCtrlDwInteraction[i]);
    }
    
    pass1.request(floorButtonPassengerInteraction[0]);
    pass2.request(floorButtonPassengerInteraction[1]);
    pass3.request(floorButtonPassengerInteraction[2]);
    
    sc_start(15, SC_SEC);
    return 0;
}