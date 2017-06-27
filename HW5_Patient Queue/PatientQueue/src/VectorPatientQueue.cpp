/* File VectorPatientQueue.cpp
 * This class uses an un-sorted Vector to manages a waiting line of patients to be processed at a hospital.
 * Creates a private struct to holds a patient name, a priority, an integer timestamp for breaking ties.
 * This timestamp can be based on an incrementing counter elsewhere in your class,
 * and every time a patient is enqueued you can update the timestamp and add it to the patient's struct.
 */

#include "VectorPatientQueue.h"

VectorPatientQueue::VectorPatientQueue() {
    /*In this parameterless constructor you should initialize a new empty queue
     * (with a null front for your internal linked list, and an empty Vector for your Vector class).*/

}

VectorPatientQueue::~VectorPatientQueue() {
    // TODO: write this destructor
}

void VectorPatientQueue::clear() {
    // TODO: write this function
}

string VectorPatientQueue::frontName() {
    // TODO: write this function
    return "";   // this is only here so it will compile
}

int VectorPatientQueue::frontPriority() {
    // TODO: write this function
    return 0;   // this is only here so it will compile
}

bool VectorPatientQueue::isEmpty() {
    // TODO: write this function
    return false;   // this is only here so it will compile
}

void VectorPatientQueue::newPatient(string name, int priority) {
    // TODO: write this function
}

string VectorPatientQueue::processPatient() {
    // TODO: write this function
    return "";   // this is only here so it will compile
}

void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    // TODO: write this function
}

string VectorPatientQueue::toString() {
    // TODO: write this function
    return ""; // this is only here so it will compile
}
