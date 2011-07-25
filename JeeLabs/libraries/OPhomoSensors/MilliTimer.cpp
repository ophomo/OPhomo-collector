/*
 * MilliTimer.cpp
 *
 *  Created on: Feb 8, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#include "MilliTimer.h"


byte MilliTimer::poll(word ms) {
    byte ready = 0;
    if (armed) {
        word remain = next - millis();
        // since remain is unsigned, it will overflow to large values when
        // the timeout is reached, so this test works as long as poll() is
        // called no later than 5535 millisecs after the timer has expired
        if (remain <= 60000)
            return 0;
        // return a value between 1 and 255, being msecs+1 past expiration
        // note: the actual return value is only reliable if poll() is
        // called no later than 255 millisecs after the timer has expired
        ready = -remain;
    }
    set(ms);
    return ready;
}

word MilliTimer::remaining() const {
    word remain = armed ? next - millis() : 0;
    return remain <= 60000 ? remain : 0;
}

void MilliTimer::set(word ms) {
    armed = ms != 0;
    if (armed)
        next = millis() + ms - 1;
}
