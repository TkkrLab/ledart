#ifndef __TIMER_H__
#define __TIMER_H__

class Timer
{
public:
    Timer();
    Timer(int);
    bool valid(void);

private:
    int current = 0;
    int previous = 0;
    int interval = 0;

};

#endif
