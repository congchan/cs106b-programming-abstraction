/* Assignment 0: Getting started in C++
 *
 * @Author: Cong Chen
 * @Version: 2017/06
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "random.h"
using namespace std;
int vote(int voter, double error) {
    /* This function simulate possible misrecord of voter's vote, and return the misrecord num.*/
    int sum = 0;
    for (int i=1; i<=voter; i++) {
        bool R = randomChance(error);
        if (R) {
            sum += 1;
        }
    }
    return sum;
}

int election(int voters, double spread, double error) {
    /*This function simulate a election between A & B with a, spread percentage define the original result,
     * if spread>0 then A beats B, if spread<0 then B beats A. With a error affecting the result,
     * return 0 if result remains affected, others return 1.
     */
    int votersForA = voters*(0.5+spread);
    int votersForB = voters-votersForA;
    int votersForAmiscorrect = vote(votersForA, error);
    int votersForBmiscorrect = vote(votersForA, error);
    int votersForARecorded = votersForA - votersForAmiscorrect + votersForBmiscorrect;
    int votersForBRecorded = votersForB - votersForBmiscorrect + votersForAmiscorrect;
    if (votersForARecorded >= votersForBRecorded) {
            return 0;
    } else  {
          return 1;
    }
}

int IsPerfect(int n) {
    /* This function test whether a integer is perfect number or not. */
    int sum = 0;
    for (int i=1;i<n;i++) {
        if (n%i==0) sum+=i;
    }
    if (sum==n) return sum;
    return 0;
}

int main() {
    /*2. Simulation and use of random/io libraries. */
    cout << "2. Simulation and use of random/io libraries." << endl;
    int trials = 500;
    int invalid = 0;
    cout << "Enter number of voters: " << endl;
    int voters = getInteger();
    cout << "Enter percentage spread between candidates: " << endl;
    double spread = getDouble();
    cout << "Enter voting error percentage: " << endl;
    double error = getDouble();
    int failsTime = 0;
    for (int i=1;i<=trials;i++) {
        int result = election(voters,spread,error);
        failsTime = failsTime + result;
    }
    cout <<"Chance of an invalid election result after 500 trials = " << double(failsTime)/trials*100 << "%" << endl;

    /*1. Variables, arithmetic, and control structures. */
    cout << "1. Variables, arithmetic, and control structures." << endl;
    for (int i=1; i<=10000;i++) {
        int perfectNum = IsPerfect(i);
        if (perfectNum)
        cout << "Perfect number found is: " << perfectNum << endl;
    }
    return 0;



}



