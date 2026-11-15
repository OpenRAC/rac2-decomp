#include "include_asm.h"

#include "common.h"
typedef float V4_L11_447018[4] __attribute__((aligned(16)));
typedef struct {
    float head[2];
    s32 flag;
    s32 pad;
    V4_L11_447018 pos;
} L11_447018_Spark;
extern char *arena_get_center_point(char *);
extern void vec_add_random_offset(void *, float);
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern void enemy_spawn_record(void *, void *, void *, s32, s32);
extern s32 D_L11_001B1950 __attribute__((sda));
extern s32 D_L11_001B1954 __attribute__((sda));
extern s32 D_L11_001B1958 __attribute__((sda));
extern float D_L11_001B195C __attribute__((sda));
extern float D_L11_001B1960 __attribute__((sda));
extern float D_L11_001B1964 __attribute__((sda));
extern float D_L11_001B1968 __attribute__((sda));
extern char D_L11_001B1990[8] __attribute__((sda));

/* Emits count sparks at the object, then one more unless the chance roll says no. */
void func_PAL_L11_0044CA88(char *obj, s32 count)
{
    L11_447018_Spark s;
    s32 i;

    for (i = 0; i < count; i++) {
        qcopy(s.pos, arena_get_center_point(obj));
        vec_add_random_offset(s.pos, D_L11_001B1964);
        s.pos[2] += D_L11_001B1968;
        vec_clear_128(&s);
        vec_add_random_offset(&s, math_random_float_range(D_L11_001B195C, D_L11_001B1960) * 0.020000001f);
        s.flag = 0;
        enemy_spawn_record(s.pos, &s, D_L11_001B1990, math_random_int_below(2), math_random_int_range(D_L11_001B1954, D_L11_001B1958));
    }
    if (math_random_int_below(D_L11_001B1950) == 0) {
        qcopy(s.pos, arena_get_center_point(obj));
        vec_add_random_offset(s.pos, D_L11_001B1964);
        s.pos[2] += D_L11_001B1968;
        vec_clear_128(&s);
        vec_add_random_offset(&s, math_random_float_range(D_L11_001B195C, D_L11_001B1960) * 0.020000001f);
        s.flag = 0;
        enemy_spawn_record(s.pos, &s, D_L11_001B1990, math_random_int_below(2), math_random_int_range(D_L11_001B1954, D_L11_001B1958));
    }
}

extern s32 FastDecTimer(void *);
extern u16 D_L11_001B19A8 __attribute__((sda));
extern s32 D_L11_001B19AC __attribute__((sda));
extern s32 D_L11_005A0000 __attribute__((sda));
extern s32 func_32CAB0(s32 a0);
extern s32 func_301700(float f12);
extern s32 func_3006B8(char *a0, s32 a1);
extern s32 func_338F10(char *a0, char *a1, s32 a2);
extern s32 func_4461C0(s32 a0, char *a1);
extern s32 func_448CE0(char *a0);
extern u8 *g_group_id_lists[];
extern u8 *g_moby_l11_table __attribute__((sda));
extern s32 D_L11_001B1C50 __attribute__((sda));
extern u8 D_L11_001B1C10 __attribute__((sda));
extern s32 D_L11_001B1C54;
typedef struct JobObject JobObject;
typedef struct {
    u8 pad00[0x18];
    float *params;           
    u8 pad1C[4];
    float health;            
    u8 pad24[4];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 f34;
    u8 pad35[0x48 - 0x35];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    u8 hitInfo[0x10];        
    u8 f60;
    u8 pad61[8];
    u8 f69;
    u8 pad6A[0x80 - 0x6A];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xFC - 0x9C];
    float fFC;
    float paramBlock[5];     
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x1D4 - 0x138];
    float f1D4;
    u8 pad1D8[0x1E6 - 0x1D8];
    u8 f1E6;
    u8 pad1E7;
    u8 f1E8;
    u8 f1E9;
    u8 pad1EA[0x1FC - 0x1EA];
    u16 spawnTimer;          
    u8 pad1FE[0x2F0 - 0x1FE];
    float basis[12];         
    float anchor[4];         
    u8 pad330[0x354 - 0x330];
    JobObject *turret;       
    float turnRate;          
    u8 pad35C[0x364 - 0x35C];
    s16 fireTimer;           
    u8 pad366[0x36E - 0x366];
    s16 f36E;
} JobState;
struct JobObject {
    u8 pad00[0x10];
    float position[4];       
    u8 stage;                
    u8 pad21[0x31 - 0x21];
    u8 f31;
    u8 pad32[2];
    u16 flags;               
    u8 pad36[0x68 - 0x36];
    JobState *state;         
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0x95 - 0x70];
    u8 f95;
    u8 pad96[0xB8 - 0x96];
    s32 fB8;
    u8 padBC[4];
    float rotation[12];      
};
extern s32 FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 func_PAL_002B1A50(void *, void *, s32);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(void *, void *, s32);
extern s32 arena_is_point_in_inner_zone(s32, void *);
extern void moby_set_state(void *, s32, s32);
extern char D_L11_001BA8C0[];
extern s32 D_001A8FF4;
extern void security_robot_deactivate(void *);
extern void security_robot_update_pairing(void *);
extern s32 security_robot_is_holding_item_attacking(void *, void *);
extern void func_PAL_L02_003D5FF0(void *, s32);
extern void func_PAL_L11_0044F420(void *, s32, s32);

