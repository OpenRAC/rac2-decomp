#include "common.h"


extern s32 D_L17_001FE880[];

extern void func_2EEAF8(s32);
extern void func_2EEB28(s32);
extern void func_320B58(s32, s32);
extern void func_327E68(s32, s32, s32, s32, f32);
extern s32 func_31B160(s32);
extern f32 func_2EF0B0(s32, s32);

extern s32 D_L17_001B2748 __attribute__((sda));
extern s32 func_2F0108(u32, u32, f32);
extern f32 func_00283198(f32);

extern s32 D_L17_001B2C1C __attribute__((sda));

extern s32 D_L17_001C0018;
extern s32 func_2DF570(s32, s32, s32, s32, s32);

/* func_L17_003C7C70 is defined in L17_003C7C70-tilt-g8.c. */

/* Slowly pulses the object between two colours (moby class 2363). */
void func_L17_003C8248(s32 moby)
{
    f32 t = (f32)(D_L17_001B2748 % 150) * (1.0f / 150.0f);
    f32 ang = (t + t) * 3.1415927f;

    if (ang > 3.1415927f)
        ang = ang - 6.2831855f;
    *(s32 *)(moby + 0x78) = func_2F0108(0x80464646u, 0x80828282u,
                                      (FastSinOrCosB(ang) + 1.0f) * 0.5f);
}

typedef int TI128 __attribute__((mode(TI)));

/* A 16-byte vector: the engine's helpers take and return these, and the copies between
   them are quadword moves. */
typedef union {
    TI128 q;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } f;
} Vec4;

extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern f32 func_00282C48(f32);

/* Turns the vector at a1 into the object's frame, then into the world with the matrix at
   a0 + 0xC0, and reports whether both of the first two coordinates stay below the two
   bounds. */
s32 func_L17_003CC798(u8 *a0, TI128 *a1, f32 limitY, f32 limitX) {
    Vec4 localPoint[1];
    Vec4 mat[4];
    Vec4 worldPoint[1];
    Vec4 out[1];

    localPoint[0].q = *a1;
    matrix_from_basis_rows(mat, a0 + 0xC0);
    FastVecSub(&out[0].q, &localPoint[0].q, a0 + 0x10);
    worldPoint[0].q = out[0].q;
    transform_vector(&worldPoint[0].q, &worldPoint[0].q, mat);
    if (FloatAbs(worldPoint[0].f.x) < limitX) {
        if (FloatAbs(worldPoint[0].f.y) < limitY)
            return 1;
    }
    return 0;
}

typedef struct {
    u8 pad00[0x80];
    f32 x;
    f32 y;
    f32 z;
    u8 pad8C[0x340 - 0x8C];
    s32 w340;
} L17Player;

extern L17Player D_00189E20;
extern f32 D_L17_001B04BC SDATA(D_L17_001B04BC);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_002AA2E8(void *, f32, f32);
extern void func_00282CD8(void *, void *, void *);

/* Blows the player along the direction it faces, like a fan, while the player stands in
   front of it (moby class 2478). */
