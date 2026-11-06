/* func_PAL_L00_003C11A0, the PAL copy of func_L00_003BD510: the same C, where the lifetime 60
   becomes 50, the rise 0.05 becomes 0.06 and the drag 0.002 becomes 0.00288. The alpha word sits
   in a local set before saved: loop.c then hoists it in pass 1, ahead of saved, which is the order
   of the two in PAL's preheader. */
#include "common.h"

extern void func_002833F0(void *out, void *in);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_001163B0(void);
extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);

/* Emits count pairs of sparks at position, moving along direction turned by a random rotation;
   position is jittered a little before each pair. Both arms of the random-bit test are the same
   code: retail keeps the test, so it stays. */
void func_PAL_L00_003C11A0(float *position, float *direction, int count, int color)
{
    float velocity[4];
    float previous[4];
    float angles[4];
    char matrix[48];
    float *saved;
    float scale;
    int alpha;
    int spin;
    char *particle;
    int i;

    for (i = 0; i < count; i++) {
        scale = func_002A7878(1.75f, 2.0f);
        spin = func_002A77E0(2);
        if (!spin)
            spin--;
        angles[3] = 0;
        angles[1] = func_002A7878(-1.57079637f, 1.57079637f);
        angles[0] = func_002A7878(-1.57079637f, 1.57079637f);
        angles[2] = func_002A7878(-1.57079637f, 1.57079637f);
        func_002833F0(matrix, angles);
        func_00283098(velocity, direction, matrix);

        alpha = 0x4F000000;
        saved = previous;
        func_00282F20(velocity, velocity, 0.05f);
        velocity[2] += 0.060000002f;
        qcopy(saved, position);
        position[0] += func_002A78D8(0.0f, 0.15f);
        position[1] += func_002A78D8(0.0f, 0.15f);
        position[2] += func_002A78D8(0.0f, 0.15f);

        if (func_001163B0() & 1) {
            particle = func_002C2210(position, 50, scale * 0.1f, scale, color | alpha, 0,
                                     spin, velocity, 1, 0.0028800003f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 112;
            particle = func_002C2210(position, 50, scale * 0.07f, scale * 0.7f, 0x7FFFFFFF, 1,
                                     -spin, velocity, 1, 0.0028800003f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 112;
        } else {
            particle = func_002C2210(position, 50, scale * 0.1f, scale, color | alpha, 0,
                                     spin, velocity, 1, 0.0028800003f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 112;
            particle = func_002C2210(position, 50, scale * 0.07f, scale * 0.7f, 0x7FFFFFFF, 1,
                                     -spin, velocity, 1, 0.0028800003f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 112;
        }
    }
}
