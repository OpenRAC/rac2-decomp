#include "include_asm.h"
#include "names.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct {
    short a;
    short b;
} Rac2Native_03d37aca6ffcf794_T2;

extern int g_shrub_index_list __attribute__((nosda));

extern int *g_shrub_l04_class_table[];

extern Rac2Native_03d37aca6ffcf794_T2 g_shrub_patch_table[];

extern int *g_dma_packet_cursor_2 __attribute__((sda));

extern int *g_resident_table_ptr __attribute__((sda));

extern int g_vram_cursor __attribute__((sda));

extern int g_vram_frame_base __attribute__((sda));

extern int g_gfx_resident_count __attribute__((sda));

typedef struct { int *saved; } SavedSlot;

extern SavedSlot g_saved_resident_slot __attribute__((sda));

typedef struct {
    char gap0[12];
    short count;
    char gap14[2];
    long long *table;
} ResidentTable;

extern void Fa2d20de7_FUN_002A7988(void *object, float first, float second);

extern void Fa2d20de7_FUN_00282CC0(char *first, char *second, void *third);

extern int Fa2d20de7_FUN_002761F8(void *first, char *second, int mode, int value, int extra);

extern void Fa2d20de7_FUN_00282CF0(void *first, void *second, void *third);

extern void Fa2d20de7_FUN_00282D30(void *first, void *second, float value);

extern short Fa2d20de7_D_001B5340[];

extern short Fa2d20de7_D_001BAFA0[];

extern int Fa2d20de7_D_001886CC[];

extern char F391de845_D_001B5340[];

extern float F391de845_FUN_00282E48(char *a, char *b);

extern int snd_compute_falloff(void *curve, float distance, float near_distance, float far_distance);

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

extern u8 g_sound_state[];

extern u8 D_00189E20_10[];

extern u8 D_00188660_1[];

typedef struct {
    u8 pad0[4640];
    u32 field4640;
    u8 gap[4204];
    u32 field8848;
} NativeView;

extern int F29eece9b_FUN_002E5AD0(char *p, int a1, char *a2, int a3, int a4);

extern char F29eece9b_D_00188660[];

typedef struct { u8 before[0x1730]; s32 count; u8 *table; } CallbackGlobals;

extern void snd_clear_flag_and_update(void);

extern s32 snd_Pump(void);

extern s32 func_00132AC8(void);

/* Walk a terminated index list and nested records, clearing the low fourteen bits and ORing nonzero replacement values into two selected words. */
void patch_shrub_gifs(void)
{
    int *indexPtr;
    int *shrubClass;
    int i;
    int j;
    int k;
    int *partTable;
    int *partRecord;
    int *partHeader;
    int *entry;

    for (indexPtr = &g_shrub_index_list; *indexPtr >= 0; indexPtr++) {
        shrubClass = g_shrub_l04_class_table[*indexPtr];
        for (i = 0; i < *(short *)((char *)shrubClass + 40); i++) {
            partTable = shrubClass + 16;
            partRecord = *(int **)((char *)partTable + (i << 3));
            partHeader = partRecord + 4;
            entry = (int *)((char *)partHeader + (partHeader[1] << 4)) + 4;
            for (j = 0; j < partHeader[0]; j++) {
                Rac2Native_03d37aca6ffcf794_T2 *patch = &g_shrub_patch_table[((unsigned char *)entry)[19]];
                if (patch->a != 0)
                    entry[12] = (entry[12] & 0xFFFFC000) | patch->a;
                if (patch->b != 0)
                    entry[8] = (entry[8] & 0xFFFFC000) | patch->b;
                entry += 16;
            }
        }
    }
}

/* func_002E11C0 is matched in its own unit, src/game/002E11C0.c (default flags). */

ASM_FUNC("asm/game", func_002E1228);

ASM_FUNC("asm/game", func_002E2988);

ASM_FUNC("asm/game", func_002E2C38);

/* Original assembly: lqc2/qmfc2 VU0 ops, $at as a working register and trapping addi. */
ASM_FUNC("asm/game", func_002E31E8);

