/* func_PAL_L11_0043E660, the PAL copy of func_L11_004390D0: the same C, where expr 0.016666668f becomes 0.020000001f; expr 0.0055555557f becomes 0.008f; rename func_3739C0 becomes func_002E59F8. */
#include "common.h"
extern void func_32E480(char *, char *, int, float, float, float, int, int, int);
/* A path stores its point count in a 16-byte header, followed by vectors. */
struct RotorPath {
    int count;
    char pad04[12];
    float points[0][4];
};

/* The rotor's state (the object's field 0x68): a 13-point chain, the ten records it drives
   and the path it follows. Only the fields these functions use are named. */
/* A basis vector whose fourth word is cleared as an integer. */
/* A rotor moby, and each 256-byte record of the level's table has the same layout. */
extern struct RotorPath *g_path_l11_table[];
extern char g_sound_state[];
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, char *);
extern float IntToFloat(int);
extern float math_lerp_float(float, float, float);
extern f32 ApproachValue(float *, float, float);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);

/* func_L11_00432628 is defined in L11_00432628-dust.c. */

/* func_L11_00434580 lives in L11_00434580-g-g8.c. */

/* func_L11_00434580 is defined in L11_00432628-g8.c. */

/* Spawns a class 0xD1B moby: its position is the first vector of its own state, which then
   takes the vectors at a (at +0x00) and b (at +0x20) and the float f (at +0x3C). */
/* Hands two reads of the state's quadword to the two measured stage helpers. */
extern char g_hero_l11_position[];
extern void FastVecSub(void *, const void *, const void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
/* Stops the object's sound if its slot still belongs to it, then forgets the slot. */

/* Five-stage mover driven by the parent's state byte: when the parent reaches 2 it starts its
   sound and moves out along its +0xE0 direction over half a turn (pi/120 a frame); when the
   parent leaves 2 it does the same back, only while D_00189EA0 is more than 6 away, and at a
   full turn returns to its saved position and waits again. */
/* func_L11_00435600 is defined in L11_00435600-g8.c. */

/* func_L11_00436350 is defined in L11_00436350-g8.c. */

/* Re-arms the measured stage guard, then clears it. */
/* Same body as func_L02_003F16F0, with this function's own callees. */
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void func_002A05A8(char *);
extern void anim_start_blended(void *, int, int, int);

extern void func_002A05A8(char *);

extern void moby_set_state(void *, int, int);

/* Retires the measured stage-46 record: clears the guard, drops the effect and re-tags the object. */
/* func_L11_00436B78 is defined in L11_00436B78-flags.c. */

/* func_L11_00436F80 is defined in L11_00436F80.c. */

/* func_L11_004375B8 is defined in L11_004375B8.c. */

extern void IntegrateVerletChain(void *obj);
extern void chain_creature_update_segments(void *obj);
extern void chain_creature_update_linked(void *obj);

/* Runs the ten rotors' update, one frame each, and restarts the entry timer. */
/* Walks the ten measured indices, clearing each record selected through 0x330. */
/* Invalidates the measured slot at 0x43 of the 256-byte record indexed by 0x358. */
/* A 16-byte aligned vector, copied as one quadword. */
/* Advances the thirteen chain points one Verlet step: each moves by its damped displacement
   from its old position plus a small downward pull, and the old position takes the point's
   previous value. The damping blends 0.97 to 0.98 with the count at 0x378. */
void IntegrateVerletChain(void *object);

/* func_L11_00437FD0 lives in L11_00437FD0.c. */

/* Lays the thirteen chain points out from the object's position: the step starts as the
   reversed first basis axis, each segment takes its length from the twelve floats at 0x2F0,
   and each old point takes the new point's value. */
/* Builds the measured three-axis basis of the object and hands it to the three slots. */
void chain_creature_turn_to_face(char *obj, char *direction, float a, float b, float c);

/* Record `index` of the level's 256-byte record table. */
/* The record the object's state lists at `i`, and the one it links to. */
/* The same records for stores, with the addition ordered as retail orders it there. */
/* Updates the positions and orthonormal bases of the ten enabled records. */
void chain_creature_update_segments(void *object);

/* Updates the single record selected by the state index at 0x358. */
void chain_creature_update_linked(void *object);

/* func_L11_00438880 lives in L11_00438880-g-g8.c. */

/* Clears the two 16-bit flags at 0x374/0x376 of the object held at 0x68. */
extern void vec_random_direction(float *, float, float);

/* Emits a projectile from the next enabled record, with a fifteen-frame delay. */
/* Chooses the state-dependent path, then finds its nearest point. */
/* Follows the current path, steers toward its next point and releases the sound at the end. */
int chain_creature_follow_path_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    float target[4], direction[4], aim[4], old[4];
    float speed, duration;

    if (!*(int *)(state + 0x324)) {
        if (*(int *)(state + 0x38C) != -1) {
            char *entry = g_sound_state + *(int *)(state + 0x38C) * 0x70;
            if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74))
                snd_stop_voice(*(int *)(state + 0x38C));
        }
        *(int *)(state + 0x38C) = -1;
        return 1;
    }
    {
        char *entry = g_sound_state + *(int *)(state + 0x38C) * 0x70;
        if (*(char **)(entry + 0x88) != object || !*(unsigned char *)(entry + 0x74))
            *(int *)(state + 0x38C) = PlayMobySound(0, 4, object);
    }
    qcopy(target, *(char **)(state + 0x324) + *(short *)(state + 0x370) * 16 + 16);
    speed = IntToFloat(*(short *)(state + 0x378));
    duration = IntToFloat(8);
    speed = math_lerp_float(15.0f, 20.0f, (speed - 2.0f) / duration);
    ApproachValue((float *)(state + 0x32C), speed * (0.020000001f), 0.008f);
    FastVecSub(direction, target, (float *)(object + 0x10));
    vec_scale_to_length((char *)direction, (char *)direction, *(float *)(state + 0x32C));
    FastVecAdd(object + 0x10, object + 0x10, (char *)direction);
    FastVecSub(old, (float *)(state + 0x50), (float *)(object + 0x10));
    vec_scale_to_length((char *)old, (char *)old, 1.0f);
    vec_scale_to_length((char *)direction, (char *)direction, 1.0f);
    if (FastVecDot(direction, old) > 0.707f) {
        qcopy(aim, old);
        chain_creature_turn_to_face(object, (char *)aim, 0.010053098f,
                         0.010053098f, 0.5026549f);
    } else {
        qcopy(aim, direction);
        chain_creature_turn_to_face(object, (char *)aim, 0.010053098f,
                         0.010053098f, 0.5026549f);
    }
    if (fast_vec_dist(object + 0x10, target) < 4.0f)
        (*(short *)(state + 0x370))++;
    if (*(short *)(state + 0x370) < **(int **)(state + 0x324) - 1)
        return 0;
    *(int *)(state + 0x324) = 0;
    if (*(int *)(state + 0x38C) != -1) {
        char *entry = g_sound_state + *(int *)(state + 0x38C) * 0x70;
        if (*(char **)(entry + 0x88) == object && *(unsigned char *)(entry + 0x74))
            snd_stop_voice(*(int *)(state + 0x38C));
    }
    *(int *)(state + 0x38C) = -1;
    return 1;
}

