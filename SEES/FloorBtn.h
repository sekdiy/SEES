#ifndef FLOORBTN_H
#define FLOORBTN
#include <systemc>
using namespace sc_core;

SC_MODULE(FloorButton){
    
    // ports
    sc_in<int> requests[3];
    
    
    //members
    int pushedUp[3];
    int pushedDown[3];
    
    void pushButton();
    
    SC_CTOR(FloorButton){
        
        // registering processes
        SC_THREAD(pushButton);
        sensitive << requests[0] << requests[1] << requests[2];
    }
    
    
};
#endif