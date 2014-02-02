#include "ElevBtn.h"
#include <iostream>
using namespace std;

void ElevBtn::waitForRequest(){
    
    while(true){
        wait();
        // wait for the information that the door is open and clear the request
        if( clearRequest->event() ){
            
            for( int i = 0; i < 3; i++){
                
                if( pushed[i]->read() == clearRequest->read() ){
                    
                    pushed[i]->write(-1);
                    cout << "Cleared " << clearRequest->read();
                    
                }
            }
        }
        
        // check for a new request
        for(int i = 0; i < 3; i++){
            
            if( requests[i]->event() ){
                
                // check if the floor has been requested earlier
                if( pushed[i]->read() == -1){
                    
                    pushed[i]->write(requests[i]->read());
                    cout << "\t Pushed button " << requests[i]->read() << endl;
                    
                } else {
                    cout << "\t Button " << requests[i]->read() << " already pushed" << endl;
                }
            }
        }
    }
}