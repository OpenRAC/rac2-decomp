#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } StateVector;
typedef struct { u16 count, padding; u32 tick, flags; } ChallengeProgress;
extern ChallengeProgress D_0018C958[];
typedef struct {
    u8 padding_0[0x20];
    float movement_scale;
    s16 movement_enabled;
    u8 padding_26[0x2];
    u8 movement_mode;
    u8 padding_29[0xE7];
    float collision_radius;
    float collision_height;
    float movement_limit;
    float movement_acceleration;
    float turn_scale;
    u8 padding_124[0x18];
    float turn_step;
    float turn_limit;
    float movement_speed;
    u8 padding_148[0x10];
    u8 * movement_data;
    u8 * path_data;
    u8 padding_160[0x40];
    float floor_height;
    u8 padding_1A4[0x44];
    int path_index;
    u8 padding_1EC[0x14];
    int groups[8];
    u32 area_id;
    u8 padding_224[0x130];
    u8 * child;
    u8 * target;
    u8 padding_35C[0x8];
    int command_cooldown;
    u8 padding_368[0x1C];
    int tilt_timer;
    float tilt_pitch;
    float tilt_yaw;
    u8 padding_390[0x14];
    float initial_height;
} TargetState;

typedef struct {
    u8 padding_0[0x10];
    float position[4];
    u8 state, group;
    u8 padding_22[2];
    u8 *data;
    u8 padding_28[4];
    float scale;
    u8 padding_30;
    u8 active;
    u16 field_32, flags;
    u8 padding_36[0xD];
    u8 animation;
    u8 padding_44[0x24];
    TargetState *vars;
    u8 padding_6C[3];
    u8 event;
    u8 padding_70[0xC];
    u16 field_7C;
    u8 flags_7E;
    u8 padding_7F[0x16];
    u8 mode;
    u8 padding_96[0x12];
    u8 flags_A8;
    u8 padding_A9;
    s16 type;
    u8 padding_AC[0x14];
    StateVector forward;
} TargetMoby;
extern u32 D_001A7390 __attribute__((sda));
extern int D_001A79F0;
typedef struct {
    u8 padding_0[0x80];
    float position[4];
    u8 padding_90[0x2454];
    int command;
} TargetHero;
extern TargetHero D_00189E20;
/* Level statistics block. L03 reads and writes ints at +0, +4 and +8 from other functions, then
   these five halfwords. Every counter sits at a nonzero offset, so its macro access stays two words. */
typedef struct {
    int words[3];
    u16 near_player, active, near_940, near_93C, near_A59;
} TargetCounters;
extern TargetCounters D_L03_001B2750 __attribute__((sda));
extern float D_L03_001AFEE0 __attribute__((sda));
extern float D_L03_001AFEE4 __attribute__((sda));
extern int D_L03_001AFEF8 __attribute__((sda));
extern int D_L03_001AFEFC __attribute__((sda));
extern u16 D_L03_001AFF00 __attribute__((sda));
extern float D_L03_001B9980[];
extern int D_L03_001B2A38[] __attribute__((sda));
extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern u16 *D_L03_001FB5A0[];
extern int D_L03_001B2548;
extern void func_L03_0038A9D0(void *, void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A89A8(u8 *, int, float);
extern u8 *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7750(u8 *, s32, s32);
extern void func_002A7470(u8 *, int, int, int);
extern void func_L03_00419A60(u32, u8 *, s32);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern void func_002A93B0(void *);
extern void func_L03_0032AD10(int);
extern void *func_002A9640(void *, u32, int);
extern int func_00282C30(int);
extern u8 *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,void *);
extern void func_002B0A68(char *, int, float *, float, float, float, float, unsigned char);
extern float *func_L03_003C5668(u8 *, float *, float *);
extern void func_L02_002EF388(void *, void *, void *, int, int);
extern u8 *func_L03_003C5128(u8 *);
extern u8 *func_L03_003C52D0(u8 *);
extern u8 *func_L03_003C5488(u8 *);
extern u8 *func_L03_003C4D40(u8 *);
extern u8 *func_L03_003C4F58(u8 *);
extern int func_00288E18(int, int);
extern void func_L03_004197C8(void *, void *);
extern int func_L03_00419BD8(u32, void *, void *);
extern void func_L03_003CAAF0(void *, void *, void *);
extern void func_L03_003CA148(void *, void *, void *);
extern void func_L03_003CA230(void *, void *);
extern void func_L00_003294F0(void *, int);
extern int func_L03_003C5CE8(void *);
extern void func_L03_003C5EE8(void *);
#define ANIM_COUNT(p, offset) (*(u8 *)(*(u8 **)(*(u8 **)((p) + 0x24) + (offset)) + 0x10))


