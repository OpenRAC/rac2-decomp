#include "include_asm.h"

#include "common.h"
extern char g_sound_state[];
typedef struct { char pad[0x33c]; char *object; int active; } Player10608;
extern Player10608 g_hero_state;
extern char D_L09_001B17F8[];
extern char *D_L09_001B294C;
extern int D_L09_001BFE58 NOT_SDA;
extern float D_L09_001B17F4 __attribute__((sda));
extern void STUB_printf(void *, int, int);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern float fast_vec_dist(const void *, const void *);
extern int coll_test_point(void *, int, void *, float);
extern void func_PAL_L09_00415DA0(void *);
extern void func_PAL_L09_00415E28(void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
#define WORD(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define BYTE(p,o) (*(u8 *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef struct { char pad[0x74]; u8 active; char gap[0x13]; char *owner; } SoundSlot;
#define SLOT(i) (D_00188660 + (i)*0x70)
#define SOUND_SLOT(i) ((SoundSlot *)SLOT(i))

/* Moves to the selected waypoint while ridden, then returns to its starting position. */
void func_PAL_L09_00415868(char *object)
{
    float old_position[4] __attribute__((aligned(16)));
    float old_rotation[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *slot;
    char *state = *(char **)(object + 0x68);
    qcopy(old_position, object + 0x10);
    qcopy(old_rotation, object + 0xf0);
    switch (BYTE(object,0x20)) {
    case 0:
        *(Quad *)(state+0x80) = *(Quad *)(object+0x10);
        FLOAT(state,0x64) *= 0.020000001f;
        FLOAT(object,0x2c) *= 1.75f;
        if (WORD(state,0x60) == -1)
            STUB_printf(D_L09_001B17F8, HALF(object,0xaa), HALF(object,0xb2));
        WORD(state,0x6c) = -1;
        moby_set_state(object,1,-1);
        break;
    case 1:
        if (flag_set_first_pending(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    snd_stop_voice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = PlayMobySound(1,4,object);
        if (WORD(state,0x60) != -1 && g_hero_state.object==object && g_hero_state.active)
            moby_set_state(object,2,-1);
        break;
    case 2:
        if (flag_set_first_pending(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    snd_stop_voice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = PlayMobySound(0,4,object);
        FastVecSub(delta,D_L09_001B294C+WORD(state,0x60)*0x80+0x30,object+0x10);
        vec_scale_to_length(delta,delta,FLOAT(state,0x64));
        FastVecAdd(object+0x10,object+0x10,delta);
        if (fast_vec_dist(object+0x10,D_L09_001B294C+WORD(state,0x60)*0x80+0x30)<=0.88f)
            moby_set_state(object,3,-1);
        break;
    case 3:
        if (flag_set_first_pending(object)) {
            if (WORD(state,0x6c) != -1) {
                slot = SLOT(WORD(state,0x6c));
                if (*(char **)(slot+0x88) == object && BYTE(slot,0x74))
                    snd_stop_voice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        slot = SLOT(WORD(state,0x6c));
        if (*(char **)(slot+0x88) != object || !BYTE(slot,0x74))
            WORD(state,0x6c) = PlayMobySound(1,4,object);
        if (g_hero_state.object!=object)
            moby_set_state(object,4,-1);
        break;
    case 4: {
        if (flag_set_first_pending(object)) {
            if (WORD(state,0x6c) != -1) {
                if (SOUND_SLOT(WORD(state,0x6c))->owner == object && SOUND_SLOT(WORD(state,0x6c))->active)
                    snd_stop_voice(WORD(state,0x6c));
            }
            WORD(state,0x6c) = -1;
        }
        if (coll_test_point(object+0x10,0x10,object,D_L09_001B17F4) && D_L09_001BFE58)
            break;
        if (SOUND_SLOT(WORD(state,0x6c))->owner != object || !SOUND_SLOT(WORD(state,0x6c))->active)
            WORD(state,0x6c) = PlayMobySound(0,4,object);
        FastVecSub(delta,state+0x80,object+0x10);
        vec_scale_to_length(delta,delta,FLOAT(state,0x64));
        FastVecAdd(object+0x10,object+0x10,delta);
        if (fast_vec_dist(object+0x10,state+0x80)<=0.88f)
            moby_set_state(object,1,-1);
        break;
    }
    }
    func_PAL_L09_00415DA0(object);
    func_PAL_L09_00415E28(object);
    FastVecSub(delta,object+0x10,old_position);
    mat_combine_and_store(state+0x20,delta,old_rotation,object+0xf0);
}
