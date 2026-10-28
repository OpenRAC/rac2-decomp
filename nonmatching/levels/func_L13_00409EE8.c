/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections.
 * Emitted/retail size: 440/440 bytes.
 * us: 0 of 3 places match.
 * pal: 0 of 3 places match.
 * us2: 0 of 3 places match.
 * No strict linked build was run for this draft.
 * The state, loop counter, position and velocity pointers are allocated differently. Shortening the initial position lifetime restores the retail frame size; subsequent scope changes tie. The collision helper really returns 0 or 1. Reopen with allocation evidence.
 */
#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern int func_L13_0040A2C8(char *, char *);
extern float func_002AFF08(char *, char *, char *);
extern void func_002AFE58(char *, char *, char *, char *, float);
extern float func_002B0360(void *);
extern void func_002AFD88(float, float, float, char *, char *);
extern void func_002AFEB8(char *, char *, char *, char *, float);

void func_L13_00409EE8(char *object, char *state, char *target,
                      char *unused, char *transform)
{
    int saved_position[4] __attribute__((aligned(16)));
    int total, current;
    int i;
    char *position;
    char *velocity;
    float length;
    {
        char *start = object + 0x10;
        func_00282CC0(start, start, state + 0xa0);
        qcopy(saved_position, start);
    }
    *(int *)(state + 0x84) = 0;
    qzero(state + 0x60);
    total = 0;
    current = 0;
    for (i = 0; i < 8; ++i) {
        current |= func_L13_0040A2C8(object, state);
        total |= current;
        if (!current)
            break;
    }
    if (total) {
        char *delta = state + 0xa0;
        position = object + 0x10;
        func_00282CF0(delta, position, target);
        velocity = state + 0xa0;
        length = func_002AFF08(object, velocity, transform);
        if (*(float *)(state + 0xb0) < length)
            func_002AFE58(object, velocity, velocity, transform, *(float *)(state + 0xb0));
        else
            *(float *)(state + 0xb0) = length;
        length = func_002B0360(position);
        if (length <= *(float *)(state + 0x90)) {
            func_002AFD88(0.0f, 0.0f, *(float *)(state + 0x90) - length, object, position);
            func_002AFEB8(object, velocity, velocity, transform, 0.0f);
        }
        if (*(float *)(state + 0xb0) < *(float *)(state + 0x28) * 0.5f)
            *(int *)(state + 0x80) += 1;
        else
            *(int *)(state + 0x80) = 0;
    } else {
        *(int *)(state + 0x80) = 0;
    }
    position = object + 0x10;
    func_00282CF0(state + 0x70, position, saved_position);
}
