#include "FloorBtnUp.h"
#include <iostream>
using namespace std;

void FloorButtonUp::pushButtonUp(){
    
    cout << "Received request from floor " << requestUpFloor[0].read() << endl;

}