#include "include_asm.h"
#include "names.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct {
    short a;
    short b;
} Rac2Native_03d37aca6ffcf794_T2;

extern int D_L04_00220D60 __attribute__((nosda));

extern int *D_L04_0021F2E0[];

extern Rac2Native_03d37aca6ffcf794_T2 D_L04_00220860[];

extern int *D_L05_001B2C88 __attribute__((sda));

extern int *D_L05_001B2AA0 __attribute__((sda));

extern int D_001A72D0 __attribute__((sda));

extern int D_001A72D4 __attribute__((sda));

extern int D_L05_001B1FBC __attribute__((sda));

typedef struct { int *saved; } SavedSlot;

extern SavedSlot D_L05_001B2AC0 __attribute__((sda));

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

extern float F391de845_FUN_002E45C8(void *self, float d, float x, float y);

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

extern u8 D_00188660[];

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

extern s32 func_00133230(void);

extern s32 func_00132028(void);

extern s32 func_00132AC8(void);

/* Walk a terminated index list and nested records, clearing the low fourteen bits and ORing nonzero replacement values into two selected words. */
void func_002E10B8(void)
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

    for (indexPtr = &D_L04_00220D60; *indexPtr >= 0; indexPtr++) {
        shrubClass = D_L04_0021F2E0[*indexPtr];
        for (i = 0; i < *(short *)((char *)shrubClass + 40); i++) {
            partTable = shrubClass + 16;
            partRecord = *(int **)((char *)partTable + (i << 3));
            partHeader = partRecord + 4;
            entry = (int *)((char *)partHeader + (partHeader[1] << 4)) + 4;
            for (j = 0; j < partHeader[0]; j++) {
                Rac2Native_03d37aca6ffcf794_T2 *patch = &D_L04_00220860[((unsigned char *)entry)[19]];
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
extern void func_00283388(float *);
extern void func_002E3478(int);
/* Handles one table entry, using one of two routines depending on whether its second field is set. */
extern void func_002E3940(int);
/* Updates the transform of every view, then processes each view entry. */
void func_002E3548(void)
{
    int i;
    for (i = 0; i < *(short *)(ref_L00_002E3548_00 + 6); i++) {
        if (i >= 10)
            set_identity_matrix(ref_L00_002E3548_01);
        else
            UpdateViewRotation(i);
        ProcessViewEntry(i);
    }
}


/* func_002E35E0 is in 002E35E0-g8.c. */

/* shared native body of family 060b9f2017649e67 */
/* Starts a new buffer block and clears every entry of the resident table. */
void func_002E37B0(void)
{
    ResidentTable *resident = (ResidentTable *)D_L05_001B2AA0;
    int *current = D_L05_001B2C88;
    int index;

    D_L05_001B2AC0.saved = current;
    D_L05_001B2C88 = (int *)((char *)current + 16);
    D_001A72D0 = D_001A72D4;
    D_L05_001B1FBC = 0;
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

extern Table3940 *D_001B20C0 __attribute__((sda));

extern void func_002E3BD8(void *);

extern void func_002E3998(void *);

void func_002E3940(int index)
{
    Table3940 *table = D_001B20C0;

    if (index < table->count) {
        Entry3940 *entry = table->entries[index];

        if (entry->field4 != 0)
            DrawSkyGouraudPieces(entry);
        else
            DrawSkyTexturedPieces(entry);
    }
}

ASM_FUNC("asm/game", func_002E3E54);

ASM_FUNC("asm/game", func_002E3FA0);

ASM_FUNC("asm/game", func_002E40C8);

ASM_FUNC("asm/game", func_002E425C);

/* Original assembly: lqc2/qmfc2 VU0 ops and trapping addi; the compiler cannot emit them. */
ASM_FUNC("asm/game", func_002E4388);

/* Finds a spot near the listener by testing the ground and nearby walls, and pulls it back from a wall hit. */
void func_002E4478(void *object)
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
float func_002E46C0(char *voice, char *position)
{
    float distance = F391de845_FUN_00282E48(position, F391de845_D_001B5340);
    float *range = *(float **)(voice + 8);

    return F391de845_FUN_002E45C8(range, distance, range[0], range[1]);
}

extern float D_L00_001B8DC0[];

extern void func_00282CF0(void *dst, void *src, void *arg);
extern float func_00283248(float a, float b);
extern float func_00283B98(float a, float b);
extern float func_00282E20(void *p);
extern float func_00283BE0(float a, float b);
extern int func_00283CF0(float a);

/* Works out the left-right pan of a sound from its direction, smoothing the angle between frames. */
void func_002E4708(void *voice, void *position)
{
    struct AngleState { char reserved[0x40]; float angle; };
    struct AngleState *state = (struct AngleState *)voice;
    float buf[4];
    float angleToSource;
    float angleChange;

    FastVecSub(buf, position, gCameraPosition_L00);
    angleToSource = -FastMatrixHelperA(buf[0], buf[1]);
    angleToSource = FastAddRotations(angleToSource, gCameraPosition_L00[6]);
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
    FloatToInt(angleToSource * 57.2957763671875f);
}

/* func_002E48E8 is defined in 002E10B8-sound.c. */

extern int D_001507E4;
extern int D_001A79F0 __attribute__((sda));
extern char D_001ABE10[];
extern void func_00133750(int, int);
extern int func_001337F0(void);
extern int func_00133820(void);
extern void func_0026FEB8(char *, int, int, int);

/* Sets a sound parameter and prints the sound status. */
void func_002E4A68(void)
{
    SendSoundCommand51(2, D_001507E4);
    STUB_printf(D_001ABE10, gCurrentMapIndex, func_001337F0(), func_00133820());
}


/* Tells whether a sound voice belongs to the given owner and is starting or playing. */
s32 func_002E59B0(s32 owner,s32 voiceIndex) {
    if(voiceIndex>=0) {
        u8 *voice=gSoundState+voiceIndex*0x70;
        if(*(s32 *)(voice+0x88)==owner && (u32)voice[0x74]-1<2) return 1;
    }
    return 0;
}

/* Stops one sound voice, or frees it right away if it has not started yet. */
void func_002E59F8(s32 voiceIndex) {
    if(voiceIndex>=0) {
        u8 *voice=gSoundState+voiceIndex*0x70;
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
s32 func_002E5A50(s32 id)
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
int func_002E5CF8(int index, int flags, char *moby)
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

extern unsigned char D_L00_001DA860[];
extern char *D_L00_001D9F00[];
extern int func_002E5AD0(char *, int, char *, int, int);

/* Plays a numbered sound from the sound list of an object class and links the voice to the object. */
int func_002E5DA0(int index, int value, char *object, int kind)
{
    char *header = D_L00_001D9F00[D_L00_001DA860[kind]];
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
        row = gSoundState + result * 112;
        *(char **)(row + 0x88) = object;
        *(short *)(row + 0x7E) = index;
    }
    return result;
}

extern u8 *D_001B16AC __attribute__((sda));

extern int D_001A8BBC __attribute__((sda));

/* Plays a numbered sound from the shared sound list and links the voice to the object. */
int func_002E5E58(int index, int value, void *object)
{
    u8 *table = D_001B16AC;
    int result;
    u8 *row;

    if (table == 0)
        return -1;
    if (index >= D_001A8BBC)
        return -1;
    result = AllocateSoundVoice((char *)table + index * 32, value, (char *)object, 0, 0x400);
    if (result >= 0) {
        row = gSoundState + result * 0x70;
        *(int *)(row + 0x88) = object;
        *(short *)(row + 0x7E) = index;
    }
    return result;
}


/* func_002E5F00 is matched in its own unit, src/game/002E5F00-qcopy.c (-frac2-qcopy). */


/* Sets the pitch bend of one sound voice. */
s32 func_002E5F40(s32 index, s32 pitchBend) {
    u8 *voice = gSoundState + index * 0x70;
    *(s32 *)(voice + 0x84) = pitchBend;
    return 1;
}

/* Calls the callback of every entry in the sound callback table that has one. */
void func_002E5F60(void) {
    s32 i=0;
    for (i=0;i<((CallbackGlobals *)gSoundState)->count;i++) {
            u8 *entry=(u8 *)(i*0x90+(s32)((CallbackGlobals *)gSoundState)->table);
            void (*callback)(u8 *)=*(void (**)(u8 *))(entry+4);
            if (callback) callback(entry);
    }
}

/* Waits for the sound system to go quiet, then clears every sound voice. */
void func_002E5FE0(void) {
    typedef s32 quad __attribute__((mode(__TI__)));
    s32 count;
    u8 *p;
    ClearSoundFlagAndUpdate(); snd_Pump(); func_00132AC8();
    while (snd_Pump() != 0) {}
    p=gSoundState; count=3;
    do { *(volatile quad *)p = 0; count--; p += 16; } while (count >= 0);


    p=gSoundState;
    *(s32 *)(p+0x40)=0;
    for(count=0;count<52;count++) {
        *(s32 *)(p+count*0x70+0x70)=0;
        *(u8 *)(p+count*0x70+0x74)=0;
    }
}

/* Stores a value into the place the caller points to, if there is one. */
void func_002E6088(int value, long target) {
    int *destination = (int *)(int)target;
    if (destination != 0)
        *destination = value;
}

/* Called when a sound starts: records the result and moves the voice from starting to playing, or clears it on failure. */
void func_002E60A0(int result, long slotAddress) {
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
void func_002E60E8(int result, long slotAddress) {
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


extern void *D_00214920[];
extern void func_0029F338(void *);

/* Destroys all the hero equipment pieces and empties the list. */
void func_002E6120(void)
{
    void **entry = gEquipmentPieces;
    int count = 19;
    do {
        count--;
        if (*entry != 0)
            MarkMobySpawned(*entry);
        *entry++ = 0;
    } while (count >= 0);
}

/* func_002E6178 is in 002E6178.c. */

/* func_002E64A0 is in 002E64A0.c. */


/* func_002E6A60 is in 002E6A60.c. */

/* func_002E6B78 is in 002E6B78-g8.c. */

/* func_002E6D88 is in 002E10B8-transition-g8.c. */
