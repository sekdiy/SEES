#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <systemc>
using namespace sc_core;

SC_MODULE(Elevator){
    
    // ports
    sc_in<int>      nextMode;           // mode of the elevator,  0 - idle, 1 - up, -1 - down
    sc_in<int>      nextTarget;         // the next destination
    sc_out<int>     doorCondition;      // sends the condition of the door to the control
    sc_inout<int>   position;           // the current position of the elevator; 0 - ground floor, 5 inbetween floor 0 and floor 1, 10 for 1st floor, 15 inbetween 1st and 2nd floor etc..
    sc_out<int>     doorOpen[3];        // signals to the passenger that the door is open
    sc_in<bool>     stopHere;           // true, if the a request comes from the current position
    sc_in<int>      barrier[3];         // signals that a passenger crossed the light barrier
    sc_out<int>     clearRequestAt;     // signals to the inner buttons that a floor is reached
    
    // members
    int doorConditions;             // 0 - closed, 1 - opening, 2 - opened, 3 - closing;
    int target;                     // the current target
    int mode;                       // the current mode
    
    // methods & threads
    void drive();                   // simulates the elevators journey to the next target
    void halt();                    // simulates the halt at a position
    
    
    SC_CTOR(Elevator){
        
        SC_THREAD(drive);
        sensitive << nextMode << nextTarget << barrier[0] << barrier[1] << barrier[2] << stopHere;
        
    };
};
#endif