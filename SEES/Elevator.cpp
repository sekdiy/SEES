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
            while ( target * 10 > position->read() ) {
                position->write(position->read()+5);
                wait(1, SC_SEC);
                cout << "\t Elevator reached position " << position->read() << endl;
            }
            
            // open doors
            
        // downwards
        } else if( target * 10 < position->read()){
            while ( target * 10 < position->read() ) {
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
