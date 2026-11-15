#include "common.h"

/* Measured partial layouts for the transition's objects and shared contexts. */
typedef struct {
    char pad0[0x20];
    unsigned char status;
    char pad21[0x13];
    unsigned short flags;
    char pad36[0x74];
    short type;
    char padAC[0x54];
} TransitionMoby;

typedef struct {
    TransitionMoby *object;
    char pad4[4];
    int field8;
    char padC[20];
    short mode;
    short slot;
    char pad24[6];
    short active;
    char pad2C[64];
    int field6C;
} TransitionContext;

typedef struct {
    char pad[12];
    int start;
    int end;
} TransitionArchive;

typedef struct {
    char pad[0x6C];
    int start;
    int end;
} TransitionScene;

typedef struct {
    char pad[0x24];
    int state;
    int next;
    char gap[0x40];
    short limit;
    char gap2[4];
    short phase;
} TransitionState;

typedef struct {
    char pad[0x22B5];
    char flag;
    char gap[0x246];
    short mode;
} TransitionGlobals;

extern TransitionContext g_hero_moby_default;
extern TransitionScene g_scene_playback_state;
extern TransitionArchive D_001BAEC0;
extern TransitionState g_music_state;
extern TransitionGlobals g_hero_state;
extern char D_001B1390[] MACRO_ADDR;
extern char D_001B2980[];
extern char D_001B13D0[] MACRO_ADDR;
extern int D_001B22B0;
extern float g_screen_fade;
extern int D_001B15A4 __attribute__((sda));
extern TransitionMoby *D_001B1B60;

extern void mem_clear(void *, int, int);
extern void gfx_select_packet_buffer_setup(void);
extern unsigned int stub_empty_8(int, int);
extern void stub_empty_3(void);
extern void load_parts_set_from_disc(int, int);
extern void load_select_segment_update_world(int);
extern int UpdateSoundVoices(void);
/* The callee ignores a0; retain the caller's explicit zero argument. */
extern int sceGsSyncV(int);
extern int snd_resume_music_stream(void);

/* Sets up the scene for a screen transition: clears work areas, hides some objects, chooses the music and starting state, then waits until the scene is ready. */
void level_transition_scene_start(int mode)
{
    TransitionMoby *p;
    TransitionMoby *object;
    int offset;
    int state;
    int music;
    int channel;

    g_hero_moby_default.field6C = 0;
    g_hero_moby_default.mode = mode;
    g_hero_moby_default.field8 = 0;
    g_hero_moby_default.slot = -1;
    mem_clear(&g_scene_playback_state, 0, 0x1D0);
    mem_clear(&D_001B1390, 0, 0x40);
    mem_clear(D_001B2980, 0, 0x40);
    mem_clear(D_001B2980 + 0x40, 0, 0x40);
    mem_clear(&D_001B13D0, 0, 0x40);
    gfx_select_packet_buffer_setup();

    offset = D_001B22B0 - 0x60000;
    g_scene_playback_state.start = D_001BAEC0.start + offset;
    g_scene_playback_state.end = D_001BAEC0.end + offset;
    g_screen_fade = 1.0f;
    D_001B22B0 = offset;
    D_001B15A4 = 0;
    stub_empty_8(0x61, 2);
    g_hero_state.flag = 1;
    stub_empty_3();

    object = g_hero_moby_default.object;
    p = D_001B1B60;
    object->flags |= 1;
    for (; p->status != 255; p++) {
        if (!(p->status & 0x80) && (p->type == 0x4A /* moby class 74 */ || p->type == 0xCB /* Decoy */))
            p->flags |= 0x80;
    }

    if (mode == 0) {
        state = g_hero_state.mode ? 5 : 2;
        music = g_hero_state.mode ? 3 : 1;
        load_parts_set_from_disc(music, 6);
    } else {
        state = g_hero_state.mode ? 3 : 0;
        music = g_hero_state.mode ? 2 : 0;
        if (!g_hero_moby_default.active)
            state++;
        channel = g_hero_moby_default.active ? 0 : 2;
        load_parts_set_from_disc(music, channel);
    }

    g_music_state.state = state + 5000;
    g_music_state.next = 0;
    load_select_segment_update_world(0);
    while (g_music_state.phase != 3 || g_music_state.limit >= 6000) {
        UpdateSoundVoices();
        sceGsSyncV(0);
    }
    snd_resume_music_stream();
}
