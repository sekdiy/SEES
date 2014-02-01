#include "Control.h"
#include <iostream>
using namespace std;

void Control::youBetterStop(){
    while (true) {
        wait();
        if( (elevatorPosition->read() == targets[0]*10 && elevatorMode->read() == 1) || (elevatorPosition->read() == targets[0]*-10 && elevatorMode->read() == -1)){
            cout << "\t Stop at " << elevatorPosition->read() << endl;
            elevatorStop->write(true);
        } else if( elevatorPosition->read() == elevatorTarget->read()*10 ){
            cout << " \t Fin at " << elevatorPosition->read() << endl;
        } else {
            elevatorStop->write(false);
            cout << "\t No Stop at " << elevatorPosition->read() << endl;
        }
    }
}

void Control::receiveFloorRequest(){
    
    while (true) {
        wait();
        cout << "Ctrl \t \t \t \t \t \t DC: " << sc_delta_count() << endl;
        int request;
        
        // check which floor the request comes from
        for(int i = 0; i < 3; i++){
            
            // if the request is an upward-request
            if(uwRequests[i]->event() == 1){
                cout << "uw" << i << " " << uwRequests[i]->read() << endl;
                request = uwRequests[i]->read();
                
                // if the lift is in idle mode
                if( elevatorMode->read() == 0 && newMode == 0 ){
                    newTarget = request;
                    newMode = 1;
                    
                    cout << "\t idle, nt: " << newTarget << " nm: " << newMode << endl;
                    // get the elevator moving
                    elevatorMode->write(newMode);
                    elevatorTarget->write(newTarget);
                } else {
                    
                    // elevator will pass the request position
                    // if request comes from a higher than the elevators position floor, which is below the target and if the elevator moves upwards
                    if( (10 * request > elevatorPosition->read()) &&  request < elevatorTarget->read() && elevatorMode->read() == 1 ){
                        cout << "\t " << request << ">" << elevatorPosition->read() << " & " << request << "<" << elevatorTarget->read() << " & mode " << elevatorMode->read() << endl;
                        insertRequest(request);
                    
                    } else {
                        cout << "\t Won't pass " << request << endl;
                        queueRequest(request);
                    }
                }
            }
            
            // if the request is a downward-request
            if(dwRequests[i]->event() == 1){
                cout << "dw" << i << " " << dwRequests[i]->read() << endl;
                request = dwRequests[i]->read();
                
                // if the lift is in idle mode
                if( elevatorMode->read() == 0 && newMode == 0){
                    newTarget = dwRequests[i]->read();
                    newTarget = newTarget*-1;
                    newMode = -1;
                    
                    cout << "\t idle, nt: " << newTarget << " nm: " << newMode << endl;
                    // get the elevator moving
                    elevatorMode->write(newMode);
                    elevatorTarget->write(newTarget);
                } else {
                    
                    // elevator will pass the request position
                    // if request comes from a lower than the elevators position floor, which is above the target and if the elevator moves downwards
                    if( (10 * request < elevatorPosition->read()) &&  request > elevatorTarget->read() && elevatorMode->read() == -1 ){
                        cout << "\t " << request << "<" << elevatorPosition->read() << " & " << request << ">" << elevatorTarget->read() << " & mode " << elevatorMode->read() << endl;
                        insertRequest(request);
                    } else {
                        cout << "\t Won't pass " << request << endl;
                        queueRequest(request);
                    }
                }
            }
            
        }
        
    }
}

void Control::insertRequest(int request){
    cout << "\t\t Inserting " << request << endl;
    if( request > 0 ){
        int i = 2;
        
        
        while( targets[i] == 42 || targets[i] >= newTarget || targets[i] < 0 || targets[i] > request )
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
    
    cout << "\t\t Req inserted " << targets[0] << " " << targets[1] << " " << targets[2] << " " << endl;
}

void Control::queueRequest(int request){
    cout << "\t\t Queueing " << request << endl;
    int i = 0;
    
    while(targets[i] != 42)
        i++;
    
    targets[i] = request;
    cout << "\t\t Req queued " << targets[0] << " " << targets[1] << " " << targets[2] << " " << endl;
}