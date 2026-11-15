#include "include_asm.h"

#include "common.h"
extern void moby_set_state(int, int, int);
typedef int TI128 __attribute__((mode(TI)));
typedef union {
    TI128 q;
    float f[4];
} Vec4;
extern void FastVecSub(void *, void *, void *);
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int PlayMobySound(int, int, char *);
extern int flag_set_first_pending(char *);
extern int flag_is_third_pending_set(char *);
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int hero_is_current_selected_id(char *);
extern float math_fabs(float);
extern int snd_is_voice_playing_for_owner(char *, int);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int moby_is_hit_by_player_or_aim(char *);
extern void mat_combine_and_store(void *, void *, void *, void *);
typedef struct { char pad[0x74]; unsigned char active; char pad2[0x13]; char *owner; } SoundSlot;
extern SoundSlot g_sound_state[];
extern float D_00189EA4;

void func_PAL_L20_0044CAA8(char *arg0) {
    Vec4 pos, rot, delta;
    char *state = *(char **)(arg0 + 0x68);
    qcopy(&pos, arg0+0x10);
    qcopy(&rot, arg0+0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        *(int *)(state+0x5C) |= 1;
        {
            float target=*(float *)(state+0x60);
            float start=*(float *)(arg0+0x14);
            *(float *)(state+0x6C) = 0.0014000001f;
            *(float *)(state+0x64) = start;
            *(float *)(state+0x70) = (start+target)*0.5f;
        }
        if (*(int *)(state+0x78) == 0) *(int *)(state+0x74)=0;
        else *(int *)(state+0x74)=1;
        moby_set_state(arg0,1,-1);
        break;
    case 1:
        if (flag_is_third_pending_set(arg0)) {
            if (hero_is_current_selected_id(arg0) || (*(float *)(arg0+0x14)-*(float *)(state+0x70))*(D_00189EA4-*(float *)(state+0x70)) < 0.0f) {
                if (*(int *)(state+0x74)==0) moby_set_state(arg0,2,-1);
                else moby_set_state(arg0,3,-1);
                if (!snd_is_voice_playing_for_owner(arg0,*(int *)(state+0x7C))) *(int *)(state+0x7C)=PlayMobySound(0,4,arg0);
            }
        }
        break;
    case 2:
        if (flag_set_first_pending(arg0)) *(int *)(state+0x68)=0;
        if (math_fabs(*(float *)(state+0x60)-*(float *)(arg0+0x14)) < 0.03f) {
            int i=*(int *)(state+0x7C);
            if (i != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)g_sound_state+i*0x70);
                if (slot->owner==arg0 && slot->active) snd_stop_voice(i);
            }
            *(int *)(state+0x7C)=-1;
            if (!moby_is_hit_by_player_or_aim(arg0)) {
                *(int *)(state+0x74)=1;
                *(float *)(arg0+0x14)=*(float *)(state+0x60);
                moby_set_state(arg0,1,-1);
            }
        } else math_step_value_toward_target(arg0+0x14,state+0x68,*(float *)(state+0x60),*(float *)(state+0x6C),*(float *)(state+0x6C),0.24000001f);
        break;
    case 3:
        if (flag_set_first_pending(arg0)) *(int *)(state+0x68)=0;
        if (math_fabs(*(float *)(arg0+0x14)-*(float *)(state+0x64)) < 0.03f) {
            int i=*(int *)(state+0x7C);
            if (i != -1) {
                SoundSlot *slot=(SoundSlot *)((char *)g_sound_state+i*0x70);
                if (slot->owner==arg0 && slot->active) snd_stop_voice(i);
            }
            *(int *)(state+0x7C)=-1;
            if (!moby_is_hit_by_player_or_aim(arg0)) {
                *(int *)(state+0x74)=0;
                *(float *)(arg0+0x14)=*(float *)(state+0x64);
                moby_set_state(arg0,1,-1);
            }
        } else math_step_value_toward_target(arg0+0x14,state+0x68,*(float *)(state+0x64),*(float *)(state+0x6C),*(float *)(state+0x6C),0.24000001f);
        break;
    }
    FastVecSub(&delta,arg0+0x10,&pos);
    mat_combine_and_store(state+0x20,&delta,&rot,arg0+0xF0);
}


extern int math_fast_float_d(void *);
extern void moby_set_flag_bit(char *, int);
extern void func_PAL_L20_0044D1C8(char *);

/* func_PAL_L20_0044CEB0, the PAL copy of func_L20_004473B0: the same C, with the four timers at
   0x74-0x80 scaled to 50 Hz when the object starts (case 0). */
void func_PAL_L20_0044CEB0(char *arg0) {
    char *state;
    TI128 pos, rot, delta;
    float accel;

    state = *(char **)(arg0 + 0x68);
    qcopy(&pos, arg0 + 0x10);
    qcopy(&rot, arg0 + 0xF0);
    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        qcopy(state + 0x60, arg0 + 0x10);
        *(int *)(state + 0x5C) |= 1;
        *(int *)(state + 0x74) = (*(int *)(state + 0x74) * 5 + 2) / 6;
        *(int *)(state + 0x78) = (*(int *)(state + 0x78) * 5 + 2) / 6;
        *(int *)(state + 0x7C) = (*(int *)(state + 0x7C) * 5 + 2) / 6;
        *(int *)(state + 0x80) = (*(int *)(state + 0x80) * 5 + 2) / 6;
        moby_set_flag_bit(arg0, 1);
        moby_set_state((int)arg0, 4, -1);
        break;
    case 1:
        if (flag_set_first_pending(arg0) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x74);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)arg0, 2, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68) + speed;
            accel = (speed * 4.0f) / (float)(duration * duration);
            math_step_value_toward_target(arg0 + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 2:
        if (flag_set_first_pending(arg0) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x78);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)arg0, 3, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(arg0) != 0) {
            *(int *)(state + 0x88) = 0;
            *(int *)(state + 0x84) = *(int *)(state + 0x7C);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)arg0, 4, -1);
        }
        {
            int duration = *(int *)(state + 0x74);
            float speed = *(float *)(state + 0x70);
            float start = *(float *)(state + 0x68);
            accel = (speed * 4.0f) / (float)(duration * duration);
            math_step_value_toward_target(arg0 + 0x18, state + 0x88, start, accel,
                          accel, accel * (float)duration);
        }
        break;
    case 4:
        if (flag_set_first_pending(arg0) != 0) {
            *(int *)(state + 0x84) = *(int *)(state + 0x80);
        }
        if (math_fast_float_d(state + 0x84) != 0) {
            moby_set_state((int)arg0, 1, -1);
        }
        break;
    }
    if (flag_is_third_pending_set(arg0) == 0) {
        if (0.0f < *(float *)(state + 0x8C)) {
            func_PAL_L20_0044D1C8(arg0);
            *(float *)(state + 0x8C) = -1000.0f;
        }
    }
    FastVecSub(&delta, arg0 + 0x10, &pos);
    mat_combine_and_store(state + 0x20, &delta, &rot, arg0 + 0xF0);
}


