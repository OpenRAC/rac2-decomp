#include "common.h"

/* Dobbo data reached through $gp in ordinary flow: this unit is assembled with -G8. */
extern f32 D_L09_001B1830 __attribute__((sda));
extern f32 D_L09_001B1834 __attribute__((sda));
extern f32 D_L09_001B1838 __attribute__((sda));
extern f32 D_L09_001B183C __attribute__((sda));
extern f32 D_L09_001B1840 __attribute__((sda));

extern void func_31F728(char *a0, f32 *a1, f32 *a2, f32 f12, f32 f13, f32 f14);

extern void func_31F7E0(char *a0, f32 *a1, f32 *a2, f32 f12, f32 f13, f32 f14);

/* Drives the two angle pairs of the state, in degrees converted to radians. */
void func_L09_00410B40(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);

    func_31F728(a0, (f32 *)(s1 + 0x74), (f32 *)(s1 + 0x70), D_L09_001B1830,
                D_L09_001B1834 * 0.000290888245f, -1.0f);
    func_31F7E0(a0, (f32 *)(s1 + 0x78), (f32 *)(s1 + 0x7C), D_L09_001B1838,
                D_L09_001B183C * 0.000290888245f, D_L09_001B1840 * 0.000290888245f);
}

extern int func_002E5CF8(int, int, void *);
extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283CF0(float);

typedef struct {
    char pad0[0x33C];
    char *standing;
    char pad340[0x34E - 0x340];
    short busy;
} TriggerPlayer;
extern TriggerPlayer D_00189E20;
extern int D_001A79F0 __attribute__((sda));
/* Flag bytes indexed by level * 16 + owner; 3-bit counters indexed by level * 1024, two per byte. */
extern u8 D_0019B2E8[];
extern u8 D_0019B4A8[];
typedef struct { u8 pad[0x464]; u8 spent[0]; } TriggerCellFlags;
extern TriggerCellFlags D_L09_0021E9F0;
extern char *D_L09_001B0834;
extern char *D_L09_001B1648;

typedef struct TriggerState { float angle; int enabled; } TriggerState;
typedef struct {
    char pad00[0x10];
    float position[4];
    u8 status;
    char pad21[0x68 - 0x21];
    TriggerState *state;
    char pad6C[0x78 - 0x6C];
    unsigned int color;
    char pad7C[0xB0 - 0x7C];
    u8 owner;
    char padB1;
    u16 id;
    char padB4[0xBC - 0xB4];
    u8 activated;
} TriggerObject;

void func_L09_0041A700(TriggerObject *obj)
{
    TriggerState *s = obj->state;
    int shade, level;
    int green, red;
    char *player;
    float pos[4] __attribute__((aligned(16)));

    switch (obj->status) {
    case 0:
        s->angle = func_002A7940();
        obj->status = 1;
        obj->position[2] -= 0.35f;
        break;
    case 1:
        /* Pulse the colour: the angle advances 6 degrees per update. */
        s->angle = func_00283B98(s->angle, 0.10471977f);
        shade = func_00283CF0((func_00283198(s->angle) * 4.0f - 3.0f) * 128.0f);
        if (shade > 128) shade = 128;
        else if (shade < 32) shade = 32;
        green = (shade << 8) | (int)0x80000000;
        red = shade << 16;
        obj->color = (red | green) | shade;
        if (D_00189E20.standing != (char *)obj || D_00189E20.busy) {
            /* Loaded only on this path: reorg moves it into the bne delay slot. */
            level = D_001A79F0;
            if (!(D_0019B2E8[obj->owner + level * 16] & 0x80) || s->enabled) {
                int id;
                if (!s->enabled) return;
                id = obj->id;
                if (!D_L09_0021E9F0.spent[(short)id]) {
                    int count = D_0019B4A8[((short)id >> 1) + (level << 10)];
                    if (id & 1) {
                        if (((count >> 4) & 7) != 0) goto activate;
                        goto proximity;
                    } else if (!(count & 7)) goto proximity;
                }
            }
        }
activate:
        {
            int id;
            obj->status = 2;
            obj->activated = 1;
            obj->color = 0x80208020;
            func_002E5CF8(0, 0, obj);
            id = obj->id;
            if (id & 1) {
                u8 *counts = &D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
                if (((*counts >> 4) & 7) != 7) *counts += 16;
            } else {
                u8 *counts = &D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
                if ((*counts & 7) != 7) ++*counts;
            }
        }
proximity:
        if (s->enabled) {
            player = D_L09_001B0834;
            if (!player) {
                player = D_L09_001B1648;
                if (!player) return;
            }
            /* Retail fills this raised copy but measures from the position itself. */
            qcopy(pos, obj->position);
            pos[2] += 0.35f;
            if (func_00282E80(obj->position, player + 0x10) < 0.5f) {
                int id = obj->id;
                if (id & 1) {
                    u8 *counts = &D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
                    if (((*counts >> 4) & 7) != 7) *counts += 16;
                } else {
                    u8 *counts = &D_0019B4A8[((short)id >> 1) + (D_001A79F0 << 10)];
                    if ((*counts & 7) != 7) ++*counts;
                }
                obj->status = 2;
                obj->activated = 1;
                obj->color = 0x80208020;
                func_002E5CF8(0, 0, obj);
            }
        }
        break;
    }
}
