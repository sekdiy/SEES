#include "Passenger.h"
#include "FloorBtn.h"
#include "Control.h"
#include "Elevator.h"
#include "ElevBtn.h"
#include <systemc>
using namespace sc_core;

int sc_main (int argc, char * argv[]) {
        
    // Signals
    sc_signal<int> floorButtonPassengerInteraction[3];
    sc_signal<int> floorCtrlUwInteraction[3];
    sc_signal<int> floorCtrlDwInteraction[3];
    
    sc_signal<int>  elevCtrlMode;
    sc_signal<int>  elevCtrlTarget;
    sc_signal<int>  elevCtrlDoor;
    sc_signal<int>  elevCtrlPosition;
    sc_signal<bool> elevCtlrStop;
    sc_signal<int>  elevCtrlButtons[3];
    
    sc_signal<int> elevPassBarrier[3];
    sc_signal<int> elevPassDoor[3];
    sc_signal<int> elevPassBtn[3];
    
    sc_signal<int> elevBtnClear;
    
    // Control
    Control ctrl("Main_Control");
    ctrl.newMode = 0;
    ctrl.newTarget = 42;
    
    // Elevator
    Elevator elev("Elevator1");
    elev.target = 42;
    elev.mode = 0;
    elev.doorConditions = 0;
    
    // Passengers
    Passenger pass1("Peter");
    Passenger pass2("Paul");
    Passenger pass3("Mary");
    
    // Button on each floor to request a lift going upwards
    FloorButton buttons("FloorButtons");
    
    // Button in elevator to request a halt
    ElevBtn elevButtons("ElevatorButtons");
    
    for(int i = 0; i < 3; i++){
        
        // bind ports
        buttons.requests[i](floorButtonPassengerInteraction[i]);
        buttons.pushedUp[i](floorCtrlUwInteraction[i]);
        buttons.pushedDown[i](floorCtrlDwInteraction[i]);
        
        //
        ctrl.uwRequests[i](floorCtrlUwInteraction[i]);
        ctrl.dwRequests[i](floorCtrlDwInteraction[i]);
        ctrl.targets[i] = 42;
        ctrl.elevRequests[i](elevCtrlButtons[i]);
        
        //
        elev.barrier[i](elevPassBarrier[i]);
        elev.doorOpen[i](elevPassDoor[i]);
        
        //
        elevButtons.requests[i](elevPassBtn[i]);
        elevButtons.pushed[i](elevCtrlButtons[i]);
        
        // initialise signals
        floorButtonPassengerInteraction[i].write(-1);
        floorCtrlDwInteraction[i].write(42);
        floorCtrlUwInteraction[i].write(42);
        elevPassBarrier[i].write(-1);
        elevPassDoor[i].write(-1);
        elevPassBtn[i].write(-1);
        elevCtrlButtons[i].write(-1);
    }
    
    ctrl.elevatorMode(elevCtrlMode);
    ctrl.elevatorPosition(elevCtrlPosition);
    ctrl.elevatorTarget(elevCtrlTarget);
    ctrl.elevatorMode->write(0);
    ctrl.elevatorDoor(elevCtrlDoor);
    elevCtrlDoor.write(0);
    ctrl.elevatorStop(elevCtlrStop);
    elevCtlrStop.write(false);
    
    elev.nextMode(elevCtrlMode);
    elev.nextTarget(elevCtrlTarget);
    elev.doorCondition(elevCtrlDoor);
    elev.position(elevCtrlPosition);
    elev.position->write(0);
    elev.stopHere(elevCtlrStop);
    elev.clearRequestAt(elevBtnClear);
    
    elevButtons.clearRequest(elevBtnClear);

    
    pass1.request(floorButtonPassengerInteraction[0]);
    pass2.request(floorButtonPassengerInteraction[1]);
    pass3.request(floorButtonPassengerInteraction[2]);
    
    pass1.crossedBarrier(elevPassBarrier[0]);
    pass2.crossedBarrier(elevPassBarrier[1]);
    pass3.crossedBarrier(elevPassBarrier[2]);
    
    pass1.doorOpenAtPosition(elevPassDoor[0]);
    pass2.doorOpenAtPosition(elevPassDoor[1]);
    pass3.doorOpenAtPosition(elevPassDoor[2]);
    
    pass1.elevRequest(elevPassBtn[0]);
    pass2.elevRequest(elevPassBtn[1]);
    pass3.elevRequest(elevPassBtn[2]);
    
    
    sc_start(15, SC_SEC);
    return 0;
}