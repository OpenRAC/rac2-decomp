/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L05_003D1E60-g8.c
 * Game profile: -O2 -G8 -ffunction-sections
 * Compiled/retail bytes: 488/488. US: 0/4; US2: 0/4; PAL: 0/4.
 * Residual and reopening condition: Frame-counter GP/absolute materialization and append-store temporary ordering differ. The pool-word load in the count test is live on the short path, not a dead load. Nested eviction exits recover the exact size; mno-split-addresses shrank the body incorrectly. Reopen with truthful mixed-address declarations.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
extern float D_L05_001AFCB8 __attribute__((sda));
extern char *D_L05_001B3018[] MACRO_ADDR;
extern int D_L05_001B3030[];
extern int D_L05_001B2FA0[];
extern int D_L05_001B2048 MACRO_ADDR;
extern void func_0029F338(void *object);
extern unsigned char *func_0029EFD0(int type);

unsigned char *func_L05_003D1E60(void *position, int value, int evict)
{
    int i;
    int selected;
    int age;
    int oldest;
    int now;
    unsigned char *object;
    char *state;
    if (D_L05_001AFCB8 == -1.0f) {
        for (i = 4; i >= 0; i--)
            D_L05_001B3018[i] = 0;
        D_L05_001AFCB8 = 0.0f;
    }
    if (D_L05_001AFCB8 >= 5.0f) {
        if (evict) {
        now = D_L05_001B2048;
        oldest = 0;
        selected = -1;
        for (i = 0; i < 5; i++) {
            age = now - D_L05_001B3030[i];
            if (age > oldest) {
                oldest = age;
                selected = i;
            }
        }
        if (selected >= 0) {
        func_0029F338(D_L05_001B3018[selected]);
        D_L05_001B3018[selected] = 0;
        D_L05_001B2FA0[selected] = 0;
        D_L05_001AFCB8 -= 1.0f;
        } else {
            return 0;
        }
        } else {
            return 0;
        }
    }
    for (i = 0; i < 5 && D_L05_001B3018[i] != 0; i++) {}
    object = func_0029EFD0(0x986);
    if (object) {
        state = *(char **)(object + 0x68);
        object[0x30] = 255;
        object[0x20] = 0;
        *(int *)(state + 8) = value;
        *(int *)state = i;
        qcopy(object + 0x10, position);
        D_L05_001B3030[i] = D_L05_001B2048;
        D_L05_001B3018[i] = (char *)object;
        D_L05_001AFCB8 += 1.0f;
    }
    return object;
}