void func_L17_003CC850(u8 *moby)
{
    f32 *vars = *(f32 **)(moby + 0x68);
    TI128 here __attribute__((aligned(16)));
    f32 dir[4] __attribute__((aligned(16)));

    vars[2] = D_L17_001B04BC;
    switch (moby[0x20]) {
    case 0:
        *(f32 *)(moby + 0x18) = *(f32 *)(moby + 0x18) - 0.05f;
        moby[0x20] = 1;
        *(u16 *)(moby + 0x34) |= 0x41;
        break;
    case 1:
        break;
    case 2:
        if (!(gHeroState.z < *(f32 *)(moby + 0x18))) {
            break;
        }
        if (!(FastDiffRots(*(f32 *)(moby + 0xF8),
                          FastMatrixHelperA(gHeroState.x - *(f32 *)(moby + 0x10),
                                      gHeroState.y - *(f32 *)(moby + 0x14))) < 1.5707965f)) {
            break;
        }
        if (gHeroState.w340 != 0) {
            break;
        }
        moby[0x20] = 3;
        vars[3] = 0;
        /* fall through */
    case 3:
        if (gHeroState.w340 != 0) {
            moby[0x20] = 1;
            break;
        }
        here = *(TI128 *)&gHeroState.x;
        if (IsPointInsideObjectBounds(moby, &here, 60.0f, 2.5f)) {
            ApproachValue(vars + 3, vars[2] * (1.0f / 60.0f), vars[2] * 0.0011111112544313073f);
        } else {
            ApproachValue(vars + 3, 0.0f, vars[2] * 0.0005555556272156537f);
        }
        dir[0] = FastSinOrCosA(*(f32 *)(moby + 0xF8)) * vars[3];
        dir[1] = FastSinOrCosB(*(f32 *)(moby + 0xF8)) * vars[3];
        dir[2] = 0;
        add_vectors(&here, (u8 *)&gHeroState + 0x100, dir);
        break;
    }
    if (moby[0x20] != 3) {
        if (*(f32 *)(moby + 0x18) <= gHeroState.z) {
            *(TI128 *)dir = *(TI128 *)&gHeroState.x;
            if (IsPointInsideObjectBounds(moby, (TI128 *)dir, vars[0], vars[1])) {
                moby[0x20] = 2;
                return;
            }
        }
        if (moby[0x20] != 3) {
            moby[0x20] = 1;
        }
    }
}



extern u16 *D_L17_001FB720[];

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit; the limit
   word is loaded in a branch delay slot, so there it becomes the `$gp` form. The pool base is
   the word D_L17_001B2C1C declared above as an int, reached here as a pointer under a second
   name. */
extern u8 *D_L17_001B2C1C_base[] __asm__("D_L17_001B2C1C") __attribute__((sda));
extern s32 D_L17_001B2C38[] __attribute__((sda));

/* The object's state record up to the group word and the word stored beside it. */
typedef struct {
    u8 pad[0x43C];
    s32 group;
    s32 mode;
} L17GroupState;

/* Walks the id list of the state's group and sets the state's mode word to 0x57 for every id
   that has an entity, stopping at the first that has none. */
