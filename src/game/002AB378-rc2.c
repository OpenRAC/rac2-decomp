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
struct Ord3 {
    s32 w[3];
};
extern struct Ord3 g_quat_next_axis_table;

/* Turns a rotation matrix into a quaternion. */
void mat_to_quaternion(f32 *quat, f32 *matrix) {
    struct Ord3 next_axis = g_quat_next_axis_table;
    f32 m[3][3];
    f32 trace;
    f32 scale;
    s32 i;
    s32 j;
    s32 k;

    trace = matrix[0] + matrix[5] + matrix[10];
    if (trace > 0.0f) {
        scale = square_root(trace + 1.0f);
        quat[3] = scale * 0.5f;
        scale = 0.5f / scale;
        quat[0] = (matrix[9] - matrix[6]) * scale;
        quat[1] = (matrix[2] - matrix[8]) * scale;
        quat[2] = (matrix[4] - matrix[1]) * scale;
    } else {
        m[0][1] = matrix[1];
        m[0][2] = matrix[2];
        m[1][0] = matrix[4];
        m[1][2] = matrix[6];
        m[2][0] = matrix[8];
        m[2][1] = matrix[9];
        m[0][0] = matrix[0];
        m[1][1] = matrix[5];
        m[2][2] = matrix[10];
        i = 0;
        if (matrix[0] < matrix[5]) {
            i = 1;
        }
        if (m[i][i] < matrix[10]) {
            i = 2;
        }
        j = next_axis.w[i];
        k = next_axis.w[j];
        scale = square_root(m[i][i] - (m[j][j] + m[k][k]) + 1.0f);
        quat[i] = scale * 0.5f;
        if (scale != 0.0f) {
            scale = 0.5f / scale;
        }
        quat[3] = (m[k][j] - m[j][k]) * scale;
        quat[j] = (m[j][i] + m[i][j]) * scale;
        quat[k] = (m[k][i] + m[i][k]) * scale;
    }
}
