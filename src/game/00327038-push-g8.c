#include "include_asm.h"
#include "common.h"

/* The thresholds live in small data, so this unit is built with -G8 (and -ffast-math for the
   min.s); they differ from program to program, so they carry no level. */
typedef unsigned int B40Quad __attribute__((mode(TI)));
extern int ref_L00_00327B40_00 __attribute__((sda));
extern float ref_L00_00327B40_01 __attribute__((sda));
extern int D_001BF000[];
typedef struct { unsigned char pad[0x20]; unsigned char selection; } SettingsB40;
extern SettingsB40 g_item_slot_to_record;
typedef struct { char pad[0x70]; float damage; char tail[0x6C]; } B40Class;
extern B40Class g_weapon_table[];
typedef struct { char pad[0x2290]; char *object; } ContextB40;
extern ContextB40 g_hero_state;
extern int coll_process_hit(void *, int, void *, int, float);
extern char *moby_get_private_value_0(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern int StartAttachedEffect(void *, int, int);

typedef struct {
    char pad0[0x10];
    float pos[4];
    char pad20[0x48];
    char *state;
    char pad6C[0x4C];
    int id;
} ObjectB40;

/* Pushes every object within range (the smaller of the state's radius and a global one) away
   from this object, unless it is the hero's current object or neither pushable nor flagged
   0x4000. */
void DamageNearbyMobys(ObjectB40 *self)
{
    float direction[4];
    struct {
        float direction[4];
        char pad10[8];
        unsigned char kind, mode;
        short classid;
        int pad1C;
        int enabled;
        char tail[12];
    } hit;
    char *state = self->state;
    int count, remaining;
    int *list;
    char *obj;
    float radius;

    if (*(int *)(state + 0x20) < ref_L00_00327B40_00 - 20)
        return;
    radius = *(float *)(state + 0x24) < ref_L00_00327B40_01 ? *(float *)(state + 0x24) : ref_L00_00327B40_01;
    count = coll_process_hit(self->pos, 0, self, 0, radius);
    if (count > 0) {
        list = D_001BF000;
        remaining = count;
        do {
            obj = (char *)*list;
            if ((moby_get_private_value_0(obj) || (*(unsigned short *)(obj + 0x34) & 0x4000))
                && obj != g_hero_state.object) {
                FastVecSub(direction, obj + 0x10, self->pos);
                vec_scale_to_length(direction, direction, 1.0f);
                vec_scale_to_length(&hit, &hit, 1.0f);
                make_hit_descriptor(&hit, self, 0x830000, direction,
                              ((B40Class *)((int)g_weapon_table + g_item_slot_to_record.selection * sizeof(B40Class)))->damage);
                *(B40Quad *)hit.direction = *(B40Quad *)direction;
                hit.enabled = 1;
                hit.direction[3] = 5627.925f;
                hit.kind = 5;
                hit.mode = 3;
                hit.classid = *(short *)(obj + 0xAA);
                QueueMobyImpact(obj, &hit);
                StartAttachedEffect(obj, 32, self->id);
            }
            list++;
        } while (--remaining);
    }
}
