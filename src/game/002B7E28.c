#include "include_asm.h"
#include "common.h"

extern char *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern int gfx_pack_color_floats(float, float, float, float);
extern unsigned char *D_001F2574, *D_001F25A4;
extern void part_kill(char *);
extern void FastVecAdd(char *, char *, char *);

#ifndef RAC2_T_REC_F4EC78016
#define RAC2_T_REC_F4EC78016
typedef struct Rec_F4ec78016 {
    int f0;
    unsigned char pad4[6];
    short h10;
    unsigned char pad12[20];
    int f32;
} Rec_F4ec78016;
#endif

#ifndef RAC2_T_SLOT_F4EC78016
#define RAC2_T_SLOT_F4EC78016
typedef struct Slot_F4ec78016 {
    int f0;
    unsigned char pad4[108];
} Slot_F4ec78016;
#endif

#ifndef RAC2_T_GLOBALS_F4EC78016
#define RAC2_T_GLOBALS_F4EC78016
typedef struct Globals_F4ec78016 {
    unsigned char pad0[108];
    short h108;
    short h110;
    short h112;
    unsigned char pad114[18];
    int f132;
} Globals_F4ec78016;
#endif

extern Slot_F4ec78016 D_00188660_1[];

extern Globals_F4ec78016 D_001A63A8_4[];

extern void snd_play_stream_by_id(int a, int b, int c, int d);

extern float Fe617c30b_FUN_00283CE0(int a);

extern void Fe617c30b_FUN_00282D30(char *p, char *q, float f);

extern void Fe617c30b_FUN_00282CC0(char *p, char *q, char *r);

extern int Fe617c30b_FUN_002A9568(int a, int b, float f);

extern int Fe617c30b_FUN_00282978(char *p);

extern void Fe617c30b_FUN_002B9180(char *p);

extern int Fb77d67f1_FUN_00282948(char *p);

extern void Fb77d67f1_FUN_002B9180(char *p);

extern int func_00282978_4(char *p);

extern void func_002B9180_8(char *p);

extern int func_00283CF0_4(float f);

extern void func_00282CC0_14(char *a, char *b, char *c);

extern void func_00282D30_14(char *a, char *b, float f);

extern int Fd1c348f5_FUN_00282978(char *p);

extern int Fd1c348f5_FUN_00283CF0(float v);

extern void Fd1c348f5_FUN_002B9180(char *p);

extern int F3c007b59_FUN_00282978(void *p);

extern void F3c007b59_FUN_002B9180(void *p);

extern unsigned int F3c007b59_FUN_00283CF0(float x);

#ifndef RAC2_T_OBJ_F3C007B59
#define RAC2_T_OBJ_F3C007B59
typedef struct {
    unsigned char pad0[4];
    unsigned int w04;
    unsigned char c08;
    unsigned char c09;
    unsigned char c10;
    unsigned char c11;
    float f12;
    unsigned char pad16[8];
    float f24;
    unsigned char pad28[4];
    float f36;
    float f40;
    float f44;
} OBJ_F3c007b59;
#endif

extern void func_00282CC0_8(void *, void *, void *);

extern s32 math_fast_float_d(void *);

extern void func_002B9180_4(void *);

extern int Fc10c1216_FUN_00282978(char *);

extern void Fc10c1216_FUN_002B9180(char *);

extern int Fc10c1216_FUN_00283CF0(float);

extern void Fc10c1216_FUN_00282CC0(char *, char *, char *);

extern void snd_start_music_stream(s32, s32, s32);

extern short D_001A63D4;

#define NOT_SDA __attribute__((section(".data")))

extern short r1_D_001517F0 NOT_SDA;

extern void STUB_printf(const char *, ...);
extern char D_001AA220[];

typedef struct {
    char pad00[0x2C];
    short state;
    char pad2E[2];
    int value;
    int quarter;
} FileLoadVoiceState_002B8048;
extern FileLoadVoiceState_002B8048 g_fileLoadVoiceState;

typedef struct {
    char reserved[0x18E];
    short active;
    int value;
} State_2B8518;

extern State_2B8518 g_pad_state;

typedef int TI __attribute__((mode(TI)));

extern float coll_get_heightmap_height(TI *pos);
extern int g_current_map_index MACRO_ADDR;
extern float D_001B1DC0[] MACRO_ADDR;

extern unsigned char *D_001F2544;

