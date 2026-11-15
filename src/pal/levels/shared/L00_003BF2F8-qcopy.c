#include "include_asm.h"
#include "names.h"

typedef int Rac2TI128 __attribute__((mode(TI)));
typedef struct {
    float out0[4];           
    float out1[4];           
    Rac2TI128 start;         
    Rac2TI128 pos;           
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
} Slot3BBB68;
extern Slot3BBB68 D_L00_0023DDA0[];
typedef struct {
    char pad_00[0x74];
    float f74;
    char pad_78[0xE0 - 0x78];
} Class3BBB68;
extern unsigned char g_item_slot_to_record[];
extern Class3BBB68 g_weapon_l00_table[];
extern void FastVecScale(void *out, void *in, float scale);
extern void FastVecAdd(void *out, void *in1, void *in2);
extern void FastVecSub(char *out, char *first, char *second);
extern void vec_scale_to_length(void *out, void *in, float scale);
extern float FastAddRotations(float angle, float step);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern char *moby_get_private_value_0(char *object);
extern void moby_forward_position_call(char *object, void *out, int mode);
extern void lerp_vector(void *out, void *from, void *to, float t);
extern float IntToFloat(int ticks);
extern int math_fast_float_d(void *timer);
extern void make_hit_descriptor(void *packet, char *owner, int flags, void *direction, float amount);
extern void QueueMobyImpact(char *target, void *packet);
extern void func_PAL_0032F0B8(char *target, int kind, int value);
extern int PlayMobySound(int index, int mode, char *object);
extern void func_PAL_L00_003C11A0(void *pos, void *direction, int count, unsigned int color);
static inline Class3BBB68 *Class3BBB68At(int index)
{
    return &g_weapon_l00_table[index];
}

/* Steps every record the owner holds: refreshes its start from the owner, advances the two
   angle triples (faster while the approach timer runs), and while it has a target moves its
   position towards it. When the approach timer expires and the target is still live, it
   sends one hit packet (func_002A8C00/func_002A8E20) and marks the record; when the life
   timer expires the record is released and the owner's count drops. */
void func_PAL_L00_003BF7F8(char *owner)
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
            slot->ang0[0] = FastAddRotations(slot->ang0[0], slot->rate0[0] * 100.0f);
            slot->ang0[1] = FastAddRotations(slot->ang0[1], slot->rate0[1] * 100.0f);
            slot->ang0[2] = FastAddRotations(slot->ang0[2], slot->rate0[2] * 100.0f);
            slot->ang1[0] = FastAddRotations(slot->ang1[0], slot->rate1[0] * 100.0f);
            slot->ang1[1] = FastAddRotations(slot->ang1[1], slot->rate1[1] * 100.0f);
            slot->ang1[2] = FastAddRotations(slot->ang1[2], slot->rate1[2] * 100.0f);
        } else {
            slot->ang0[0] = FastAddRotations(slot->ang0[0], slot->rate0[0]);
            slot->ang0[1] = FastAddRotations(slot->ang0[1], slot->rate0[1]);
            slot->ang0[2] = FastAddRotations(slot->ang0[2], slot->rate0[2]);
            slot->ang1[0] = FastAddRotations(slot->ang1[0], slot->rate1[0]);
            slot->ang1[1] = FastAddRotations(slot->ang1[1], slot->rate1[1]);
            slot->ang1[2] = FastAddRotations(slot->ang1[2], slot->rate1[2]);
        }
        slot->out0[0] = math_fast_sin_or_cos_a(slot->ang0[0]) * slot->amp0[0];
        slot->out0[1] = math_fast_sin_or_cos_b(slot->ang0[1]) * slot->amp0[1];
        slot->out0[2] = -math_fast_sin_or_cos_b(slot->ang0[2]) * slot->amp0[2];
        slot->out1[0] = math_fast_sin_or_cos_a(slot->ang1[0]) * slot->amp1[0];
        slot->out1[1] = math_fast_sin_or_cos_b(slot->ang1[1]) * slot->amp1[1];
        slot->out1[2] = -math_fast_sin_or_cos_b(slot->ang1[2]) * slot->amp1[2];
        if (slot->target) {
            other = moby_get_private_value_0(slot->target);
            if (other) {
                moby_forward_position_call(slot->target, v, 1);
                FastVecScale(v, v, *(float *)(other + 0x10));
                FastVecAdd(&slot->pos, v, slot->target + 0x10);
            } else {
                slot->pos = *(Rac2TI128 *)(slot->target + 0x10);
            }
            ratio = IntToFloat(slot->time);
            ratio /= IntToFloat(slot->duration);
            lerp_vector(&slot->pos, &slot->start, &slot->pos, 1.0f - ratio);
        }
        if (!math_fast_float_d(&slot->time))
            continue;
        if (*(int *)(slot->target + 0x98) && !slot->hit) {
            FastVecSub((char *)v, (char *)&slot->pos, (char *)&slot->start);
            vec_scale_to_length(v, v, 0.040000003f);
            make_hit_descriptor(&packet, owner, 0x210000, v, Class3BBB68At(g_item_slot_to_record[0x1C])->f74);
            packet.kind = 1;
            packet.mode = 3;
            packet.id = *(short *)(owner + 0xAA);
            QueueMobyImpact(slot->target, &packet);
            func_PAL_0032F0B8(slot->target, 0x3E, *(int *)(owner + 0xB8));
            PlayMobySound(1, 0, owner);
            vec_scale_to_length(v, v, -1.0f);
            func_PAL_L00_003C11A0(&slot->pos, v, 9, 0xFF0000);
            slot->hit = 1;
        }
        if (math_fast_float_d(&slot->life)) {
            slot->owner = 0;
            --*(int *)(ctx + 0x54);
        }
    }
}
