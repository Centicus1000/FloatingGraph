#ifndef morfmaker_timer_h
#define morfmaker_timer_h

#include <chrono>

class Timer {
    // type definition
    typedef std::chrono::duration<double> duration;
    typedef std::chrono::steady_clock::time_point time_point;
    
    time_point t1, t2, t3;
    duration adjust, load;
    
    void warn();

public:
    duration frame {     0. };
    duration target{ 1./60. };

    void tik();
    void tok();
    void print();
    float dt();
};

#endif /* morfmaker_timer_h */
