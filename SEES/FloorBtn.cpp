#include "FloorBtn.h"
#include <iostream>
using namespace std;

void FloorButton::pushButton(){
    
    while(true){
        wait(); // wait for a new request
        /*
        cout << "Woke up and read: \n"
        << "Req0: " << requests[0]->event() << " - " << */
        int req;
        for(int i = 0; i < 3; i++){
            // check which signal caused the wake-up
            if( requests[i]->event() == 1){
                req = requests[i]->read();
                
                // check if it is an upward or downward request
                if( req >= 0 ){
                    if( !pushedUp[i]->read() ){
                        pushedUp[i]->write(1);
                        cout << name() << " received new upward request from floor " << i << endl;
                
                    }
                } else {
                    if( !pushedDown[i]->read() ) {
                        pushedDown[i]->write(1);
                        cout << name() << " received new downward request from floor " << i << endl;
                    }
                }
            }
        }
    }
}