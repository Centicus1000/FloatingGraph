#include "timer.h"

#include <thread>
#include <iostream>

/// tik
/// call at begining of loop, saves current time for measuring
void Timer::tik() {
    t1 = std::chrono::steady_clock::now();
}

/// tok
/// call at end of loop, checks how much time has passes since tik()
/// sleeps remaining time to reach target loop frequency
/// uses low pass filter for adaptive adjustment of sleep time
void Timer::tok() {
    t2 = std::chrono::steady_clock::now();
    
    // find current workload and warn if too high
    duration load{ t1 - t2 };
    warn();
    
    // sleep remaning time
    duration sleep{ target - load + adjust };
    if (sleep > duration{0.f}) {
        std::this_thread::sleep_for(sleep);
    }
    
    // find real frame time
    t3 = std::chrono::steady_clock::now();
    frame = t3 - t1;
    
    // Compute the sleep adjustment using a low pass filter
    adjust = 0.9 * adjust + 0.1 * (target - frame);
}

/// print
/// prints message of current frame time, work load and sleep adjustment
void Timer::print() {
    std::cout << "frame: " << frame.count() << "\tload: " << load.count()/target.count()*100. << "%\tadjust: " << adjust.count() << std::endl;
}

/// warn
/// gets called in tok, prints a waring if load exceeds 90.0%
void Timer::warn() {
    double percent{ load.count()/target.count()*100. };
    if (percent > 90.) std::cout << "Timer Warning: work load " << percent << " exceeds 90.% of target. " << std::endl;
}

/// return current frame time (delta time)
float Timer::dt() {
    return frame.count();
}
