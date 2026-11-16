#include "include_asm.h"

#include "common.h"
extern int g_beam_slot_angle_x[] MACRO_ADDR;
extern int g_beam_slot_angle_y[] MACRO_ADDR;
extern int g_beam_slot_angle_z[] MACRO_ADDR;
extern int g_beam_slot_light_handle[] MACRO_ADDR;
extern int g_beam_slot_light_handle_alt[] MACRO_ADDR;
extern int g_beam_slot_third_value[] MACRO_ADDR;
extern int g_beam_slot_flag[] MACRO_ADDR;
extern float g_beam_slot_uv_scroll[16] MACRO_ADDR;
extern int g_beam_slot_state_2[16] MACRO_ADDR;
extern unsigned char *g_sound_slot_ptrs[16][2];
extern void gfx_queue_draw_callback(void *, void *);
extern void beam_slot_clear_by_index(int);
extern void UpdateBeamLinkStrips_pal(void *, int);
extern void DrawBeamLinks_pal(char *);
typedef struct DobboMoby DobboMoby;
typedef struct {
    float direction[4];
    float velocity[4];
    DobboMoby *owner;
    DobboMoby *partner;
    float radius;
    float f2c;
    int timer;
    float max_distance;
    float duration_f;
    int hit_timer;
} DobboLinkState;
typedef struct {
    char pad00[0x24];
    float scale;
} DobboMobyClass;
struct DobboMoby {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[2];
    unsigned char alpha;
    DobboMobyClass *cls;
    char pad28[4];
    float scale;
    unsigned char f30;
    unsigned char f31;
    unsigned short f32;
    unsigned short flags;
    char pad36[0x43 - 0x36];
    unsigned char f43;
    char pad44[4];
    float f48;
    char pad4C[0x60 - 0x4C];
    unsigned char f60;
    char pad61[0x68 - 0x61];
    DobboLinkState *data;
    char pad6C[0xAA - 0x6C];
    short type;
    char padAC[0xBC - 0xAC];
    unsigned char f_bc;
    char padBD[0xF0 - 0xBD];
    float rotation[3];
};

/* func_L09_003F69A0 is defined in L09_002F8BA0-g8.c (it reads a global through $gp). */

/* func_L09_003F6AB8 lives in the -g8.c brother: it loads a global through $gp. */

/* func_L09_003F6B28 is defined in L09_002F8BA0-beam-g8.c. */

/* Steps the beam-link slot table once per frame. State 0 clears all sixteen slots. State 1 walks
   them: a slot whose first moby has been destroyed is released, a slot in state 4 is handed to
   func_L09_003FB860, and any other live slot is handed to func_PAL_L09_004005A8 and moves to state 4.
   If any slot was handed over, func_PAL_L09_00400B48 is queued on the moby to draw the links. */
void UpdateBeamLinkSlots_pal(DobboMoby *moby)
{
    int i, count;
    int clearIndex;

    switch (moby->state) {
    case 0:
        for (clearIndex = 0; clearIndex < 16; clearIndex++) {
            g_beam_slot_state_2[clearIndex] = 0;
            g_sound_slot_ptrs[clearIndex][0] = 0;
            g_sound_slot_ptrs[clearIndex][1] = 0;
        }
        moby->state = 1;
        moby->f30 = 255;
        break;
    case 1:
        count = 0;
        for (i = 0; i < 16; i++) {
            if (g_beam_slot_state_2[i] == 1) {
                if ((signed char)g_sound_slot_ptrs[i][0][0x20] < 0) {
                    g_sound_slot_ptrs[i][0] = 0;
                    g_beam_slot_state_2[i] = 0;
                    g_sound_slot_ptrs[i][1] = 0;
                }
            } else if (g_beam_slot_state_2[i] == 4) {
                beam_slot_clear_by_index(i);
            } else if (g_beam_slot_state_2[i]) {
                count++;
                UpdateBeamLinkStrips_pal(g_sound_slot_ptrs[i][0], i);
                g_beam_slot_state_2[i] = 4;
            }
        }
        if (count)
            gfx_queue_draw_callback(DrawBeamLinks_pal, moby);
        break;
    }
}

