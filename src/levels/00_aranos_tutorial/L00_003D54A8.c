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
void func_L00_003DA548(int unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    func_L00_003DA2B0(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_0027C878(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = D_L00_001B8C80.x - *(float *)pos;
    dy = D_L00_001B8C80.y - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_00283248(dx, dy);
    quat[1] = -func_00283248(func_00282E80(pos, &D_L00_001B8C80.x),
                              D_L00_001B8C80.z - *(float *)(pos + 8));
    quat[0] = func_002A7940();
    func_00283410(m, quat);
    func_00282CF0(off, &D_L00_001B8C80.x, pos);
    func_00282F20(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    func_00282D30(pkt, pkt, scale);
    func_00282D30(pkt + 16, pkt + 16, scale);
    func_00282D30(pkt + 32, pkt + 32, scale);
    func_00282D30(pkt + 48, pkt + 48, scale);
    func_00280B90(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    func_00282D30(pkt, pkt, 0.5f);
    func_00282D30(pkt + 16, pkt + 16, 0.5f);
    func_00282D30(pkt + 32, pkt + 32, 0.5f);
    func_00282D30(pkt + 48, pkt + 48, 0.5f);
    func_00280B90(pkt, m, 0);
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
void func_L00_003E7768(unsigned char *object) {
    int *state=*(int **)(object+0x68);
    unsigned char *other;
    switch(object[0x20]) {
    case 0:
        object[0x30]=255; object[0x20]=1; break;
    case 1:
        if(!D_0018C958[0x48/2]) {
            for(other=D_L00_001B1EA8;other;other=*(unsigned char **)(other+0x28)) {
                if(*(short *)(other+0xaa)==0x326 && func_00282E48(other+0x10,D_00189EA0)<10.0f && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x48/2] && !func_00312E10(other)) {
                    if(D_00189E20.count<D_001A7A00) func_00288E18(0x9af,6);
                    else if(func_00282E48(other+0x10,D_00189EA0)<1.0f && !D_0018C958[0x2e8/2]) func_00288E18(0x9e7,0x3e);
                }
            }
        }
        if(func_002ACBC8(D_00189EA0,state[0]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x18/2]) func_00288E18(0x9ab,2);
        if(func_002ACBC8(D_00189EA0,state[1]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x24/2] && !D_0018C958[0x30/2]) {
            if(D_001A7398==30) func_00288E18(0x9ac,3);
            else if(D_001A7398==42) func_00288E18(0x9ad,4);
        }
        if(func_002ACBC8(D_00189EA0,state[3]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x54/2] && !D_0018C958[0x60/2] && !D_0018C958[0x6c/2] && func_002A8508(state[5],-1)) {
            if(D_001A7398==42) func_00288E18(0x9b0,7);
            else if(D_0018C840[0]) func_00288E18(0x9b1,8);
            else func_00288E18(0x9b2,9);
        }
        if(func_002ACBC8(D_00189EA0,state[2]) && !D_L00_0027D848.active && D_L00_0027D848.id==-1) {
            if(func_00288D58() && !D_0018C958[0x5a0/2]) {
                int first,second;
                D_0018C958[0x5a0/2]=1;
                first=func_00288FB8(0x112b);second=func_00288FB8(0xa21);
                func_00285828(first,0,second,1);func_00285788(0x40,0);func_002B49E0(4,1,10,0,0);
            } else if(!func_00288D58() && !D_0018C958[0x3c/2] && !D_0018C7B0[0]) func_00288E18(0x9ae,5);
        }
        if(func_002ACBC8(D_00189EA0,state[4]) && !D_0018C828[0] && !D_L00_0027D848.active && D_L00_0027D848.id==-1 && !D_0018C958[0x78/2]) func_00288E18(0x9b3,10);
        break;
    }
    D_00189E20.moby[0x7e]|=1;
    { unsigned char *scan; for(scan=D_L00_001B1EA8;scan;scan=*(unsigned char **)(scan+0x28)) if(*(short *)(scan+0xaa)==0xac1) scan[0x7e]|=1; }
    if(func_002ACBC8(D_00189EA0,state[6]) || func_002ACBC8(D_00189EA0,state[7])) D_00189EA0[0x2470]=1;
    else D_00189EA0[0x2470]=0;
}

void func_L00_003EACC0(unsigned char *p) {
    float v[4], pos[4];
    float radius, secondRadius, z;
    int *s = *(int **)(p + 0x68);
    unsigned char *base;

    if (p[0x20] == 0) {
        p[0x30] = 0x80;
        p[0x20] = 1;
        s[1] = 20;
        s[0] = 0;
    }
    if (p[0x20] == 1) {
        if (func_00282948(s)) {
            p[0x20] = 2;
            s[0] = func_002A7820(50, 120);
        }
    }
    if (p[0x20] == 2) {
        if (func_00282948(s + 1)) {
            p[0x20] = 1;
            s[1] = func_002A7820(10, 25);
        } else {
            v[0] = func_00283180(*(float *)(p + 0xf8) - 1.570796489715576171875f)
                   * 0.416666686534881591797f;
            v[1] = func_00283198(*(float *)(p + 0xf8) - 1.570796489715576171875f)
                   * 0.416666686534881591797f;
            v[2] = 0.0f;
            base = p + 0x10;
            qcopy(pos, base);
            z = v[2];
            pos[2] += func_002A78D8(z, 0.5f);
            radius = func_002A7878(0.1f, 3.0f);
            func_L00_00338E90(pos, v, 300, radius,
                             func_00283CF0(func_002A78D8(1.0f, 4.0f)), 0x40808080);
            qcopy(pos, base);
            pos[2] += func_002A78D8(z, 0.5f);
            secondRadius = func_002A7878(0.1f, 3.0f);
            func_L00_00338E90(pos, v, 300, secondRadius,
                             func_00283CF0(func_002A78D8(1.0f, 4.0f)), 0x40808080);
        }
    }
}

extern int func_002ACBC8(void *a0, int a1);
extern char D_00189EA0[];
extern float D_L00_001B1AE8 __attribute__((sda));

void func_L00_003EB3B8(void *a0) {
    int result = func_002ACBC8(D_00189EA0,
                               *(int *)*(int *)((char *)a0 + 0x68));
    if (result != 0) {
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
void func_L00_003EE288(unsigned char *p)
{
    float vel[4], pos[4];
    float one = 1.0f;
    int n;
    unsigned char *first, *second, *third;
    unsigned char *particle1, *particle2, *particle3;

    vel[0] = 0.0f;
    vel[1] = -0.5f;
    vel[2] = 0.0f;
    vel[3] = one;
    n = func_002A77E0(16);
    if (func_002A77E0(2)) {
        n = -n;
    }
    qcopy(pos, p + 0x10);
    first = func_002BDCE8(pos, 0.1f, 1.0f, 0.9f, n, vel, 630000.0f, 0xDF204080, 0);
    if (first) {
        particle1 = first + 0x20;
        *(unsigned short *)(first + 0xA) = 25;
        first[9] = func_00283CF0(4.0f) + 112;
        *(int *)(particle1 + 4) = 2;
        particle1[0xA] = 0xDF;
        particle1[0xB] = first[0xA];
    }
    second = func_002BDCE8(pos, 0.1f, 1.0f, 0.9f, n, vel, 630000.0f, 0xDF204080, 0);
    if (second) {
        particle2 = second + 0x20;
        *(unsigned short *)(first + 0xA) = 25;
        first[9] = func_00283CF0(4.0f) + 112;
        *(int *)(particle2 + 4) = 2;
        particle2[0xA] = 0xDF;
        particle2[0xB] = first[0xA];
    }
    third = func_002BDCE8(pos, 0.05f, 1.0f, 0.97f, 16, vel, 315000.0f, 0xDFFFFFFF, 0);
    if (third) {
        int v;
        particle3 = third + 0x20;
        v = func_00283CF0(4.0f);
        *(unsigned short *)(third + 0xA) = 35;
        third[9] = v + 112;
        third[8] = func_002A77E0(255);
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
void func_L00_0040D648(unsigned char *object)
{
    int *state = *(int **)(object + 0x68);
    unsigned char *counter;

    switch (object[0x20]) {
    case 0:
        state[9] = 0;
        state[10] = 0;
        state[12] = 0;
        state[13] = 0;
        object[0x30] = 255;
        object[0x20] = 1;
        if (!D_L00_0021DDB0.collected[(short)*(unsigned short *)(object + 0xb2)]) {
            int n = D_0019B4A8[((short)*(unsigned short *)(object + 0xb2) >> 1) + (D_001A79F0 << 10)];
            /* One 3-bit count per nibble; the low bit of the number picks the nibble. */
            if (!((*(unsigned short *)(object + 0xb2) & 1) ? (n >> 4) & 7 : n & 7)) {
                return;
            }
        }
        if (state[17] != -1) {
            func_0029F338(D_L00_001B1E9C + (state[17] << 8));
        }
        if (state[16] != -1) {
            func_0029F338(D_L00_001B1E9C + (state[16] << 8));
        }
        break;
    case 1:
        if (D_L00_001A8F00 != 2 && state[8] != -1) {
            ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[8] << 8));
            other->flags = (other->flags & 0xffbe) | 0x1000;
            other->field98 = *(int *)(other->classData + 0x10);
        }
        if (D_L00_001BCAC0.phase == 1 && D_L00_001A8F00 == 2) {
            if (D_L00_001BCAC0.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[8] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                if (state[17] != -1) {
                    func_0029F338(D_L00_001B1E9C + (state[17] << 8));
                }
                if (state[16] != -1) {
                    func_0029F338(D_L00_001B1E9C + (state[16] << 8));
                }
                if (*(unsigned short *)(object + 0xb2) & 1) {
                    counter = D_0019B4A8 + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (D_001A79F0 << 10));
                    if (((*counter >> 4) & 7) != 7) {
                        *counter += 16;
                    }
                } else {
                    counter = D_0019B4A8 + (((short)*(unsigned short *)(object + 0xb2) >> 1) + (D_001A79F0 << 10));
                    if ((*counter & 7) != 7) {
                        ++*counter;
                    }
                }
                func_00325B70(D_L00_001BCAC0.first, state + 9, 0, 2);
            } else {
                int first = D_L00_001BCAC0.first;
                if (D_L00_001BCAC0.frame >= 1976) {
                    *(float *)(state + 11) = func_00283B98(*(float *)(state + 11), 0.436332345f);
                    func_00325C50(first, *(float *)(state + 11), state + 9, 1, D_L00_001A8F20);
                } else {
                    func_00325C50(first, *(float *)(state + 11), state + 9, 0, D_L00_001A8F20);
                }
            }
            if (D_L00_001BCAC0.frame == 223) {
                int i;
                for (i = 0; i < 2; i++) {
                    ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[i] << 8));
                    if (other && other->state != 254 && other->state != 253) {
                        func_002E5CF8(0, 0, other);
                        other->state = 1;
                    }
                }
            }
            if (D_L00_001BCAC0.frame == 226) {
                func_0026FEB8(D_L00_001B1010);
            }
        }
        if (D_L00_001A8F00 != 2) {
            if (state[9]) {
                func_0029F338((void *)state[9]);
                func_0029F338((void *)state[10]);
                state[9] = 0;
                state[10] = 0;
            }
            if (state[12]) {
                func_0029F338((void *)state[12]);
                func_0029F338((void *)state[13]);
                state[12] = 0;
                state[13] = 0;
            }
        }
        if (D_L00_001BCAC0.phase == 2 && D_L00_001A8F00 == 2) {
            if (D_L00_001BCAC0.frame == 0) {
                ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[4] << 8));
                other->field98 = 0;
                other->flags = (other->flags | 0x41) & 0xefff;
                {
                    int i;
                    for (i = 0; i < 3; i++) {
                        ControllerMoby10 *other = (ControllerMoby10 *)(D_L00_001B1E9C + (state[5 + i] << 8));
                        other->field98 = 0;
                        other->flags = (other->flags | 0x41) & 0xefff;
                    }
                }
                func_00325B70(D_L00_001BCAC0.first, state + 9, 0, 2);
                func_00325B70(D_L00_001BCAC0.second, state + 12, 0, 2);
            } else {
                int first = D_L00_001BCAC0.first, second = D_L00_001BCAC0.second;
                if (D_L00_001BCAC0.frame < 780) {
                    *(float *)(state + 11) = func_00283B98(*(float *)(state + 11), 0.261799425f);
                    *(float *)(state + 14) = func_00283B98(*(float *)(state + 14), 0.261799425f);
                    func_00325C50(first, *(float *)(state + 11), state + 9, 1, D_L00_001A8F20);
                    func_00325C50(second, *(float *)(state + 14), state + 12, 1, D_L00_001A8F20);
                } else {
                    *(float *)(state + 11) = func_00283B98(*(float *)(state + 11), 0.087266475f);
                    *(float *)(state + 14) = func_00283B98(*(float *)(state + 14), 0.087266475f);
                    func_00325C50(first, *(float *)(state + 11), state + 9, 0, D_L00_001A8F20);
                    func_00325C50(second, *(float *)(state + 14), state + 12, 0, D_L00_001A8F20);
                }
            }
        }
        break;
    }
}

/* func_L00_0040EAA0 is in L00_003D54A8-f7-g8.c. */



void func_L00_00419B80(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419BA8(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419BD0(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419BF8(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419C20(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419C48(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}

void func_L00_00419C70(void *a0) {
    unsigned char *p = (unsigned char *)a0;
    if (p[0x20] == 0) {
        p[0x20] = 1;
        *(unsigned short *)(p + 0x34) |= 0x800;
    }
}
