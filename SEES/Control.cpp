#include "Control.h"
#include <iostream>
using namespace std;

void Control::keepOnRunning(){
    
    while(true){
        wait();
        
        // wait until the elevators door is open
        if( elevatorDoor->read() == 2 ){
//            cout << "keep on running" << endl;
            // check if a target at the elevators current position exists and remove it from the targets list
            for( int i = 0; i < 3; i++){
                if(targets[i]*10 == elevatorPosition->read() * elevatorMode){
                    targets[i] = 42;
                    // fill the emptied requests
                    shiftRequests();
                }
            }
            
            if( elevatorPosition->read() == elevatorTarget->read()*10 ){
                newTarget = 42;
//                cout << " Target is set to 42" << endl;
            }

            while (elevatorDoor->read() != 0) {
                elevatorCloseDoor->write(true);
//                cout << "Ctrl tells to close the door" << endl;
                wait();
            }
            elevatorCloseDoor->write(false);
//            cout << "Ctrl does not tell to close the door anymore" << endl;
        }
    }
}

void Control::shiftRequests(){
//    cout << "\t\t Will shift " << targets[0] << " " << targets[1] << " " << targets[2] << "... " << endl;
    int newTargets[3] = {42,42,42};
    int j = 0;
    for( int i = 0; i < 3; i++ ){
        
        if( targets[i] != 42){
            newTargets[j] = targets[i];
            j++;
        }
    }
    
    for( int i = 0; i < 3; i++)
        targets[i] = newTargets[i];
//    cout << "\t\t To " << targets[0] << " " << targets[1] << " " << targets[2] << " " << endl;
}

void Control::youBetterStop(){
    while (true) {
//        cout << " \n ELEV CAN CONTINUE " << elevatorStop->read() << " \n" << endl;
        wait();
        
        if( (elevatorPosition->read() == targets[0]*10 && elevatorMode->read() == 1) || (elevatorPosition->read() == targets[0]*-10 && elevatorMode->read() == -1) ){
            cout << "Control told elevator to halt at position " << elevatorPosition->read() << endl;

            while(elevatorDoor->read() != 2 ){
                elevatorStop->write(true);
                wait();
            }
            
            elevatorStop->write(false);
            wait();
            
        } else if( (elevatorPosition->read() == elevatorTarget->read()*10) && newTarget != 42 ){
            cout << "Ctrl told elevator to end at position " << elevatorPosition->read() << endl;

            while(elevatorDoor->read() != 2 ){
                elevatorStop->write(true);
                wait();
            }
            
            elevatorStop->write(false);
            wait();
            
        } else {
            elevatorStop->write(false);
//            cout << "\t No Stop at " << elevatorPosition->read() << endl;
        }
    }
}

