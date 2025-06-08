#ifndef FPSLIMITER_H
#define FPSLIMITER_H

#include <chrono>
#include <thread>

class fpsLimiter
{
private:
    unsigned int FPS;
public:
    fpsLimiter(unsigned int value);
    void wait();
};

#endif // FPSLIMITER_H
