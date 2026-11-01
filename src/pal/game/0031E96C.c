#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_0031E96C);



#include "common.h"
extern int D_001B2758 MACRO_ADDR;
extern float func_002A7878(float, float), func_002A78D8(float, float);
extern void func_00282C88(void *), func_002B00B0(void *, void *, int);
extern char *func_002AB1F0(void *);
extern void func_00282CC0(void *, void *, void *);
extern u8 D_00189E20[];
extern u8 D_00188660[];
extern char D_001A8BD0[16] MACRO_ADDR;
extern unsigned char D_00188660[];
extern unsigned char D_00189E20[];
extern void func_00282D30(void *dst, void *src, float scale);
extern u8 D_00189E20[];
extern u8 *D_001B1B5C MACRO_ADDR;

/* func_0031D3E0 is in 0031D3E0.c. */

/* func_0031D588 is in 0031D588-g8.c. */


void func_PAL_0031F230(char *self, char *target, int count)
{
    int pool = D_001B2758;
    char *position = self + 0x10;
    char *target_position = target + 0x10;
    char *data = *(char **)(self + 0x68);
    char *p;
    char *info;
    float v[4];
    int i;
    for (i = 0; i < 12; i++) {
        p = (char *)(pool + i * 0xA0);
        if (*(int *)(p + 0x8C) == 0) {
            *(char **)(p + 0x8C) = self;
            (*(int *)(data + 0x1C))++;
            qcopy(p + 0x20, position);
            *(float *)(p + 64) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 68) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 72) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 100) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 104) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 108) = func_002A7878(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(p + 76) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 80) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 84) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 112) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 116) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 120) = func_002A78D8(0.001f, 0.05f);
            *(float *)(p + 88) = func_002A7878(3.25f, 6.75f);
            *(float *)(p + 92) = func_002A7878(3.25f, 6.75f);
            *(float *)(p + 96) = func_002A7878(3.25f, 6.75f);
            *(float *)(p + 124) = func_002A7878(1.25f, 4.75f);
            *(float *)(p + 128) = func_002A7878(1.25f, 4.75f);
            *(float *)(p + 132) = func_002A7878(1.25f, 4.75f);
            func_00282C88(p);
            func_00282C88(p + 0x10);
            *(int *)(p + 0x94) = count;
            *(int *)(p + 0x98) = count;
            *(char **)(p + 0x90) = target;
            *(int *)(p + 0x9C) = 0;
            *(int *)(p + 0x88) = 17;
            info = func_002AB1F0(target);
            if (info) {
                func_002B00B0(target, v, 1);
                func_00282D30(v, v, *(float *)(info + 0x10));
                func_00282CC0(p + 0x30, v, target + 0x10);
            } else {
                qcopy(p + 0x30, target_position);
            }
            break;
        }
    }
}


