#ifndef ELEVBTN_H
#define ELEVBTN_H
#include <systemc>
using namespace sc_core;

SC_MODULE(ElevBtn){
    // ports
    sc_in<int>  requests[3];  // requests coming from passenger
    sc_out<int> pushed[3];    // signaling request to control
    sc_in<int>  clearRequest; // signal from elevator that door is open at a floor
    
    void waitForRequest();
  
    SC_CTOR(ElevBtn){
        
        SC_THREAD(waitForRequest);
        sensitive << clearRequest << requests[0] << requests[1] << requests[2];
        
    };
};
#endif
