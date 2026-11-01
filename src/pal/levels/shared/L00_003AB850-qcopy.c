#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern unsigned char D_0013957F[];
typedef struct { char pad[112]; float scale; char tail[108]; } TableEntry;
extern char D_L00_00262570[];
extern void *D_0018C0B0;
typedef struct {
    char state[24];
    void *object;
    unsigned int detail;
    float position[4];
} CollisionResultPrefix;
extern CollisionResultPrefix D_L00_001BF200;
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_PAL_L00_003AB990(char *, void *);
extern void func_PAL_00335DD0(void *, int, int);

int func_PAL_L00_003AB850(char *object, void *target)
{
    char local[64];
    char *state = *(char **)(object + 104);
    *(char **)(local + 16) = object;
    *(int *)(local + 20) = 0x10000;
    *(int *)(local + 32) = 1;
    *(float *)(local + 28) = ((TableEntry *)(D_L00_00262570 + D_0013957F[0] * 224))->scale;
    *(TI128 *)local = *(TI128 *)state;
    func_00282F20(local, local, 1.0f);
    *(unsigned short *)(local + 26) = *(unsigned short *)(object + 0xAA);
    *(float *)(local + 12) = 5627.925f;
    *(unsigned char *)(local + 24) = 1;
    *(unsigned char *)(local + 25) = 1;
    if (*(short *)(state + 18) == 1)
        *(TI128 *)(local + 48) = *(TI128 *)(state + 48);
    else
        *(TI128 *)(local + 48) = *(TI128 *)(object + 16);
    if (func_002761F8(target, local + 48, 0, D_0018C0B0, local) != 0) {
        func_PAL_L00_003AB990(object, D_L00_001BF200.position);
        if (D_L00_001BF200.object != 0)
            func_PAL_00335DD0(D_L00_001BF200.object, 23, *(int *)(object + 184));
        return 1;
    }
    return 0;
}
