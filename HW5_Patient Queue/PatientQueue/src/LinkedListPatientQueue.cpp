/* File LinkedListPatientQueue.cpp
 * This class uses a sorted linked list to manages a waiting line of patients to be processed at a hospital.
 */
#include "LinkedListPatientQueue.h"

LinkedListPatientQueue::LinkedListPatientQueue() {
    /*In this parameterless constructor you should initialize a new empty queue
     * (with a null front for your internal linked list, and an empty Vector for your Vector class).*/
    qHead = NULL;
//    qHead = NULL;
//    qHead->name = NULL;
//    qHead->next = NULL;
//    qHead->priority = NULL;

}

LinkedListPatientQueue::~LinkedListPatientQueue() {
    // TODO: write this destructor
    delete qHead;

}

void LinkedListPatientQueue::clear() {
    /*Remove all elements from the patient queue, freeing memory for all nodes that are removed.*/
    while(qHead !=NULL) {
        PatientNode *cur;
        cur = &*qHead;
        qHead = qHead->next;
        delete cur;
//        qHead = qHead->next;
    }
}

string LinkedListPatientQueue::frontName() {
    /* Return the name of the most urgent patient, without removing it or altering the state of the queue.*/
    if (qHead==NULL) {
        return "exception error";
    } else{
        string firstOne = qHead->name;
        return firstOne;
    }

}

int LinkedListPatientQueue::frontPriority() {
    /* Return the priority of the most urgent patient, without removing it or altering the state of the queue.*/
    int firstOne;
    try {
        firstOne = qHead->priority;
    }
    catch(...) {
        cerr << "exception";
    }
    return firstOne;
//    if (qHead==NULL) {
//        return -1;
//    } else{
//        string firstOne = qHead->priority;
//        return firstOne;
//    }
}

bool LinkedListPatientQueue::isEmpty() {
    /* Return true if your patient queue does not contain any elements,
     * Return false if it does contain at least one patient.*/
    if (qHead == NULL) {
        return true;
    } else {
        return false;
    }

}

void LinkedListPatientQueue::newPatient(string name, int priority) {
    /* Create new patient.
     * Add the given person into your patient queue with the given priority.
     * Duplicate names and priorities are allowed. Any string and integer is legal; */
    PatientNode *cur=NULL, *prev=NULL,*newOne = new PatientNode;
    PatientNode patientIn(name,priority,cur);
    newOne->name = name;
    newOne->priority = priority;
    newOne->next = cur;
    for (cur = qHead; cur!= NULL; cur=cur->next) {
        if (patientIn.priority < cur->priority) break;
        prev = cur;
    }

    newOne->next = cur; //splice outgoing ptr
    if(prev != NULL)
        prev->next = newOne; // splice incoming ptr
    else
        qHead = newOne;

}

string LinkedListPatientQueue::processPatient() {
    /* remove the patient with the most urgent priority from your queue,
     * also return their name as a string.
     * Throw a string exception if the queue does not contain any patients.*/

    if (qHead==NULL) {
        return "exception error";
    } else{
        string firstOne = qHead->name;
        qHead = qHead->next;
        return firstOne;
    }

}

void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
/* Modify the priority of a given existing patient in the queue.
 * The intent is to change the patient's priority to be more urgent.
 * Your function should throw a string exception, if:
 * 1, the given patient is present in the queue and already has a more urgent priority than the given new priority,
 * 2, the given patient is not already in the queue,
 * If the given patient name occurs multiple times in the queue,
 * you should alter the priority of the highest priority person with that name that was placed into the queue. */
    for (PatientNode *cur = qHead; cur!= NULL; cur=cur->next) {
        if (cur->name == name ) {
            if (cur->priority < newPriority)
                cout << "exception" << endl;
            else
                cur->priority = newPriority;
            return;
        }
    }
    cout << "exception" << endl;
}

string LinkedListPatientQueue::toString() {
/* Printing the patient queue to the console.
 * The function should return a string as defined as follows:
 * The elements should be printed out in front-to-back order and must be in the form of
 * priority: value with {} braces and separated by a comma and space, such as:
 * {2:Ford, 4:Bernard, 5:Dolores, 5:William, 5:Teddy, 8:Arnold}
 * The PatientNode structure has a << operator that may be useful to you.
 */
    string output = "{";

    for (PatientNode *cur = qHead; cur!= NULL; cur=cur->next) {
        output += integerToString(cur->priority) + ":" + cur->name + "," + " ";
    }

    output += "}";
    return output;
}
