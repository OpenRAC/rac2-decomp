#include "include_asm.h"



#include "common.h"
extern int g_spark_slot_pool MACRO_ADDR;
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float);
extern void vec_clear_128(void *), gravity_get_dir_at_object(void *, void *, int);
extern char *moby_get_private_value_0(void *);
extern void FastVecAdd(void *, void *, void *);
extern u8 g_hero_state[];
extern u8 g_sound_state[];
extern char g_default_effect_vector[16] MACRO_ADDR;
extern unsigned char g_sound_state[];
extern unsigned char g_hero_state[];
extern void FastVecScale(void *dst, void *src, float scale);
extern u8 g_hero_state[];
extern u8 *g_moby_pool_start MACRO_ADDR;

/* func_0031D3E0 is in 0031D3E0.c. */

/* func_0031D588 is in 0031D588-g8.c. */


/* Starts a new spark on a free slot, flying toward the target with random spin and speed. */
void spark_spawn_targeted_pal(char *self, char *target, int count)
{
    int pool = g_spark_slot_pool;
    char *position = self + 0x10;
    char *target_position = target + 0x10;
    char *data = *(char **)(self + 0x68);
    char *slot;
    char *info;
    float offset[4];
    int i;
    for (i = 0; i < 12; i++) {
        slot = (char *)(pool + i * 0xA0);
        if (*(int *)(slot + 0x8C) == 0) {
            *(char **)(slot + 0x8C) = self;
            (*(int *)(data + 0x1C))++;
            qcopy(slot + 0x20, position);
            *(float *)(slot + 64) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(slot + 68) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(slot + 72) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(slot + 100) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(slot + 104) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(slot + 108) = math_random_float_range(-3.14159274101257324219f, 3.14159274101257324219f);
            *(float *)(slot + 76) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(slot + 80) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(slot + 84) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(slot + 112) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(slot + 116) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(slot + 120) = math_random_signed_float_range(0.001f, 0.05f);
            *(float *)(slot + 88) = math_random_float_range(3.25f, 6.75f);
            *(float *)(slot + 92) = math_random_float_range(3.25f, 6.75f);
            *(float *)(slot + 96) = math_random_float_range(3.25f, 6.75f);
            *(float *)(slot + 124) = math_random_float_range(1.25f, 4.75f);
            *(float *)(slot + 128) = math_random_float_range(1.25f, 4.75f);
            *(float *)(slot + 132) = math_random_float_range(1.25f, 4.75f);
            vec_clear_128(slot);
            vec_clear_128(slot + 0x10);
            *(int *)(slot + 0x94) = count;
            *(int *)(slot + 0x98) = count;
            *(char **)(slot + 0x90) = target;
            *(int *)(slot + 0x9C) = 0;
            *(int *)(slot + 0x88) = 17;
            info = moby_get_private_value_0(target);
            if (info) {
                gravity_get_dir_at_object(target, offset, 1);
                FastVecScale(offset, offset, *(float *)(info + 0x10));
                FastVecAdd(slot + 0x30, offset, target + 0x10);
            } else {
                qcopy(slot + 0x30, target_position);
            }
            break;
        }
    }
}


extern int math_fast_float_d(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
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
extern unsigned char g_item_slot_to_record[];
extern Class31DEE8 g_weapon_table[];
extern float FastAddRotations(float angle, float step);
extern float math_fast_sin_or_cos_a(float angle);
extern float math_fast_sin_or_cos_b(float angle);
extern float IntToFloat(int ticks);
extern int math_fast_float_d(void *timer);
extern void lerp_vector(void *out, void *from, void *to, float t);
extern void make_hit_descriptor(void *packet, char *owner, int flags, void *direction, float amount);
extern void QueueMobyImpact(char *target, void *packet);
extern void part_spawn_hit_sparks_pal(void *pos, int count, int mode);
extern int StartAttachedEffect_pal(char *target, int kind, int value);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float scale);
extern void FastVecSub(void *, void *, void *);
static inline Class31DEE8 *Class31DEE8At(int index)
{
    return &g_weapon_table[index];
}

/* Steps every record the owner holds: refreshes its start from the owner, advances the two
   angle triples (faster while the approach timer runs), and while it has a target moves its
   position towards it. When the approach timer expires and the target is still live, it
   sends one hit packet (func_002A8C00/func_002A8E20) and marks the record; when the life
   timer expires the record is released and the owner's count drops. */
void spark_update_targeted_pal(char *owner)
{
    float offset[4];
    struct {
        char pad_00[0x18];
        unsigned char kind;
        unsigned char mode;
        short id;
        char pad_1c[0x14];
    } packet;
    char *data = *(char **)(owner + 0x68);
    Slot31DEE8 *slot;
    char *other;
    float ratio;
    float damage;
    float boost = 100.0f;
    int i;

    for (i = 0; i < 12; i++) {
        if (((Slot31DEE8 *)g_spark_slot_pool)[i].owner != owner)
            continue;
        slot = &((Slot31DEE8 *)g_spark_slot_pool)[i];
        qcopy(slot->start, owner + 0x10);
        if (slot->time) {
            slot->ang0[0] = FastAddRotations(slot->ang0[0], slot->rate0[0] * boost);
            slot->ang0[1] = FastAddRotations(slot->ang0[1], slot->rate0[1] * boost);
            slot->ang0[2] = FastAddRotations(slot->ang0[2], slot->rate0[2] * boost);
            slot->ang1[0] = FastAddRotations(slot->ang1[0], slot->rate1[0] * boost);
            slot->ang1[1] = FastAddRotations(slot->ang1[1], slot->rate1[1] * boost);
            slot->ang1[2] = FastAddRotations(slot->ang1[2], slot->rate1[2] * boost);
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
                gravity_get_dir_at_object(slot->target, offset, 1);
                FastVecScale(offset, offset, *(float *)(other + 0x10));
                FastVecAdd(slot->pos, offset, slot->target + 0x10);
            } else {
                qcopy(slot->pos, slot->target + 0x10);
            }
            ratio = IntToFloat(slot->time);
            ratio /= IntToFloat(slot->duration);
            lerp_vector(slot->pos, slot->start, slot->pos, 1.0f - ratio);
        }
        if (!math_fast_float_d(&slot->time))
            continue;
        if (*(int *)(slot->target + 0x98) && !slot->hit) {
            FastVecSub(offset, slot->pos, slot->start);
            vec_scale_to_length(offset, offset, 0.040000003f);
            damage = Class31DEE8At(g_item_slot_to_record[0x1C])->f74;
            make_hit_descriptor(&packet, owner, 0x210000, offset, damage);
            packet.kind = 1;
            packet.mode = 3;
            packet.id = *(short *)(owner + 0xAA);
            QueueMobyImpact(slot->target, &packet);
            slot->hit = 1;
            part_spawn_hit_sparks_pal(slot->pos, 10, 1);
            StartAttachedEffect_pal(slot->target, 28, *(int *)(owner + 0xB8));
        }
        if (math_fast_float_d(&slot->life)) {
            slot->owner = 0;
            --*(int *)(data + 0x1C);
        }
    }
}