extern void vec_transform_or_copy(char *, char *);

/* func_002BB838 uses the profile in 002BB838-qcopy.c. */

extern int FastTweenColor(int, int, float);
extern unsigned char *D_001F2560;


/* Stores the incoming handle into the record's first word and, for a non-negative index, into the next slot of a 112-byte-stride table, then either bumps a state short from 1 to 2 or passes three shorts and one word of a global block to a helper. */
/* Called when a loading request gets its result. It stores the result in the request and moves the request on to its next step. */
void request_store_result_and_advance(void *result, long requestAddr)
{
    Rec_F4ec78016 *request = (Rec_F4ec78016 *)requestAddr;
    Slot_F4ec78016 *slot;
    int slotIndex;

    if (request == 0)
        return;
    request->f0 = (int)result;
    slotIndex = request->f32;
    if (slotIndex >= 0) {
        slot = D_00188660_1 + slotIndex;
        *(int *)((char *)slot + 112) = (int)result;
    }
    if (result != 0) {
        if (request->h10 == 1)
            request->h10 = 2;
    } else {
        snd_play_stream_by_id(D_001A63A8_4->h108, D_001A63A8_4->h112, D_001A63A8_4->f132, D_001A63A8_4->h110);
    }
}

/* Called when a loading request gets its result. It stores the result and moves the request on to its next step. */
void request_store_result_and_advance_alt(s32 result, long requestAddr)
{
    s32 request = (s32)requestAddr;
    if (request == 0)
        return;
    *(s32 *)request = result;
    if (result != 0) {
        if (*(short *)(request + 10) == 1)
            *(short *)(request + 10) = 2;
    } else {
        u8 *globals = (u8 *)D_001A63A8_4;
        snd_start_music_stream(*(short *)(globals + 0x48),
                      *(short *)(globals + 0x4C),
                      *(short *)(globals + 0x4A));
    }
}

/* Called when a request gets its result. A good result moves the request to state 4, and a zero result resets it. */
void request_store_result_move_to_done(int result, long requestAddr)
{
    short *request = (short *)(int)requestAddr;
    short oldState;
    if (request != 0) {
        *(int *)request = result;
        if (result != 0) {
            oldState = request[5];
            if (oldState == 1) {
                request[5] = 4;
                if (request[8] != 0) D_001A63D4 = oldState;
            }
        } else {
            request[5] = 0;
        }
    }
}

/* rac1-decomp src/game/stream.c: func_00217970 */
/* Called when a request gets its result. A pending request in state 9 is moved to state 4, and a zero result resets it. */
void request_resume_pending_result(int result, long requestAddr) {
    short *request = (short *)(int)requestAddr;
    if (request != 0) {
        if (result < 0) {
            *(int *)request = result;
        }
        if (result != 0) {
            if (request[5] == 9) {
                request[5] = 4;
                if (request[8] != 0) {
                    r1_D_001517F0 = 1;
                }
            }
        } else {
            request[5] = 0;
        }
    }
}

/* Called when a request gets its result. A request in state 1 moves to state 8, and a zero result resets it. */
void request_store_result_move_to_end(int result, long requestAddr) {
    short *request = (short *)(int)requestAddr;

    if (request != 0) {
        *(int *)request = result;
        if (result != 0) {
            if (request[5] == 1) {
                request[5] = 8;
            }
        } else {
            request[5] = 0;
        }
    }
}

/* Stores the result into a request that is still waiting. Prints an error if the request already had a result. */
void request_store_result_once(int value, long address)
{
    char *request = (char *)(int)address;
    if (request == 0)
        return;
    if (*(unsigned int *)request != 0xFFFFFFFFU) {
        STUB_printf(D_001AA220);
        return;
    }
    *(int *)request = value;
    if (value == 0)
        *(short *)(request + 10) = 7;
}

/* Called when a streamed file has loaded. Remembers the result and its quarter value for the file voice state. */
void music_remaining_time_callback(int value, long address)
{
    char *request = (char *)(int)address;
    int result = value;
    if (request == 0)
        return;
    *(int *)(request + 0x18) = result;
    if (*(short *)(request + 0x10) == 0)
        return;
    {
        FileLoadVoiceState_002B8048 *voice = &g_fileLoadVoiceState;
        if (voice->state != 1)
            return;
        if (result == 0)
            return;
        voice->state = 2;
        voice->value = *(int *)(request + 0x18);
        voice->quarter = *(int *)(request + 0x18) / 4;
    }
}