/* Original assembly: $at as a working register and trapping add/addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002E3360);



extern char *ref_L00_002E3548_00 __attribute__((sda));
extern float ref_L00_002E3548_01[16] __attribute__((sda));
extern void set_identity_matrix(float *);
extern void cam_update_view_rotation(int);
/* Handles one table entry, using one of two routines depending on whether its second field is set. */
extern void gfx_process_view_entry(int);
/* Updates the transform of every view, then processes each view entry. */
void gfx_update_all_view_transforms(void)
{
    int i;
    for (i = 0; i < *(short *)(ref_L00_002E3548_00 + 6); i++) {
        if (i >= 10)
            set_identity_matrix(ref_L00_002E3548_01);
        else
            cam_update_view_rotation(i);
        gfx_process_view_entry(i);
    }
}


/* func_002E35E0 is in 002E35E0-g8.c. */

/* shared native body of family 060b9f2017649e67 */
/* Starts a new buffer block and clears every entry of the resident table. */
void gfx_resident_table_reset(void)
{
    ResidentTable *resident = (ResidentTable *)g_resident_table_ptr;
    int *current = g_dma_packet_cursor_2;
    int index;

    g_saved_resident_slot.saved = current;
    g_dma_packet_cursor_2 = (int *)((char *)current + 16);
    g_vram_cursor = g_vram_frame_base;
    g_gfx_resident_count = 0;
    for (index = 0; index < resident->count; ++index)
        *(long long *)((char *)resident->table + index * 16) = 0;
}



typedef struct {
    int field0;
    int field4;
} Entry3940;

typedef struct {
    char pad0[6];
    short count;
    char pad1[24];
    Entry3940 *entries[1];
} Table3940;

extern Table3940 *g_sky_shell_definition __attribute__((sda));

extern void gfx_sky_gouraud_pieces_draw(void *);

extern void gfx_sky_textured_pieces_draw(void *);

void gfx_process_view_entry(int index)
{
    Table3940 *table = g_sky_shell_definition;

    if (index < table->count) {
        Entry3940 *entry = table->entries[index];

        if (entry->field4 != 0)
            gfx_sky_gouraud_pieces_draw(entry);
        else
            gfx_sky_textured_pieces_draw(entry);
    }
}

ASM_FUNC("asm/game", func_002E3E54);

ASM_FUNC("asm/game", func_002E3FA0);

ASM_FUNC("asm/game", func_002E40C8);

ASM_FUNC("asm/game", func_002E425C);

/* Original assembly: lqc2/qmfc2 VU0 ops and trapping addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002E4388);

/* Finds a spot near the listener by testing the ground and nearby walls, and pulls it back from a wall hit. */
void snd_probe_listener_occlusion_point(void *object)
{
    Fa2d20de7_FUN_002A7988(object, 0.5f, 6.0f);
    Fa2d20de7_FUN_00282CC0(object, object, Fa2d20de7_D_001B5340);
    if (Fa2d20de7_FUN_002761F8(Fa2d20de7_D_001B5340, object, 130, Fa2d20de7_D_001886CC[0], 0)) {
        Fa2d20de7_FUN_00282CF0(object, Fa2d20de7_D_001BAFA0, Fa2d20de7_D_001B5340);
        Fa2d20de7_FUN_00282D30(object, object, 0.75f);
        Fa2d20de7_FUN_00282CC0(object, object, Fa2d20de7_D_001B5340);
    }
}



/* Works out how loud a sound should be from its distance to the listener. */
int snd_compute_voice_volume_from_distance(char *voice, char *position)
{
    float distance = F391de845_FUN_00282E48(position, F391de845_D_001B5340);
    float *range = *(float **)(voice + 8);

    return snd_compute_falloff(range, distance, range[0], range[1]);
}

extern float g_camera_l00_position[];

extern void FastVecSub(void *dst, void *src, void *arg);
extern float mat_fast_helper_a(float a, float b);
extern float FastAddRotations(float a, float b);
extern float vec_length_xy(void *p);
extern float fast_subtract_rotations(float a, float b);
extern int FloatToInt(float a);

/* Works out the left-right pan of a sound from its direction, smoothing the angle between frames. */
int snd_compute_voice_pan(void *voice, void *position)
{
    struct AngleState { char reserved[0x40]; float angle; };
    struct AngleState *state = (struct AngleState *)voice;
    float buf[4];
    float angleToSource;
    float angleChange;

    FastVecSub(buf, position, g_camera_l00_position);
    angleToSource = -mat_fast_helper_a(buf[0], buf[1]);
    angleToSource = FastAddRotations(angleToSource, g_camera_l00_position[6]);
    if (angleToSource < 0.0f)
        angleToSource += 6.283185307179586f;
    if (vec_length_xy(buf) < 2.0f) {
        if (state->angle >= 0.0f) {
            angleChange = fast_subtract_rotations(angleToSource, state->angle);
            if (angleChange > 0.2f) {
                angleToSource = FastAddRotations(state->angle, 0.2f);
            } else if (angleChange < -0.2f) {
                angleToSource = fast_subtract_rotations(state->angle, 0.2f);
            }
            state->angle = angleToSource;
        } else {
            state->angle = angleToSource;
        }
    } else {
        state->angle = -1.0f;
    }
    return FloatToInt(angleToSource * 57.2957763671875f);
}

