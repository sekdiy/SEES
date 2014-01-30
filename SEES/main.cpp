#include "Passenger.h"
#include "FloorBtn.h"
#include <systemc>
using namespace sc_core;

int sc_main (int argc, char * argv[]) {
    
    // Signals
    sc_signal<int> floorButtonPassengerInteraction[3];
    
    // Passengers
    Passenger pass1("Peter");
    Passenger pass2("Paul");
    Passenger pass3("Mary");
    
    // Button on each floor to request a lift going upwards
    FloorButton buttons("FloorButtons");
    
    for(int i = 0; i < 3; i++){
        
        floorButtonPassengerInteraction[i].write(-1);
        buttons.requests[i](floorButtonPassengerInteraction[i]);
    }
    
    pass1.request(floorButtonPassengerInteraction[0]);
    pass2.request(floorButtonPassengerInteraction[1]);
    pass3.request(floorButtonPassengerInteraction[2]);
    
    sc_start(15, SC_SEC);
    return 0;
}