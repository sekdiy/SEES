#ifndef CONTROL_H
#define CONTROL_H
#include <systemc>
using namespace sc_core;

SC_MODULE(Control){
    
    // ports
    // floor-signals
    sc_in<int> uwRequests[3];       // upward-requests from FloorBtn
    sc_in<int> dwRequests[3];       // downward-requests from FloorBtn
    
    // elevator-buttons
    sc_in<int> elevRequests[3];     // requests coming from inside the elevator
    
    // elevator signals
    sc_inout<int> elevatorMode;     // mode the elevator is in
    sc_inout<int> elevatorTarget;   // floor towards which the elev is going
    sc_in<int>    elevatorDoor;     // the condition of the elevators door
    sc_out<bool>  elevatorCloseDoor;// signals the eleavtor to close the door
    sc_in<int>    elevatorPosition; // the elevators current position; for further details refer to Elevator.h
    sc_out<bool>  elevatorStop;     // if the elevator has to stop
    
    // members
    int newMode;                       // mode of the elevator; 0 - idle, 1 - up, -1 - down
    int newTarget;                     // the elevators next target
    int targets[3];                    // queue with requests, value is 42 if queue position is empty

    
    // method waits for requests from floor buttons
    void receiveFloorRequest();
    
    // method queues a request
    void queueRequest(int request);
    void insertRequest(int request);
    void shiftRequests();
    
    // method checks if the lift has to stop at the current floor
    void youBetterStop();
    
    // method clears the targets and surveils the closing of the door
    void keepOnRunning();
    
    
    SC_CTOR(Control){
        
        SC_THREAD(receiveFloorRequest);
        sensitive << uwRequests[0] << uwRequests[1] << uwRequests[2] << dwRequests[0] << dwRequests[1] << dwRequests[2] << elevRequests[0] << elevRequests[1] << elevRequests[2] << elevatorDoor;
        
        SC_THREAD(youBetterStop);
        sensitive << elevatorPosition << elevatorDoor;
        
        SC_THREAD(keepOnRunning);
        sensitive << elevatorDoor;
        
    }
};

#endif