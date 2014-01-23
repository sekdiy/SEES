#include "Passenger.h"
#include <iostream>
using namespace std;

void Passenger::sayMyName(){
    cout << "Hi, my name is " << name() << endl;
}

void Passenger::travel(){
    
    // get a random start and end for the passengers journey
    position = rand() % 4;
    destination = rand() % 4;
    
    while(destination == position)
        destination = rand() % 4;
    
    // check if the button for up- or downward requests has to be pushed
    if( destination > position)
        requestUpFloor.write(position);
    // else push btn downwards
        
    cout << name() << " started travelling from floor " << position << " towards floor " << destination << "." << endl;
    wait(2, SC_SEC);
}