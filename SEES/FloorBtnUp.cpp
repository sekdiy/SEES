#include "FloorBtnUp.h"
#include <iostream>
using namespace std;

void FloorButtonUp::pushButtonUp(){
    
    while(true){
        wait();
        cout << name() << " says:\n" << "\t Button on floor " << position << " received request from floor " << requestUpFloor.read() << endl;
    }

}