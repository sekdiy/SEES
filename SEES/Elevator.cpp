#include "Elevator.h"
#include <iostream>
using namespace std;

void Elevator::drive(){
    
    while (true) {
        wait();
        cout << "Elev in scheduler \t \t \t \t DC: " << sc_delta_count() << endl;
//        cout << "nm: " << nextMode->event() << " nt: " << nextTarget << " b0: " << barrier[0]->event() << " b1: " << barrier[1]->event() << " b2: " << barrier[2]->event() << endl;
        // wait for instructions from control
        while ( nextTarget->event() == false && nextMode->event() == false ) {
            wait();
        }
//        cout << "\t\t\t\t\t\t\t DC: "<< sc_delta_count() << "\nT nm: " << nextMode->event() << " nt: " << nextTarget << " b0: " << barrier[0]->event() << " b1: " << barrier[1]->event() << " b2: " << barrier[2]->event() << endl;
        
        target = nextTarget->read();
        mode   = nextMode->read();
        
        cout << "New target is: " << target << " with mode: " << mode << " and stop-request: " << stopHere->read() << endl;
        
        // check in which direction the journey goes
        // upwards
        if( target * 10 > position->read() ){
            
            // travel upwards
            while ( target * 10 > position->read() && doorConditions == 0) {
                position->write(position->read()+5);
                wait(1, SC_SEC);
                cout << "\t Elevator reached position " << position->read() << endl;
                
                // if control signals the elevator to stop
                if( stopHere->read() == true ){
                    
                    // open the door
                    cout << "\t Elevator opens door... " << endl;
                    position->write(position->read());
                    
                    // door is opening
                    wait(1, SC_SEC);
                    doorConditions++;
                    doorCondition->write(doorConditions);
                    
                    // door is open in 1 sec
                    wait(1,SC_SEC);
                    doorConditions++;
                    doorCondition->write(doorCondition);
                    cout << "\t Door is open. (" << doorConditions << ")" << endl;

                    // signal to inner buttons that request can be cleared
                    clearRequestAt->write(position->read() /10);
                    
                    // signal to the passengers on which floor the door is open
                    for(int i = 0; i < 3; i++)
                        doorOpen[i]->write((position->read()/10) * mode );
                    
                    // as long as the barrier wasn't crossed wait
                    while( !(barrier[0]->event() || barrier[1]->event() || barrier[2]->event()) )
                        wait();
                    
                    while( doorConditions != 0){
                        // send door condition to control to get woke up again
                        doorCondition->write(doorConditions);
                        
                        // wait three seconds after the last passenger crossed the barrier
                        wait(3,SC_SEC);
                        
                        // close the door (agian)
                        doorCondition->write(doorConditions);
                        wait(1,SC_SEC);
                        doorConditions++;
                        doorCondition->write(doorConditions);
                        
                        // check if the barrier was crossed again
                        if( barrier[0]->event() || barrier[1]->event() || barrier[2]->event() ){
                            
                            wait(1,SC_SEC);
                            doorConditions = 1;
                            doorCondition->write(doorConditions);
                            wait(1,SC_SEC);
                            doorConditions++;
                            doorCondition->write(doorConditions);
                            
                            // signal to the passengers on which floor the door is open
                            for(int i = 0; i < 3; i++)
                                doorOpen[i]->write((position->read()/10) * mode );
                            
                        } else {
                            wait(1,SC_SEC);
                            doorConditions = 0;
                            doorCondition->write(doorConditions);
                        }
                    } // end while doorConditions
                    
                    cout << "\t Door closed: " << doorConditions << endl;
                }
            }
            
            
        // downwards
        } else if( target * 10 < position->read()){
            while ( target * 10 < position->read() && doorConditions == 0 ) {
                position->write(position->read()-5);
                wait(1, SC_SEC);
                cout << "\t Elevator reached position " << position->read() << endl;
                // if control signals the elevator to stop
                if( stopHere->read() == true ){
                    
                    // open the door
                    cout << "\t Elevator opens door... " << endl;
                    position->write(position->read());
                    
                    // door is opening
                    wait(1, SC_SEC);
                    doorConditions++;
                    doorCondition->write(doorConditions);
                    
                    // door is open in 1 sec
                    wait(1,SC_SEC);
                    doorConditions++;
                    doorCondition->write(doorCondition);
                    cout << "\t Door is open. (" << doorConditions << ")" << endl;
                    
                    // signal to inner buttons that request can be cleared
                    clearRequestAt->write(position->read() /10);
                    
                    // signal to the passengers on which floor the door is open
                    for(int i = 0; i < 3; i++)
                        doorOpen[i]->write((position->read()/10) * mode );
                    
                    // as long as the barrier wasn't crossed wait
                    while( !(barrier[0]->event() || barrier[1]->event() || barrier[2]->event()) )
                        wait();
                    
                    while( doorConditions != 0){
                        // send door condition to control to get woke up again
                        doorCondition->write(doorConditions);
                        
                        // wait three seconds after the last passenger crossed the barrier
                        wait(3,SC_SEC);
                        
                        // close the door (agian)
                        doorCondition->write(doorConditions);
                        wait(1,SC_SEC);
                        doorConditions++;
                        doorCondition->write(doorConditions);
                        
                        // check if the barrier was crossed again
                        if( barrier[0]->event() || barrier[1]->event() || barrier[2]->event() ){
                            
                            wait(1,SC_SEC);
                            doorConditions = 1;
                            doorCondition->write(doorConditions);
                            wait(1,SC_SEC);
                            doorConditions++;
                            doorCondition->write(doorConditions);
                            
                            // signal to the passengers on which floor the door is open
                            for(int i = 0; i < 3; i++)
                                doorOpen[i]->write((position->read()/10) * mode );
                            
                        } else {
                            wait(1,SC_SEC);
                            doorConditions = 0;
                            doorCondition->write(doorConditions);
                        }
                        cout << "\t Door closed: " << doorConditions << endl;
                    }
                }
            }
            
            
        // request from same floor
        } else {
            
            cout << "\t Elevator is on position " << position->read();
            
            // open the door
            cout << "\t Elevator opens door... " << endl;
            position->write(position->read());
            
            // door is opening
            wait(1, SC_SEC);
            doorConditions++;
            doorCondition->write(doorConditions);
            
            // door is open in 1 sec
            wait(1,SC_SEC);
            doorConditions++;
            doorCondition->write(doorCondition);
            cout << "\t Door is open. (" << doorConditions << ")" << endl;
            
            // signal to inner buttons that request can be cleared
            clearRequestAt->write(position->read() /10);
            
            // signal to inner buttons that request can be cleared
            clearRequestAt->write(position->read() /10);
            
            // signal to the passengers on which floor the door is open
            for(int i = 0; i < 3; i++)
                doorOpen[i]->write((position->read()/10) * mode );
            
            // as long as the barrier wasn't crossed wait
            while( !(barrier[0]->event() || barrier[1]->event() || barrier[2]->event()) )
                wait();
            
            while( doorConditions != 0){
                // send door condition to control to get woke up again
                doorCondition->write(doorConditions);
                
                // wait three seconds after the last passenger crossed the barrier
                wait(3,SC_SEC);
                
                // close the door (agian)
                doorCondition->write(doorConditions);
                wait(1,SC_SEC);
                doorConditions++;
                doorCondition->write(doorConditions);
                
                // check if the barrier was crossed again
                if( barrier[0]->event() || barrier[1]->event() || barrier[2]->event() ){
                    
                    wait(1,SC_SEC);
                    doorConditions = 1;
                    doorCondition->write(doorConditions);
                    wait(1,SC_SEC);
                    doorConditions++;
                    doorCondition->write(doorConditions);
                    
                    // signal to the passengers on which floor the door is open
                    for(int i = 0; i < 3; i++)
                        doorOpen[i]->write((position->read()/10) * mode );
                    
                } else {
                    wait(1,SC_SEC);
                    doorConditions = 0;
                    doorCondition->write(doorConditions);
                }
            }
        }
        
    }
}
