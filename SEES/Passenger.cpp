#include "Passenger.h"
#include <iostream>
using namespace std;

void Passenger::sayMyName(){
    cout << "Hi, my name is " << name() << " \t \t DC: " << sc_delta_count() << endl;
}

void Passenger::travel(){
    
    position = rand() % 4; // get a random start...
    
    while (true) {
        
        cout << name() << endl;
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
        cout << "\t from " << position << " to " << destination << " \t\t\t DC: " << sc_delta_count() << endl;
        
        wait();
        while ( doorOpenAtPosition->read() != request->read() ) {
            wait();
        }
        cout << "\t " << name() << " enters lift \t\t\t DC: " << sc_delta_count() << endl;
        elevRequest->write(destination);
        wait();
        position = destination;
    }
}