/* Per-frame update of a turret-like enemy: on its first frame it seeds its parameter block
   (including a random-sign turn rate of 10 to 30 degrees), then handles hits, firing, damage
   and the death sequence. The turn rate's sign is chosen in the store's own expression so the
   stored value does not cross the coin-flip call. */
void func_PAL_L11_0044DF38(JobObject *object)
{
    JobState *state = object->state;
    void *hit;
    float speed;

    if (object->stage == 0) {
        state->params = state->paramBlock;
        state->f48 = FloatToInt(15.0f);
        state->f4A = FloatToInt(16.0f);
        speed = math_random_float_range(10.0f, 30.0f) * 0.01745329424738884f;
        state->turnRate = math_random_int_below(2) ? -speed : speed;
        state->f80 = 1.3f;
        state->f84 = 1.3f;
        state->f69 = 2;
        state->f1E9 = 3;
        state->f1D4 = 0.5f;
        state->paramBlock[1] = 0.5f;
        state->paramBlock[2] = 0.5f;
        state->f60 = 16;
        state->f98 = 7;
        state->f8C = 0.4f;
        state->f1E6 = 5;
        state->f1E8 = 2;
        state->paramBlock[0] = 1.3f;
        state->paramBlock[3] = 0.5f;
        state->paramBlock[4] = 1.5707964897155762f;
        state->f130 = 0.523598849773407f;
        state->f134 = 0.01f;
        state->f12C = 0.008f;
        state->f28 = 3;
        state->f29 = 1;
        state->f30 = 0.75f;
        state->fireTimer = 0;
        if (!math_random_int_below(2))
            object->flags |= 0x8000;
        state->turret = 0;
        security_robot_deactivate(object);
    }
    if (state->f36E == 0 && object->stage != 18 && !D_001A8FF4) {
        object->flags |= 0x400;
        if (object->f31 && fast_vec_dist(object->position, D_L11_001BA8C0) < 24.0f) {
            moby_update_ground_check(object);
            object->f6F = 22;
        }
    } else {
        object->flags &= 0xFBFF;
    }
    if (object->stage >= 3) {
        state->fFC = 1.0f;
        hit = part_find_owned_effect_slot(object, 0x10000, 1);
        if (hit) {
            state->fFC = 1.0f;
            if (security_robot_is_holding_item_attacking(object, hit)) {
                state->f60 = 15;
                func_PAL_002B1A50(object, state->hitInfo, 1);
                state->f60 = 16;
                if (state->turret && state->fireTimer == 0 && object->f31) {
                    func_PAL_L02_003D5FF0(state->turret->position, 2);
                    state->fireTimer = 50;
                }
            } else {
                func_PAL_002B1A50(object, state->hitInfo, 0);
            }
        } else {
            func_PAL_002B1A50(object, state->hitInfo, 0);
        }
        if (state->health <= 0.0f && object->f95 != 7 && object->f95 != 8)
            func_PAL_L11_0044F420(object, 1, 0);
        if (state->f36E) {
            matrix_from_basis_rows(state->basis, object->rotation);
            cam_compute_view_direction(object->position, state->anchor, 0);
            if (!arena_is_point_in_inner_zone(object->fB8, object->position) && object->f95 != 8) {
                state->health = 0;
                moby_set_state(object, 18, 8);
            }
        }
        if (object->stage >= 2 && state->f2E == 2)
            func_PAL_L11_0044F420(object, 1, 1);
        security_robot_update_pairing(object);
    }
}
