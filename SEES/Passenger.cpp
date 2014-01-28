#include "Passenger.h"
#include <iostream>
using namespace std;

void Passenger::sayMyName(){
    cout << "Hi, my name is " << name() << endl;
}

void Passenger::travel(){
    
    position = rand() % 4; // get a random start...
    
    while (true) {
        
        destination = rand() % 4; // ... and end for the passengers journey
        
        while(destination == position)
            destination = rand() % 4;
        
        // check if the button for up- or downward requests has to be pushed
        if( position < destination && requestUpFloor[position]->read() == -1 ){
            requestUpFloor[position]->write(position);
        } else {
            
        }
        // else push btn downwards
        cout << name() << " waits to travel from floor " << position << " towards floor " << destination << "." << endl;
        wait(2, SC_SEC);
        position = destination;
    }
}