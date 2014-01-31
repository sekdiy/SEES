#ifndef FLOORBTN_H
#define FLOORBTN
#include <systemc>
using namespace sc_core;

SC_MODULE(FloorButton){
    
    // ports
    sc_in<int> requests[3];
    sc_inout<int> pushedUp[3];
    sc_inout<int> pushedDown[3];
    
    void pushButton();
    
    SC_CTOR(FloorButton){
        
        // registering processes
        SC_THREAD(pushButton);
        sensitive << requests[0] << requests[1] << requests[2];
    }
    
    
};
#endif