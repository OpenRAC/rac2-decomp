#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { Vec vector; int owner, flags; u8 kind, active; unsigned short id; int pad; int enabled; } Impact;
typedef struct { int timer, first, second; float phase, damage; char *object; int owner, hold; } Slot;
extern unsigned char D_00189E20[];
extern Slot D_L00_002533B0[30];
extern float func_00283B98(float, float);
extern float *func_002AB1F0(char *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8E20(void *, void *);
extern int func_00282948(void *);
extern void func_L00_003F89F8(void *);
extern float func_00283180(float);
extern int func_00283D38(int, int, float);
extern void func_002A0488(void *, int, int, int);
extern void ref_L00_003F87B0_00(void (*)(char *), char *);
extern void func_PAL_L00_003FD600(char *);

/* Per frame, for each occupied slot: advances the pulse phase, drains the attached moby's health
   and, when it runs out, sends a kill impact pointing back along the moby's facing. A slot whose
   moby is dead, gone or finished is released; otherwise the moby is tinted with the colour
   between the slot's two colours at the current pulse, unless the slot is on hold. Then it
   schedules func_PAL_L00_003FD600 for the object. */
void func_PAL_L00_003FCD70(char *object)
{
    Vec direction;
    Impact impact;
    int i;

    qcopy(object + 0x10, D_00189E20);
    for (i = 0; i < 30; i++) {
        if (D_L00_002533B0[i].object != 0) {
            Slot *record = &D_L00_002533B0[i];
            int remove;
            float *health;

            record->phase = func_00283B98(record->phase, 0.25132746f);
            remove = 0;
            if (*(signed char *)(record->object + 0x20) < 0)
                remove = 1;
            if (*(int *)(record->object + 0x98) == 0)
                remove = 1;
            health = func_002AB1F0(record->object);
            if (health != 0) {
                *health -= record->damage;
                if (*health <= 0.0f) {
                    func_00282D30(&direction, record->object + 0xC0, -1.0f);
                    func_00282F20(&impact, &impact, 0.002f);
                    *(int *)(object + 0xB8) = record->owner;
                    func_002A8C00(&impact, object, 0x810000, 0.001f, &direction);
                    impact.vector.q = direction.q;
                    impact.vector.f[3] = 5627.925f;
                    impact.enabled = 1;
                    impact.kind = 5;
                    impact.active = 1;
                    impact.id = *(unsigned short *)(record->object + 0xAA);
                    func_002A8E20(record->object, &impact);
                    remove = 1;
                }
            } else {
                remove = 1;
            }
            if (func_00282948(record) != 0)
                remove = 1;
            if (remove) {
                func_L00_003F89F8(record);
                record->object = 0;
            } else if (record->hold == 0) {
                int color = func_00283D38(record->first, record->second,
                                          (func_00283180(record->phase) + 1.0f) * 0.5f);

                func_002A0488(record->object, color & 255, (color >> 8) & 255, (color >> 16) & 255);
            } else {
                record->hold--;
            }
        }
    }
    ref_L00_003F87B0_00(func_PAL_L00_003FD600, object);
}

