#ifndef FLOORBTNUP_H
#define FLOORBTNUP
#include <systemc>
using namespace sc_core;

SC_MODULE(FloorButtonUp){
    
    // ports
    sc_signal<int>  pushed;
    sc_in<int> requestUpFloor[1];
    sc_event        buttonUp;
    
    void pushButtonUp();
    
    SC_CTOR(FloorButtonUp){
        
        // registering processes
        SC_METHOD(pushButtonUp);
        sensitive << requestUpFloor[0];
    }
    

};
#endif