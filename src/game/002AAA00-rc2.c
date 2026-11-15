
/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "common.h"

extern f32 func_00282C10(f32);
extern f32 func_00282C48(f32);
extern f32 func_00283B98(f32, f32);
extern void func_002AA2E8(f32 *, f32, f32);
extern f32 func_002AA738(s32, f32, f32);
extern void func_002AA800(f32 *, s32, f32, f32);

/* Moves a value toward a target using a speed that builds up and then brakes in time to
   stop on the target. Mode 2 lets it pick the shorter way around. */
f32 func_002AAA00(f32 *value, f32 *velocity, s32 mode, f32 target, f32 accel, f32 brake, f32 maxSpeed)
{
    s32 direction;
    f32 delta;
    f32 stopDistance;
    f32 absDelta;
    f32 absDeltaTmp;
    f32 desiredSpeed;

    direction = mode;
    if (mode != 2) {
        goto abc;
    }
    if (target > 0.0f && *value < 0.0f) {
        goto aa0;
    }
    direction = 0;
    if (target < 0.0f && *value > 0.0f) {
        goto aa0;
    }
    goto abc;
aa0:
    direction = 1;
    if (target < 0.0f) {
        direction = -1;
    }
abc:
    delta = GetShortestAngleDelta(direction, target, *value);
    if (*velocity == 0.0f && delta == 0.0f) {
        return 0.0f;
    }
    {
        f32 oldVelocity = *velocity;
        f32 newVelocity;

        if (0.0f <= oldVelocity * delta) {
            stopDistance = ((oldVelocity * oldVelocity) / brake) * 0.5f;
            if (FloatAbs(delta) < stopDistance) {
                absDeltaTmp = FloatAbs(delta);
                if (stopDistance < absDeltaTmp + FloatAbs(*velocity)) {
                    ApproachValue(velocity, 0.0f, brake);
                } else {
                    ApproachValue(velocity, 0.0f, brake * 1.1f);
                }
            } else {
                desiredSpeed = square_root((brake + brake) * delta);
                if (maxSpeed < desiredSpeed) {
                    desiredSpeed = maxSpeed;
                }
                if (delta < 0.0f) {
                    StepAngleTowardTarget(velocity, 0, -desiredSpeed, accel);
                } else {
                    StepAngleTowardTarget(velocity, 0, desiredSpeed, accel);
                }
            }
            absDelta = FloatAbs(delta);
            if (FloatAbs(*velocity) < absDelta) {
                newVelocity = *velocity;
            } else {
                *value = target;
                return delta;
            }
        } else {
            if (0.0f <= oldVelocity) {
                newVelocity = oldVelocity - brake;
            } else {
                newVelocity = oldVelocity + brake;
            }
            *velocity = newVelocity;
        }
        *value = FastAddRotations(newVelocity, *value);
        return *velocity;
    }
}
