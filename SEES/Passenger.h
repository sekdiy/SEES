#ifndef PASSENGER_H
#define PASSENGER_H
#include <systemc>
using namespace sc_core;

SC_MODULE(Passenger){
    
    // ports
    sc_out<int> request;
    
    // members
    int position;
    int destination;
    
    // process declaratioins
    void sayMyName();
    void travel();
    
    SC_CTOR(Passenger){
    
        // process registrations
        SC_METHOD(sayMyName);
        // sensitivity list here
        SC_THREAD(travel);
        // sensitivity list here
    }
    
};

#endif