/* func_002B8108 is in 002B7E28-g8.c. */

/* Clears the active flag and value of the first controller port state. */
void pad_clear_port_state(void) {
    g_pad_state.active = 0;
    g_pad_state.value = 0;
}

/* func_002B85F8 is in 002B7E28-g8.c. */

/* Clears all the saved input values for a controller. */
void ClearPadInput(u8 *pad) {
 s32 *slots=(s32 *)(pad+0x140);s32 remaining=15;
 *(s32 *)(pad+0x1b0)=0;*(volatile s32 *)(pad+0x1d4)=1;
 *(volatile s32 *)(pad+0x1a0)=0;*(volatile s32 *)(pad+0x1a4)=0;*(volatile s32 *)(pad+0x1a8)=0;
 *(volatile s32 *)(pad+0x1d0)=1;*(volatile s32 *)(pad+0x1b4)=0;*(volatile s32 *)(pad+0x1b8)=0;
 *(volatile s32 *)(pad+0x1c0)=0;*(volatile s32 *)(pad+0x1c4)=0;*(volatile s32 *)(pad+0x1c8)=0;*(volatile s32 *)(pad+0x1d8)=0;
 do { slots[-16]=0;remaining--;slots[0]=0;slots++; }while(remaining>=0);
}


/* Updates both controller ports. */
void pad_poll_ports(void) {
    extern void poll_pad_device_state(void *);
    extern State_2B8518 D_00138500;
    poll_pad_device_state(&g_pad_state);
    poll_pad_device_state(&D_00138500);
}

/* Original assembly: a `j` with a trapping `addi $a1,$zero,0` in its delay slot; the compiler emits only addiu. */
/* Gets a free particle of the given kind from the particle pool. */
ASM_FUNC("asm/game", func_002B9030);

ASM_FUNC("asm/game", func_002B9038);

/* Original assembly: RAC1 overlays/shared/particle_create_kill.c, func_L00_002688A8. */
/* Removes a particle and gives its slot back to the pool. */
ASM_FUNC("asm/game", func_002B9180);

/* Original assembly: lqc2/qmtc2/vitof VU0 ops and trapping addi; the compiler cannot emit them. */
/* Updates a particle with the vector unit, moving it by its velocity. */
ASM_FUNC("asm/game", func_002B9288);

/* Original assembly: `lw; nop; jr $v0` keeps a load-delay nop before an indirect tail jump; cc1 never emits the nop and has no indirect sibling call (MATCHING-BLOCKERS 4). */
/* Jumps to the update function for a particle kind. */
ASM_FUNC("asm/game", func_002B9380);

/* Original assembly: RAC1 game/render/partproc.c, func_00218A80; $ra saved at $gp+0x2DB8, $at as a working register and trapping add/addi. */
/* Updates every live particle once per frame. */
ASM_FUNC("asm/game", func_002B9390);

/* Draws all the live particles. */
ASM_FUNC("asm/game", func_002B9420);

/* Original assembly: qmfc2 VU0 op and trapping add/addi; the compiler cannot emit them. */
/* Processes a batch of particles with the vector unit. */
ASM_FUNC("asm/game", func_002BA048);

/* Moves a falling particle and removes it when it sinks below its floor or leaves the map. */
void part_update_falling(char *particle)
{
    float *fields = (float *)particle;
    float *motion = fields + 0xC;
    float floorHeight = motion[3];
    float step[4] __attribute__((aligned(16)));
    TI pos1, pos2;
    int oldX, oldY;
    float groundHeight;

    if (g_current_map_index == 15) {
        if (fields[6] < floorHeight) {
            part_kill(particle);
            return;
        }
    } else if (fields[6] < floorHeight || fields[4] < 0.0f || fields[5] < 0.0f || fields[4] > 1024.0f || fields[5] > 1024.0f) {
        part_kill(particle);
        return;
    }
    oldX = (int)fields[8];
    oldY = (int)fields[9];
    FastVecAdd((char *)step, (char *)motion, (char *)D_001B1DC0);
    FastVecAdd((char *)(fields + 8), (char *)(fields + 8), (char *)step);
    FastVecAdd((char *)(fields + 4), (char *)(fields + 4), (char *)step);
    if (*(short *)(particle + 0xA) != 2 && (oldX != (int)fields[8] || oldY != (int)fields[9])) {
        pos1 = *(TI *)(fields + 8);
        groundHeight = coll_get_heightmap_height(&pos1);
        if (groundHeight >= D_001B1DC0[4]) {
            pos2 = *(TI *)(fields + 8);
            floorHeight = coll_get_heightmap_height(&pos2);
        } else {
            floorHeight = D_001B1DC0[4];
        }
        if (fields[10] < floorHeight) {
            part_kill(particle);
            return;
        }
    }
    motion[2] -= 0.0027222223f;
    motion[3] = floorHeight + D_001B1DC0[2];
}

