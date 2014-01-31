#ifndef ELEVATOR_H
#define ELEVATOR_H
#include <systemc>
using namespace sc_core;

SC_MODULE(Elevator){
    
    // ports
    sc_in<int> mode;    // mode of the elevatro
    sc_in<int> target;  // the next destination

    sc_in<int> barrier; // signals that a passenger crossed the light barrier
    
    // members

    
    void drive();
    
    void lightBarrier();
    
    SC_CTOR(Elevator){
        SC_THREAD(drive);
        SC_THREAD(lightBarrier);
    };
};
#endif