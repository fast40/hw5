#include <cstddef>
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

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t i
);

bool invalid(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);

bool invalid(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::map<Worker_T, size_t> &shifts,
    size_t i
);


// Add your implementation of schedule() and other helper functions here

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t i
) {
        if (invalid(avail, dailyNeed, maxShifts, sched)) {
                return false;
        }

        if (i >= avail.size() * dailyNeed) {  // TODO: fix the -1 issue
                return true;
        }

        size_t day_index = i / dailyNeed;
        size_t worker_index = i % dailyNeed;

        if (day_index == sched.size()) {
                sched.resize(sched.size() + 1);
        }

        for (size_t worker = 0; worker < avail[day_index].size(); worker++) {
                if (!avail[day_index][worker] || std::find(sched[day_index].begin(), sched[day_index].end(), worker) != sched[day_index].end()) {
                        continue;
                }
                
                sched[day_index].push_back(worker);

                if (scheduleHelper(avail, dailyNeed, maxShifts, sched, i + 1)) {
                        return true;
                }

                sched[day_index].pop_back();
        }

        if (worker_index == 0) {
                sched.pop_back();
        }

        return false;
}

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

        bool x = scheduleHelper(avail, dailyNeed, maxShifts, sched, 0);

        return x;
}

bool invalid(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {

        map<Worker_T, size_t> shifts;

        // cout << "asdf asdf asdf asd fasdfa sdf as df"<< shifts[sched[day_index][worker_index]] << endl;;
        // cout << "haha"<< endl;

        return invalid(avail, dailyNeed, maxShifts, sched, shifts, 0);
}

bool invalid(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::map<Worker_T, size_t> &shifts,
    size_t i
) {
        // cout << "invalid called" << endl;
        size_t day_index = i / dailyNeed;
        size_t worker_index = i % dailyNeed;

        if (day_index >= sched.size() || worker_index >= sched[day_index].size()) {
                return false;
        }
        else if (++shifts[sched[day_index][worker_index]] > maxShifts) {
                return true;
        }
        else {
                return invalid(avail, dailyNeed, maxShifts, sched, shifts, i + 1);
        }
}
