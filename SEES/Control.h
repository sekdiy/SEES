#ifndef CONTROL_H
#define CONTROL_H
#include <systemc>
using namespace sc_core;

SC_MODULE(Control){
    
    // ports
    sc_in<int> uwRequests[3];       // upward-requests from FloorBtn
    sc_in<int> dwRequests[3];       // downward-requests from FloorBtn
    sc_inout<int> elevatorMode;     // mode the elevator is in
    sc_inout<int> elevatorTarget;   // floor towards which the elev is going
    
    // members
    int targets[3];                 // queue with requests, value is 42 if queue position is empty

    
    // method waits for requests from floor buttons
    void receiveFloorRequest();

    // method changes the elevators mode and target
    void sendElevator();
    
    // method queues a request
    void queueRequest(int request);
    
    SC_CTOR(Control){
        
        SC_THREAD(receiveFloorRequest);
        sensitive << uwRequests[0] << uwRequests[1] << uwRequests[2] << dwRequests[0] << dwRequests[1] << dwRequests[2];
        
        SC_METHOD(sendElevator);
    }
};

#endif