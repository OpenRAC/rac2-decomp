#include "common.h"

/* Borrowed player-state prefix; this view never owns an allocation. */
typedef struct {
    u8 reserved00[0x250];
    float parameter250, parameter254, parameter258, parameter25c;
    u8 reserved260[4];
    float parameter264;
    u8 reserved268[0xC24 - 0x268];
    float scale;
    u8 reservedc28[0x1888 - 0xC28];
    void *entry_table;
    u8 reserved188c[0x2294 - 0x188C];
    s32 state;
    u8 reserved2298[0x24F0 - 0x2298];
    u8 special_level;
} LevelPlayerPrefix;

extern LevelPlayerPrefix D_00189E20;
extern s32 D_001A79F0[] __attribute__((sda));
extern s32 D_001A73A0[] __attribute__((sda));
extern char D_L22_001B1920[];
extern void func_L00_002D24B8(void);
extern s32 func_L22_002C9898(s32, s32);
extern void func_L00_003B09F8(void);

/* Install this level's player parameters and start the shared subsystems. */
void func_L22_002A8B98(void)
{
    s32 special_level = D_001A79F0[0] == 0x1A;
    LevelPlayerPrefix *state = &D_00189E20;

    state->parameter250 = 0.8f;
    state->parameter254 = 0.7f;
    state->parameter264 = 0.45f;
    state->parameter258 = 0.8f;
    state->parameter25c = 0.7f;
    state->scale = 1.0f;
    state->special_level = special_level;
    D_001A73A0[0] = 0;
    state->state = 0;
    func_L00_002D24B8();
    func_L22_002C9898(0, 1);
    func_L00_003B09F8();
    state->entry_table = D_L22_001B1920;
}
