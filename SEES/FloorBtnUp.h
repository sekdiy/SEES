#ifndef FLOORBTNUP_H
#define FLOORBTNUP
#include <systemc>
using namespace sc_core;

SC_MODULE(FloorButtonUp){
    
    // ports
    sc_port<sc_signal_in_if<int>, 0, SC_ZERO_OR_MORE_BOUND> requestUpFloor;

    
    //members
    int position; // level on which the button is installed
    int pushed;
    
    void pushButtonUp();
    
    SC_CTOR(FloorButtonUp){
        
        // registering processes
        SC_THREAD(pushButtonUp);
        sensitive << requestUpFloor;
    }
    

};
#endif