void Control::receiveFloorRequest(){
    
    while (true) {
        wait();
//        cout << "Ctrl \t \t \t \t \t \t DC: " << sc_delta_count() << endl;
        int request;
        
        // check which floor the request comes from
        for(int i = 0; i < 3; i++){
            
            // if the request is an upward-request
            if(uwRequests[i]->event() == 1){
//                cout << "uw" << i << " " << uwRequests[i]->read() << endl;
                request = uwRequests[i]->read();
                
                // if the lift is in idle mode
                if( elevatorMode->read() == 0 && newMode == 0 ){
                    newTarget = request;
                    newMode = 1;
                    
                    cout << "\t Elevator is idle, newTarget: " << newTarget << " newMode: " << newMode << endl;
                    // get the elevator moving
                    elevatorMode->write(newMode);
                    elevatorTarget->write(newTarget);
                } else {
                    
                    // elevator will pass the request position
                    // if request comes from a higher than the elevators position floor, which is below the target and if the elevator moves upwards
                    if( (10 * request > elevatorPosition->read()) &&  request < elevatorTarget->read() && elevatorMode->read() == 1 ){
//                        cout << "\t " << request << ">" << elevatorPosition->read() << " & " << request << "<" << elevatorTarget->read() << " & mode " << elevatorMode->read() << endl;
                        if( request != newTarget )
                            insertRequest(request);
                    
                    } else {
//                        cout << "\t Won't pass " << request << endl;
                        if( request != newTarget )
                            queueRequest(request);
                    }
                }
            }
            
            // if the request is a downward-request
            if(dwRequests[i]->event() == 1){
//                cout << "dw" << i << " " << dwRequests[i]->read() << endl;
                request = dwRequests[i]->read();
                
                // if the lift is in idle mode
                if( elevatorMode->read() == 0 && newMode == 0){
                    newTarget = dwRequests[i]->read();
                    newTarget = newTarget*-1;
                    newMode = -1;
                    
                    cout << "Elevator is idle, newTarget: " << newTarget << " newMode: " << newMode << endl;
                    // get the elevator moving
                    elevatorMode->write(newMode);
                    elevatorTarget->write(newTarget);
                } else {
                    
                    // elevator will pass the request position
                    // if request comes from a lower than the elevators position floor, which is above the target and if the elevator moves downwards
                    if( (10 * request < elevatorPosition->read()) &&  request > elevatorTarget->read() && elevatorMode->read() == -1 ){
//                        cout << "\t " << request << "<" << elevatorPosition->read() << " & " << request << ">" << elevatorTarget->read() << " & mode " << elevatorMode->read() << endl;
                        if( request != newTarget )
                            insertRequest(request);
                    } else {
//                        cout << "\t Won't pass " << request << endl;
                        if( request != newTarget )
                            queueRequest(request);
                    }
                }
            } // end if dwRequest
            
            // check if request comes from the inside
            if( elevRequests[i] > -1 && elevRequests[i]->event() ){
                int innerReq =  elevRequests[i]->read();
                cout << "\t Ctrl received request from elevator-button " << innerReq << endl;
                
                if( newTarget == 42 ){
                    
                    while( elevatorDoor->read() != 0 )
                        wait();
                    
                    newTarget = innerReq;
                    if( newTarget < elevatorPosition->read() /10)
                        newMode = -1;
                    else
                        newMode = 1;
                    

                    // get the elevator moving
                    cout << "\t Ctrl sends new target: " << newTarget << " and new mode: " << newMode << endl;
                    elevatorMode->write(newMode);
                    elevatorTarget->write(newTarget);
                } else {
                    // queue the request
                    insertRequest(innerReq);
                }
            } // end check for request
            
            // if the elevator has nothing to do
            if( elevatorDoor->read() == 0 && newTarget == 42){
                
                if( targets[0] == 42 ){
                    newMode = 0;
                    cout << "Elevator is idle  \t\t\t\t DC: " << sc_delta_count() << endl;
                } else {
                    // get a target from the queue;
                    newTarget = targets[0];
                    newMode = newTarget >= 0 ? 1 : -1;
                    newTarget = newTarget >= 0 ? newTarget : newTarget*-1;
                    
                    targets[0] = 42;
                    cout << "Elevators newTarget: " << newTarget << " newMode: " << newMode << endl;
                    shiftRequests();
                    // get the elevator moving
                    elevatorMode->write(newMode);
                    elevatorTarget->write(newTarget);
                }
            }
                
            
        }
        
    }
}

void Control::insertRequest(int request){
    bool alreadyExists = false;
    
    // check if the request already exists in the table
    for(int i = 0; i < 3; i++){
        if( targets[i] == request)
            alreadyExists = true;
    }
    
    // if it does not exist, insert the request
    if( !alreadyExists ){
        cout << "\t Insert priority request from floor " << request << endl;
        if( request > 0 ){
            int i = 2;
            
            
            while( targets[i] == 42 || targets[i] >= newTarget || targets[i] < 0 || targets[i] > request)
                i--;
            
            
            for(int j = 2; j > i; j--)
                targets[j] = targets[j-1];
            
            targets[i] = request;
            
        } else {
            int i = 2;
            
            while( targets[i] == 42 || (targets[i]*-1 >= newTarget && targets[i] > request) || targets[i] > 0 )
                i--;
            
            for(int j = 2; j > i; j--)
                targets[j] = targets[j-1];
            
            targets[i] = request;
        }
        
        cout << "\t Queue is: " << targets[0] << " " << targets[1] << " " << targets[2] << " " << endl;
    }
}

void Control::queueRequest(int request){
    bool alreadyExists = false;
    
    // check if the request already exists in the table
    for(int i = 0; i < 3; i++){
        if( targets[i] == request)
            alreadyExists = true;
    }
    
    // if it does not exist, queue the request
    if( !alreadyExists && request != newTarget ){
        cout << "\t Queueing request from floor " << request << endl;
        int i = 0;
        
        while(targets[i] != 42)
            i++;
        
        targets[i] = request;
        cout << "\t Queue is: " << targets[0] << " " << targets[1] << " " << targets[2] << " " << endl;
    }
}