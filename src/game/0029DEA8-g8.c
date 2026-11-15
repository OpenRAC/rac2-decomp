/* func_0029DEA8 in its own unit (-G8 from the file name). Lays out the map
   markers of one map: fixed marker positions by key, else the projected
   position of the marker's target, then each marker's visibility. */
#include "common.h"

/* Only measured fields are named. The terminated entry list advances by 0x28. */
typedef struct MapEntry {
    s16 key,parent;
    s16 flags;
    u8 reserved06[4];
    s16 state;
    u8 reserved0c[12];
    float x,y,scale;
    int visible;
} MapEntry;
typedef struct {
    u8 reserved00[0x20];
    MapEntry *entries;
    u8 reserved24[0xE4];
    int cachedX[21],cachedY[21];
} MapEntryState;
typedef struct { float x,y,z; unsigned int flags; } MapDefinition;
typedef struct { u8 reserved00[0x10]; float x,y; u8 reserved18[0xE0]; float scale; } MapTarget;
typedef struct { u8 reserved00[0x24]; s16 enabled; u8 reserved26[2]; } MapParent;
typedef struct { float x,y; } MapCoordinates;

/* These objects move between the boot and level placements (the levels read theirs
   from the bytes). The fallback position is two adjacent small-data floats. */
extern MapEntryState g_map_overlay_state;
extern MapEntry *D_00258C10[];
extern MapTarget *D_001C1220[];
extern MapParent *D_001B1A58;
extern int D_001A9598 __attribute__((sda));
extern int D_001A9DB0 __attribute__((sda));
extern float D_001A9B20 __attribute__((sda));
extern float D_001A9B24 __attribute__((sda));
extern u8 D_001A7BE8[];
extern int g_current_map_index;
typedef struct { u8 reserved00[0x80]; float x,y,z; } MapPlayerView;
extern MapPlayerView g_hero_state;
extern MapDefinition D_00139A28[];
extern void map_convert_world_to_map_position(float,float,float *,float *,int);

