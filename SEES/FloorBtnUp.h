#ifndef FLOORBTNUP_H
#define FLOORBTNUP
#include <systemc>
using namespace sc_core;

SC_MODULE(FloorButtonUp){
    
    // ports
    sc_in<int> requestUpFloor;

    
    //members
    int position; // level on which the button is installed
    
    void pushButtonUp();
    
    SC_CTOR(FloorButtonUp){
        
        // registering processes
        SC_THREAD(pushButtonUp);
        sensitive << requestUpFloor;
    }
    

};
#endif