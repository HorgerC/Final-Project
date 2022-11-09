/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Elevator.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <Chris Horger, Ella Coulter, Isabella Vong, Keith Wu>
 * <horgerc, emcoult, isvong, keithwu>
 *
 * Final Project - Elevators
 */

#include "Elevator.h"
#include <iostream>

using namespace std;

//Function to process elevator tick and where elevators are servicing 
void Elevator::tick(int currentTime) {

    if ((currentTime % TICKS_PER_ELEVATOR_MOVE == 0) && servicing)
    {
        if (currentFloor > targetFloor)
        {
            currentFloor -= 1;
        }

        else
        {
            currentFloor += 1;
        }
    }
    //if the elevator reaches its target, it is servicing
    if (currentFloor == targetFloor)
    {
        servicing = false;
    }
}

//Function that processes elevators service requests
void Elevator::serviceRequest(int floorNum) {

    int MAXFLOORNUM = NUM_FLOORS - 1;
    if (floorNum <= MAXFLOORNUM && floorNum >= 0)
    {
        targetFloor = floorNum;
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

void Elevator::print(ostream &outs) {
    outs << currentFloor;
    if (servicing = false){
        outs << "w";
    } else {
        outs << "s" << targetFloor;
    }
}

Elevator::Elevator() {
    currentFloor = 0;
    servicing = false;
	targetFloor = 0;
}

void Elevator::setCurrentFloor(int currentFloorIn) {
    currentFloor = currentFloorIn;
}

bool Elevator::isServicing() const {
	return servicing;
}

int Elevator::getCurrentFloor() const {
    return currentFloor;
}

int Elevator::getTargetFloor() const {
    return targetFloor;
}