extern int func_00282948(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
typedef struct {
    float out0[4];           
    float out1[4];           
    float start[4];          
    float pos[4];            
    float ang0[3];           
    float rate0[3];          
    float amp0[3];           
    float ang1[3];           
    float rate1[3];          
    float amp1[3];           
    int life;                
    char *owner;             
    char *target;            
    int time;                
    int duration;            
    int hit;                 
} Slot31DEE8;
typedef struct {
    char pad_00[0x74];
    float f74;
    char pad_78[0xE0 - 0x78];
} Class31DEE8;
extern unsigned char D_00139568[];
extern Class31DEE8 D_00239BA0[];
extern float func_00283B98(float angle, float step);
extern float func_00283180(float angle);
extern float func_00283198(float angle);
extern float func_00283CE0(int ticks);
extern int func_00282948(void *timer);
extern void func_00282D08(void *out, void *from, void *to, float t);
extern void func_002A8C00(void *packet, char *owner, int flags, void *direction, float amount);
extern void func_002A8E20(char *target, void *packet);
extern void func_PAL_00320D00(void *pos, int count, int mode);
extern void func_PAL_0032F0B8(char *target, int kind, int value);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00282F20(void *dst, void *src, float scale);
extern void func_00282CF0(void *, void *, void *);
static inline Class31DEE8 *Class31DEE8At(int index)
{
    return &D_00239BA0[index];
}

/* Steps every record the owner holds: refreshes its start from the owner, advances the two
   angle triples (faster while the approach timer runs), and while it has a target moves its
   position towards it. When the approach timer expires and the target is still live, it
   sends one hit packet (func_002A8C00/func_002A8E20) and marks the record; when the life
   timer expires the record is released and the owner's count drops. */
void func_PAL_0031F500(char *owner)
{
    float v[4];
    struct {
        char pad_00[0x18];
        unsigned char kind;
        unsigned char mode;
        short id;
        char pad_1c[0x14];
    } packet;
    char *ctx = *(char **)(owner + 0x68);
    Slot31DEE8 *slot;
    char *other;
    float ratio;
    float damage;
    float boost = 100.0f;
    int i;

    for (i = 0; i < 12; i++) {
        if (((Slot31DEE8 *)D_001B2758)[i].owner != owner)
            continue;
        slot = &((Slot31DEE8 *)D_001B2758)[i];
        qcopy(slot->start, owner + 0x10);
        if (slot->time) {
            slot->ang0[0] = func_00283B98(slot->ang0[0], slot->rate0[0] * boost);
            slot->ang0[1] = func_00283B98(slot->ang0[1], slot->rate0[1] * boost);
            slot->ang0[2] = func_00283B98(slot->ang0[2], slot->rate0[2] * boost);
            slot->ang1[0] = func_00283B98(slot->ang1[0], slot->rate1[0] * boost);
            slot->ang1[1] = func_00283B98(slot->ang1[1], slot->rate1[1] * boost);
            slot->ang1[2] = func_00283B98(slot->ang1[2], slot->rate1[2] * boost);
        } else {
            slot->ang0[0] = func_00283B98(slot->ang0[0], slot->rate0[0]);
            slot->ang0[1] = func_00283B98(slot->ang0[1], slot->rate0[1]);
            slot->ang0[2] = func_00283B98(slot->ang0[2], slot->rate0[2]);
            slot->ang1[0] = func_00283B98(slot->ang1[0], slot->rate1[0]);
            slot->ang1[1] = func_00283B98(slot->ang1[1], slot->rate1[1]);
            slot->ang1[2] = func_00283B98(slot->ang1[2], slot->rate1[2]);
        }
        slot->out0[0] = func_00283180(slot->ang0[0]) * slot->amp0[0];
        slot->out0[1] = func_00283198(slot->ang0[1]) * slot->amp0[1];
        slot->out0[2] = -func_00283198(slot->ang0[2]) * slot->amp0[2];
        slot->out1[0] = func_00283180(slot->ang1[0]) * slot->amp1[0];
        slot->out1[1] = func_00283198(slot->ang1[1]) * slot->amp1[1];
        slot->out1[2] = -func_00283198(slot->ang1[2]) * slot->amp1[2];
        if (slot->target) {
            other = func_002AB1F0(slot->target);
            if (other) {
                func_002B00B0(slot->target, v, 1);
                func_00282D30(v, v, *(float *)(other + 0x10));
                func_00282CC0(slot->pos, v, slot->target + 0x10);
            } else {
                qcopy(slot->pos, slot->target + 0x10);
            }
            ratio = func_00283CE0(slot->time);
            ratio /= func_00283CE0(slot->duration);
            func_00282D08(slot->pos, slot->start, slot->pos, 1.0f - ratio);
        }
        if (!func_00282948(&slot->time))
            continue;
        if (*(int *)(slot->target + 0x98) && !slot->hit) {
            func_00282CF0(v, slot->pos, slot->start);
            func_00282F20(v, v, 0.040000003f);
            damage = Class31DEE8At(D_00139568[0x1C])->f74;
            func_002A8C00(&packet, owner, 0x210000, v, damage);
            packet.kind = 1;
            packet.mode = 3;
            packet.id = *(short *)(owner + 0xAA);
            func_002A8E20(slot->target, &packet);
            slot->hit = 1;
            func_PAL_00320D00(slot->pos, 10, 1);
            func_PAL_0032F0B8(slot->target, 28, *(int *)(owner + 0xB8));
        }
        if (func_00282948(&slot->life)) {
            slot->owner = 0;
            --*(int *)(ctx + 0x1C);
        }
    }
}


