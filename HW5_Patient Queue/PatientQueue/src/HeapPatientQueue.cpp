// heappatientqueue.cpp
// THIS IS AN EXTENSION AND NOT REQUIRED FOR THE ASSIGNMENT
// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "HeapPatientQueue.h"

HeapPatientQueue::HeapPatientQueue() {
    /* Dynamicly allocate memory for initialization of an patientNode array with size = 1,
     * leave index 0 blank and start the data at an overall parent "root" or "start" index of 1.*/
    capacity = 1;
    binaryQueue = new PatientNode[capacity];
    size = 0;
}

HeapPatientQueue::~HeapPatientQueue() {
    /* Because memory has been dynamically allocated, it must be freed with delete[].
     * Otherwise, a memory leak will result*/
    delete [] binaryQueue;
}

void HeapPatientQueue::clear() {
    /* Remove all elements from the patient queue, freeing memory for all nodes that are removed.*/
    delete [] binaryQueue;
    capacity = 1;
    binaryQueue = new PatientNode[capacity];
    size = 0;
}

string HeapPatientQueue::frontName() {
    /* Return the name of the most urgent patient, without removing it or altering the state of the queue.*/
    if (size==0) {
        throw underflow_error("exception");
    } else{
        return binaryQueue[1].name;
    }
}

int HeapPatientQueue::frontPriority() {
    /* Return the priority of the most urgent patient, without removing it or altering the state of the queue.*/
    if (size==0) {
        throw underflow_error("exception");
    } else{
        return binaryQueue[1].priority;
    }
}

bool HeapPatientQueue::isEmpty() {
    /* Return true if your patient queue does not contain any elements,
     * Return false if it does contain at least one patient.
     To check the HeapPatientQueue isEmpty, simply check the size;*/
    return (size==0);
}

void HeapPatientQueue::newPatient(string name, int priority) {   
    /* Add the given person into your patient queue with the given priority.
     * Duplicate names and priorities are allowed. Any string and integer is legal; */

    //First check the Size and Capacity, and expand the size if necessary
    if (size == capacity-1) {
        PatientNode *newArray = new PatientNode[capacity*2];
        for (int k=0;k<=size;++k) {
            newArray[k] = std::move(binaryQueue[k]);
        }
        capacity = capacity*2;
        std::swap(binaryQueue,newArray);
        delete [] newArray;
    }

    //Create new patient.
    PatientNode *newOne = new PatientNode(name,priority);

    /* Adding (enqueuing) a new element into a heap involves placing it into the first empty index i
     * and then "bubbling up" or "percolating up" by swapping it with its parent index (i/2)
     * so long as it has a more urgent (lower) priority than its parent. Use integer division. */
    // percolate up
    int hole = ++size;
    binaryQueue[0]=std::move(*newOne);
    for (;(priority<binaryQueue[hole/2].priority || (priority==binaryQueue[hole/2].priority && name<binaryQueue[hole/2].name) );hole/=2) {
        binaryQueue[hole] = std::move(binaryQueue[hole/2]);
    }
    binaryQueue[hole] = std::move(binaryQueue[0]);

}

string HeapPatientQueue::processPatient() {
    /* Removing (dequeuing) the most urgent element from a heap involves moving
     * the element from the last occupied index all the way up to the "root" or "start" index of 1,
     * replacing the root that was there before; and then "bubbling down" or "percolating down"
     * by swapping it with its more urgent-priority child index (i*2 or i*2+1) so long as
     * it has a less urgent (higher) priority than its child.
     * also return their name as a string.
     * Throw a string exception if the queue does not contain any patients.*/
    if (isEmpty()) throw underflow_error("exception") ;
    int hole = 1;
    string name_tobeProcess = binaryQueue[hole].name;
    int priority_tobeProcess = binaryQueue[hole].priority;
    //replacing the root with the last one;
    binaryQueue[hole]=std::move(binaryQueue[size--]);
    string name_tobePerD = binaryQueue[hole].name;
    int priority_tobePerD = binaryQueue[hole].priority;
    //percolating down
    int child;
    for (; hole*2<=size;hole=child) {
        child = hole*2;
        if ( child!=size && (binaryQueue[child+1].priority<binaryQueue[child].priority || (binaryQueue[child+1].priority==binaryQueue[child].priority && binaryQueue[child+1].name<binaryQueue[child].name)) )
            ++child;
        if ( binaryQueue[child].priority<priority_tobePerD || (binaryQueue[child].priority==priority_tobePerD && binaryQueue[child].name<name_tobePerD) ) {
            binaryQueue[hole] = std::move(binaryQueue[child]);
        } else break;

    }
    binaryQueue[hole].name=name_tobePerD;
    binaryQueue[hole].priority=priority_tobePerD;

    return name_tobeProcess;
}

void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    /* Modify the priority of a given existing patient in the queue.
     * The intent is to change the patient's priority to be more urgent.
     * Your function should throw a string exception, if:
     * 1, the given patient is present in the queue and already has a more urgent priority than the given new priority,
     * 2, the given patient is not already in the queue,
     * If the given patient name occurs multiple times in the queue,
     * you should alter the priority of the highest priority person with that name that was placed into the queue. */

    // looping over the heap to, find out the most urgent one where mutiple names exsist.
    int mostUrgent=NULL;
    int hole;
    for (int i=1;i<=size;i++) {
        if (binaryQueue[i].name==name) {
            if (mostUrgent == NULL || binaryQueue[i].priority<mostUrgent ) {
                mostUrgent = binaryQueue[i].priority;
                hole = i;
            }
        }
    }

    if (mostUrgent==NULL || mostUrgent<=newPriority) {
//        throw underflow_error("exception") ;
        cout << "exception" << endl;
        return;
    } else
        binaryQueue[hole].priority=newPriority;


    // "bubbling up" that value from its present location, somewhat like an enqueue operation.
    binaryQueue[0]=std::move(binaryQueue[hole]);
    for (;(newPriority<binaryQueue[hole/2].priority || (newPriority==binaryQueue[hole/2].priority && name<binaryQueue[hole/2].name) );hole/=2) {
        binaryQueue[hole] = std::move(binaryQueue[hole/2]);
    }
    binaryQueue[hole] = std::move(binaryQueue[0]);

}

string HeapPatientQueue::toString() {
    /* Printing the patient queue to the console.
     * The function should return a string as defined as follows:
     * The elements should be printed out in front-to-back order and must be in the form of
     * priority: value with {} braces and separated by a comma and space, such as:
     * {2:Ford, 4:Bernard, 5:Dolores, 5:William, 5:Teddy, 8:Arnold}
     * The PatientNode structure has a << operator that may be useful to you.
     */
        string output = "{";
        for (int i=1;i<=size;i++) {
            output += integerToString(binaryQueue[i].priority) + ":" + binaryQueue[i].name + "," + " ";
        }
        output += "}";
        return output;
}
