/* SPDX-License-Identifier: MIT
 * MIT License
 *
 * Copyright (c) 2026 RC2 decomp contributions
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

extern s32 D_001AFC6C;
extern s32 g_001AFC6C __attribute__((sda));
extern f32 D_001B0A80 __attribute__((sda));
extern f32 D_001B0A84 __attribute__((sda));
extern s8 D_001B5200[];

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct Obj { s8 pad[0x10]; struct Vec4 pos; };
struct Tab { s8 pad[0x140]; f32 f140; f32 f144; };

f32 func_002A7878(f32 a, f32 b);
f32 func_002A7940(void);
void func_002AF000(struct Vec4 *p, f32 x, f32 y, f32 z);
s32 func_002A7820(s32 a, s32 b);
void func_002BDBC0(struct Vec4 *a, struct Vec4 *b, u32 c, s32 d, s32 e, f32 f);
void func_00282CC0(struct Vec4 *a, struct Vec4 *b, struct Vec4 *c);
f32 func_00283248(f32 a, f32 b);
f32 func_002A78D8(f32 a, f32 b);
void func_00283CF0(f32 a);
f32 func_00283B98(f32 a, f32 b);
f32 func_00283180(f32 a);
f32 func_00283198(f32 a);
void func_002C7E28(struct Vec4 *a, struct Vec4 *b, s32 c);
void func_003323F0(struct Obj *a);
void func_0029F338(struct Obj *a);

/* Per-frame update for an explosion effect: throws out a few sparks and pushed particles (fewer as the counter drops), counts the counter down and then runs the shared update. */
void func_003320F0(struct Obj *moby)
{
    struct Vec4 vecB;
    struct Vec4 vecA;
    struct Tab *camera;
    s32 i;
    s32 j;
    f32 randA;
    f32 randB;
    f32 randC;
    f32 randD;
    f32 randE;
    f32 randF;
    f32 randG;
    s32 randH;
    f32 angle;
    f32 spreadAngle;
    f32 offsetX;
    f32 offsetY;
    f32 offsetZ;
    f32 turn;
    f32 cosPart;
    f32 sinPart;
    f32 speed;

    i = 0;
    if (0x21 - D_001AFC6C > 0) {
        do {
            i++;
            randA = RandomFloatRange(0.0f, 0.3700000047683716f);
            randB = RandomAngle();
            randC = RandomAngle();
            BuildSphericalOffset(&vecA, randA, randB, randC);
            randD = RandomFloatRange(0.3499999940395355f, 0.6000000238418579f);
            vecA.z = vecA.z + randD;
            FastVecAdd(&vecA, &vecA, &moby->pos);
            randE = RandomFloatRange(0.0016666668234393f, 0.01666666753590107f);
            randF = RandomAngle();
            randG = RandomAngle();
            BuildSphericalOffset(&vecB, randE, randF, randG);
            randH = RandomIntRange(0x1E, 0x39);
            SpawnGrowingPuffParticle(&vecA, &vecB, 0x4F20507F, 0x102F, randH, 150000.0f);
        } while (i < 0x21 - D_001AFC6C);
    }
    j = 0;
    if (0x32 - D_001AFC6C > 0) {
        camera = (struct Tab *)gActiveCamera;
        do {
            j++;
            angle = FastMatrixHelperA(camera->f140 - moby->pos.x, camera->f144 - moby->pos.y);
            FloatToInt(RandomSignedFloatRange(1.0f, 2.0f));
            offsetX = RandomSignedFloatRange(0.0f, 0.15000000596046448f);
            vecB.x = moby->pos.x + offsetX;
            offsetY = RandomSignedFloatRange(0.0f, 0.15000000596046448f);
            vecB.y = moby->pos.y + offsetY;
            offsetZ = RandomSignedFloatRange(0.0f, 0.15000000596046448f);
            vecB.z = moby->pos.z + offsetZ;
            speed = D_001B0A80;
            turn = RandomSignedFloatRange(0.0f, -1.5707964897155762f);
            spreadAngle = FastAddRotations(angle, turn);
            cosPart = FastSinOrCosA(spreadAngle);
            vecA.x = cosPart * 0.01666666753590107f * speed;
            sinPart = FastSinOrCosB(spreadAngle);
            vecA.y = sinPart * 0.01666666753590107f * speed;
            speed = D_001B0A84;
            vecA.z = speed * 0.01666666753590107f;
            SpawnSpinningSparkParticle_002C7E28(&vecB, &vecA, 0x12C);
        } while (j < 0x32 - D_001AFC6C);
    }
    g_001AFC6C = D_001AFC6C - 1;
    ReleaseSlotById(moby);
    MarkMobySpawned(moby);
}