/* Fades a particle in and out over its short life and steps through its texture frames. */
void part_update_fading_texture(char *particle)
{
    int alpha = *(short *)(particle + 0xA) * *(int *)(particle + 0x20) / 27;
    *(unsigned int *)(particle + 4) = (*(unsigned int *)(particle + 4) & 0xFFFFFFu) | (alpha << 24);
    if (func_00282978_4(particle + 0xA)) {
        func_002B9180_8(particle);
    } else {
        particle[2] = D_001F2544[(27 - *(short *)(particle + 0xA)) / 3];
    }
}

/* func_002BABE8 is in 002B7E28-g8.c (its global read uses the retail's one-register
   `lui`/`lw` pair, which only a -G8 unit emits). */

/* Does nothing. This particle kind needs no update. */
void part_update_noop_a(void) {
}

/* func_002BAE50 is matched in its own unit, src/game/002BAE50.c (default flags). */

/* Changes the size of a particle over its life, slows it down, moves it and fades its colour. */
void part_update_scaling(char *particle)
{
    char *motion = particle + 32;
    int totalLife;
    int scaledLife;
    int timeLeft;
    float size;

    totalLife = *(int *)(motion + 28);
    timeLeft = *(short *)(particle + 10);
    scaledLife = *(short *)(motion + 24) * (totalLife - timeLeft) / totalLife + *(short *)(motion + 26);

    size = Fe617c30b_FUN_00283CE0(scaledLife) * 1000.0f;
    *(float *)(particle + 12) = size;
    Fe617c30b_FUN_00282D30(motion, motion, 9.8000001907348632812500e-01f);
    Fe617c30b_FUN_00282CC0(particle + 16, particle + 16, motion);
    *(unsigned char *)(particle + 8) = *(unsigned char *)(particle + 8) + 1;
    size = Fe617c30b_FUN_00283CE0(*(int *)(motion + 28));
    *(int *)(particle + 4) = Fe617c30b_FUN_002A9568(*(int *)(motion + 20), *(int *)(motion + 16),
                               (float)*(short *)(particle + 10) / size);
    if (Fe617c30b_FUN_00282978(particle + 10) != 0)
        Fe617c30b_FUN_002B9180(particle);
}

/* Moves a particle upward, grows it and fades it out at the end of its life. */
void part_update_rising_fade(u8 *particle)
{
    u8 *head = particle;
    u8 *motion = particle + 0x20;

    if (math_fast_float_d((char *)motion) != 0) {
        part_kill((char *)head);
        return;
    }
    {
        u8 *position = head + 0x10;

        vec_transform_or_copy((char *)position, (char *)position);
    }
    *(f32 *)(head + 0xC) = *(f32 *)(head + 0xC) + *(f32 *)(motion + 4);
    if (*(s32 *)(motion) < 6) {
        *(unsigned int *)(head + 4) = (*(unsigned int *)(head + 4) & 0xFFFFFF)
            | ((unsigned int)(*(s32 *)(motion) * 127 / 6) << 24);
    }
}


/* Grows a particle and fades it out at the end of its life. */
void part_update_growing_fade(char *particle)
{
    char *motion = particle + 32;

    if (Fb77d67f1_FUN_00282948(motion) != 0) {
        Fb77d67f1_FUN_002B9180(particle);
        return;
    }
    *(float *)(particle + 12) = *(float *)(particle + 12) + *(float *)(motion + 4);
    if (*(int *)(particle + 32) < 6)
        *(int *)(particle + 4) = (*(int *)(particle + 4) & 0xFFFFFF)
                         | ((*(int *)(particle + 32) * 127 / 6) << 24);
}