void func_L03_003C3220(u8 *object)
{
    StateVector point, first, second;
    TargetMoby *mob = (TargetMoby *)object;
    TargetState *vars = mob->vars;
    u8 *state = (u8 *)vars;
    u8 *target;
    int type, i;
    float distance;
    int permitted;
    if (mob->state == 0) {
        if (func_002A77E0(2)) mob->flags |= 0x8000;
        else mob->flags &= 0x7FFF;
        mob->flags_7E |= 1;
        mob->position[2] = func_002A89A8((u8 *)mob->position, 0, 0.5f);
        vars->initial_height = mob->position[2];
        type = mob->type;
        if (type == 0x964) {
            vars->child = func_0029EFD0(0x972);
            if (vars->child) {
                func_002B37E8(vars->child, object);
                *(u16 *)(vars->child + 0x32) = 0x30;
            }
        } else {
            vars->child = func_0029EFD0(0xD75);
            if (vars->child) {
                func_002B37E8(vars->child, object);
                *(u16 *)(vars->child + 0x7C) = D_L03_001AFF00;
                *(u16 *)(vars->child + 0x32) = 0x30;
                if (mob->type == 0x93C) {
                    *(float *)(vars->child + 0x2C) = *(float *)(*(u8 **)(vars->child + 0x24) + 0x24) * 1.2f;
                }
            }
        }
        vars->movement_mode = 3;
        vars->movement_scale = 1.0f;
        vars->movement_enabled = 1;
        vars->movement_speed = D_L03_001AFEE0;
        vars->collision_height = 0.3f;
        switch (mob->type) {
        case 0x93C:
            vars->collision_radius = 0.42f;
            mob->position[2] += 0.089f;
            break;
        case 0x940:
            vars->collision_radius = 0.39f;
            mob->position[2] += 0.089f;
            func_00282F20(&point, &mob->forward, -0.2f);
            func_00282CC0(mob->position, &point, mob->position);
            break;
        case 0xA59:
            vars->collision_radius = 0.42f;
            mob->position[2] += 0.089f;
            break;
        default:
            vars->collision_radius = 0.15f;
            mob->position[2] += 0.089f;
            break;
        }
        vars->movement_limit = 0.5f;
        vars->movement_acceleration = 0.5f;
        vars->turn_scale = 1.5882498f;
        vars->turn_limit = 0.523598849773407f;
        vars->movement_data = state + 0x240;
        vars->path_data = state + 0x2C0;
        vars->turn_step = 0.0055555557f;
        func_002A7750(object, 1, 0);
        if (mob->animation)
            func_002A7470(object, 0, func_002A77E0(ANIM_COUNT(object, 0x48)), 0);
        if (mob->type == 0x940) {
            for (i = 0; i < 8; i++) {
                u16 *ids;
                if (vars->groups[i] == -1) continue;
                for (ids = D_L03_001FB5A0[vars->groups[i]];
                     (vars->groups[i] & 255) != 255 && vars->groups[i] <= D_L03_001B2A38[0] && ids != 0 &&
                     ((s16)ids[-1] >= 0 || ids == D_L03_001FB5A0[vars->groups[i]]);
                     ids++) {
                    u8 *member = D_L03_001B2A1C[0] + ((*ids & 0x7FFF) << 8);
                    if (member == 0) break;
                    if (*(s16 *)(member + 0xAA) == 0x97A)
                        func_L03_00419A60(vars->area_id, member + 0x10, 0);
                }
            }
        } else if (mob->type == 0xA59 && mob->animation != 6) {
            func_002A7470(object, 6, 0, 0);
        }
    }
    if (mob->active && func_00282E48(mob->position, D_L03_001B9980) < 24.0f) {
        func_002A93B0(object);
        mob->event = 0x16;
    }
    if (mob->state > 1 && mob->mode != 4) func_L03_0032AD10((int)object);
    if (func_002A9640(object, 1, 0) ||
        (mob->position[2] < vars->initial_height - 10.0f &&
         mob->position[2] - 10.0f < vars->floor_height)) {
        if (func_00282C30(D_L03_001AFEF8 - D_L03_001B2548) > D_L03_001AFEFC) {
            point.q = 0;
            point.f[2] = 0.5f;
            D_L03_001AFEF8 = D_L03_001B2548;
            func_00282CC0(&point, &point, mob->position);
            func_0032C700(mob->position,0,5,5,5,10,20,0,0.25f,20.0f,1,0,0,0);
            if (mob->type == 0x964)
                func_002B0A68((char *)object, 15, (float *)(state + 0x1B0), 3.0f, 6.0f, 3.0f, 6.0f, 255);
            func_002A7750(object, 4, 1);
            qzero(state + 0x1B0);
            vars->path_index = -1;
            func_L03_003C5668(object, first.f, second.f);
            func_L02_002EF388(object, &first, &second, 0, 0);
        }
        mob->flags_A8 = 255;
    }
    if (mob->mode == 4) D_L03_001B2750.active++;
    if (D_0018C958[39].count < 65535 && mob->type == 0x940 && mob->state != 1 && func_L03_003C5128(object)) {
        if (D_0018C958[39].count != 0) {
            if (D_001A7390 - D_0018C958[39].tick > 1080 || D_0018C958[39].tick == 0)
                func_00288E18(0x9D0, 0x27);
            else if (D_0018C958[39].tick < D_001A7390) D_0018C958[39].tick = D_001A7390;
        } else {
            D_0018C958[39].count++;
            if (D_0018C958[39].tick < D_001A7390) D_0018C958[39].tick = D_001A7390;
            D_0018C958[39].flags = (D_0018C958[39].flags | (1U << D_001A79F0)) | 0x80000000U;
        }
    }
    if (D_0018C958[128].count < 65535 && mob->type == 0x93C && mob->state != 1 && func_L03_003C52D0(object)) {
        if (D_0018C958[128].count != 0) {
            if (D_001A7390 - D_0018C958[128].tick > 1080 || D_0018C958[128].tick == 0)
                func_00288E18(0xA29, 0x80);
            else if (D_0018C958[128].tick < D_001A7390) D_0018C958[128].tick = D_001A7390;
        } else {
            D_0018C958[128].count++;
            if (D_0018C958[128].tick < D_001A7390) D_0018C958[128].tick = D_001A7390;
            D_0018C958[128].flags = (D_0018C958[128].flags | (1U << D_001A79F0)) | 0x80000000U;
        }
    }
    if (D_0018C958[97].count < 65535 && mob->type == 0xA59 && mob->state != 1 && func_L03_003C5488(object)) {
        if (D_0018C958[97].count != 0) {
            if (D_001A7390 - D_0018C958[97].tick > 1080 || D_0018C958[97].tick == 0)
                func_00288E18(0xA0A, 0x61);
            else if (D_0018C958[97].tick < D_001A7390) D_0018C958[97].tick = D_001A7390;
        } else {
            D_0018C958[97].count++;
            if (D_0018C958[97].tick < D_001A7390) D_0018C958[97].tick = D_001A7390;
            D_0018C958[97].flags = (D_0018C958[97].flags | (1U << D_001A79F0)) | 0x80000000U;
        }
    }
    if (mob->state != 1 && func_00282E80(mob->position, D_00189E20.position) < 16.0f) {
        D_L03_001B2750.near_player++;
        switch (mob->type) {
        case 0x940: D_L03_001B2750.near_940++; break;
        case 0x93C: D_L03_001B2750.near_93C++; break;
        case 0xA59: D_L03_001B2750.near_A59++; break;
        }
    }
    permitted = 1;
    if (D_00189E20.command == 0 || mob->state == 1 || mob->state == 13 || mob->mode == 7)
        permitted = 0;
    else if (vars->command_cooldown) permitted = 0;
    else if (mob->mode == 4 && D_00189E20.command != 6) permitted = 0;
    else if (mob->mode == 5 && D_00189E20.command != 5) permitted = 0;
    if (!permitted) return;
    switch (D_00189E20.command) {
    case 1:
        if (mob->mode == 1) return;
        distance = func_00282E80(mob->position, D_00189E20.position);
        if (distance > D_L03_001AFEE4) {
            func_002A7750(object, 3, 1);
            if (mob->animation == 2) return;
            func_002A7470(object, 2, func_002A77E0(ANIM_COUNT(object, 0x50)), 10);
        } else {
            func_002A7750(object, 4, 1);
            if (mob->animation == 0) return;
            func_002A7470(object, 0, func_002A77E0(ANIM_COUNT(object, 0x48)), 10);
        }
        break;
    case 3:
        if (mob->mode == 2 || mob->type != 0x964) return;
        vars->target = func_L03_003C4D40(object);
        if (vars->target) {
            func_002A7750(object, 9, 2);
            if (mob->animation != 3)
                func_002A7470(object, 3, func_002A77E0(ANIM_COUNT(object, 0x54)), 10);
        } else {
            func_002A7750(object, 11, 2);
            if (mob->animation != 0)
                func_002A7470(object, 0, func_002A77E0(ANIM_COUNT(object, 0x48)), 10);
        }
        break;
    case 2:
        if (mob->mode != 0) {
            func_002A7750(object, 2, 0);
            if (mob->animation) func_002A7470(object, 0, func_002A77E0(ANIM_COUNT(object, 0x48)), 10);
            vars->tilt_timer = func_002A7820(60, 120);
            vars->tilt_pitch = 0;
            vars->tilt_yaw = 0;
        }
        break;
    case 4:
        if (mob->type != 0x964) return;
        vars->command_cooldown = 30;
        if (mob->mode != 3) {
            vars->target = func_L03_003C4F58(object);
            if (!vars->target) return;
            func_L03_004197C8(vars->target, &point);
            if (func_L03_00419BD8(vars->area_id, mob->position, &point)) {
                qcopy(state + 0x340, &point);
                func_002A7750(object, 12, 3);
                if (mob->animation != 2) func_002A7470(object, 2, 0, 10);
            } else vars->target = 0;
        } else if (mob->state != 13) {
            func_002A7750(object, 4, 1);
            if (mob->animation != 0) func_002A7470(object, 0, 0, 10);
        }
        break;
    case 6:
        if (mob->type != 0x940) return;
        vars->command_cooldown = 30;
        if (mob->mode != 4) {
            vars->target = func_L03_003C5128(object);
            if (!vars->target) return;
            func_002A7750(object, 14, 4);
            if (mob->animation != 2) func_002A7470(object, 2, 0, 10);
            func_L03_003CAAF0(vars->target, &point, &first);
            if (func_L03_00419BD8(vars->area_id, mob->position, &point))
                qcopy(state + 0x340, &point);
            else qcopy(state + 0x340, &first);
        } else if (mob->state == 14) {
            func_002A7750(object, 4, 1);
            if (mob->animation) func_002A7470(object, 0, 0, 20);
        } else if (mob->state == 16 && !func_L03_003C5CE8(object)) func_L03_003C5EE8(object);
        break;
    case 5:
        if (mob->type != 0x93C) return;
        if (mob->mode != 5) {
            vars->target = func_L03_003C52D0(object);
            if (!vars->target) return;
            func_002A7750(object, 18, 5);
            if (mob->animation != 2) func_002A7470(object, 2, 0, 10);
            vars->command_cooldown = 30;
            func_L03_003CA148(vars->target, mob->position, state + 0x340);
            return;
        }
        if (mob->state != 19) {
            func_L00_003294F0(vars->target, 0);
            vars->target = 0; vars->command_cooldown = 30;
            func_002A7750(object, 4, 1);
            if (mob->animation) func_002A7470(object, 0, 0, 20);
        }
        break;
    case 7:
        if (mob->type != 0xA59) return;
        if (mob->mode != 6) {
            vars->target = func_L03_003C5488(object);
            if (!vars->target) return;
            func_002A7750(object, 20, 6);
            if (mob->animation != 2) func_002A7470(object, 2, 0, 10);
            target = vars->target; vars->command_cooldown = 30;
            switch (*(s16 *)(target + 0xAA)) {
            case 0xB10: func_L03_0038A9D0(target, state + 0x340); break;
            case 0xF4D: func_L03_003CA230(target, state + 0x340); break;
            }
        } else if (mob->state != 21) {
            func_L00_003294F0(vars->target, 0);
            vars->target = 0; vars->command_cooldown = 30;
            func_002A7750(object, 4, 1);
            if (mob->animation) func_002A7470(object, 0, 0, 20);
        }
        break;
    case 8:
        if (mob->type == 0x964) {
            if (mob->mode != 1) func_002A7750(object, 4, 1);
        } else func_002A7750(object, 6, 1);
        break;
    }
}
