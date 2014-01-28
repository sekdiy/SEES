#include "FloorBtnUp.h"
#include <iostream>
using namespace std;

void FloorButtonUp::pushButtonUp(){
    
    while(true){
        wait();
        if( pushed == 0 ){
            pushed = 1;
            cout << name() << " says:\n" << "\t Button on floor " << position << " received request from floor " << requestUpFloor->read() << "\n" << endl;
        } else {
            cout << name() << " says:\n" << "\t Button on floor " << position << " has been pushed on floor " << requestUpFloor->read() << " already \n" << endl;
        }
    }

}