/* blends a sub-object into a position, adds a float field, stores an interpolated value in the
   word at +4 and scales the frame count into a byte table at +2 */
/* Moves a particle, blends its colour over its life and steps through its texture frames. */
void part_update_color_blend(char *particle)
{
    char *head = particle;
    char *motion = particle + 32;
    unsigned int color;
    float totalLife;

    Fe617c30b_FUN_00282CC0(head + 16, head + 16, motion);
    if (Fe617c30b_FUN_00282978(head + 10) != 0) {
        Fe617c30b_FUN_002B9180(head);
        return;
    }
    *(float *)(head + 12) = *(float *)(head + 12) + *(float *)(motion + 0x1C);
    totalLife = Fe617c30b_FUN_00283CE0(*(int *)(motion + 0x18));
    color = FastTweenColor(*(int *)(motion + 0x14), *(int *)(motion + 0x10),
                      (float)*(short *)(head + 0xA) / totalLife);
    *(int *)(head + 4) = color;
    if (*(short *)(head + 0xA) < 6) {
        *(int *)(head + 4) = (color & 0xFFFFFF) | (((int)(*(short *)(head + 0xA) * (color >> 24))) / 6 << 24);
    }
    *(unsigned char *)(head + 2) = D_001F2560[((*(int *)(motion + 0x18) - *(short *)(head + 0xA)) * 10) / *(int *)(motion + 0x18)];
}

/* decays a float field by 0.04 with a saturating early-out that consults a helper and returns; otherwise adds 12000 to a second field, nudges a third by 0.0484 while it stays below 0.225, merges two 255-scaled byte lanes into a header word, hands a sub-object to two helpers and decrements a byte counter */
/* Fades a sparkle particle out, makes it glow brighter for a moment and slows it down. */
void part_update_sparkle(char *particle)
{
    char *motion = particle + 32;
    float fadeLeft;
    int blue, alpha;
    int oldColor;

    fadeLeft = *(float *)(motion + 28) + (-0.04f);
    *(float *)(motion + 28) = fadeLeft;
    if (fadeLeft <= 0.0f || func_00282978_4(particle + 10) != 0) {
        func_002B9180_8(particle);
        return;
    }
    *(float *)(particle + 12) = *(float *)(particle + 12) + 12000.0f;
    if (*(float *)(motion + 24) < 0.225f) {
        *(float *)(motion + 24) = *(float *)(motion + 24) + 0.0484f;
    }
    blue = func_00283CF0_4(*(float *)(motion + 24) * 255.0f) & 0xff;
    alpha = func_00283CF0_4(*(float *)(motion + 28) * 255.0f);
    oldColor = *(unsigned short *)(particle + 4);
    *(int *)(particle + 4) = oldColor | (blue << 16) | (alpha << 24);
    func_00282CC0_14(particle + 16, particle + 16, motion);
    func_00282D30_14(motion, motion, 0.9f);
    *(char *)(particle + 8) = *(unsigned char *)(particle + 8) - 1;
}

/* func_002BBCB0 is in 002BBCB0-g8-qcopy.c. */


/* func_002BC508 is in 002BC508-g8.c. */

/* Creates a flashing particle near a point. It spins in a random direction and grows each frame. */
char *part_spawn_flash(char *pos, int spin, int color, float spread, float low, float high, float accel, float size)
{
    char *particle = part_alloc(13);
    char *motion;
    if (particle) {
        qcopy(particle + 16, pos);
        motion = particle + 32;
        *(int *)(particle + 4) = color;
        particle[9] = FloatToInt(4.0f) + 64;
        particle[3] = 0x48;
        *(float *)(particle + 12) = size;
        particle[1] = 0;
        particle[8] = 0;
        particle[2] = D_001F2574[0];
        *(float *)(particle + 16) += math_random_signed_float_range(0.0f, spread);
        *(float *)(particle + 20) += math_random_signed_float_range(0.0f, spread);
        *(float *)(particle + 24) += math_random_signed_float_range(0.0f, spread);
        *(short *)(particle + 10) = 10;
        *(int *)(motion + 4) = 0;
        if (math_random_int_below(2))
            *(int *)(motion + 8) = spin;
        else
            *(int *)(motion + 8) = -spin;
        *(int *)(motion + 20) = color & 0xffffff;
        *(float *)(motion + 12) = math_random_float_range(low, high);
        *(float *)(motion + 16) = accel;
    }
    return particle;
}

