/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G0 -ffunction-sections -frac2-qcopy -mno-split-addresses.
 * us: 0/4; us2: 0/4; pal: absent.
 * 444/444 bytes. Capturing the real entity-pool pointer before the definition lookup recovers
 * the retail load order, but its scratch binding differs; first mismatch+0x58. Canonical level-
 * data names replace boot-style aliases. The actual nine scanned slots and complete copy/reset
 * spans are retained.
 * Reopen: Independent pool/definition lifetime or typed definition-record witness.
 */
#include "common.h"

extern char *D_L05_001B1EC4;
extern char *D_L05_001B251C;
extern char *D_L05_001B260C;
extern char D_L05_001B3600[];

extern float func_00282E48(char *, char *);
extern void func_00282F20(char *, char *, float);
extern s32 func_002A77E0(s32);
extern void func_L05_00443740(char *);
extern void func_L05_004427A8(void);

/* Picks the best-scoring of the entity's eight slots (or the runner-up on a random draw), copies its transform to the object and to the entity, and resets the object. */
void func_L05_00442560(char *obj)
{
    s32 best = -1;
    s32 second = -1;
    s32 count = 8;
    float next = 0.0f;
    float top = 0.0f;
    s32 offset;
    char *self;
    char *pool;
    s32 *slot;
    s32 pick;
    char *rec;

    pool = D_L05_001B251C;
    offset = *(s32 *)(*(char **)(D_L05_001B1EC4 + *(short *)(obj + 0x84) * 32 + 0x1C) + 0x20) << 8;
    self = pool + offset;
    slot = (s32 *)(*(char **)(self + 0x68) + 0x21C);
    do {
        if (*slot >= 0) {
            float score = func_00282E48(self + 0x10, D_L05_001B260C + (*slot << 7) + 0x30);
            if (top < score) {
                next = top;
                second = best;
                top = score;
                best = *slot;
            } else if (next < score) {
                second = *slot;
                next = score;
            }
        }
        count--;
        slot++;
    } while (count >= 0);
    pick = best;
    if (func_002A77E0(2) != 0)
        pick = second >= 0 ? second : pick;
    rec = D_L05_001B260C + (pick << 7);
    qcopy(obj + 0x30, rec + 0x30);
    qcopy(D_L05_001B3600, obj + 0x30);
    qcopy(self + 0x10, obj + 0x30);
    func_00282F20(obj, rec, 1.0f);
    func_00282F20(obj + 0x10, rec + 0x10, 1.0f);
    func_00282F20(obj + 0x20, rec + 0x20, 1.0f);
    qzero(*(char **)(obj + 0x70) + 0xB0);
    func_L05_00443740(obj);
    func_L05_004427A8();
}
