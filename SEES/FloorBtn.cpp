#include "FloorBtn.h"
#include <iostream>
using namespace std;

void FloorButton::pushButton(){
    
    while(true){
        wait(); // wait for a new request
//        cout << name() << "\t\t\t\t DC: " << sc_delta_count() << endl;
        
        int req;
        for(int i = 0; i < 3; i++){
            // check which signal caused the wake-up
            if( requests[i]->event() == 1){
                req = requests[i]->read();
                
                // check if it is an upward or downward request
                if( req >= 0 ){
                    if( pushedUp[i]->read() == 42 ){
                        pushedUp[i]->write(req);
 //                       cout <<"\t upward   floor " << req << "\t\t DC: " << sc_delta_count() << endl;
                
                    }
                } else {
                    if( pushedDown[i]->read() == 42 ) {
                        pushedDown[i]->write(req);
 //                       cout << "\t downward floor " << (req*-1) << "\t\t DC: " << sc_delta_count() << endl;
                    }
                }
            }
        }
    }
}