#include "Elevator.h"
#include <iostream>
using namespace std;

void Elevator::drive(){
    
    while (true) {
        wait();
        cout << "Elev \t \t \t \t \t \t DC: " << sc_delta_count() << endl;
        cout << "nm: " << nextMode->event() << " nt: " << nextTarget << " b0: " << barrier[0]->event() << " b1: " << barrier[1]->event() << " b2: " << barrier[2]->event() << endl;
        // wait for instructions from control
        while ( nextTarget->event() == false || nextMode->event() == false ) {
            wait();
        }
        cout << "\t\t\t\t\t\t\t DC: "<< sc_delta_count() << "\nT nm: " << nextMode->event() << " nt: " << nextTarget << " b0: " << barrier[0]->event() << " b1: " << barrier[1]->event() << " b2: " << barrier[2]->event() << endl;
        
        target = nextTarget->read();
        mode   = nextMode->read();
        
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
                    cout << "\t Opens door " << endl;
                    position->write(position->read());
                    
                    // door is opening
                    wait(1, SC_SEC);
                    doorConditions++;
                    doorCondition->write(doorConditions);
                    
                    // door is open in 1 sec
                    wait(1,SC_SEC);
                    doorConditions++;
                    doorCondition->write(doorCondition);
                    cout << "\t Door open " << doorConditions << endl;
                    
                    // signal to the passengers on which floor the door is open
                    for(int i = 0; i < 3; i++)
                        doorOpen[i]->write((position->read()/10) * mode );
                    
                    wait();
                    
                }
            }
            
            // open doors
            
        // downwards
        } else if( target * 10 < position->read()){
            while ( target * 10 < position->read() && doorConditions == 0 ) {
                position->write(position->read()-5);
                wait(1, SC_SEC);
                cout << "\t Elevator reached position " << position->read();
            }
            
            // open doors
            
        // request from same floor
        } else {
            
            cout << "\t Elevator is on position " << position->read();
        }
        
    }
}