/* Spins and grows a flash particle. It flares up, then fades out and is removed. */
void part_update_flash(char *particle)
{
    char *motion = particle + 32;
    int expired;
    int alphaByte;
    float fadeScale;

    *(unsigned char *)(particle + 8) = *(unsigned char *)(particle + 8) + *(unsigned char *)(motion + 8);
    *(float *)(particle + 24) = *(float *)(particle + 24) + *(float *)(motion + 16);
    *(float *)(particle + 12) = *(float *)(particle + 12) * *(float *)(motion + 12);
    if (*(int *)(motion + 4) == 0) {
        expired = Fd1c348f5_FUN_00282978(particle + 10);
        if (expired != 0) {
            *(int *)(motion + 4) = 1;
            *(short *)(particle + 10) = 30;
            *(int *)(particle + 4) = *(int *)(motion + 20) | 0x7f000000;
        } else {
            fadeScale = (float)(10 - *(short *)(particle + 10)) * 9.6000003814697265625000e+00f;
            alphaByte = Fd1c348f5_FUN_00283CF0(fadeScale);
            *(int *)(particle + 4) = ((alphaByte + 32) << 24) | *(int *)(motion + 20);
        }
    } else {
        expired = Fd1c348f5_FUN_00282978(particle + 10);
        if (expired != 0) {
            Fd1c348f5_FUN_002B9180(particle);
        } else {
            fadeScale = (float)*(short *)(particle + 10) * 4.2333333492279052734375e+00f;
            alphaByte = Fd1c348f5_FUN_00283CF0(fadeScale);
            *(int *)(particle + 4) = (alphaByte << 24) | *(int *)(motion + 20);
        }
    }
}

/* func_002BCB00 is defined in 002BCB00-zero-ti-barrier.c. */

/* func_002BCC58 is in 002BCC58-g8.c. */


/* func_002BD0D0 is in 002BD0D0-g8.c. */

/* Does nothing. This particle kind needs no update. */
void part_update_noop_b(void) {
}

/* Makes a particle pulse in brightness while it drifts, then removes it when it has faded. */
void part_update_pulsing(OBJ_F3c007b59 *particle)
{
    float *motion = (float *)((char *)particle + 32);
    float pulse;
    float negated;

    pulse = motion[1] + motion[3] * 1.3000000268220901489258e-02f;
    motion[1] = pulse;
    if (pulse <= 0.0f || F3c007b59_FUN_00282978(&particle->c10) != 0) {
        F3c007b59_FUN_002B9180(particle);
    } else {
        pulse = motion[1];
        if (2.1999999880790710449219e-01f <= pulse) {
            negated = motion[3];
            negated = -negated;
            motion[3] = negated;
            motion[1] = pulse + negated * 1.3000000268220901489258e-02f;
        }
        particle->f12 = particle->f12 + 8.1900000000000000000000e+03f;
        particle->w04 = (particle->w04 & 0xFFFFFFu) |
                 (F3c007b59_FUN_00283CF0(motion[1] * 2.5500000000000000000000e+02f) << 24);
        motion[2] = motion[2] + 1.2000000104308128356934e-02f;
        if (motion[2] > 1.0f)
            motion[2] = motion[2] - 1.0f;
        particle->c08 = (unsigned char)(motion[2] * 2.5500000000000000000000e+02f);
        particle->f24 = particle->f24 - 1.9999999552965164184570e-02f;
    }
}

/* Moves two points of a streak particle along a velocity, fades it and removes it when it is invisible. */
void part_update_streak(char *particle)
{
    char *posA = particle + 16;
    char *posB = particle + 32;
    char *velocity = particle + 48;
    int color;

    FastVecAdd(posA, posA, velocity);
    FastVecAdd(posB, posB, velocity);
    vec_transform_or_copy(posA, posA);
    vec_transform_or_copy(posB, posB);
    color = *(int *)(particle + 4) - (FloatToInt(*(float *)(velocity + 12)) << 24);
    *(int *)(particle + 4) = color;
    *(int *)(particle + 12) = color;
    if (color < 0)
        part_kill(particle);
}

/* func_002BDCE8 uses the qcopy profile in 002BDCE8.c. */

/* func_002BDEB0 is in 002BDEB0.c. */


/* func_002BE278 uses the quadword-copy profile in 002BE278-qcopy.c. */