void func_L17_003E3148(u8 *moby)
{
    L17GroupState *state = *(L17GroupState **)(moby + 0x68);
    u16 *groupIds;
    u8 *entity;

    for (groupIds = D_L17_001FB720[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= D_L17_001B2C38[0] && groupIds != 0 &&
         ((groupIds != 0 && (s16)groupIds[-1] >= 0) || groupIds == D_L17_001FB720[state->group]);
         groupIds++) {
        entity = D_L17_001B2C1C_base[0] + ((*groupIds & 0x7FFF) << 8);
        if (entity == 0)
            break;
        state->mode = 0x57;
    }
}





/* Updates the creature's animation and counts up a frame counter. */
void func_L17_003E47E8(s32 moby) {
    s32 vars = *(s32 *)(moby + 0x68);

    func_320B58(moby, vars + 0x50);
    func_2EEAF8(vars + 0x3FC);
    func_2EEB28(vars + 0x402);
    if (*(u16 *)(moby + 0x96) < 0xFFFF) {
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
    }
    func_327E68(moby, vars + 0x350, 1, 1, 2.5f);
}




/* Claims the shared slot at state+0x720 for this object (index into the object array):
   taken when free or when its holder is in state 0xFE/0xFD, then in mode 1 handed to the
   nearest candidate; returns 1 once this object holds it in mode 2. func_L17_003E6F20
   releases it. */
extern float func_00282E48(void *, void *);

int func_L17_003E6DE8(char *object)
{
    char *base = (char *)gMobyPool_L17;
    int index = (object - base) >> 8;
    char *state = *(char **)(object + 0x68);
    int other;
    char *target;
    float *nearest;
    float *best;
    float distance;

    if (*(u8 *)(object + 0x21) == 0xFF)
        return 1;
    other = **(int **)(state + 0x720);
    if (other == -1 || (target = base + (other << 8)) == 0
        || *(u8 *)(target + 0x20) == 0xFE || *(u8 *)(target + 0x20) == 0xFD) {
        **(int **)(state + 0x720) = index;
        **(int **)(state + 0x748) = 1;
        nearest = *(float **)(state + 0x74C);
        *nearest = fast_vec_dist(object + 0x10, state + 0x240);
        return 0;
    }
    if (**(int **)(state + 0x748) == 1) {
        if (index == other) {
            **(int **)(state + 0x748) = 2;
            return 1;
        }
        distance = fast_vec_dist(object + 0x10, state + 0x240);
        best = *(float **)(state + 0x74C);
        if (distance < *best) {
            **(int **)(state + 0x720) = index;
            *best = distance;
            return 0;
        }
    }
    if (**(int **)(state + 0x748) == 2 && **(int **)(state + 0x720) == index)
        return 1;
    return 0;
}

/* Gives up the shared slot if this object is the one holding it. */
void func_L17_003E6F20(s32 moby)
{
    s32 vars = *(s32 *)(moby + 0x68);
    s32 *slot = *(s32 **)(vars + 0x720);

    if (*slot == (moby - gMobyPool_L17) >> 8) {
        *slot = -1;
        *(s32 *)(*(s32 *)(vars + 0x748)) = 0;
    }
}

/* Picks a random point on the object's path that is more than 3 units away from it. */
s32 func_L17_003E6F58(s32 moby) {
    s32 pointIndex;
    s32 path = gPathTable_L17[*(s32 *)(*(s32 *)(moby + 0x68) + 0x684)];
    s32 pointCount = *(s32 *)path;
    s32 attempts = 0;

    do {
        s32 offset;

        pointIndex = func_31B160(pointCount);
        offset = (pointIndex << 4) + 0x10;
        if (func_2EF0B0(moby + 0x10, path + offset) > 3.0f) {
            return pointIndex;
        }
    } while (++attempts < 5);
    return pointIndex;
}

/* Tells whether the way to the target is clear (1 if nothing blocks it). */
s32 func_L17_003E7010(s32 moby) {
    s32 vars = *(s32 *)(moby + 0x68);

    if (func_2DF570(moby + 0x10, vars + 0x240, 0, moby, 0) == 0)
        return 1;
    return D_L17_001C0018 == *(s32 *)(vars + 0x250);
}

/* func_L17_003E8A58 is defined in L17_003E8A58-fighter-g8.c. */

/* func_L17_00417DB0 is in L17_003C7C70-f7-g8.c. */



/* func_L17_0041E208 is defined in L17_0041E208-g8.c. */

/* func_L17_0041EAA8 is defined in L17_003C7C70-g8.c. */

typedef struct { unsigned char pad[0x464]; unsigned char flags[0]; } PickupFlags;
extern PickupFlags D_L17_0021EBB0;
extern unsigned char D_0019B4A8[], D_0013963C, D_001395B8[];
extern int D_001A79F0 SDATA(D_001A79F0);
typedef struct { unsigned char pad[0x20]; unsigned char state; unsigned char rest[0xDF]; } Entity;
extern Entity *entity_base_ptr __asm__("D_L17_001B2C1C") __attribute__((sda));
extern Entity *entity_base_gp SDATA(D_L17_001B2C1C);
extern char D_00189EA0[];
extern float func_00283B98(float,float), func_002A7878(float,float), func_002A7940(void), func_002A78D8(float,float);
extern int func_002A77E0(int);
extern void func_002AF000(void *,float,float,float);
extern void *func_002C2210(void *,int,unsigned,int,int,void *,float,float,float,int);
extern float func_00282E80(void *,void *);
extern void func_L00_003294F0(void *,int),func_002A7750(void *,int,int),func_0029F338(void *),func_002B0A18(int,int);
extern int func_00288E18(int,int);
/* Spins and sparkles an uncollected pickup; when the player comes within 1.5 units it bumps the
   pickup's saved count and triggers its linked entity, and when inactive it removes itself once
   that entity dies. */
void func_L17_0041ED58(unsigned char *moby)
{
    int *vars=*(int **)(moby+0x68);
    unsigned short id;
    unsigned char *position;
    int pass,sign,count;
    int bits;
    float size,ang,speed,scale;
    float vel[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    if(moby[0x20]!=0) goto inactive;
    id=*(unsigned short *)(moby+0xb2);
    if(D_L17_0021EBB0.flags[(short)id]!=0) goto remove_self;
    {
        bits=D_0019B4A8[((short)id>>1)+(gCurrentMapIndex<<10)];
        if(id&1) bits=(bits>>4)&7; else bits=bits&7;
        if(bits) goto remove_self;
        position=moby+0x10;
        {
            *(float *)(moby+0xf8)=FastAddRotations(*(float *)(moby+0xf8),0.087266474f);
            pass=1;
            do {
                size=RandomFloatRange(2.0f,5.0f);
                sign=RandomIntBelow(2); if(sign==0)--sign;
                ang=RandomAngle();
                speed=RandomFloatRange(0.3490659f,1.5358899f);
                scale=RandomFloatRange(0.05f,0.1f);
                BuildSphericalOffset(vel,scale,ang,speed);
                qcopy(pos,position);
                pos[0]+=RandomSignedFloatRange(0.0f,0.15f);
                pos[1]+=RandomSignedFloatRange(0.0f,0.15f);
                pos[2]+=RandomSignedFloatRange(0.0f,0.15f);
                SpawnGroundEffectParticle(pos,3,0x208020ff,0,sign,vel,size*0.1f,size,0.006f,0);
                SpawnGroundEffectParticle(pos,3,0x20ffffff,1,-sign,vel,size*0.03f,size*0.3f,0.006f,0);
            } while(--pass>=0);
            if(vec_distance_xy(position,gHeroPosition)<1.5f) {
                unsigned short pickupId;
                unsigned char *counter;
                D_0013963C=1;
                pickupId=*(unsigned short *)(moby+0xb2);
                if(pickupId&1) {
                    counter=(((short)pickupId>>1)+(gCurrentMapIndex<<10))+D_0019B4A8;
                    if(((*counter>>4)&7)!=7)*counter+=16;
                } else {
                    counter=(((short)pickupId>>1)+(gCurrentMapIndex<<10))+D_0019B4A8;
                    if((*counter&7)!=7)++*counter;
                }
                if(*(int *)vars!=-1) {
                    ((unsigned short *)moby)[0x1a]|=1;
                    moby[0x31]=0;
                    SetObjectFlagBit(&entity_base_ptr[*vars],1);
                    SetMobyState(moby,1,-1);
                } else goto remove_self;
            }
            return;
        }
    }
remove_self:
    MarkMobySpawned(moby);
    return;
inactive:
    if(*(int *)vars!=-1) {
        int state;
        state=entity_base_gp[*vars].state;
        if(state==0xfe)goto dead;
        if(state!=0xfd)goto done;
    }
dead:
    {
        SetEntryValueByIndex(0x1292,0x78);
        count=D_001395B8[0x86]?1:2;
        if(D_001395B8[0x89])--count;
        if(count>0)RequestSubtitleVoiceLine(0xa0f,0x66);else RequestSubtitleVoiceLine(0xa10,0x67);
        MarkMobySpawned(moby);
    }
done:;
}

/* func_L17_0041F180 is defined in L17_collision.c. */

/* func_L17_0041F478 is defined in L17_003C7C70-link.c. */


/* func_L17_00420758 is defined in L17_collision.c. */

/* func_L17_00420A50 is defined in L17_00420A50-g8.c. */

/* func_L17_00420E08 is defined in L17_003C7C70-g8.c. */
