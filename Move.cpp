/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

//function for move that the player makes
Move::Move(string commandString) : Move() {
    isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;

    //condition for blank string as pass
    if (commandString == "")
    {
        isPass = true;
    }

    //conditon for recognizing save command 
    else if (commandString == "S" || commandString == "s")
    {
        isSave = true;
    }

    //condtion for recognizing quit command
    else if (commandString == "Q" || commandString == "q")
    {
        isQuit = true;
    }

    //condition for Floor and Pickup commands
    else
    {
        string str = commandString;
        stringstream ss(str);
        char temp;
        char temp2;
        ss >> temp >> elevatorId >> temp2;

        if (temp2 == 'f')
        {
            ss >> targetFloor;
        }
        
        else if (temp2 == 'p')
        {
            isPickup = true;
        }
    }
}

//checking if it is a valid move
bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {

    //Checking for move condition, either pickup or floor cmd
    if (isPass == true || isQuit == true || isSave == true) {
        return true;
    }
    // by checking if elevator ID is valid and isnt servicing already
    else if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS) {
        if (!(elevators[elevatorId].isServicing())) {
            if (isPickup == true) {
                return true;
            }
            //checking validity of traget floor
            else if (targetFloor >= 0 && targetFloor < NUM_FLOORS) {
                if (targetFloor != elevators[elevatorId].getCurrentFloor()) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        else {
            return false;
        }
    }
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) 
{
    int index = 0;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;

    //counting people to be picked up in queue
    for (int i = 0; i < pickupList.size(); i++) {
        peopleToPickup[i] = (pickupList[i] - '0');
        numPeopleToPickup++;
    }
    int maxDistance = 0;

    //establishing anger in index of people picked up
    for (int i = 0; i < numPeopleToPickup; i++) {
        int anger = pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        totalSatisfaction += MAX_ANGER - anger;
        int distance = abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor);
        if (maxDistance < distance) {
            maxDistance = distance;
            index = i;
        }
    }
    targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[index]).getTargetFloor();
    return;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
