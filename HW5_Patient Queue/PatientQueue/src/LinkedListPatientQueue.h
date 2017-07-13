/* File LinkedListPatientQueue.h
 * Defines a class uses a sorted singly linked list to manages a waiting line of patients to be processed at a hospital.
 * When inserting a new node with priority number N, travers the list to find the position to insert.
 * Beginning with the front end with the smallest prior num.
 * Keep looking for the next node until which with the bigger priority number M(M>N).
 *
 * @author Cong Chen
 * @version 2017/07
 */
#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"
#include "strlib.h"
using namespace std;

class LinkedListPatientQueue : public PatientQueue {
public:
    LinkedListPatientQueue();
    ~LinkedListPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    /*The linked-list class is only allowed to have a single private member variable inside it:
     * a pointer to the front of your list (for the linked list implementation).*/
    PatientNode *qHead; //list

};
