#include "names.h"
/* Shuts the scene down: runs the helpers, clears the resident flag and, when the scene record has no active entry, lifts the copy of its next record (third component adjusted) before the final transition. */
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
void scene_end_playback(void) {
    char *data;
    char *scene;
    float liftedPoint[4] __attribute__((aligned(16)));

    music_Unpause();
    data = g_hero_state;
    data[0x22B5] = 0;
    stub_empty_4();
    scene = g_hero_moby_default;
    if (*(short *)(scene + 0x2A) != 0) {
        stub_empty_9(1);
        data[0x22B5] = 0;
        stub_empty_4();
        stub_empty_18();
        cam_set_transition_frames(8.0f);
        pad_clear_port_state();
    } else {
        data = scene + 0x80;
        *(TI128 *)liftedPoint = *(TI128 *)data;
        liftedPoint[2] = FastAddRotations(liftedPoint[2], -2.3f);
        scene += 0x70;
        stub_empty_14(scene, liftedPoint, 0, 1);
        stub_empty_14(scene, data, 0, 0);
        cam_set_transition_frames(8.0f);
        pad_clear_port_state();
    }
}
