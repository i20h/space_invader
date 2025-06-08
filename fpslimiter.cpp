#include "fpslimiter.h"

fpsLimiter::fpsLimiter(unsigned int value) {
    this->FPS = value;
}

void fpsLimiter::wait() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / this->FPS));
}
