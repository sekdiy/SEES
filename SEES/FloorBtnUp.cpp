#include "FloorBtnUp.h"
#include <iostream>
using namespace std;

void FloorButtonUp::pushButtonUp(){
    
    wait();
    cout << "Received request from floor " << requestUpFloor.read() << endl;

}