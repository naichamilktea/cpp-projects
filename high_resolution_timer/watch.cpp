#include "watch.h"
Watch::Watch(){
    elapsed=0;
    start.QuadPart=stop.QuadPart=0;
    QueryPerformanceFrequency(&frequency);
}
Watch::~Watch(){

}
void Watch::Start(){
    QueryPerformanceCounter(&start);
}
void Watch::Stop(){
    QueryPerformanceCounter(&stop);
    elapsed+=(stop.QuadPart-start.QuadPart)*1000000/frequency.QuadPart;
}
void Watch::Restart(){
    elapsed=0;
    Start();
}
double Watch::Elapsed(){
    return static_cast<double>(elapsed);
}
double Watch::ElapsedMS(){
    return elapsed/1000.0;
}
double Watch::ElapsedSecond(){
    return elapsed/1000000.0;
}