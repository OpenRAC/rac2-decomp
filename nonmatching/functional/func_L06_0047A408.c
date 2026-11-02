/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Tier: GPT-6.1 Sol (high effort), task v1356; supersedes v1017's profile.
 * USA v1.01, game -O2 -G0 -ffunction-sections -g -frac2-hazard-labels.
 * Best check.py: 2144/2144 bytes, 0 of 3 places match (06, 12, 13).
 * Requalified on the current pinned compiler in an isolated source unit.
 * The hazard-label option fixes the branch at +0x580 (0047A988 in level 06):
 * its displacement now equals retail's 0x1D instead of the old draft's 0x1E.
 * No other instruction changes against the original draft's current check.
 * First mismatch remains +0x8: retail loads the descriptor table before
 * spilling a0. Rig/follow/snap and focus-copy allocation still differ;
 * follow spills while retail keeps it in s4. Saved one/at_end/ten allocation
 * also differs (retail s0/s1/s2, candidate lacks the separate saved one).
 * Fourteen successful checker compiles plus one allocator diagnostic pair.
 * Typed scalar descriptor indexing and a local table pointer tie the original
 * array/explicit-index expression exactly. A byte-sized at_end and a float-first
 * interleaving of the first vector-scale call also tie the original bytes.
 * -mno-split-addresses fixes the initial load sequence but grows to 2160 bytes
 * and changes other global accesses. Independent hero symbols with reordered
 * rig aliases reach 2160; explicit follow-member accesses and G8/NOT_SDA tie it.
 * On that independent-symbol form, -fno-gcse gives 2152 bytes and
 * -fno-force-mem gives 2136; neither resolves the follow spill. Mixed hero
 * base/subobject addressing gives 2156 bytes. None improves the retained body.
 * All declarations are below. External refs remain unqualified because
 * instruction comparison fails before relocation qualification. No link check
 * was run; the src marker and temporary per-file profile were restored.
 * Next: recover the original camera-object/pointer lifetime model to keep
 * follow resident without retaining a separate hero-focus address. Do not
 * repeat the tied descriptor, boolean or call-interleaving wordings.
 */
#include "common.h"
typedef struct {
    f32 swing; u8 pad04[4]; s32 volume_25faf0; s32 clip_volume; s32 volume_25fa38; s32 path; u8 pad18[8];
    f32 pitch; f32 distance; f32 height; s16 type; s16 timer; f32 offset_scale; s16 keep_unk10; s16 check_yaw;
    f32 lateral_stiffness; f32 lateral_damping; f32 start_lateral_stiffness; f32 start_lateral_damping;
    s16 l_buttons_end; s16 done; s32 clip_volume2; f32 unk50; s16 set_flag1; s16 set_flag0;
} SwingCameraParams;
typedef struct { u8 pad0[0x18]; f32 yaw; SwingCameraParams *params; } CamDesc;
typedef struct { u8 pad0[0x100]; f32 analog[4]; } PadSt;

