/*
 * MilliTimer.h
 *
 *  Created on: Feb 8, 2011
 *      Author: dd@ophomo.org
 *
 *  http://opensource.org/licenses/mit-license.php
 */

#ifndef MILLITIMER_H_
#define MILLITIMER_H_
#include <Arduino.h>

// The millisecond timer can be used for timeouts up to 60000 milliseconds.
// Setting the timeout to zero disables the timer.
//
// for periodic timeouts, poll the timer object with "if (timer.poll(123)) ..."
// for one-shot timeouts, call "timer.set(123)" and poll as "if (timer.poll())"

class MilliTimer {
    word next;
    byte armed;
public:
    MilliTimer () : armed (0) {}

    byte poll(word ms =0);
    word remaining() const;
    byte idle() const { return !armed; }
    void set(word ms);
};

#endif /* MILLITIMER_H_ */
