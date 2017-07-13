/* File VectorPatientQueue.h
 * Defines a class using a Stanford Vector to manages a waiting line of patients to be processed at a hospital.
 * Creates a private struct to holds a patient name, a priority, an integer timestamp for breaking ties.
 * This timestamp can be based on an incrementing counter elsewhere in your class,
 * and every time a patient is enqueued you can update the timestamp and add it to the patient's struct.
 *
 * @author Cong Chen
 * @version 2017/07
 */
#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
using namespace std;

class VectorPatientQueue : public PatientQueue {
public:
    VectorPatientQueue();
    ~VectorPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    // TODO: add specified member variable(s)
    // TODO: add any member functions necessary

};
