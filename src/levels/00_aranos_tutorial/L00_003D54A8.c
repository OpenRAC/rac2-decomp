#include "include_asm.h"
#include "common.h"

extern int func_00282948(int *);
extern int func_002A7820(int, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
/* EE integer and floating-point argument banks retain their independent order. */
extern void func_L00_00338E90(void *, void *, int, float, int, int);



extern void func_L00_003DA2B0(char *);
extern long long func_0027C878(int);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_002A7940(void);
extern void func_00283410(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);
typedef struct { char pad[0x140]; float x,y,z; } AimVector10;
extern AimVector10 D_L00_001B8C80;
/* Draws a two-layer glowing sprite stretched between a point and the hero, used for the tutorial aim marker. */
void func_L00_003DA548(int unused, char *pos, int color, int first, int second, float scale)
{
    char sprite[144];
    float matrix[16];
    float rotation[4];
    float midOffset[4];
    long long texture;
    float dx, dy;

    InitLargeSpritePacketB(sprite);
    *(int *)(sprite + 80) = 0;
    *(float *)(sprite + 92) = 1.0f;
    *(float *)(sprite + 96) = 1.0f;
    *(float *)(sprite + 104) = 1.0f;
    *(float *)(sprite + 108) = 1.0f;
    *(int *)(sprite + 84) = 0;
    *(int *)(sprite + 88) = 0;
    *(int *)(sprite + 100) = 0;
    texture = GetEffectTextureDescriptor(11);
    *(long long *)(sprite + 112) = 0;
    *(long long *)(sprite + 120) = texture;
    *(long long *)(sprite + 128) = 0xFF9000000260LL;
    *(long long *)(sprite + 136) = 0x8000000048LL;
    dx = D_L00_001B8C80.x - *(float *)pos;
    dy = D_L00_001B8C80.y - *(float *)(pos + 4);
    *(int *)(sprite + 76) = color + first;
    *(int *)(sprite + 72) = color + first;
    *(int *)(sprite + 68) = color + first;
    *(int *)(sprite + 64) = color + first;
    rotation[3] = 0;
    rotation[2] = FastMatrixHelperA(dx, dy);
    rotation[1] = -FastMatrixHelperA(vec_distance_xy(pos, &D_L00_001B8C80.x),
                              D_L00_001B8C80.z - *(float *)(pos + 8));
    rotation[0] = RandomAngle();
    euler_to_matrix(matrix, rotation);
    FastVecSub(midOffset, &D_L00_001B8C80.x, pos);
    vec_scale_to_length(midOffset, midOffset, 0.5f);
    matrix[12] = *(float *)(pos) + midOffset[0];
    matrix[13] = *(float *)(pos + 4) + midOffset[1];
    matrix[14] = *(float *)(pos + 8) + midOffset[2];
    matrix[15] = 1.0f;
    FastVecScale(sprite, sprite, scale);
    FastVecScale(sprite + 16, sprite + 16, scale);
    FastVecScale(sprite + 32, sprite + 32, scale);
    FastVecScale(sprite + 48, sprite + 48, scale);
    draw_world_quad(sprite, matrix, 0);
    *(int *)(sprite + 76) = color + second;
    *(int *)(sprite + 72) = color + second;
    *(int *)(sprite + 68) = color + second;
    *(int *)(sprite + 64) = color + second;
    FastVecScale(sprite, sprite, 0.5f);
    FastVecScale(sprite + 16, sprite + 16, 0.5f);
    FastVecScale(sprite + 32, sprite + 32, 0.5f);
    FastVecScale(sprite + 48, sprite + 48, 0.5f);
    draw_world_quad(sprite, matrix, 0);
}



/* Tutorial prompts, interaction locks and traversal visibility. */
extern char D_00189EA0[];
typedef struct { char pad[0x2290]; unsigned char *moby; char pad2[0x238]; int count; } TutorialPlayer;
extern TutorialPlayer D_00189E20;
extern unsigned short D_0018C958[];
extern unsigned short D_0018C840[],D_0018C7B0[],D_0018C828[];
extern int D_001A7A00 __attribute__((sda)),D_001A7398 __attribute__((sda));
extern unsigned char *D_L00_001B1EA8 __attribute__((sda));
typedef struct {int active;char pad[0x20];int id;} TutorialPromptState;
extern TutorialPromptState D_L00_0027D848;
extern float func_00282E48(void *,void *);
extern int func_00312E10(void *);
extern void func_00288E18(int,int);
extern int func_002ACBC8(void *,int);
extern int func_002A8508(int,int),func_00288D58(void),func_00288FB8(int);
extern void func_00285828(int,int,int,int),func_00285788(int,int),func_002B49E0(int,int,int,int,int);
/* Shows tutorial help prompts when the hero reaches the matching trigger area, and locks interaction while a prompt is up. */
void func_L00_003E7768(unsigned char *object) {
    int *zones=*(int **)(object+0x68);
    unsigned char *nearby;
    switch(object[0x20]) {
    case 0:
        object[0x30]=255; object[0x20]=1; break;
    case 1:
        if(!gSubtitleHistory[0x48/2]) {
            for(nearby=D_L00_001B1EA8;nearby;nearby=*(unsigned char **)(nearby+0x28)) {
                if(*(short *)(nearby+0xaa)==0x326 && fast_vec_dist(nearby+0x10,gHeroPosition)<10.0f && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !gSubtitleHistory[0x48/2] && !IsMobyInState1_00312E10(nearby)) {
                    if(gHeroState.count<D_001A7A00) RequestSubtitleVoiceLine(0x9af,6);
                    else if(fast_vec_dist(nearby+0x10,gHeroPosition)<1.0f && !gSubtitleHistory[0x2e8/2]) RequestSubtitleVoiceLine(0x9e7,0x3e);
                }
            }
        }
        if(IsPointInCuboid(gHeroPosition,zones[0]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !gSubtitleHistory[0x18/2]) RequestSubtitleVoiceLine(0x9ab,2);
        if(IsPointInCuboid(gHeroPosition,zones[1]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !gSubtitleHistory[0x24/2] && !gSubtitleHistory[0x30/2]) {
            if(D_001A7398==30) RequestSubtitleVoiceLine(0x9ac,3);
            else if(D_001A7398==42) RequestSubtitleVoiceLine(0x9ad,4);
        }
        if(IsPointInCuboid(gHeroPosition,zones[3]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !gSubtitleHistory[0x54/2] && !gSubtitleHistory[0x60/2] && !gSubtitleHistory[0x6c/2] && CountMobysInGroupNotInState(zones[5],-1)) {
            if(D_001A7398==42) RequestSubtitleVoiceLine(0x9b0,7);
            else if(D_0018C840[0]) RequestSubtitleVoiceLine(0x9b1,8);
            else RequestSubtitleVoiceLine(0x9b2,9);
        }
        if(IsPointInCuboid(gHeroPosition,zones[2]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1) {
            if(IsFlagByteSet() && !gSubtitleHistory[0x5a0/2]) {
                int first,second;
                gSubtitleHistory[0x5a0/2]=1;
                first=GetLocalizedString(0x112b);second=GetLocalizedString(0xa21);
                StoreFourSettings(first,0,second,1);SetMenuSizeLimits(0x40,0);BeginSlotRequest(4,1,10,0,0);
            } else if(!IsFlagByteSet() && !gSubtitleHistory[0x3c/2] && !D_0018C7B0[0]) RequestSubtitleVoiceLine(0x9ae,5);
        }
        if(IsPointInCuboid(gHeroPosition,zones[4]) && !D_0018C828[0] && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !gSubtitleHistory[0x78/2]) RequestSubtitleVoiceLine(0x9b3,10);
        break;
    }
    gHeroState.moby[0x7e]|=1;
    { unsigned char *scanMoby; for(scanMoby=D_L00_001B1EA8;scanMoby;scanMoby=*(unsigned char **)(scanMoby+0x28)) if(*(short *)(scanMoby+0xaa)==0xac1) scanMoby[0x7e]|=1; }
    if(IsPointInCuboid(gHeroPosition,zones[6]) || IsPointInCuboid(gHeroPosition,zones[7])) gHeroPosition[0x2470]=1;
    else gHeroPosition[0x2470]=0;
}

/* Emits bursts of small particles from the object, waiting a random time between bursts. */
void func_L00_003EACC0(unsigned char *moby) {
    float velocity[4], pos[4];
    float firstSize, secondRadius, z;
    int *vars = *(int **)(moby + 0x68);
    unsigned char *origin;

    if (moby[0x20] == 0) {
        moby[0x30] = 0x80;
        moby[0x20] = 1;
        vars[1] = 20;
        vars[0] = 0;
    }
    if (moby[0x20] == 1) {
        if (FastFloatHelperD(vars)) {
            moby[0x20] = 2;
            vars[0] = RandomIntRange(50, 120);
        }
    }
    if (moby[0x20] == 2) {
        if (FastFloatHelperD(vars + 1)) {
            moby[0x20] = 1;
            vars[1] = RandomIntRange(10, 25);
        } else {
            velocity[0] = FastSinOrCosA(*(float *)(moby + 0xf8) - 1.570796489715576171875f)
                   * 0.416666686534881591797f;
            velocity[1] = FastSinOrCosB(*(float *)(moby + 0xf8) - 1.570796489715576171875f)
                   * 0.416666686534881591797f;
            velocity[2] = 0.0f;
            origin = moby + 0x10;
            qcopy(pos, origin);
            z = velocity[2];
            pos[2] += RandomSignedFloatRange(z, 0.5f);
            firstSize = RandomFloatRange(0.1f, 3.0f);
            SpawnAranosSpark(pos, velocity, 300, firstSize,
                             FloatToInt(RandomSignedFloatRange(1.0f, 4.0f)), 0x40808080);
            qcopy(pos, origin);
            pos[2] += RandomSignedFloatRange(z, 0.5f);
            secondRadius = RandomFloatRange(0.1f, 3.0f);
            SpawnAranosSpark(pos, velocity, 300, secondRadius,
                             FloatToInt(RandomSignedFloatRange(1.0f, 4.0f)), 0x40808080);
        }
    }
}

extern int func_002ACBC8(void *a0, int a1);
extern char D_00189EA0[];
extern float D_L00_001B1AE8 __attribute__((sda));

/* Sets a global value to 30 when the hero is inside the area, otherwise to 95. */
void func_L00_003EB3B8(void *moby) {
    int heroInside = IsPointInCuboid(gHeroPosition,
                               *(int *)*(int *)((char *)moby + 0x68));
    if (heroInside != 0) {
        D_L00_001B1AE8 = 30.0f;
    } else {
        D_L00_001B1AE8 = 95.0f;
    }
}


extern int func_002A77E0(int);
/* EE integer and floating-point argument banks retain their independent order. */
extern unsigned char *func_002BDCE8(void *, float, float, float, int, void *, float, int, int);
/* Spawns three particle bursts at the object. The second burst updates the first
 * particle's header, as retail does. */
/* Spawns three particle bursts at the object. */
void func_L00_003EE288(unsigned char *moby)
{
    float velocity[4], pos[4];
    float one = 1.0f;
    int spin;
    unsigned char *first, *second, *third;
    unsigned char *particle1, *particle2, *particle3;

    velocity[0] = 0.0f;
    velocity[1] = -0.5f;
    velocity[2] = 0.0f;
    velocity[3] = one;
    spin = RandomIntBelow(16);
    if (RandomIntBelow(2)) {
        spin = -spin;
    }
    qcopy(pos, moby + 0x10);
    first = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, spin, velocity, 630000.0f, 0xDF204080, 0);
    if (first) {
        particle1 = first + 0x20;
        *(unsigned short *)(first + 0xA) = 25;
        first[9] = FloatToInt(4.0f) + 112;
        *(int *)(particle1 + 4) = 2;
        particle1[0xA] = 0xDF;
        particle1[0xB] = first[0xA];
    }
    second = SpawnSpinningSparkParticle(pos, 0.1f, 1.0f, 0.9f, spin, velocity, 630000.0f, 0xDF204080, 0);
    if (second) {
        particle2 = second + 0x20;
        *(unsigned short *)(first + 0xA) = 25;
        first[9] = FloatToInt(4.0f) + 112;
        *(int *)(particle2 + 4) = 2;
        particle2[0xA] = 0xDF;
        particle2[0xB] = first[0xA];
    }
    third = SpawnSpinningSparkParticle(pos, 0.05f, 1.0f, 0.97f, 16, velocity, 315000.0f, 0xDFFFFFFF, 0);
    if (third) {
        int v;
        particle3 = third + 0x20;
        v = FloatToInt(4.0f);
        *(unsigned short *)(third + 0xA) = 35;
        third[9] = v + 112;
        third[8] = RandomIntBelow(255);
        *(int *)(particle3 + 4) = 2;
        particle3[0xA] = 0xDF;
        particle3[0xB] = first[0xA];
    }
}


/* Aranos controller: initialize linked objects and drive the two scripted sequences. */
typedef struct { char pad[0x464]; unsigned char collected[0]; } ControllerLevelState;
extern ControllerLevelState D_L00_0021DDB0;
extern unsigned char D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
extern int D_L00_001A8F00 __attribute__((sda));
extern unsigned char *D_L00_001B1E9C __attribute__((sda));
extern char D_L00_001A8F20[] __attribute__((sda));
extern char D_L00_001B1010[];
typedef struct { char pad[0x30]; int phase, frame; char pad2[0x15c]; int first, second; } Controller10;
extern Controller10 D_L00_001BCAC0;
extern void func_0029F338(void *);
extern void func_00325B70(int, void *, int, int);
extern void func_00325C50(int, float, void *, int, void *);
extern float func_00283B98(float, float);
extern void func_002E5CF8(int, int, void *);
extern void func_0026FEB8(void *);
typedef struct { char pad[0x20]; unsigned char state; char pad2[3]; char *classData; char pad3[0xC]; unsigned short flags; char pad4[0x62]; int field98; } ControllerMoby10;
/* Updates the Aranos controller object, which runs the two scripted camera and object sequences. */
void func_L00_0040D648(unsigned char *object)
{
    int *vars = *(int **)(object + 0x68);
    unsigned char *counter;

    switch (object[0x20]) {
    case 0:
        vars[9] = 0;
        vars[10] = 0;
        vars[12] = 0;
        vars[13] = 0;
        object[0x30] = 255;
        object[0x20] = 1;
        if (!D_L00_0021DDB0.collected[(short)*(unsigned short *)(object + 0xb2)]) {
            int countByte = D_0019B4A8[((short)*(unsigned short *)(object + 0xb2) >> 1) + (gCurrentMapIndex << 10)];
            /* One 3-bit count per nibble; the low bit of the number picks the nibble. */
            if (!((*(unsigned short *)(object + 0xb2) & 1) ? (countByte >> 4) & 7 : countByte & 7)) {
                return;
            }
        }
        if (vars[17] != -1) {
            MarkMobySpawned(D_L00_001B1E9C + (vars[17] << 8));
        }
        if (vars[16] != -1) {
            MarkMobySpawned(D_L00_001B1E9C + (vars[16] << 8));
        }
        break;
    case 1:
        if (D_L00_001A8F00 != 2 && vars[8] != -1) {
            ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (vars[8] << 8));
            other->flags = (other->flags & 0xffbe) | 0x1000;
            other->field98 = *(int *)(other->classData + 0x10);
        }
        if (D_L00_001BCAC0.phase == 1 && D_L00_001A8F00 == 2) {
            if (D_L00_001BCAC0.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (vars[8] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                if (vars[17] != -1) {
                    MarkMobySpawned(D_L00_001B1E9C + (vars[17] << 8));
                }
                if (vars[16] != -1) {
                    MarkMobySpawned(D_L00_001B1E9C + (vars[16] << 8));
                }
                if (*(unsigned short *)(object + 0xb2) & 1) {
                    counter = D_0019B4A8 + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (gCurrentMapIndex << 10));
                    if (((*counter >> 4) & 7) != 7) {
                        *counter += 16;
                    }
                } else {
                    counter = D_0019B4A8 + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (gCurrentMapIndex << 10));
                    if ((*counter & 7) != 7) {
                        ++*counter;
                    }
                }
                SpawnEnemyChildParts(D_L00_001BCAC0.first, vars + 9, 0, 2);
            } else {
                int first = D_L00_001BCAC0.first;
                if (D_L00_001BCAC0.frame >= 1976) {
                    *(float *)(vars + 11) = FastAddRotations(*(float *)(vars + 11), 0.436332345f);
                    AttachAndTurnChildParts(first, *(float *)(vars + 11), vars + 9, 1, D_L00_001A8F20);
                } else {
                    AttachAndTurnChildParts(first, *(float *)(vars + 11), vars + 9, 0, D_L00_001A8F20);
                }
            }
            if (D_L00_001BCAC0.frame == 223) {
                int i;
                for (i = 0; i < 2; i++) {
                    ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (vars[i] << 8));
                    if (other && other->state != 254 && other->state != 253) {
                        PlayMobySound(0, 0, other);
                        other->state = 1;
                    }
                }
            }
            if (D_L00_001BCAC0.frame == 226) {
                STUB_printf(D_L00_001B1010);
            }
        }
        if (D_L00_001A8F00 != 2) {
            if (vars[9]) {
                MarkMobySpawned((void *)vars[9]);
                MarkMobySpawned((void *)vars[10]);
                vars[9] = 0;
                vars[10] = 0;
            }
            if (vars[12]) {
                MarkMobySpawned((void *)vars[12]);
                MarkMobySpawned((void *)vars[13]);
                vars[12] = 0;
                vars[13] = 0;
            }
        }
        if (D_L00_001BCAC0.phase == 2 && D_L00_001A8F00 == 2) {
            if (D_L00_001BCAC0.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (vars[4] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                {
                    int i;
                    for (i = 0; i < 3; i++) {
                        ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (vars[5 + i] << 8));
                        other->field98 = 0;
                        other->flags = (other->flags | 0x41) & 0xefff;
                    }
                }
                SpawnEnemyChildParts(D_L00_001BCAC0.first, vars + 9, 0, 2);
                SpawnEnemyChildParts(D_L00_001BCAC0.second, vars + 12, 0, 2);
            } else {
                int first = D_L00_001BCAC0.first, second = D_L00_001BCAC0.second;
                if (D_L00_001BCAC0.frame < 780) {
                    *(float *)(vars + 11) = FastAddRotations(*(float *)(vars + 11), 0.261799425f);
                    *(float *)(vars + 14) = FastAddRotations(*(float *)(vars + 14), 0.261799425f);
                    AttachAndTurnChildParts(first, *(float *)(vars + 11), vars + 9, 1, D_L00_001A8F20);
                    AttachAndTurnChildParts(second, *(float *)(vars + 14), vars + 12, 1, D_L00_001A8F20);
                } else {
                    *(float *)(vars + 11) = FastAddRotations(*(float *)(vars + 11), 0.087266475f);
                    *(float *)(vars + 14) = FastAddRotations(*(float *)(vars + 14), 0.087266475f);
                    AttachAndTurnChildParts(first, *(float *)(vars + 11), vars + 9, 0, D_L00_001A8F20);
                    AttachAndTurnChildParts(second, *(float *)(vars + 14), vars + 12, 0, D_L00_001A8F20);
                }
            }
        }
        break;
    }
}

/* func_L00_0040EAA0 is in L00_003D54A8-f7-g8.c. */



/* Marks the object as ready on its first frame by setting a flag. */
void func_L00_00419B80(void *moby) {
    unsigned char *mobyBytes = (unsigned char *)moby;
    if (mobyBytes[0x20] == 0) {
        mobyBytes[0x20] = 1;
        *(unsigned short *)(mobyBytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void func_L00_00419BA8(void *moby) {
    unsigned char *mobyBytes = (unsigned char *)moby;
    if (mobyBytes[0x20] == 0) {
        mobyBytes[0x20] = 1;
        *(unsigned short *)(mobyBytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void func_L00_00419BD0(void *moby) {
    unsigned char *mobyBytes = (unsigned char *)moby;
    if (mobyBytes[0x20] == 0) {
        mobyBytes[0x20] = 1;
        *(unsigned short *)(mobyBytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void func_L00_00419BF8(void *moby) {
    unsigned char *mobyBytes = (unsigned char *)moby;
    if (mobyBytes[0x20] == 0) {
        mobyBytes[0x20] = 1;
        *(unsigned short *)(mobyBytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void func_L00_00419C20(void *moby) {
    unsigned char *mobyBytes = (unsigned char *)moby;
    if (mobyBytes[0x20] == 0) {
        mobyBytes[0x20] = 1;
        *(unsigned short *)(mobyBytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void func_L00_00419C48(void *moby) {
    unsigned char *mobyBytes = (unsigned char *)moby;
    if (mobyBytes[0x20] == 0) {
        mobyBytes[0x20] = 1;
        *(unsigned short *)(mobyBytes + 0x34) |= 0x800;
    }
}

/* Marks the object as ready on its first frame by setting a flag. */
void func_L00_00419C70(void *moby) {
    unsigned char *mobyBytes = (unsigned char *)moby;
    if (mobyBytes[0x20] == 0) {
        mobyBytes[0x20] = 1;
        *(unsigned short *)(mobyBytes + 0x34) |= 0x800;
    }
}
