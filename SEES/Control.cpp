#include "Control.h"
#include <iostream>
using namespace std;

void Control::sendElevator(){
    
    elevatorMode->write(newMode);
    elevatorTarget->write(newTarget);
}

void Control::receiveFloorRequest(){
    
    while (true) {
        wait();
        // check which floor the request comes from
        for(int i = 0; i < 3; i++){
            
            // if the request is an upward-request
            if(uwRequests[i]->event() == 1){
                
                // if the lift is in idle mode
                if( elevatorMode->read() == 0 ){

                    newTarget = i;
                    newMode = 1;
                    
                    // get the elevator moving
                    sendElevator();
                } else {
                    
                    // check if request comes from a higher floor and if the elevator moves upwards
                    if( (elevatorPosition->read() > 10 * i) && elevatorMode->read() == 1 ){
                        
                    } else {
                        queueRequest(uwRequests[i]->read());
                    }
                }
            }
            
            // if the request is an downward-request
            if(dwRequests[i]->event() == 1){
                
                // if the lift is in idle mode
                if( true ){
                    elevatorTarget->write(i);
                    // get the elevator moving
                    sendElevator();
                } else {
                    
                    // check if request comes from a lower floor and if the elevator moves downwards
                    if(true){
                        
                    } else {
                        queueRequest(uwRequests[i]->read());
                    }
                }
            }
            
        }
        
    }
}

void Control::queueRequest(int request){
    
    int i = 0;
    
    while(targets[i] != 42)
        i++;
    
    targets[i] = request;
    
    
}