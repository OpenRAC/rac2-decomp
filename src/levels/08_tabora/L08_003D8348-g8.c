#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef int s32;
typedef unsigned int u32;

/* the level's object-handle table: a pointer global holding the base of 0x100-byte entries */
typedef struct {
    u8 pad00[0x20];
    u8 f20;
    u8 f21;
    u8 pad22[0x68 - 0x22];
    void *f68;
    u8 pad6C[0x95 - 0x6C];
    u8 f95;
    u16 f96;
    u8 pad98[0xBC - 0x98];
    u8 fBC;
    u8 padBD[0x100 - 0xBD];
} Ent;

extern Ent *D_L08_001B29DC __attribute__((sda));

/* handle is valid and the entry's class byte is a live one */
/* Tells whether the linked object is running (or when there is no link, says yes). */
s32 func_L08_003D8918(s32 mobyIndex)
{
    Ent *mobyTable;
    s32 byteOffset;

    if (mobyIndex != -1) {
        mobyTable = D_L08_001B29DC;
        byteOffset = mobyIndex << 8;
        return *(u8 *)((u8 *)mobyTable + byteOffset + 0x20) >= 3;
    }
    return 1;
}

/* handle is valid and the entry's class byte is a live one */
/* Tells whether the linked object is running (or when there is no link, says yes). */
s32 func_L08_004229C8(s32 mobyIndex)
{
    Ent *mobyTable;
    s32 byteOffset;

    if (mobyIndex != -1) {
        mobyTable = D_L08_001B29DC;
        byteOffset = mobyIndex << 8;
        return *(u8 *)((u8 *)mobyTable + byteOffset + 0x20) >= 3;
    }
    return 1;
}

/* the entry's two faces are either unset or already gone */
/* Tells whether the linked object is gone (or when there is no link, says yes). */
s32 func_L08_003D8948(s32 mobyIndex)
{
    Ent *linked;
    s32 gone;

    if (mobyIndex != -1) {
        linked = D_L08_001B29DC + mobyIndex;
        gone = 0;
        if (linked == 0 || linked->f20 == 0xFE || linked->f20 == 0xFD) gone = 1;
        return gone;
    }
    return 1;
}

/* the entry's two faces are either unset or already gone */
/* Tells whether the linked object is gone (or when there is no link, says yes). */
s32 func_L08_003D8990(s32 mobyIndex)
{
    Ent *linked;
    s32 gone;

    if (mobyIndex != -1) {
        linked = D_L08_001B29DC + mobyIndex;
        gone = 0;
        if (linked == 0 || linked->f20 == 0xFE || linked->f20 == 0xFD) gone = 1;
        return gone;
    }
    return 1;
}

/* the entry's two faces are either unset or already gone */
/* Tells whether the linked object is gone (or when there is no link, says yes). */
s32 func_L08_004229F8(s32 mobyIndex)
{
    Ent *linked;
    s32 gone;

    if (mobyIndex != -1) {
        linked = D_L08_001B29DC + mobyIndex;
        gone = 0;
        if (linked == 0 || linked->f20 == 0xFE || linked->f20 == 0xFD) gone = 1;
        return gone;
    }
    return 1;
}

/* the entry's two faces are either unset or already gone */
/* Tells whether the linked object is gone (or when there is no link, says yes). */
s32 func_L08_00422A40(s32 mobyIndex)
{
    Ent *linked;
    s32 gone;

    if (mobyIndex != -1) {
        linked = D_L08_001B29DC + mobyIndex;
        gone = 0;
        if (linked == 0 || linked->f20 == 0xFE || linked->f20 == 0xFD) gone = 1;
        return gone;
    }
    return 1;
}

/* the entry is a live class or an unset one */
/* Tells whether the linked object is running or gone (or when there is no link, says yes). */
s32 func_L08_003D89D8(s32 mobyIndex)
{
    Ent *linked;
    u32 stateByte;
    s32 ready;

    if (mobyIndex != -1) {
        linked = D_L08_001B29DC + mobyIndex;
        stateByte = linked->f20;
        ready = 0;
        if (stateByte >= 3u || linked == 0 || stateByte == 0xFE || stateByte == 0xFD) ready = 1;
        return ready;
    }
    return 1;
}

/* the entry is a live class or an unset one */
/* Tells whether the linked object is running or gone (or when there is no link, says yes). */
s32 func_L08_00422A88(s32 mobyIndex)
{
    Ent *linked;
    u32 stateByte;
    s32 ready;

    if (mobyIndex != -1) {
        linked = D_L08_001B29DC + mobyIndex;
        stateByte = linked->f20;
        ready = 0;
        if (stateByte >= 3u || linked == 0 || stateByte == 0xFE || stateByte == 0xFD) ready = 1;
        return ready;
    }
    return 1;
}


extern volatile s32 D_001A7344[] __attribute__((sda));
extern void ref_L08_003F76C0_00(void *dest, s32 *position, void *table);
extern float ref_L08_003F76C0_01(void *work, void *table);
extern void ref_L08_003F76C0_02(s32 *position, s32 *x, s32 *y);
extern s32 ref_L08_003F76C0_03(s32 sentinel, u16 x, u16 y, s32 width, s32 rowBytes, s32 flags, float *out);
extern s32 D_001A7340;
extern float ref_L08_003F76C0_04 __attribute__((sda));
extern signed char ref_L08_003F76C0_05[];

typedef struct {
    s32 pad[4];
    s32 x;
    s32 y;
    s32 tail[2];
} QueryWork;

/* Looks up the ground height under the object from the level height map, giving -1 when the spot is off the map. */
float func_L08_003F76C0(void *moby) {
    QueryWork query;
    float groundHeight;
    s32 positionAddr;

    positionAddr = *(s32 *)((signed char *)moby + 0x68) + 0x10;
    ref_L08_003F76C0_00(&query, (s32 *)positionAddr, ref_L08_003F76C0_05);
    groundHeight = ref_L08_003F76C0_01(&query, ref_L08_003F76C0_05 + 0x230);
    ref_L08_003F76C0_02((s32 *)positionAddr, &query.x, &query.y);
    if (query.x < 0 ||
        query.x >= gScreenWidth - 0x10 ||
        query.y < 0 ||
        query.y >= gScreenHeight[0] - 8 ||
        !(groundHeight > 0.0f) ||
        ref_L08_003F76C0_03(-1, (u16)query.x, (u16)query.y, 0x10, 8, 0, &ref_L08_003F76C0_04) == -1) {
        ref_L08_003F76C0_04 = -1.0f;
    }
    return ref_L08_003F76C0_04;
}
