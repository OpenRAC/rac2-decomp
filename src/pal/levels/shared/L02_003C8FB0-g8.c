#include "include_asm.h"

#include "common.h"
extern void func_002A7750(void *, int, int);
extern void func_PAL_L02_003CDF48(char *);
extern void func_L02_003C9ED0(char *);
extern float func_002AA2E8(float *, float, float);
extern void func_002AEC18(void *, int);
extern void func_0029F338(void *);
extern void func_L00_002E6CF0(void *, void *);
extern float D_L02_001AFFB8 __attribute__((sda));
extern float D_L02_001AFFBC[] __attribute__((sda));
extern void func_L02_003CA280(char *);

/* Advance the two timers, initialize the effect once, and release four children. */
void func_PAL_L02_003CDC18(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char **list;
    int count;
    float one;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        one = 1.0f;
        if (*(float *)(sub + 8) < one) {
            func_002AA2E8((float *)(sub + 8), one, D_L02_001AFFB8 * (0.020000001f));
            goto update;
        }
        list = (char **)(sub + 0x10);
        if (!(*(float *)(sub + 12) < one))
            goto cleanup;
        if (*(int *)(sub + 4) == 0) {
            *(int *)(sub + 4) = 1;
            func_PAL_L02_003CDF48(obj);
        }
        func_L02_003C9ED0(obj);
        func_002AA2E8((float *)(sub + 12), one, D_L02_001AFFBC[0] * (0.020000001f));
        goto update;
    cleanup:
        count = 3;
        sub += 0x30;
        do {
            if (*list) {
                *(unsigned short *)(*list + 0x34) = *(unsigned short *)(sub - 0x10);
                func_002AEC18(*list, *(int *)sub);
            }
            sub += 4;
            count--;
            list++;
        } while (count >= 0);
        func_0029F338(obj);
        break;
    update:
        func_L00_002E6CF0((void *)func_L02_003CA280, obj);
        break;
    }
}
