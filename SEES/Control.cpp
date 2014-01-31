#include "Control.h"
#include <iostream>
using namespace std;

void Control::sendElevator(){
    
}

void Control::receiveFloorRequest(){
    
    while (true) {
        wait();
        // check which floor the request comes from
        for(int i = 0; i < 3; i++){
            
            // if the request is an upward-request
            if(uwRequests[i]->event() == 1){
                
                // if the lift is in idle mode
                if( true ){
                    target = i;
                    // get the elevator moving
                    sendElevator();
                } else {
                    
                    // check if request comes from a higher floor
                    if(true){
                        
                    } else {
                        queueRequest(i);
                    }
                }
            }
            
            // if the request is an downward-request
            if(dwRequests[i]->event() == 1){
                
                // if the lift is in idle mode
                if( true ){
                    target = i;
                    // get the elevator moving
                    sendElevator();
                } else {
                    
                    // check if request comes from a lower floor
                    if(true){
                        
                    } else {
                        queueRequest(i);
                    }
                }
            }
            
        }
        
    }
}

void Control::queueRequest(int request){
    
    int i = 0;
    
    while(uwRequests[i] != 42)
        i++;
    
    uwRequests[i] = request;
    
    
}