/* func_L11_004393D8 is defined in L11_00432628-g8.c (it reaches D_L11_001B12C4
   through $gp). */

/* func_L11_004395C8: attempt kept in drafts (112 bytes, expected 116). */
/* func_L11_004395C8 is defined in L11_00432628-g8.c (this unit has no $gp access for it). */

/* func_L11_00439640 is defined in L11_00432628-burst-g8.c. */

/* func_L11_00439950 is defined in L11_00432628-reset-g64.c. */

extern void snd_stop_voice(int a);

extern struct RotorPath *g_path_l11_table[];
extern char g_sound_state[];

/* Releases the object's measured slot and clears the six flags of its record. */
/* Picks the measured 3/4 code from the counter at 0x364 of the object at 0x68. */
/* func_L11_00439DD0 is defined in L11_00439DD0-g8.c. */

extern int FloatToInt(float);
extern void drone_kill_with_effects(char *);
extern float fast_vec_dist(void *, void *);
extern char g_hero_l11_position[];

extern void func_32E480(char *p, char *q, int a, float b, float c, float d, int e, int f, int g);

/* Bumps the 16-bit counter at 0x96 while it is under the measured ceiling, then re-arms. */
/* func_L11_0043A680 is defined in L11_0043A680-g8.c. */

/* True when the byte at 0x20 is above the measured small-id range. */
extern void vec_random_direction(float *out, float a, float b);
extern float math_random_float_range(float a, float b);
extern int PlayMobySound(int index, int a1, char *a2);
/* Spawns the object's jitter effect while its flag byte is set, then retires the state. */
void drone_kill_with_effects(char *obj);

/* Places out at src plus dist along the heading from src to out's old position, the heading
   and the distance each jittered at random; z comes from src. */
/* Maps the measured selector onto its small index. */
/* func_L11_0043E090 is defined in L11_0043E090.c. */

/* Maps the measured selector onto its large index. */
/* func_L11_0043E108 is defined in L11_0043E108.c. */
