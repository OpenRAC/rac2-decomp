#include "include_asm.h"

#include "common.h"
typedef int Quad128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void moby_mark_spawned(void *);
extern void func_002A0F48(void *);
extern char *moby_get_private_value_0(char *);
extern void cam_compute_view_direction(void *, void *, int);
extern int save_is_record_value(int, int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int part_alloc_effect_slot(void *, float, float, float, void *);
extern void math_compute_aim_direction(void *, void *, float, float, float);
extern void ref_L00_0041EB38_00(void (*)(void *), void *);
extern void shot_update_and_draw_trail_pal(void *);
typedef struct {
    char pad0[0x50];
    float speed;                   
    char pad54[224 - 0x54];
} ShotKind;
typedef struct {
    unsigned int slot;             
    int pad04[3];
    int frame;                     
    int ownerIndex;                
    int ownerKind;                 
    char *target;                  
    float velocity[3];             
    float speed;                   
    int pad30;
    int handle;                    
    int count;                     
    float step;                    
    float fade;                    
} ShotState;
extern ShotKind g_weapon_l00_table[];
extern char g_projectile_weapon_info[];
extern Quad128 g_hero_position __attribute__((nosda));
extern char g_hero_state[];
extern float g_shot_l00_speed_scale __attribute__((sda));
extern float g_shot_trail_scroll_offset __attribute__((sda));
extern unsigned int g_shot_trail_slot_index __attribute__((sda));

/* Spawn object 0xC89 at origin, aimed along the owner, at target or along the hero. */
char *SpawnAimedShot_pal(Quad128 *origin, char *owner, char *target)
{
    Quad128 normal, position;
    char *object, *collision, *hero;
    ShotState *state;
    float speed;
    int count, ownerIndex, ownerKind;

    object = CreateMoby(0xC89);
    if (object) {
        ((unsigned char *)object)[0x30] = 255;
        *(short *)(object + 0x34) = 0x100;
        *(short *)(object + 0x32) = 255;
        object[0x31] = 1;
        *(char **)(object + 0xB8) = owner;
        object[0x20] = 0;
        state = *(ShotState **)(object + 0x68);
        speed = (g_weapon_l00_table + ((unsigned char *)g_projectile_weapon_info)[0x16])->speed * 0.020000001f;
        hero = g_hero_state;
        if (*(short *)(hero + 0x24EC) == 1) {
            vec_scale_to_length(state->velocity, owner + 0xD0, -speed);
            *(Quad128 *)(object + 0x10) = *origin;
        } else {
            if (target) {
                char *point = target + 0x10;

                qcopy(&position, point);
                collision = moby_get_private_value_0(target);
                if (collision) {
                    cam_compute_view_direction(point, &normal, 1);
                    FastVecScale(&normal, &normal, *(float *)(collision + 0x10));
                    FastVecAdd(&position, &position, &normal);
                }
                FastVecSub(state->velocity, &position, origin);
                vec_scale_to_length(state->velocity, state->velocity, speed);
            } else if (*(int *)(hero + 0x1500)) {
                math_compute_aim_direction(state->velocity, origin, speed, 30.0f, 0.3490658998f);
            } else {
                vec_scale_to_length(state->velocity, hero + 0x760, speed);
            }
            *(Quad128 *)(object + 0x10) = *origin;
        }
        state->speed = speed;
        count = FloatToInt(30.0f / speed) + 1;
        state->count = count;
        state->step = 1.0f / IntToFloat(count);
        *(float *)(object + 0x2C) = *(float *)(*(char **)(object + 0x24) + 0x24) * g_shot_l00_speed_scale;
        object[0x20] = 0;
        state->target = target;
        if (target) {
            collision = moby_get_private_value_0(target);
            if (collision)
                *(unsigned short *)(collision + 0x1E) |= 0x80;
        }
        state->fade = 1;
        ownerIndex = *(short *)(*(char **)(owner + 0x68) + 0x12);
        state->ownerIndex = ownerIndex;
        ownerKind = *(short *)(owner + 0xAA);
        state->ownerKind = ownerKind;
        if (!save_is_record_value(ownerKind, ownerIndex)) {
            moby_mark_spawned(object);
            return 0;
        }
        state->frame = 0;
        g_shot_trail_scroll_offset = 0;
        if (g_shot_trail_slot_index > 15)
            g_shot_trail_slot_index = 0;
        state->slot = g_shot_trail_slot_index;
        g_shot_trail_slot_index++;
        if ((int)g_shot_trail_slot_index > 15)
            g_shot_trail_slot_index = 0;
        position = *(Quad128 *)(object + 0x10);
        *(Quad128 *)(object + 0x10) = g_hero_position;
        state->handle = part_alloc_effect_slot(object, 1.0f, 1.0f, 1.0f, 0);
        *(Quad128 *)(object + 0x10) = position;
        ref_L00_0041EB38_00(shot_update_and_draw_trail_pal, object);
        func_002A0F48(object);
    }
    return object;
}
