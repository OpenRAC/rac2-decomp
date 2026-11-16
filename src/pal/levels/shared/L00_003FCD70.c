#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { Vec vector; int owner, flags; u8 kind, active; unsigned short id; int pad; int enabled; } Impact;
typedef struct { int timer, first, second; float phase, damage; char *object; int owner, hold; } Slot;
extern unsigned char g_hero_state[];
extern Slot g_health_l00_drain_slots[30];
extern float FastAddRotations(float, float);
extern float *moby_get_private_value_0(char *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern void QueueMobyImpact(void *, void *);
extern int math_fast_float_d(void *);
extern void part_copy_color_to_linked_record(void *);
extern float math_fast_sin_or_cos_a(float);
extern int FastTweenColor(int, int, float);
extern void set_moby_color(void *, int, int, int);
extern void ref_L00_003F87B0_00(void (*)(char *), char *);
extern void SpawnHealthDrainSparks_pal(char *);

/* Per frame, for each occupied slot: advances the pulse phase, drains the attached moby's health
   and, when it runs out, sends a kill impact pointing back along the moby's facing. A slot whose
   moby is dead, gone or finished is released; otherwise the moby is tinted with the colour
   between the slot's two colours at the current pulse, unless the slot is on hold. Then it
   schedules func_PAL_L00_003FD600 for the object. */
void UpdateHealthDrainSlots_pal(char *object)
{
    Vec direction;
    Impact impact;
    int i;

    qcopy(object + 0x10, g_hero_state);
    for (i = 0; i < 30; i++) {
        if (g_health_l00_drain_slots[i].object != 0) {
            Slot *record = &g_health_l00_drain_slots[i];
            int remove;
            float *health;

            record->phase = FastAddRotations(record->phase, 0.25132746f);
            remove = 0;
            if (*(signed char *)(record->object + 0x20) < 0)
                remove = 1;
            if (*(int *)(record->object + 0x98) == 0)
                remove = 1;
            health = moby_get_private_value_0(record->object);
            if (health != 0) {
                *health -= record->damage;
                if (*health <= 0.0f) {
                    FastVecScale(&direction, record->object + 0xC0, -1.0f);
                    vec_scale_to_length(&impact, &impact, 0.002f);
                    *(int *)(object + 0xB8) = record->owner;
                    make_hit_descriptor(&impact, object, 0x810000, 0.001f, &direction);
                    impact.vector.q = direction.q;
                    impact.vector.f[3] = 5627.925f;
                    impact.enabled = 1;
                    impact.kind = 5;
                    impact.active = 1;
                    impact.id = *(unsigned short *)(record->object + 0xAA);
                    QueueMobyImpact(record->object, &impact);
                    remove = 1;
                }
            } else {
                remove = 1;
            }
            if (math_fast_float_d(record) != 0)
                remove = 1;
            if (remove) {
                part_copy_color_to_linked_record(record);
                record->object = 0;
            } else if (record->hold == 0) {
                int color = FastTweenColor(record->first, record->second,
                                          (math_fast_sin_or_cos_a(record->phase) + 1.0f) * 0.5f);

                set_moby_color(record->object, color & 255, (color >> 8) & 255, (color >> 16) & 255);
            } else {
                record->hold--;
            }
        }
    }
    ref_L00_003F87B0_00(SpawnHealthDrainSparks_pal, object);
}

