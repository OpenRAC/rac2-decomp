#include "include_asm.h"
#include "names.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers. */
typedef int Rac2TI128 __attribute__((mode(TI)));

extern float IntToFloat(int a);

extern void FastVecAdd(void *out, void *in1, void *in2);

extern void ref_L00_003BCE28_00(void *out, void *a, void *b, void *c, void *d, float f);

extern unsigned int math_random_int_range(int a, int b);

extern void DrawTaperedTwoLayerRibbon(void *a0, unsigned int a1, void *a2, int a3);

/* Walks eight steps of a state block. Each step adds the block's two constant vectors
   to its two moving ones, then the shared helper builds the step's own vector from the
   four of them, scaled by the step's share of the whole. The block's two counts choose
   the range the block is finally emitted with. */
/* Builds a bendy lightning ribbon from eight points and draws it. The brightness depends on how far along the effect is. */
void lightning_build_and_draw_ribbon(char *owner, char *state)
{
    Rac2TI128 pts[8];
    Rac2TI128 tmp[3];
    Rac2TI128 *t1 = &tmp[1];
    Rac2TI128 *t2 = &tmp[2];
    Rac2TI128 *p1 = (Rac2TI128 *)(state + 0x10);
    char *c0 = state + 0x20;
    char *c1 = state + 0x30;
    int i;
    float share;
    int halfCount;
    int progress;

    i = 0;
    do {
        share = IntToFloat(i) / IntToFloat(7);
        *t1 = *(Rac2TI128 *)state;
        *t2 = *p1;
        FastVecAdd(t1, t1, c0);
        FastVecAdd(t2, t2, c1);
        ref_L00_003BCE28_00(&pts[i], c0, c1, t1, t2, share);
        i++;
    } while (i < 8);

    halfCount = *(int *)(state + 0x9C) >> 1;
    progress = *(int *)(state + 0x98);
    if (progress >= halfCount)
        DrawTaperedTwoLayerRibbon(owner, math_random_int_range(0x40, 0x80), pts, 9);
    else
        DrawTaperedTwoLayerRibbon(owner, math_random_int_range(0, 0x40), pts, 9);
}

/* One of the thirty 0xA0-byte records at D_L00_0023DDA0 that func_L00_003BBB68 updates for
   its owner. Measured layout; the field roles are inferred from this function alone. */
typedef struct {
    float out0[4];          /* 0x00: ang0 through the two angle helpers, times amp0 */
    float out1[4];          /* 0x10: the same for ang1 */
    Rac2TI128 start;        /* 0x20: copied from the owner's position each frame */
    Rac2TI128 pos;          /* 0x30: follows the target */
    float ang0[3];          /* 0x40 */
    float rate0[3];         /* 0x4C */
    float amp0[3];          /* 0x58 */
    float ang1[3];          /* 0x64 */
    float rate1[3];         /* 0x70 */
    float amp1[3];          /* 0x7C */
    int life;               /* 0x88: timer, frees the record when it expires */
    char *owner;            /* 0x8C */
    char *target;           /* 0x90 */
    int time;               /* 0x94: timer, also counts the approach */
    int duration;           /* 0x98 */
    int hit;                /* 0x9C */
} Slot3BBB68;

extern Slot3BBB68 D_L00_0023DDA0[];

/* The 0xE0-byte class records; D_00139568 maps a class number to its record. */
typedef struct {
    char pad_00[0x74];
    float f74;
    char pad_78[0xE0 - 0x78];
} Class3BBB68;

extern unsigned char g_item_slot_to_record[];
extern Class3BBB68 g_weapon_l00_table[];

extern void func_00282D30_6(void *out, void *in, float scale);
extern void func_00282CC0_6(void *out, void *in1, void *in2);
extern void func_00282CF0_9(char *out, char *first, char *second);
extern void func_00282F20_2(void *out, void *in, float scale);
extern float func_00283B98_8(float angle, float step);
extern float func_00283180_8(float angle);
extern float func_00283198_8(float angle);
extern char *func_002AB1F0_8(char *object);
extern void moby_forward_position_call(char *object, void *out, int mode);
extern void func_00282D08_8(void *out, void *from, void *to, float t);
extern float func_00283CE0_8(int ticks);
extern int func_00282948_8(void *timer);
extern void func_002A8C00_8(void *packet, char *owner, int flags, void *direction, float amount);
extern void func_002A8E20_8(char *target, void *packet);
extern int func_0032D758_8(char *target, int kind, int value);
extern int func_002E5CF8_8(int index, int mode, char *object);
extern void part_l00_spawn_spark_burst_2(void *pos, void *direction, int count, unsigned int color);

