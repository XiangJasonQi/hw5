#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// check if last element in matrix is not filled
bool check_status(const DailySchedule& sched);

// back track
bool sched_helper(const AvailabilityMatrix& avail, const size_t max, DailySchedule& sched, int day, int worker, int* shift_storage); 

// check max shift
// bool check_maxshift(const DailySchedule& sched, const size_t max, int day, const Worker_T ID);

// check if need to move to next day
bool check_day(const DailySchedule& sched, int day);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    //create the matrix
    for(int i = 0; i < avail.size(); i++){
        sched.push_back(vector<Worker_T>());

        for(int j = 0; j < dailyNeed; j++){
            sched[i].push_back(INVALID_ID);

        }
    }

    //create vector to record how many days each worker worked
    int* shift_storage = new int[avail[0].size()]();

    bool status = sched_helper(avail, maxShifts, sched, 0, 0, shift_storage);

    delete[] shift_storage; 

    return status;
}


bool check_status(const DailySchedule& sched){
    if(sched[sched.size()-1][sched[sched.size()-1].size()-1] != INVALID_ID){
        return true;
    }

    return false;


}

bool sched_helper(const AvailabilityMatrix &avail, const size_t max, DailySchedule &sched, int day, int worker, int* shift_storage)
{

    if(day >= avail.size()){
        return check_status(sched);
    }
    if(worker >= sched[day].size()){
        return sched_helper(avail, max, sched, day + 1, 0, shift_storage);
    }



    for(int i = 0; i < avail[day].size(); i++){
        if(avail[day][i] == 1){
            Worker_T worker_ID = i;

            //check if this worker has already been scheduled
            if(find(sched[day].begin(), sched[day].end(), worker_ID) != sched[day].end()){
                continue;
            }

            //check max shift
            if(shift_storage[i] < max){
                sched[day][worker] = worker_ID;
                shift_storage[i]++;
                if(check_status(sched)) return true;

                //check if change row
                bool status;
                if(check_day(sched, day)){
                    status = sched_helper(avail, max, sched, day+1, 0, shift_storage);
                } else{
                    status = sched_helper(avail, max, sched, day, worker+1, shift_storage);
                }

                if(status == true){
                    return true;
                }

                sched[day][worker] = INVALID_ID;
                shift_storage[i]--;

            }
        }
    }


    if(check_status(sched)) return true;

    return false;
}

// bool check_maxshift(const DailySchedule &sched, const size_t max, int day, const Worker_T ID)
// {
//     if(max == 0){
//         return true;
//     }

//     if(day == 0){
//         return false; 
//     }

//     if(find(sched[day - 1].begin(), sched[day - 1].end(), ID) != sched[day - 1].end()){
//         return check_maxshift(sched, max - 1, day - 1, ID);
//     }
// }

bool check_day(const DailySchedule &sched, int day)
{
    if(sched[day][sched[day].size() - 1] != INVALID_ID) return true;

    return false;
}
