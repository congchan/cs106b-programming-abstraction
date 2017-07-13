/* File: heappatientqueue.h
 * @author Cong Chen
 * @version 2017/07

 Uses a special array structure called a binary heap as its internal data storage.
 The only private member variables this class is allowed to have inside it are
 a pointer to your internal array of elements,
 and integers for the array's capacity
 and the priority queue's size.*/

#pragma once
#include "array"
#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"
using namespace std;

class HeapPatientQueue : public PatientQueue  {
public:
    HeapPatientQueue();
    ~HeapPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    /*The only private member variables this class is allowed to have inside it
     * are a pointer to your internal array of elements,
     * and integers for the array's capacity
     * and the priority queue's size.*/
    PatientNode *binaryQueue;

    int capacity;
    int size;

};
