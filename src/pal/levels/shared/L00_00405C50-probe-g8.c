#include "include_asm.h"
#include "common.h"

/* func_PAL_L00_00405C50, the PAL copy of func_00330150: the same C without the
   copy of the settings record, where the state word's 10 becomes 8. It reads two
   small-data constants $gp-relative, so it needs -G8. */

typedef struct {
    char pad[0x18];
    char *object;
    int unknown;
    float position[4];
    float point[4];
    float normal[4];
} SweepHit;

extern float D_001B096C __attribute__((sda));
extern float D_001B0970 __attribute__((sda));
extern float D_001B2830[4] __attribute__((sda));
extern int D_001B2848;
extern float D_001BAFB0[4];
extern SweepHit D_001BAF80;
extern float func_00282C48(float);
extern void func_00282C88(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282D90(void *, void *, float);
extern float func_00283CE0(int);
extern float func_00283198(float), func_00283180(float);
extern void func_002837D0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278870(void *, float);

/* Casts 32 rays over a quarter turn about the row at +0xE0, in the direction
   of the sign of the state's +0x58. Each hit adds its correction to a sum,
   and the mean of the sum moves the position at +0x10. A hit on a surface of
   type 5 sets object state 9 and the state word at +0x60 to 8.

   The two copies of the object give the order of the spill slots at
   0xBC..0xCC. gcse numbers its reaching registers in hash-bucket order, and
   the bucket of an address includes the number of its base register, so
   retail's order needs a base of pseudo 118 to 133, set before the block
   that holds the first object + 0x10. GCSE copy propagation goes one copy
   deep per pass, so PRE sees self's offsets based on moby. moby has to stay
   in use beyond the block, and the copies must not be adjacent, or cse
   collapses them. moby's number follows the declarations before it, so the
   function's named scalars are what bring it to that pseudo. */
void func_PAL_L00_00405C50(char *object)
{
    float base[4], sum[4], axis[4], first[4], rotated[4], temporary[4], inverse[4];
    float endpoint[4], opposite[4], normal[4], correction[4];
    char *state = *(char **)(object + 0x68);
    int negative, hits, i, hit, last;
    float angle, sine, cosine;
    float speed, threshold, radius, zero, lift, drop;
    float step, span, quarter, x, y, z, nx, ny, nz;
    float down, unit, one, total;
    char *other, *info;
    float ratio;
    int type;

    speed = func_00282C48(*(float *)(state + 0x58));
    threshold = 0.0001f;
    if (speed < threshold) return;
    {
        char *self;
        char *moby = object;

        negative = 1;
        self = moby;
        radius = *(float *)(state + 0x58);
        zero = 0.0f;
        if (!(radius <= zero)) negative = 0;
        func_00282C88(sum);
        hits = 0;
        lift = D_001B096C;
        drop = -lift;
        func_00282F20(base, D_001B2830, drop);
        func_00282CC0(base, base, self + 0x10);
        if (!D_001B2848 && func_00278870(base, D_001B0970)) {
            func_00282CF0(axis, D_001BAFB0, base);
            func_00282CC0(self + 0x10, axis, self + 0x10);
        }
        for (i = 0; i < 32; i++) {
            step = func_00283CE0(i);
            last = 31;
            span = func_00283CE0(last);
            ratio = step / span;
            func_00282F20(axis, self + 0xD0, D_001B0970);
            quarter = 1.57079637f;
            angle = ratio * quarter;
            sine = func_00283198(angle);
            if (!negative) sine = -sine;
            func_00282D30(rotated, self + 0xE0, sine);
            cosine = func_00283180(angle);
            rotated[3] = cosine;
            x = rotated[0];
            nx = -x;
            inverse[0] = nx;
            y = rotated[1];
            ny = -y;
            inverse[1] = ny;
            z = rotated[2];
            nz = -z;
            inverse[2] = nz;
            inverse[3] = cosine;
            func_002837D0(temporary, rotated, axis);
            func_002837D0(first, temporary, inverse);
            func_00282CC0(endpoint, first, base);
            hit = func_002761F8(base, endpoint, 0, moby, 0);
            if (hit) {
                hits++;
                down = -1.0f;
                func_00282D30(opposite, D_001B2830, down);
                unit = 0.0009765625f;
                func_00282D30(normal, D_001BAF80.normal, unit);
                one = 1.0f;
                func_00282F20(normal, normal, one);
                func_00282CF0(correction, D_001BAF80.position, endpoint);
                func_00282CC0(sum, sum, correction);
                other = D_001BAF80.object;
                if (other) {
                    info = *(char **)(other + 0x24);
                    type = *(short *)(info + 0x46);
                    if (type == 5) {
                        self[0x20] = 9;
                        *(int *)(state + 0x60) = 8;
                    }
                }
            }
        }
        if (hits) {
            total = (float)hits;
            func_00282D90(sum, sum, total);
            func_00282CC0(self + 0x10, self + 0x10, sum);
        }
    }
}
