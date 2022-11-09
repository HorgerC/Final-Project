/*
 * Copyright 2022 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 28eb18c2c1ce490aada441e65559efdd
 *
 * <Chris Horger, Ella Coulter, Isabella Vong, Keith Wu>
 * <horgerc, emcoult, isvong, keithwu>
 *
 * Final Project - Elevators
 */


#include "Floor.h"
#include <algorithm>

using namespace std;

int Floor::tick(int currentTime) {
    int exploded[numPeople];
    int index = 0;
    for (int i = 0; i < numPeople; i++)
    {
        if (people[i].tick(currentTime))
        {
            exploded[index] = i;
            index++;
        }
    }
    removePeople(exploded, index);

    //returning 0 to prevent compilation error
    return 0;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
        people[numPeople] = newPerson;
        numPeople++;
    }

    //Condition for recognizing a down request
    if (request < 0) {
        hasDownRequest = true;
    }

    //Condition for recognizing an up request
    else if (request > 0) {
        hasUpRequest = true;
    }

    //If request = 0, reset up and down requests to false
    resetRequests();
}

//Function to remove people from elevator, and track how many will be removed
void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
    sort(indicesToRemove, indicesToRemove + numPeopleToRemove);

    int removeCount = 0;
    for (int i = 0; i < numPeopleToRemove; i++)
    {
        int personToRemove = indicesToRemove[i];
        for (int j = personToRemove - removeCount; j < numPeople - 1; j++)
        {
            people[j] = people[j + 1];
        }
        //removeCount and numPeople move inversely
        removeCount++;
        numPeople--;
    }
    resetRequests();
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
    sort(indicesToRemove, indicesToRemove + numPeopleToRemove);

    Person remove[MAX_PEOPLE_PER_FLOOR];
    int removeCounter = 0;
    int counter = 0;
    int otherCounter = 0;
    int personToRemove = indicesToRemove[counter];

    for (int j = 0; j < numPeople; j++)
    {
        if (j != personToRemove)
        {
            remove[otherCounter] = people[j];
            otherCounter++;
        }
        else
        {
            if(counter < numPeopleToRemove-1)
            {
                counter++;
                personToRemove = indicesToRemove[counter];
            }
        }
    }
    numPeople -= numPeopleToRemove;
    removeCounter++;
    for (int k = 0; k < numPeople; k++)
    {
        people[k] = remove[k];
    }
}

void Floor::resetRequests() {

    //Up and Down Requests are reset to false
    hasUpRequest = false;
    hasDownRequest = false;

    //Up and Down requests are checked if either needs to be changed to true
    for (int i = 0; i < numPeople; i++) {

        if 
           (people[i].getTargetFloor() -
            people[i].getCurrentFloor() > 0) {
            hasUpRequest = true;
        }

        else if 
           (people[i].getTargetFloor() -
            people[i].getCurrentFloor() < 0) {
            hasDownRequest = true;
        }
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
    string up = "U";
    outs << (hasUpRequest ? up : " ") << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << people[i].getAngerLevel();
        outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
    }
    outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
    string down = "D";
    outs << (hasDownRequest ? down : " ") << " ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "o   ";
    }
    outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
    cout << endl;
    outs << "Select People to Load by Index" << endl;
    outs << "All people must be going in same direction!";
    /*  O   O
    // -|- -|-
    //  |   |
    // / \ / \  */
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " O   ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "-|-  ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " |   ";
    }
    outs << endl << "              ";
    for (int i = 0; i < numPeople; ++i) {
        outs << "/ \\  ";
    }
    outs << endl << "INDEX:        ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << i << "   ";
    }
    outs << endl << "ANGER:        ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getAngerLevel() << "   ";
    }
    outs << endl << "TARGET FLOOR: ";
    for (int i = 0; i < numPeople; ++i) {
        outs << " " << people[i].getTargetFloor() << "   ";
    }
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
    return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
    return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
