#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <systemc>
using namespace sc_core;

SC_MODULE(Elevator){
    
    // ports
    sc_in<int> mode;            // mode of the elevator,  0 - idle, 1 - up, -1 - down
    sc_in<int> target;          // the next destination
    sc_inout<int> position;     // the current position of the elevator; 0 - ground floor, 5 inbetween floor 0 and floor 1, 10 for 1st floor, 15 inbetween 1st and 2nd floor etc..

    sc_in<int> barrier; // signals that a passenger crossed the light barrier
    
    // members
    int doorConditions; // 0 - closed, 1 - opening, 2 - opened, 3 - closing;
    
    void drive();
    
    
    SC_CTOR(Elevator){
        SC_THREAD(drive);
        sensitive << mode << target << barrier;
    };
};
#endif