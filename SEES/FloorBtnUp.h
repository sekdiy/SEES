#ifndef FLOORBTNUP_H
#define FLOORBTNUP
#include <systemc>
using namespace sc_core;

SC_MODULE(FloorButtonUp){
    
    // ports
    sc_signal<int>  pushed;
    sc_fifo_in<int> requestUpFloor;
    sc_event        buttonUp;
    
    void pushButtonUp();
    
    SC_CTOR(FloorButtonUp){
        
        // registering processes
        SC_THREAD(pushButtonUp);
        sensitive << requestUpFloor;
    }
    

};
#endif