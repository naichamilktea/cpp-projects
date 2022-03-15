#ifndef __WATCH_H__
#define __WATCH_H__
#include <windows.h>
class Watch{
private:
    long long elapsed;
    LARGE_INTEGER start,stop,frequency;
public:
    Watch();
    ~Watch();
    void Start();
    void Stop();
    void Restart();
    double Elapsed();
    double ElapsedMS();
    double ElapsedSecond();
};
#endif