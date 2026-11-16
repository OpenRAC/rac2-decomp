#include "common.h"

typedef struct SceneObject {
    char pad0[0x24]; unsigned char *model; char pad28[0xA]; unsigned short flags32, flags34;
    char pad36[2]; unsigned long long color; char pad40[2]; unsigned char slot, slot2;
    char pad44[0x1E]; unsigned char alpha, mode; char pad64[4]; void *data;
    char pad6C[0x2C]; int field98; char pad9C[0xE]; short kind;
} SceneObject;
typedef struct {
    char pad[0x38]; int frame; char pad3C[4]; short field40; char pad42[2]; short count;
    char pad46[2]; short field48; char pad4A[2]; void *optional; char pad50[4]; SceneObject *special;
    char pad58[0x10]; void *tail; unsigned char *source; int destination;
    char pad74[0x118]; SceneObject *objects[17];
} SceneList;
extern SceneList g_scene_playback_state;

typedef struct { char pad0[0x24]; int pending; char pad28[0x40]; int busy; char pad6C[6]; unsigned short state; } SceneContextEnd;
extern SceneContextEnd D_001A63A8_3;
typedef struct { char pad[0x12C0]; SceneObject *object; } SceneEndRoot;
extern SceneEndRoot D_00189E20_9;
typedef struct { char pad[0xB0]; float fade; } SceneFade;
extern SceneFade g_view_params;
typedef struct { char pad[0xFC]; SceneObject *object; } SceneOwnerEnd;
extern SceneOwnerEnd g_pause_menu_state;
/* Read at an offset from an earlier small-data name (as in 002F5220-g8.c), so
   retail never puts the load in a delay slot. */
typedef struct { int unk0; SceneObject *moby; void *data; } SceneTalkEnd;
extern SceneTalkEnd g_dialogue_talk_state MACRO_ADDR;
extern int g_cutscene_active_flag __attribute__((section(".sdata")));
extern int g_cutscene_letterbox_progress __attribute__((section(".sdata")));
extern float g_screen_fade __attribute__((sda));
extern void FadeToBlack(int);
extern s32 UpdateSoundVoices(void);
extern int sceGsSyncV(int);
extern int snd_Pump(void);
extern void UpdateViewContext(void);
extern void moby_mark_spawned(SceneObject *);

/* Scene teardown: puts the transition word back to 5 unless it is 6 or 7,
   calls func_0027D330(12) and waits until the transition is idle with
   nothing pending, then until func_00132028 returns 0; sets the fade to
   0.63, clears the control words, releases every scene object (dropping its
   model's use count and entry) and the object held at D_00189E20+0x12C0,
   and clears bit 0 of flags34 on the objects held at D_001B178C+4 and
   D_001F2840+0xFC. */
/* Ends a scripted scene: waits for loading to finish and frees all of its objects. */
void cutscene_end_scripted(void)
{
    int i;
    SceneObject *obj;
    SceneContextEnd *context = &D_001A63A8_3;
    unsigned short state = context->state;
    if ((unsigned int)(state - 6) >= 2) context->state = 5;
    FadeToBlack(12);
    while (D_001A63A8_3.busy || D_001A63A8_3.pending != -1) {
        UpdateSoundVoices(); sceGsSyncV(0);
    }
    while (snd_Pump()) {}
    g_view_params.fade = 0.63f;
    g_cutscene_active_flag = 0;
    g_cutscene_letterbox_progress = 0;
    g_screen_fade = 0.0f;
    UpdateViewContext();
    for (i = 0; i < g_scene_playback_state.count; i++) {
        obj = g_scene_playback_state.objects[i];
        if (obj) {
            obj->model[12]--;
            { unsigned char *model = obj->model;
            model += model[12] * 4;
            *(int *)(model + 0x48) = 0; }
            moby_mark_spawned(obj);
        }
    }
    { SceneEndRoot *owner = &D_00189E20_9;
    if (owner->object) { moby_mark_spawned(owner->object); owner->object = 0; } }
    if (g_dialogue_talk_state.moby) g_dialogue_talk_state.moby->flags34 &= ~1;
    obj = g_pause_menu_state.object;
    if (obj) { obj->flags34 &= ~1; g_pause_menu_state.object = 0; }
}
