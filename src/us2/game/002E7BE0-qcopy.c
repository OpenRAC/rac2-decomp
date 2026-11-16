#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern char g_hero_state[];
extern char g_hero_moby_default[];
extern void music_Unpause(void);
extern void stub_empty_5_us2(void);
extern void stub_empty_10(int);
extern void stub_empty_19_us2(void);
extern void stub_empty_15(char *, void *, int, int);
extern void cam_set_transition_frames(float);
extern void pad_clear_port_state(void);
extern float FastAddRotations(float, float);

/* Ends the scene and starts the closing transition (USA v2.00). */
void scene_end_playback_us2(void) {
    char *p;
    char *scene;
    float v[4] __attribute__((aligned(16)));

    music_Unpause();
    p = g_hero_state;
    p[0x22B5] = 0;
    stub_empty_5_us2();
    scene = g_hero_moby_default;
    if (*(short *)(scene + 0x2A) != 0) {
        stub_empty_10(1);
        p[0x22B5] = 0;
        stub_empty_5_us2();
        stub_empty_19_us2();
        cam_set_transition_frames(8.0f);
        pad_clear_port_state();
    } else {
        p = scene + 0x80;
        *(TI128 *)v = *(TI128 *)p;
        v[2] = FastAddRotations(v[2], -2.3f);
        scene += 0x70;
        stub_empty_15(scene, v, 0, 1);
        stub_empty_15(scene, p, 0, 0);
        cam_set_transition_frames(8.0f);
        pad_clear_port_state();
    }
}
