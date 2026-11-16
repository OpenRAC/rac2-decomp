#include "include_asm.h"

#include "common.h"
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
extern TransitionArchive g_loader_memory;
extern TransitionState g_music_state;
extern TransitionGlobals g_hero_state;
extern char g_cutscene_scratch_a[] MACRO_ADDR;
extern char g_cutscene_scratch_state[];
extern char g_cutscene_scratch_b[] MACRO_ADDR;
extern int g_packet_buffer_size;
extern float g_screen_fade;
extern int g_screen_flash_alpha __attribute__((sda));
extern TransitionMoby *g_moby_pool_end;
extern void mem_clear(void *, int, int);
extern void gfx_select_packet_buffer_setup(void);
extern unsigned int stub_empty_8(int, int);
extern void stub_empty_3(void);
extern void load_parts_set_from_disc(int, int);
extern void load_select_segment_update_world(int);
extern int UpdateSoundVoices(void);
extern int sceGsSyncV(int);
extern int snd_resume_music_stream(void);

/* Starts the scene that plays between two levels, for the given mode (USA v2.00). */
void level_transition_scene_start_us2(int mode)
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
    mem_clear(&g_cutscene_scratch_a, 0, 0x40);
    mem_clear(g_cutscene_scratch_state, 0, 0x40);
    mem_clear(g_cutscene_scratch_state + 0x40, 0, 0x40);
    mem_clear(&g_cutscene_scratch_b, 0, 0x40);
    gfx_select_packet_buffer_setup();

    offset = g_packet_buffer_size - 0x60000;
    g_scene_playback_state.start = g_loader_memory.start + offset;
    g_scene_playback_state.end = g_loader_memory.end + offset;
    g_screen_fade = 1.0f;
    g_packet_buffer_size = offset;
    g_screen_flash_alpha = 0;
    stub_empty_8(0x61, 2);
    g_hero_state.flag = 1;
    stub_empty_3();

    object = g_hero_moby_default.object;
    p = g_moby_pool_end;
    object->flags |= 1;
    for (; p->status != 255; p++) {
        if (!(p->status & 0x80) && (p->type == 0x4A || p->type == 0xCB))
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
