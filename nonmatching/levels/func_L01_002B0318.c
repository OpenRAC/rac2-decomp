/* Nonmatching weapon-slot update reconstruction, 2026-10-28.
 * No C coverage credit. US0/8. Three bounded probes: explicit hero pointer
 * and qcopy736/704B; direct canonical hero references, TI copies and narrow
 * unsplit edges712B; broad -fno-gcse gives704B but differs in saved high-half
 * lifetime, initial branch materialization, pointer allocation and reloads.
 * Diagnostic profile -O2 -G0 -ffunction-sections -fno-gcse; no config retained.
 * Reopen with independent original hero/high-part lifetime evidence.
 *
 * Raw002AA2E8 forwards the float fabsf(target-updated_field) result via
 * 00282C48. The float-return interface remains provisional without an
 * actual definition or caller consuming it; this is not a void proof either.
 * 002D4040/002ADEA0 return int. Actual00311080 and00310C88 mutate slot
 * records and return void. Full00310D30 retail body consumes actor and
 * record and mutates animation state; its raw-only void-return hypothesis
 * remains provisional, since no consistent result alone is insufficient.
 * 00282C88 writes all16B. 00283098 reads one16B vector and48B orientation,
 * then writes16B. All copied global orientation rows have complete16B
 * transfers; the complete translation is initialized before transforming.
 * No local packet or array. Unknown external extents remain incomplete.
 */

#include "common.h"
typedef int WeaponSlotQuad __attribute__((mode(TI)));
extern unsigned char D_00189E20[], D_00139568[];
extern unsigned char D_L01_001B7B00[], D_L01_002637A0[];
extern int func_L00_002D4040(int), func_L00_002ADEA0(int);
extern void func_L00_002AF7D0(void);
extern void func_L00_00311080(void *, void *, int, int, int, int);
extern void func_L00_00310D30(void *, void *), func_L00_00310C88(void *, void *);
/* Clamps the field and forwards fabsf(target-updated); provisional return. */
extern float func_002AA2E8(float *, float, float);
extern void func_00282C88(void *), func_00283098(void *, const void *, const void *);
extern float func_00283B98(float, float);

void func_L01_002B0318(void)
{
    unsigned char **slot;
    unsigned char *row;
    int i, kind, animation;
    if (D_00189E20[0x22B8] && D_00189E20[0x22BA] && !func_L00_002D4040(-1)) func_L00_002AF7D0();
    slot = (unsigned char **)(D_00189E20 + 0xE98);
    for (i = 0; i < 2; i++, slot++) {
        if (!*slot) continue;
        *(unsigned char **)(*slot + 0x38) = D_L01_001B7B00 + i * 0xC00;
        *(unsigned char **)(*slot + 0x3C) = D_L01_001B7B00 + i * 0xC00 + 0x600;
        kind = func_L00_002ADEA0(0);
        if (kind == *(int *)(D_00189E20 + 0x24B4)) {
            row = D_L01_002637A0 + D_00139568[kind] * 0xE0;
            animation = *(int *)(row + 0x2C);
            if (*(int *)(D_00189E20 + 0x229C) == 12) animation = *(int *)(row + 0x30);
            if (animation != -1 && (*slot)[0x23] != animation) {
                *(int *)(D_00189E20 + 0x24B0) = animation;
                func_L00_00311080(*(void **)(D_00189E20 + 0x2290), *slot, animation, 0, 8, 1);
            }
        }
        func_L00_00310D30(*(void **)(D_00189E20 + 0x2290), *slot);
        if (*(int *)(D_00189E20 + 0xEA4)) {
            if (*(int *)(D_00189E20 + 0xEA4) == 2) func_002AA2E8((float *)(*slot + 8), 0.0f, 0.25f);
            else func_002AA2E8((float *)(*slot + 8), 0.0f, 0.07f);
            if (*(float *)(*slot + 8) == 0.0f) {
                func_L00_00310C88(*(void **)(D_00189E20 + 0x2290), slot);
                return;
            }
        } else func_002AA2E8((float *)(*slot + 8), 1.0f, 0.2f);
        if (((*slot)[5] & 2) && !D_00189E20[0x22BA]) {
            *(int *)(D_00189E20 + 0xEA4) = 1;
            *(int *)(*slot + 0x28) = 0;
            D_00189E20[0x22B8] = 0;
            return;
        }
    }
    {
        unsigned char *basis = D_00189E20 + 0x730;
        unsigned char *translation = basis + 0x30;
        unsigned char *actor = *(unsigned char **)(D_00189E20 + 0x2290);
        *(WeaponSlotQuad *)basis = *(WeaponSlotQuad *)(actor + 0xC0);
        *(WeaponSlotQuad *)(basis + 0x10) = *(WeaponSlotQuad *)(actor + 0xD0);
        *(WeaponSlotQuad *)(basis + 0x20) = *(WeaponSlotQuad *)(actor + 0xE0);
        func_00282C88(translation);
        *(float *)(D_00189E20 + 0x760) = 1.0f;
        func_00283098(translation, translation, basis);
        *(WeaponSlotQuad *)(D_00189E20 + 0x770) = *(WeaponSlotQuad *)(D_00189E20 + 0x90);
        if (!D_00189E20[0x22C3]) *(float *)(D_00189E20 + 0x778) = func_00283B98(*(float *)(D_00189E20 + 0x778), 0.0f);
    }
}