/* func_002E48E8 is defined in 002E10B8-sound.c. */

extern int g_snd_status_value;
extern int g_current_map_index __attribute__((sda));
extern char g_str_sound_status[];
extern void snd_send_cmd51(int, int);
extern int func_001337F0(void);
extern int func_00133820(void);
extern void STUB_printf(char *, int, int, int);

/* Sets a sound parameter and prints the sound status. */
void snd_print_status(void)
{
    snd_send_cmd51(2, g_snd_status_value);
    STUB_printf(g_str_sound_status, g_current_map_index, func_001337F0(), func_00133820());
}


/* Tells whether a sound voice belongs to the given owner and is starting or playing. */
s32 snd_is_voice_playing_for_owner(s32 owner,s32 voiceIndex) {
    if(voiceIndex>=0) {
        u8 *voice=g_sound_state+voiceIndex*0x70;
        if(*(s32 *)(voice+0x88)==owner && (u32)voice[0x74]-1<2) return 1;
    }
    return 0;
}

/* Stops one sound voice, or frees it right away if it has not started yet. */
void snd_stop_voice(s32 voiceIndex) {
    if(voiceIndex>=0) {
        u8 *voice=g_sound_state+voiceIndex*0x70;
        s32 state=voice[0x74];
        if(state==7) {
            *(s32 *)(voice+0x88)=0;
            *(s32 *)(voice+0x8c)=0;
            voice[0x74]=0;
            return;
        }
        if(state!=0 && state!=6) voice[0x74]=4;
    }
}

/* shared native body of family 62e6ff2b3d3a */
/* Finds a free sound voice slot and returns its number, or 52 when none is free. */
s32 snd_find_free_voice(s32 id)
{
    u8 *record;
    u8 *cursor;
    s32 limit;

    limit = 52;
    if (id == 0 || (((NativeView *)&D_00189E20_10)->field8848 != (u32)id &&
                    ((NativeView *)&D_00189E20_10)->field4640 != (u32)id))
        limit = 42;

    id = 0;
    if (limit != 0) {
        record = (u8 *)&D_00188660_1;
        if (record[116] != 0) {
            cursor = record + 116;
            do {
                id++;
                if (id >= limit)
                    break;
                cursor += 112;
            } while (*cursor != 0);
        }
    }
    return (id != limit) ? id : 52;
}

/* func_002E5AD0 is defined in 002E5AD0.c. */

/* Plays a numbered sound from the sound list of a moby and links the voice to that moby. */
int PlayMobySound(int index, int flags, char *moby)
{
    int classData;
    int definitions;
    int voiceIndex;
    char *voice;

    if (moby == 0)
        return -1;
    classData = *(int *)(moby + 36);
    if (classData == 0)
        return -1;
    definitions = *(int *)(classData + 40);
    if (definitions == 0)
        return -1;
    classData = *(unsigned char *)(classData + 13);
    if (index >= classData)
        return -1;
    voiceIndex = F29eece9b_FUN_002E5AD0((char *)(definitions + index * 32), flags, moby, 0, 1024);
    if (voiceIndex >= 0) {
        voice = &F29eece9b_D_00188660[voiceIndex * 112];
        *(int *)(voice + 136) = (int)moby;
        *(short *)(voice + 126) = (short)index;
    }
    return voiceIndex;
}

extern unsigned char g_class_slot_indices[];
extern char *g_sound_bank_table[];
extern int AllocateSoundVoice(char *, int, char *, int, int);

/* Plays a numbered sound from the sound list of an object class and links the voice to the object. */
int snd_play_from_class_bank(int index, int value, char *object, int kind)
{
    char *header = g_sound_bank_table[g_class_slot_indices[kind]];
    char *entries;
    int result;
    char *row;
    if (header == 0)
        return -1;
    entries = *(char **)(header + 0x28);
    if (entries == 0)
        return -1;
    if (index >= (unsigned char)header[0xD])
        return -1;
    result = AllocateSoundVoice(entries + index * 32, value, object, 0, 0x400);
    if (result >= 0) {
        row = g_sound_state + result * 112;
        *(char **)(row + 0x88) = object;
        *(short *)(row + 0x7E) = index;
    }
    return result;
}