/* Adapted from OpenRAC/rac1-decomp camera_modes_and_scripts.c (GPL-3.0), volume_camera_swing. */
typedef float CameraVec[4];
typedef struct { float f[4]; } Vec4f;
typedef struct {
 float focus[4], velocity[4]; u8 pad80[0x20]; float look_target[4], eye[4], offset[4], lateral_ease[4], up_ease[4], unkD0[4]; u8 pad100[0x10]; float look_height; u8 pad114[0x28]; float lateral_stiffness, lateral_damping; u8 pad144[0x1c];
} FollowCamBlock;
typedef struct { u8 pad[0x10]; s32 flags; } FollowCamFlags;
typedef struct { u8 pad[0x20]; float unk1F0[4]; float unk200; u8 pad224[0x2c]; } FollowCamSnap;
typedef struct { float unk130[4], unk140[4]; u8 pad180[0xc]; float unk15C, distance; u8 pad194[0x2c]; FollowCamFlags ctl; u8 pad1d4[0x1c]; FollowCamSnap snap; s32 mode; } FollowCamTail;
typedef struct { u8 pad[4]; float look_height, distance, unk2C, unk30, unk34, unk38; u8 pad3c[4]; } FollowCamReset;
typedef struct { float position[4]; u8 pad10[0x10]; FollowCamReset reset; u8 pad40[0x20]; FollowCamBlock follow; FollowCamTail tail; } FollowCamState;
struct UpdateCam { u8 pad0[0x30]; Vec4f pos; u8 pad40[0x30]; void *saved_state; u8 pad74[0x10]; s16 descriptor_index; };
#define FOLLOW_CAM_STATE(cam) ((FollowCamState *)(cam)->saved_state)
extern char *D_L06_001B21C4[];
extern char *D_L06_001B9890;
extern char D_L06_001B9700[];
extern float D_L06_001B9858, D_L06_001B9944;
extern char D_00189E20[];
extern s32 D_00138320[];
extern PadSt D_00138180;
#define pad_held_r D_00138320
#define controller_state D_00138180
extern int func_L00_00424978(void *);
extern void func_L00_00424940(void *);
extern f32 func_00283C80(f32, f32);
extern void func_00282F20(void *, void *, f32);
extern void func_00282D30(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern f32 func_00283CE0(int);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_L00_00424F00(void *, f32, f32);
extern void func_L00_00424C60(void);
extern void func_L00_00424C00(void);
extern void func_L00_00424C28(void);
extern void func_L00_00424A08(s32, f32, f32);
extern void func_L06_00475C10(f32);
extern void func_L00_00424A50(f32, f32);
extern void func_L00_00424A88(s32, f32, f32);
extern void func_L00_00424B20(f32);
extern void func_L00_00424B48(int);
extern void func_L00_00424B70(f32, f32);
extern void func_L00_00424BB8(f32, f32);

extern int func_L06_0047A268(void *);
extern void func_L00_00424B70(f32, f32);
void func_L06_0047A408(char *arg) {
    struct UpdateCam *cam = (struct UpdateCam *)arg;
    CameraVec dir;
    SwingCameraParams *params;
    struct UpdateCam *rec;
    Vec4f *pos;
    FollowCamState *rig;
    FollowCamState *state;
    FollowCamBlock *follow;
    FollowCamTail *tail;
    FollowCamSnap *snap;
    FollowCamReset *reset;
    s32 at_end;
    f32 total;
    f32 swing;
    f32 t;

    params = ((CamDesc *)((cam->descriptor_index << 5) + (s32)D_L06_001B21C4[0]))->params;
    if (params->type == 8 && FOLLOW_CAM_STATE(((struct UpdateCam *)D_L06_001B9890))->tail.mode == 0) {
        return;
    }
    if (params->type == 6 && FOLLOW_CAM_STATE(((struct UpdateCam *)D_L06_001B9890))->tail.mode != 0) {
        return;
    }
    if (func_L06_0047A268((void *)cam) == 0) {
        goto stop;
    }
    if (func_L00_00424978(cam) <= 0) {
        if (params->timer != 0) {
            params->done = 1;
        }
        params->timer = 0;
        return;
    }
    if (params->check_yaw != 0
        && func_00283C80(((CamDesc *)D_L06_001B21C4[0])[cam->descriptor_index].yaw, D_L06_001B9858) >= 1.396263599395752f) {
        goto stop;
    }
    if (params->l_buttons_end != 0 && params->type == 5 && (pad_held_r[0] & 4)) {
stop:
        if (params->timer != 0) {
            params->done = 1;
        }
        params->timer = 0;
        func_L00_00424940(cam);
        return;
    }
    if (params->timer == 0) {
        u8 *g = (u8 *)&D_L06_001B9700;
        params->start_lateral_stiffness = FOLLOW_CAM_STATE(*(struct UpdateCam **)(g + 0x190))->follow.lateral_stiffness;
        params->start_lateral_damping = FOLLOW_CAM_STATE(*(struct UpdateCam **)(g + 0x190))->follow.lateral_damping;
    }
    if (*(s32 *)&params->type == 5) {
        *(s32 *)&params->swing = 0;
        rec = ((struct UpdateCam *)D_L06_001B9890);
        rig = FOLLOW_CAM_STATE(rec);
        tail = &rig->tail;
        state = rig;
        snap = &rig->tail.snap;
        follow = &rig->follow;
        reset = &state->reset;
        func_00282F20(tail->unk130, tail->unk130, params->distance);
        tail->unk15C = params->distance;
        tail->distance = params->height;
        follow->look_height = params->offset_scale;
        qcopy(state->tail.unk140, tail->unk130);
        func_00282D30(dir, D_00189E20 + 0x2C0, -tail->distance);
        pos = &rec->pos;
        func_00282CC0(state->follow.eye, D_00189E20 + 0x80, dir);
        func_00282CC0(pos, state->follow.eye, tail->unk130);
        func_00282D30(dir, D_00189E20 + 0x2C0, -follow->look_height);
        func_00282CC0(state->follow.look_target, D_00189E20 + 0x80, dir);
        qcopy(state->follow.unkD0, state->follow.look_target);
        qcopy(follow->focus, D_00189E20 + 0x80);
        qcopy(state->follow.offset, follow->focus);
        qcopy(state->position, pos);
        qcopy(state->tail.snap.unk1F0, pos);
        snap->unk200 = tail->unk15C - func_00282DF0(tail->unk130);
        *(s32 *)&reset->unk34 = 0;
        reset->look_height = follow->look_height;
        { f32 zero = reset->unk34;
        f32 distance = tail->distance;
        reset->distance = distance;
        reset->unk38 = zero;
        reset->unk30 = zero;
        reset->unk2C = zero; }
    }
    at_end = 0;
    total = func_00283CE0(200);
    params->timer++;
    if (params->type == 10) {
        func_L00_00424C60();
        FOLLOW_CAM_STATE(((struct UpdateCam *)D_L06_001B9890))->tail.mode = 0x14D;
    }
    if (params->type == 11) {
        func_L00_00424C60();
        FOLLOW_CAM_STATE(((struct UpdateCam *)D_L06_001B9890))->tail.mode = 2;
    }
    if (params->type == 2 || params->type == 4) {
        { FollowCamFlags *ctl = &FOLLOW_CAM_STATE(((struct UpdateCam *)D_L06_001B9890))->tail.ctl; ctl->flags |= 3; }
        if (params->timer > 200) {
            at_end = 1;
            params->timer = 200;
        }
        func_L00_00424C00();
    } else if (params->type == 1 || params->type == 7 || params->type == 10 || params->type == 9) {
        PadSt *pad = &controller_state;
        if (pad->analog[0] != 0.0f || pad->analog[1] != 0.0f) {
            params->timer = 200;
        }
        if (params->timer >= 200) {
            at_end = 1;
            if (D_L06_001B9944 > 0.0f) {
                params->timer = 200;
            }
        }
        if (params->timer >= 400) {
            at_end = 0;
            params->timer = 1;
        }
    } else if (params->type == 3) {
        total = func_00283CE0(1);
        if (params->timer > 1) {
            at_end = 1;
            params->timer = 1;
        }
    } else {
        if (params->timer > 200) {
            at_end = 1;
            params->timer = 200;
        }
    }
    dir[0] = func_00283180(((CamDesc *)D_L06_001B21C4[0])[cam->descriptor_index].yaw);
    dir[1] = func_00283198(((CamDesc *)D_L06_001B21C4[0])[cam->descriptor_index].yaw);
    *(s32 *)&dir[2] = 0;
    swing = params->swing * ((params->timer / total) * 0.01745329424738884f);
    if ((params->type != 1 && params->type != 7 && params->type != 9) || at_end == 0) {
        func_L00_00424F00(dir, swing, params->pitch * 0.01745329424738884f);
    }
    if (params->distance != 0.0f) {
        if (params->type == 6 || params->type == 8) {
            func_L00_00424A08(0, params->distance, 0.002f);
            func_L06_00475C10(params->distance + 1.36f);
        } else {
            func_L00_00424A08(0, params->distance, 0.003f);
            func_L00_00424C00();
        }
    }
    if (params->height != 0.0f) {
        if (params->type == 6 || params->type == 8) {
            func_L00_00424A50(params->height, 0.002f);
        } else {
            func_L00_00424A50(params->height, 0.003f);
        }
    }
    if (params->offset_scale != 0.0f) {
        if (params->type == 6 || params->type == 8) {
            func_L00_00424A88(0, params->offset_scale, 0.002f);
        } else {
            func_L00_00424A88(0, params->offset_scale, 0.005f);
        }
    }
    if (params->unk50 != 0.0f) {
        func_L00_00424B20(params->unk50 * 0.01745329424738884f);
    }
    if (params->set_flag1 != 0) {
        { FollowCamFlags *ctl = &FOLLOW_CAM_STATE(((struct UpdateCam *)D_L06_001B9890))->tail.ctl; ctl->flags |= 2; }
    }
    if (params->set_flag0 != 0) {
        { FollowCamFlags *ctl = &FOLLOW_CAM_STATE(((struct UpdateCam *)D_L06_001B9890))->tail.ctl; ctl->flags |= 1; }
    }
    if (params->keep_unk10 == 0) {
        func_L00_00424B48(0);
    }
    if (params->lateral_stiffness != 0.0f || params->lateral_damping != 0.0f) {
        if (params->timer >= 120) {
            func_L00_00424B70(params->lateral_stiffness, params->lateral_damping);
        } else {
            t = params->timer / func_00283CE0(120);
            func_L00_00424B70(
                params->start_lateral_stiffness + (params->lateral_stiffness - params->start_lateral_stiffness) * t,
                params->start_lateral_damping + (params->lateral_damping - params->start_lateral_damping) * t);
        }
    }
    if (params->type == 1 || params->type == 7 || params->type == 10) {
        func_L00_00424C00();
        func_L00_00424C28();
        func_L00_00424BB8(0.01f, 0.2f);
    }
}