void func_0029DEA8(int selector,int update)
{
    float x,y,fallbackX,fallbackY;
    MapEntry *entry,*cursor;
    int offset,index,mapSelector;
    if (selector<21 && D_001A7BE8[selector]) g_map_overlay_state.entries=D_00258C10[selector];
    else g_map_overlay_state.entries=0;
    if (g_hero_state.z!=0.0f && selector==g_current_map_index && update) {
        mapSelector=selector+100;
        if (!D_001A9598) mapSelector=selector;
        map_convert_world_to_map_position(g_hero_state.x,g_hero_state.y,&x,&y,mapSelector);
        g_map_overlay_state.cachedX[selector]=(int)(x*4096.0f)<<16;
        g_map_overlay_state.cachedY[selector]=(int)(y*4096.0f)<<16;
    } else if ((int)g_map_overlay_state.cachedX==0) {
        g_map_overlay_state.cachedX[selector]=0x08000000;
        g_map_overlay_state.cachedY[selector]=0x08000000;
    }
    if (!g_map_overlay_state.entries) return;
    offset=0;
    while (!(g_map_overlay_state.entries[offset].flags&4)) {
        entry=&g_map_overlay_state.entries[offset];
        if (D_001A9DB0) {
            fallbackX=D_001A9B20;
            fallbackY=D_001A9B24;
            entry->x=fallbackX;
            entry->y=fallbackY;
        } else {
            if (entry->key==-1000) { entry->x=0.415f; entry->y=0.39f; }
            else if (entry->key==-0x396) { entry->x=0.635f; entry->y=0.065f; }
            else if (entry->key==-0x3E2) { entry->x=0.42292f; entry->y=0.20047f; }
            else if (entry->key==-0x3E1) { entry->x=0.4615f; entry->y=0.69332f; }
            else if (entry->key==-0x3DD) { entry->x=0.188f; entry->y=0.51f; }
            else if (entry->key==-0x3DC) { entry->x=0.8f; entry->y=0.75f; }
            else if (entry->key==-0x3D8) { entry->x=0.697f; entry->y=0.465f; }
            else if (entry->key==-0x3D3) { entry->x=0.29598f; entry->y=0.16702f; }
            else if (entry->key==-0x3CF) { entry->x=0.65519f; entry->y=0.73443f; }
            else if (entry->key==-0x3CA) { entry->x=0.80234f; entry->y=0.26487f; }
            else if (entry->key==-0x3C9) { entry->x=0.43668f; entry->y=0.05949f; }
            else if (entry->key==-0x3C8) { entry->x=0.43668f; entry->y=0.05949f; }
            else if (entry->key==-0x3C7) { entry->x=0.24665f; entry->y=0.30165f; }
            else if (entry->key==-0x3C1) { entry->x=0.465f; entry->y=0.68f; }
            else if (entry->key==-0x3C0) { entry->x=0.71f; entry->y=0.4f; }
            else if (entry->key==-0x3C4) { entry->x=0.46784f; entry->y=0.2526f; }
            else if (entry->key==-0x3C3) { entry->x=0.71312f; entry->y=0.72318f; }
            else if (entry->key==-0x3B7) { entry->x=0.67f; entry->y=0.48f; }
            else if (entry->key==-0x3B6) { entry->x=0.37f; entry->y=0.8f; }
            else if (entry->key==-1) { entry->x=0.234375f; entry->y=0.30078125f; }
            else if (entry->key==-2) { entry->x=0.5390625f; entry->y=0.365234375f; }
            else if (entry->key==-3) { entry->x=0.58203125f; entry->y=0.6875f; }
            else if (entry->key==-4) { entry->x=0.720703125f; entry->y=0.728515625f; }
            else if (entry->key==-5) { entry->x=0.8671875f; entry->y=0.23046875f; }
            else if (entry->key==-6) { entry->x=0.48046875f; entry->y=0.5703125f; }
            else if (entry->key==-7) { entry->x=0.625f; entry->y=0.72265625f; }
            else if (entry->key==-0x3D5) { entry->x=0.365f; entry->y=0.3f; }
            else if (entry->key==-0x3AE) { entry->x=0.4f; entry->y=0.65f; }
            else if (entry->key==-0x3AD) { entry->x=0.63f; entry->y=0.58f; }
            else if (entry->key==-0x3A7) { entry->x=0.785f; entry->y=0.26f; }
            else if (entry->key==-0x3A6) { entry->x=0.586f; entry->y=0.365f; }
            else if (entry->key==-0x3A5) { entry->x=0.627f; entry->y=0.769f; }
            else if (entry->key==-0x3B3) { entry->x=0.12f; entry->y=0.92f; }
            else if (entry->key==-0x3AC) { entry->x=0.373f; entry->y=0.795f; }
            else if (entry->key==-0x3A4) { entry->x=0.688f; entry->y=0.705f; }
            else if (entry->key==-0x39E) { entry->x=0.422f; entry->y=0.582f; }
            else if (entry->key==-0x39A) { entry->x=0.615f; entry->y=0.658f; }
            else if (entry->key==-0x3A1) { entry->x=0.537f; entry->y=0.61f; }
            else if (entry->key==-0x3A0) { entry->x=0.394f; entry->y=0.558f; }
            else if (entry->key==-0x39F) { entry->x=0.395f; entry->y=0.625f; }
            else if (entry->key==-0x39B) { entry->x=0.337f; entry->y=0.284f; }
            else if (entry->key==-0x3E6) { entry->x=0.253f; entry->y=0.66f; }
            else if (entry->key==-0x3E0) { entry->x=0.435f; entry->y=0.9f; }
            else if (entry->key==-0x3DF) { entry->x=0.415f; entry->y=0.195f; }
            else if (entry->key==-0x3DB) { entry->x=0.485f; entry->y=0.755f; }
            else if (entry->key==-0x3DA) { entry->x=0.5f; entry->y=0.083f; }
            else if (entry->key==-0x3D7) { entry->x=0.58f; entry->y=0.61f; }
            else if (entry->key==-0x3D6) { entry->x=0.76f; entry->y=0.775f; }
            else if (entry->key==-0x3D4) { entry->x=0.342f; entry->y=0.645f; }
            else if (entry->key==-0x3D2) { entry->x=0.565f; entry->y=0.91f; }
            else if (entry->key==-0x3D1) { entry->x=0.465f; entry->y=0.695f; }
            else if (entry->key==-0x3D0) { entry->x=0.285f; entry->y=0.115f; }
            else if (entry->key==-0x3CE) { entry->x=0.865f; entry->y=0.73f; }
            else if (entry->key==-0x3CD) { entry->x=0.683f; entry->y=0.945f; }
            else if (entry->key==-0x3CC) { entry->x=0.633f; entry->y=0.665f; }
            else if (entry->key==-0x3CB) { entry->x=0.718f; entry->y=0.615f; }
            else if (entry->key==-0x3C6) { entry->x=0.805f; entry->y=0.788f; }
            else if (entry->key==-0x3C5) { entry->x=0.766f; entry->y=0.752f; }
            else if (entry->key==-0x3C2) { entry->x=0.547f; entry->y=0.665f; }
            else if (entry->key==-0x3BF) { entry->x=0.77f; entry->y=0.895f; }
            else if (entry->key==-0x3BE) { entry->x=0.545f; entry->y=0.585f; }
            else if (entry->key==-0x3BB) { entry->x=0.555f; entry->y=0.287f; }
            else if (entry->key==-0x3BA) { entry->x=0.554f; entry->y=0.5f; }
            else if (entry->key==-0x3B9) { entry->x=0.573f; entry->y=0.51f; }
            else if (entry->key==-0x3B8) { entry->x=0.2f; entry->y=0.62f; }
            else if (entry->key==-0x3BC) { entry->x=0.687f; entry->y=0.523f; }
            else if (entry->key==-0x3B5) { entry->x=0.565f; entry->y=0.915f; }
            else if (entry->key==-0x3B4) { entry->x=0.71f; entry->y=0.515f; }
            else if (entry->key==-0x3B2) { entry->x=0.103f; entry->y=0.897f; }
            else if (entry->key==-0x3B1) { entry->x=0.23f; entry->y=0.403f; }
            else if (entry->key==-0x3B0) { entry->x=0.23f; entry->y=0.45f; }
            else if (entry->key==-0x3AF) { entry->x=0.703f; entry->y=0.38f; }
            else if (entry->key==-0x3AB) { entry->x=0.375f; entry->y=0.78f; }
            else if (entry->key==-0x3AA) { entry->x=0.115f; entry->y=0.635f; }
            else if (entry->key==-0x3A9) { entry->x=0.268f; entry->y=0.53f; }
            else if (entry->key==-0x3A8) { entry->x=0.46f; entry->y=0.628f; }
            else if (entry->key==-0x3A3) { entry->x=0.613f; entry->y=0.71f; }
            else if (entry->key==-0x3A2) { entry->x=0.424f; entry->y=0.465f; }
            else if (entry->key==-0x39D) { entry->x=0.412f; entry->y=0.605f; }
            else if (entry->key==-0x39C) { entry->x=0.445f; entry->y=0.695f; }
            else if (entry->key==-0x399) { entry->x=0.515f; entry->y=0.647f; }
            else if (entry->key==-0x398) { entry->x=0.505f; entry->y=0.402f; }
            else if (entry->key==-0x397) { entry->x=0.39f; entry->y=0.275f; }
            else if (entry->key==-0x3BD) { entry->x=0.18f; entry->y=0.33f; }
            else if (entry->key==-0x3E4) { entry->x=0.422f; entry->y=0.1f; }
            else if (entry->key==-0x3DE) { entry->x=0.486f; entry->y=0.865f; }
            else if (entry->key==-0x3E3) { entry->x=0.405f; entry->y=0.081f; }
            else if (selector==g_current_map_index) {
                if (D_001C1220[entry->key]) {
                    map_convert_world_to_map_position(D_001C1220[entry->key]->x,D_001C1220[entry->key]->y,
                        &g_map_overlay_state.entries[offset].x,&g_map_overlay_state.entries[offset].y,selector);
                    g_map_overlay_state.entries[offset].scale=D_001C1220[entry->key]->scale;
                }
            } else {
                map_convert_world_to_map_position(D_00139A28[entry->key].x,D_00139A28[entry->key].y,
                    &g_map_overlay_state.entries[offset].x,&g_map_overlay_state.entries[offset].y,selector);
                g_map_overlay_state.entries[offset].scale=D_00139A28[entry->key].z;
            }
        }
        offset++;
    }
    index=0;
    if (!(g_map_overlay_state.entries[0].flags&4)) {
        do {
        cursor=&g_map_overlay_state.entries[index];
        (*(int *)((u8 *)cursor+0x24))=0;
        (*(short *)((u8 *)cursor+4))&=~0x10;
        if ((*(short *)((u8 *)cursor+2))==-1) (*(int *)((u8 *)cursor+0x24))=1;
        else (*(int *)((u8 *)cursor+0x24))=D_001B1A58[(*(short *)((u8 *)cursor+2))].enabled==1;
        if (((*(short *)((u8 *)cursor+4))&0x1000) && ((D_00139A28[(*(short *)cursor)].flags^1)&1)) (*(int *)((u8 *)cursor+0x24))=0;
        if (g_map_overlay_state.entries[index].state) g_map_overlay_state.entries[index].flags|=0x10;
        index++;
        } while (!(g_map_overlay_state.entries[index].flags&4));
    }
}
