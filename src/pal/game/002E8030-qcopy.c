#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern char g_hero_state[];
extern char g_hero_moby_default[];
extern void music_Unpause(void);
extern void stub_empty_4(void);
extern void stub_empty_9(int);
extern void stub_empty_18(void);
extern void stub_empty_14(char *, void *, int, int);
extern void cam_set_transition_frames(float);
extern void pad_clear_port_state(void);
extern float FastAddRotations(float, float);

/* Ends the scene and starts the closing transition. */
void scene_end_playback_pal(void) {
    char *state;
    char *mode_block;
    float pose[4] __attribute__((aligned(16)));

    music_Unpause();
    state = g_hero_state;
    state[0x22B5] = 0;
    stub_empty_4();
    mode_block = g_hero_moby_default;
    if (*(short *)(mode_block + 0x2A) != 0) {
        stub_empty_9(1);
        state[0x22B5] = 0;
        stub_empty_4();
        stub_empty_18();
        cam_set_transition_frames(7.0f);
        pad_clear_port_state();
    } else {
        state = mode_block + 0x80;
        *(TI128 *)pose = *(TI128 *)state;
        pose[2] = FastAddRotations(pose[2], -2.3f);
        mode_block += 0x70;
        stub_empty_14(mode_block, pose, 0, 1);
        stub_empty_14(mode_block, state, 0, 0);
        cam_set_transition_frames(7.0f);
        pad_clear_port_state();
    }
}