extern u8 *g_global_sound_bank_table __attribute__((sda));

extern int g_global_bank_count __attribute__((sda));

/* Plays a numbered sound from the shared sound list and links the voice to the object. */
int snd_play_from_global_bank(int index, int value, void *object)
{
    u8 *table = g_global_sound_bank_table;
    int result;
    u8 *row;

    if (table == 0)
        return -1;
    if (index >= g_global_bank_count)
        return -1;
    result = AllocateSoundVoice((char *)table + index * 32, value, (char *)object, 0, 0x400);
    if (result >= 0) {
        row = g_sound_state + result * 0x70;
        *(int *)(row + 0x88) = object;
        *(short *)(row + 0x7E) = index;
    }
    return result;
}


/* func_002E5F00 is matched in its own unit, src/game/002E5F00-qcopy.c (-frac2-qcopy). */


/* Sets the pitch bend of one sound voice. */
s32 snd_set_voice_pitch_bend(s32 index, s32 pitchBend) {
    u8 *voice = g_sound_state + index * 0x70;
    *(s32 *)(voice + 0x84) = pitchBend;
    return 1;
}

/* Calls the callback of every entry in the sound callback table that has one. */
void snd_run_callbacks(void) {
    s32 i=0;
    for (i=0;i<((CallbackGlobals *)g_sound_state)->count;i++) {
            u8 *entry=(u8 *)(i*0x90+(s32)((CallbackGlobals *)g_sound_state)->table);
            void (*callback)(u8 *)=*(void (**)(u8 *))(entry+4);
            if (callback) callback(entry);
    }
}

/* Waits for the sound system to go quiet, then clears every sound voice. */
void snd_clear_all_voices(void) {
    typedef s32 quad __attribute__((mode(__TI__)));
    s32 count;
    u8 *p;
    snd_clear_flag_and_update(); snd_Pump(); func_00132AC8();
    while (snd_Pump() != 0) {}
    p=g_sound_state; count=3;
    do { *(volatile quad *)p = 0; count--; p += 16; } while (count >= 0);


    p=g_sound_state;
    *(s32 *)(p+0x40)=0;
    for(count=0;count<52;count++) {
        *(s32 *)(p+count*0x70+0x70)=0;
        *(u8 *)(p+count*0x70+0x74)=0;
    }
}

/* Stores a value into the place the caller points to, if there is one. */
void snd_store_result(int value, long target) {
    int *destination = (int *)(int)target;
    if (destination != 0)
        *destination = value;
}

/* Called when a sound starts: records the result and moves the voice from starting to playing, or clears it on failure. */
void snd_voice_started_callback(int result, long slotAddress) {
    unsigned char *slot = (unsigned char *)(int)slotAddress;

    if (slot != 0) {
        *(int *)slot = result;
        if (result != 0) {
            if (slot[4] == 1) {
                slot[4] = 2;
            }
        } else {
            *(int *)(slot + 0x18) = 0;
            *(int *)(slot + 0x1C) = 0;
            slot[4] = 0;
        }
    }
}

/* Called when a sound ends: records the result and clears the voice when it is done. */
void voice_update_callback(int result, long slotAddress) {
    int *slot = (int *)(int)slotAddress;

    if (slot != 0) {
        *slot = result;
        if (result == 0) {
            *(int *)((char *)slot + 0x18) = 0;
            *(int *)((char *)slot + 0x1C) = 0;
            *(unsigned char *)((char *)slot + 4) = 0;
        }
    }
}


extern void *g_equipment_pieces[];
extern void moby_mark_spawned(void *);

/* Destroys all the hero equipment pieces and empties the list. */
void hero_destroy_equipment_pieces(void)
{
    void **entry = g_equipment_pieces;
    int count = 19;
    do {
        count--;
        if (*entry != 0)
            moby_mark_spawned(*entry);
        *entry++ = 0;
    } while (count >= 0);
}

/* func_002E6178 is in 002E6178.c. */

/* func_002E64A0 is in 002E64A0.c. */


/* func_002E6A60 is in 002E6A60.c. */

/* func_002E6B78 is in 002E6B78-g8.c. */

/* func_002E6D88 is in 002E10B8-transition-g8.c. */