/* func_002BE400 uses the no-gcse profile in 002BE400.c. */

/* func_002BE7E8 uses the quadword-copy profile in 002BE7E8-qcopy.c. */

/* calls a three-argument helper on the sub-objects at +16 and +32, then packs ((v[6]*v[4])/v[5])<<24 into the low 24 bits of the word at +4 and conditionally calls a second helper on +48 before a final call. */
/* Moves a particle and fades its colour in step with its timer. Removes it when it is done. */
void part_update_color_ramp(s32 *particle) {
    s32 *motion = (s32 *)((char *)particle + 32);
    s32 *position = (s32 *)((char *)particle + 16);
    func_00282CC0_8(position, position, motion);
    particle[1] = (particle[1] & 0x00ffffff) + ((motion[6] * motion[4] / motion[5]) << 24);
    if (math_fast_float_d((s32 *)((char *)particle + 48)) != 0) {
        func_002B9180_4(particle);
    }
}

/* Makes a glowing particle pulse and cycle its colour while it drifts, then removes it when it has faded. */
void part_update_glow_pulse(char *particle)
{
    float *motion = (float *)(particle + 32);

    if (0.0f < motion[3])
        motion[1] = motion[1] + motion[3] * 0.007f;
    else if (0.03f < motion[1])
        motion[1] = motion[1] + motion[3] * 0.007f;
    else {
        motion[1] = motion[1] + motion[3] * 1.4000000664964318275452e-03f;
        *(float *)(particle + 12) = *(float *)(particle + 12) + 5460.0f;
    }

    if (motion[1] <= 0.0244f || Fc10c1216_FUN_00282978(particle + 10) != 0) {
        Fc10c1216_FUN_002B9180(particle);
        return;
    }

    if (motion[1] >= 0.12f) {
        motion[3] = -motion[3];
        motion[1] = motion[1] + motion[3] * 0.007f;
    }
    *(float *)(particle + 12) = *(float *)(particle + 12) + 5460.0f;
    *(int *)(particle + 4) = (*(int *)(particle + 4) & 0xffffff) | (Fc10c1216_FUN_00283CF0(motion[1] * 255.0f) << 24);
    motion[2] = motion[2] + 0.002f;
    if (motion[2] > 1.0f)
        motion[2] = motion[2] - 1.0f;
    *(char *)(particle + 8) = (char)(motion[2] * 255.0f);
    Fc10c1216_FUN_00282CC0(particle + 16, particle + 16, (char *)(motion + 4));
}

/* func_002BEBC0 is in 002BEBC0-hazard-labels.c (retail keeps a branch label on its
   mtc1 hazard nop, which only a -frac2-hazard-labels unit reproduces). */

/* func_002BEE70 is in 002BEE70-g.c (it needs -g for its line notes' pre-division nops). */

/* Makes a glow particle follow its parent object and pulse. Removes it when the parent is gone. */
void part_update_following_glow(char *particle)
{
    float *motion;
    char *owner;
    float pulse;

    if (particle == 0)
        return;
    motion = (float *)(particle + 0x20);
    owner = *(char **)motion;
    if (owner == 0 || (*(unsigned char *)(owner + 0x20) & 0xF0) == 0xF0) {
        part_kill(particle);
        return;
    }
    qcopy(particle + 0x10, owner + 0x10);
    pulse = motion[1] + motion[2];
    motion[1] = pulse;
    if (pulse < 0.0f) {
        part_kill(particle);
        return;
    }
    if (pulse > 0.6f) {
        motion[2] = -motion[2];
        motion[1] = pulse + motion[2];
    }
    motion[4] += -0.0174f;
    if (motion[4] < 0.0f)
        motion[4] = 0.0f;
    motion[5] += -0.01446f;
    if (motion[5] < 0.0f)
        motion[5] = 0.0f;
    motion[6] += -0.0015f;
    if (motion[6] < 0.0f)
        motion[6] = 0.0f;
    *(int *)(particle + 4) = gfx_pack_color_floats(motion[4], motion[5], motion[6], motion[1]);
    motion[3] += 0.0011f;
    if (motion[3] > 1.0f)
        motion[3] -= 1.0f;
    *(char *)(particle + 8) = FloatToInt(motion[3] * 255.0f);
    *(float *)(particle + 0xC) = (*(float **)(particle + 0x20))[0xB] * 3000000.0f + 50000.0f;
}
