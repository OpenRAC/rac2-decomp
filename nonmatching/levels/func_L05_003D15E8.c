/* Nonmatching actor update reconstruction, 2026-10-28. No C coverage credit.
 * Seven US probes, 0/2 placements. Retained 760/760B with -O2 -G0
 * -ffunction-sections -frac2-gcse-unsplit-edges. Explicit active=1 restores
 * all prologue/register roles. Remaining: actor-table load order/registers,
 * sound-address add destination ties and two equal-value store orderings.
 * Plain diagnostic 752B; grouped sound offsets and narrow edge/CSE controls
 * 756B; active constant 764B before control-flow correction; retained source
 * 760B. Broad -fno-gcse is worse, 756B with missing high-half save, rejected.
 * Initial diagnostic nested transition branch was corrected from the actual
 * +0x248 target: when the gate fails, skip both transition and state helper;
 * when the gate succeeds, choose mode 5 or 1 before that state helper.
 * Reopen with independent original source/address-expression evidence.
 *
 * Actual 002ED688 returns signed32 owner address, explicitly cast to pointer.
 * 0037B538 returns int even when ignored. The complete raw 0037B948 and
 * 003D1AB8 mutation bodies were inspected, but their void-return hypotheses
 * remain provisional. Other helpers checked
 * against actual definitions; 002E5DA0, 0037B888, 0037CE08, 00282948 return int;
 * 002EE6A8 returns unsigned32. The actual callback-table registrar stores
 * four 32-bit integer entries; object/function addresses are explicitly cast
 * for those integer parameters. Empty callback uses canonical 003E7760.
 * One local 16B zero buffer is fully written before any use; external state
 * vectors are whole-cleared before quaternion component stores. Global
 * extents stay incomplete. Sound addresses use observed 32-bit arithmetic
 * for the real index=-1 sentinel, not negative C-array pointer indexing.
 */

#include "common.h"
extern unsigned char *D_L05_001B251C __attribute__((sda));
extern unsigned char D_00188660[];
extern int func_L00_00367720(void), func_002ED688(void *);
extern void func_L05_003D18E0(void *), func_L05_003D19F0(void *), func_L05_003D1AB8(void *);
extern void func_L00_003E7760(void);
/* This table registrar's actual definition takes four32-bit integers. */
extern void func_L05_00379E60(int, int, int, int);
extern void func_00282C88(void *), func_0029F978(void *, unsigned int, void *);
extern void func_L05_0037C160(void *), func_L05_0037B948(void *, int, float);
extern int func_L05_0037B538(void *, void *, int, int);
extern float func_00282E48(const void *, const void *), func_00283198(float), func_00283180(float);
extern int func_002A77E0(int), func_002E5DA0(int, int, void *, int);
extern unsigned int func_002EE6A8(void *);
extern int func_L05_0037B888(void *), func_L05_0037CE08(void *, int);
extern void func_L05_0037CDD8(void *, int), func_L05_0037B6D0(void *);
extern int func_00282948(void *);

void func_L05_003D15E8(unsigned char *object)
{
    float zero[4] __attribute__((aligned(16)));
    unsigned char *state = *(unsigned char **)(object + 0x68);
    unsigned char *owner;
    unsigned char *sound;
    float angle;
    int active;
    if (object[0x20] == 0) {
        object[0x30] = 0xFF;
        if (!func_L00_00367720()) return;
        func_L05_003D18E0(object);
        func_00282C88(zero);
        if (*(int *)(state + 0x264)) func_L05_00379E60((int)object, (int)func_L00_003E7760, 0, 0);
        func_0029F978(object, 2, state + 0x270);
        func_0029F978(object, 3, state + 0x2B0);
        return;
    }
    owner = (unsigned char *)func_002ED688(object);
    if (!*(int *)(owner + 0x110)) return;
    active = 1;
    func_L05_0037C160(object);
    func_L05_0037B538(object, 0, 0, 0);
    func_L05_0037B948(object, active, 32.0f);
    if (*(int *)(owner + 0x110) == active) {
        if (*(int *)(state + 0x260) != -1) {
            *(int *)(owner + 0x11C) = active;
            {
                unsigned char *actors = D_L05_001B251C;
                int targetIndex = *(int *)(state + 0x260);
                *(unsigned char **)(owner + 0x120) = actors + targetIndex * 256;
            }
            if (func_00282E48(*(unsigned char **)(owner + 0x120) + 0x10, object + 0x10) < 10.0f) {
                sound = (unsigned char *)(*(int *)(state + 0x2F4) * 0x70 + (unsigned int)D_00188660);
                if (*(unsigned char **)(sound + 0x88) != object || !sound[0x74])
                    if (!func_002A77E0(750)) *(int *)(state + 0x2F4) = func_002E5DA0(14, 0, object, 0xFBF);
            }
        }
        func_00282C88(state + 0x280);
        func_00282C88(state + 0x2C0);
        if (func_002EE6A8(object) == 8) {
            angle = 0.7853982448577881f;
            *(float *)(state + 0x284) = func_00283198(angle);
            *(float *)(state + 0x28C) = func_00283180(angle);
            *(float *)(state + 0x2C4) = func_00283198(angle);
            *(float *)(state + 0x2CC) = func_00283180(angle);
            if (*(int *)(owner + 0x108)) func_L05_003D19F0(object);
        } else {
            *(float *)(state + 0x28C) = *(float *)(state + 0x2CC) = 1.0f;
            if (*(int *)(owner + 0x108) && *(int *)(owner + 0x104)) func_L05_003D19F0(object);
        }
        if (func_L05_0037B888(object)) {
            if (func_L05_0037CE08(object, 5) <= 0) func_L05_0037CDD8(object, 5);
            else func_L05_0037CDD8(object, 1);
            func_L05_0037B6D0(object);
        }
        func_00282948(state + 0x268);
        func_L05_003D1AB8(object);
    }
    sound = (unsigned char *)(*(int *)(state + 0x2F0) * 0x70 + (unsigned int)D_00188660);
    if (*(unsigned char **)(sound + 0x88) != object || !sound[0x74])
        *(int *)(state + 0x2F0) = func_002E5DA0(1, 6, object, 0x97C);
}
