#include "Passenger.h"
#include <iostream>
using namespace std;

void Passenger::sayMyName(){
    cout << "Hi, my name is " << name() << " \t \t DC: " << sc_delta_count() << endl;
}

void Passenger::travel(){
    
    position = rand() % 4; // get a random start...
    
//    while (true) {
        
        destination = rand() % 4; // ... and end for the passengers journey
        
        while(destination == position)
            destination = rand() % 4;
        
        // check if the button for up- or downward requests has to be pushed
        if( position < destination && request->read() == -1 ){
            request->write(position);
        } else if ( position > destination && request->read() == -1) {
            request->write(position * -1);
        }
        // else push btn downwards
        cout << name() << " goes from " << position << " to " << destination << " \t\t DC: " << sc_delta_count() << endl;
        
        wait();
        while ( doorOpenAtPosition->read() != request->read() ) {
            wait();
        }
        crossedBarrier->write(1);
        cout << "\t " << name() << " entered the lift \tDC: " << sc_delta_count() << endl;
        elevRequest->write(destination);
        cout << "\t " << name() << " pushed button " << elevRequest->read() << " \tDC: " << sc_delta_count() << endl;
    
        while ( doorOpenAtPosition->read() != destination && doorOpenAtPosition->read() *-1 != destination ) {
            cout << "\t " << name() << " listens to the elevator-music, because the door is open on floor " << doorOpenAtPosition->read() << endl;
            wait();
        }
        crossedBarrier->write(1);
    
        cout << "\n\t" << name() << " reached his destination.\n" << endl;
        position = destination;
 //   }
}