static inline Class3BBB68 *Class3BBB68At(int index)
{
    return &g_weapon_l00_table[index];
}

/* Steps every record the owner holds: refreshes its start from the owner, advances the two
   angle triples (faster while the approach timer runs), and while it has a target moves its
   position towards it. When the approach timer expires and the target is still live, it
   sends one hit packet (func_002A8C00/func_002A8E20) and marks the record; when the life
   timer expires the record is released and the owner's count drops. */
/* Updates every spark slot owned by this effect: it spins them, moves them toward the target,
   deals damage when they arrive, and frees them when their time runs out. */
void effect_update_spark_slots(char *owner)
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
    Slot3BBB68 *slot;
    char *other;
    float ratio;
    int i;

    for (i = 0; i < 30; i++) {
        if (D_L00_0023DDA0[i].owner != owner)
            continue;
        slot = &D_L00_0023DDA0[i];
        slot->start = *(Rac2TI128 *)(owner + 0x10);
        if (slot->time) {
            slot->ang0[0] = func_00283B98_8(slot->ang0[0], slot->rate0[0] * 100.0f);
            slot->ang0[1] = func_00283B98_8(slot->ang0[1], slot->rate0[1] * 100.0f);
            slot->ang0[2] = func_00283B98_8(slot->ang0[2], slot->rate0[2] * 100.0f);
            slot->ang1[0] = func_00283B98_8(slot->ang1[0], slot->rate1[0] * 100.0f);
            slot->ang1[1] = func_00283B98_8(slot->ang1[1], slot->rate1[1] * 100.0f);
            slot->ang1[2] = func_00283B98_8(slot->ang1[2], slot->rate1[2] * 100.0f);
        } else {
            slot->ang0[0] = func_00283B98_8(slot->ang0[0], slot->rate0[0]);
            slot->ang0[1] = func_00283B98_8(slot->ang0[1], slot->rate0[1]);
            slot->ang0[2] = func_00283B98_8(slot->ang0[2], slot->rate0[2]);
            slot->ang1[0] = func_00283B98_8(slot->ang1[0], slot->rate1[0]);
            slot->ang1[1] = func_00283B98_8(slot->ang1[1], slot->rate1[1]);
            slot->ang1[2] = func_00283B98_8(slot->ang1[2], slot->rate1[2]);
        }
        slot->out0[0] = func_00283180_8(slot->ang0[0]) * slot->amp0[0];
        slot->out0[1] = func_00283198_8(slot->ang0[1]) * slot->amp0[1];
        slot->out0[2] = -func_00283198_8(slot->ang0[2]) * slot->amp0[2];
        slot->out1[0] = func_00283180_8(slot->ang1[0]) * slot->amp1[0];
        slot->out1[1] = func_00283198_8(slot->ang1[1]) * slot->amp1[1];
        slot->out1[2] = -func_00283198_8(slot->ang1[2]) * slot->amp1[2];
        if (slot->target) {
            other = func_002AB1F0_8(slot->target);
            if (other) {
                moby_forward_position_call(slot->target, v, 1);
                func_00282D30_6(v, v, *(float *)(other + 0x10));
                func_00282CC0_6(&slot->pos, v, slot->target + 0x10);
            } else {
                slot->pos = *(Rac2TI128 *)(slot->target + 0x10);
            }
            ratio = func_00283CE0_8(slot->time);
            ratio /= func_00283CE0_8(slot->duration);
            func_00282D08_8(&slot->pos, &slot->start, &slot->pos, 1.0f - ratio);
        }
        if (!func_00282948_8(&slot->time))
            continue;
        if (*(int *)(slot->target + 0x98) && !slot->hit) {
            func_00282CF0_9((char *)v, (char *)&slot->pos, (char *)&slot->start);
            func_00282F20_2(v, v, 0.033333335f);
            func_002A8C00_8(&packet, owner, 0x210000, v, Class3BBB68At(g_item_slot_to_record[0x1C])->f74);
            packet.kind = 1;
            packet.mode = 3;
            packet.id = *(short *)(owner + 0xAA);
            func_002A8E20_8(slot->target, &packet);
            func_0032D758_8(slot->target, 0x3E, *(int *)(owner + 0xB8));
            func_002E5CF8_8(1, 0, owner);
            func_00282F20_2(v, v, -1.0f);
            part_l00_spawn_spark_burst_2(&slot->pos, v, 9, 0xFF0000);
            slot->hit = 1;
        }
        if (func_00282948_8(&slot->life)) {
            slot->owner = 0;
            --*(int *)(ctx + 0x54);
        }
    }
}
