#include "names.h"

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

extern f32 square_root(f32);
extern f32 math_fabs(f32);
extern f32 FastAddRotations(f32, f32);
extern void ApproachValue(f32 *, f32, f32);
extern f32 math_shortest_angle_delta(s32, f32, f32);
extern void StepAngleTowardTarget(f32 *, s32, f32, f32);

/* Moves a value toward a target using a speed that builds up and then brakes in time to
   stop on the target. Mode 2 lets it pick the shorter way around. */
f32 math_approach_target_with_direction_mode(f32 *value, f32 *velocity, s32 mode, f32 target, f32 accel, f32 brake, f32 max_speed)
{
    s32 direction;
    f32 delta;
    f32 stop_distance;
    f32 abs_delta;
    f32 abs_delta_tmp;
    f32 desired_speed;

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
    delta = math_shortest_angle_delta(direction, target, *value);
    if (*velocity == 0.0f && delta == 0.0f) {
        return 0.0f;
    }
    {
        f32 old_velocity = *velocity;
        f32 new_velocity;

        if (0.0f <= old_velocity * delta) {
            stop_distance = ((old_velocity * old_velocity) / brake) * 0.5f;
            if (math_fabs(delta) < stop_distance) {
                abs_delta_tmp = math_fabs(delta);
                if (stop_distance < abs_delta_tmp + math_fabs(*velocity)) {
                    ApproachValue(velocity, 0.0f, brake);
                } else {
                    ApproachValue(velocity, 0.0f, brake * 1.1f);
                }
            } else {
                desired_speed = square_root((brake + brake) * delta);
                if (max_speed < desired_speed) {
                    desired_speed = max_speed;
                }
                if (delta < 0.0f) {
                    StepAngleTowardTarget(velocity, 0, -desired_speed, accel);
                } else {
                    StepAngleTowardTarget(velocity, 0, desired_speed, accel);
                }
            }
            abs_delta = math_fabs(delta);
            if (math_fabs(*velocity) < abs_delta) {
                new_velocity = *velocity;
            } else {
                *value = target;
                return delta;
            }
        } else {
            if (0.0f <= old_velocity) {
                new_velocity = old_velocity - brake;
            } else {
                new_velocity = old_velocity + brake;
            }
            *velocity = new_velocity;
        }
        *value = FastAddRotations(new_velocity, *value);
        return *velocity;
    }
}
