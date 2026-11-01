#include "common.h"
#include "include_asm.h"

extern int D_001A72E0;

extern int D_001A72E0_1;

extern short D_001A6480[];

extern void func_002FC560(int id, long long value);

extern void func_0027DE50(int a, int b, int c, int d, int e);

extern char D_L00_0024EFC0[];

extern int D_L00_001B2B60;

extern void func_00282A88(char *buf, int size);

void func_L00_003E55B0(char *object)
{
    char *s1;

    s1 = *(char **)(object + 0x68);
    if (*(int *)(s1 + 0x24) != 0) {
        func_002FC560(0x4E, (((long long)(D_001A72E0 >> 13) | 0x1000000) | (1LL << 32)));
        func_0027DE50(0, D_001A6480[0xA9], 0, D_001A6480[0xA8], (*(int *)(s1 + 0x24) << 24) | 0xFFFFFF);
        func_002FC560(0x4E, (D_001A72E0_1 >> 13) | 0x1000000);
    }
}

void func_L00_003E8150(void)
{
    func_00282A88(D_L00_0024EFC0, 0x800);
    D_L00_001B2B60 = 0;
}

typedef float QuadVector[4] __attribute__((aligned(16)));

extern int D_L00_001B05E0 __attribute__((sda));
extern int D_L00_001B05E4 __attribute__((sda));
extern int D_L00_001B05E8 __attribute__((sda));
extern int D_L00_001B05EC __attribute__((sda));
extern int D_L00_001B05F0 __attribute__((sda));
extern int D_L00_001B05F4 __attribute__((sda));
extern int D_L00_001B05F8 __attribute__((sda));
extern float D_L00_001B05FC __attribute__((sda));
/* 64 quads of a shared mesh: per corner, a vertex index and a texture-coordinate index. */
extern short D_L00_00297020[][4][2];
extern QuadVector D_L00_00296B20[];
extern float D_L00_00297420[][2];
extern unsigned long long func_0027C878(int);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00280B90(void *, int, int);
extern void ref_L00_003E5710_00(void *, void *, int);
extern void ref_L00_003E5978_00(void *, void *, int);

/* Draws the 64-quad mesh at OBJECT: every corner of the shared vertex table is scaled by the
   state's size (doubled on the first two axes, a quarter on the third), turned by the object's
   matrix, moved to its position and offset by the vector the helper leaves in matrix[3], which
   is halved at every corner. */
void func_L00_003E5710(char *object)
{
    QuadVector vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long long registers[4];
    QuadVector matrix[4];
    char *state = *(char **)(object + 0x68);
    int quad, corner;
    float *first_u, *first_v;

    registers[1] = func_0027C878(D_L00_001B05F4);
    registers[2] = 0xFF9000000260ULL;
    registers[3] = D_L00_001B05E0 | (unsigned long long)D_L00_001B05E4 << 2;
    registers[3] |= (unsigned long long)D_L00_001B05E8 << 4;
    registers[3] |= (unsigned long long)D_L00_001B05EC << 6;
    registers[3] |= (unsigned long long)D_L00_001B05F0 << 32;
    registers[0] = 0;
    func_00282C88(matrix[0]);
    func_00282C88(matrix[1]);
    func_00282C88(matrix[2]);
    matrix[0][0] = *(float *)(state + 0x10) * 2.0f;
    matrix[1][1] = *(float *)(state + 0x10) * 2.0f;
    matrix[2][2] = *(float *)(state + 0x10) * 0.25f;
    colors[0] = colors[1] = colors[2] = colors[3] = D_L00_001B05F8 + (*(int *)(state + 0x24) << 24);
    ref_L00_003E5710_00(object + 0x10, matrix[3], 1);
    first_u = &uv[0][0];
    first_v = &uv[0][1];
    quad = 0;
    do {
        float *u, *v;

        v = first_v;
        u = first_u;
        for (corner = 0; corner < 4; corner++) {
            int vertex = D_L00_00297020[quad][corner][0];
            int texel = D_L00_00297020[quad][corner][1];

            func_00282D30(vertices[corner], D_L00_00296B20[vertex], D_L00_001B05FC);
            *u = D_L00_00297420[texel][0];
            *v = D_L00_00297420[texel][1];
            func_00283098(vertices[corner], vertices[corner], matrix);
            func_00283098(vertices[corner], vertices[corner], object + 0xC0);
            func_00282CC0(vertices[corner], vertices[corner], object + 0x10);
            func_00282F20(matrix[3], matrix[3], 0.5f);
            func_00282CC0(vertices[corner], vertices[corner], matrix[3]);
            u += 2;
            v += 2;
        }
        func_00280B90(vertices, 0, 0);
    } while (++quad < 64);
}

/* The same mesh at the state's size (an eighth on the third axis); the position pointer is
   taken again for every quad. */
void func_L00_003E5978(char *object)
{
    QuadVector vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long long registers[4];
    QuadVector matrix[4];
    char *state = *(char **)(object + 0x68);
    int quad, corner;
    char *position;
    float *first_u, *first_v;

    registers[1] = func_0027C878(D_L00_001B05F4);
    registers[2] = 0xFF9000000260ULL;
    registers[3] = D_L00_001B05E0 | (unsigned long long)D_L00_001B05E4 << 2;
    registers[3] |= (unsigned long long)D_L00_001B05E8 << 4;
    registers[3] |= (unsigned long long)D_L00_001B05EC << 6;
    registers[3] |= (unsigned long long)D_L00_001B05F0 << 32;
    registers[0] = 0;
    func_00282C88(matrix[0]);
    func_00282C88(matrix[1]);
    func_00282C88(matrix[2]);
    matrix[0][0] = *(float *)(state + 0x10) * 1.0f;
    matrix[1][1] = *(float *)(state + 0x10) * 1.0f;
    matrix[2][2] = *(float *)(state + 0x10) * 0.125f;
    colors[0] = colors[1] = colors[2] = colors[3] = D_L00_001B05F8 + (*(int *)(state + 0x24) << 24);
    ref_L00_003E5978_00(object + 0x10, matrix[3], 1);
    first_u = &uv[0][0];
    first_v = &uv[0][1];
    quad = 0;
    do {
        float *u, *v;

        position = object + 0x10;
        v = first_v;
        u = first_u;
        for (corner = 0; corner < 4; corner++) {
            int vertex = D_L00_00297020[quad][corner][0];
            int texel = D_L00_00297020[quad][corner][1];

            func_00282D30(vertices[corner], D_L00_00296B20[vertex], D_L00_001B05FC);
            *u = D_L00_00297420[texel][0];
            *v = D_L00_00297420[texel][1];
            func_00283098(vertices[corner], vertices[corner], matrix);
            func_00283098(vertices[corner], vertices[corner], object + 0xC0);
            func_00282CC0(vertices[corner], vertices[corner], position);
            func_00282F20(matrix[3], matrix[3], 0.5f);
            func_00282CC0(vertices[corner], vertices[corner], matrix[3]);
            u += 2;
            v += 2;
        }
        func_00280B90(vertices, 0, 0);
    } while (++quad < 64);
}

typedef int TI4BF0 __attribute__((mode(TI)));
typedef float Vec4BF0[4] __attribute__((aligned(16)));
typedef struct { char prefix[0x74]; float damage; char tail[0x68]; } Weapon4BF0;
extern Weapon4BF0 D_L00_00262570[] __attribute__((nosda));
extern unsigned char D_00139568[];
typedef struct { char pad[0x2290]; char *target; } Hero4BF0;
extern Hero4BF0 D_00189E20;
typedef struct { char pad[0x160]; float amount; int unused, timer, state; } Camera4BF0;
extern Camera4BF0 D_L00_001B8C80;
extern char *D_L00_001B2B50 __attribute__((sda));
extern char *D_L00_001B2B54;
extern int *D_L00_001B2B58[] MACRO_ADDR;
extern float D_L00_001B05D4 __attribute__((sda));
extern float D_L00_001B05D8 __attribute__((sda));
extern char *D_L00_001B2B50_1 MACRO_ADDR;
extern char *D_L00_001C3280[];
extern int func_002B4038(short,int);
extern void func_00300190(void *,void *);
extern int func_L00_00329E90(void *,int,void *);
extern char *func_L00_0032A088(short,int);
extern int func_L00_003E4B80(int);
extern void func_002AFFD8(void *,void *,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_L00_003E64F8(void *,int,void *,void *,float);
extern void func_L00_003E5340(void *,void *);
extern int func_00283DB8(void *,float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00277F48(void *,int,void *,int,float);
extern int func_002AB1F0(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002A8C00(float,void *,void *,int,void *);
extern void func_002A8E20(void *,void *);
extern void func_0032D758(void *,int,int);
extern int func_00282948(void *);
extern void func_L00_003E5330(void);
extern void func_0029F338(void *);
extern void func_L00_003E6628(void *);
extern void ref_L00_003E4BF0_00(void (*)(void *),void *);
extern void func_L00_003E5650(void *);
typedef struct { char pad[0x10]; float phase; int timer; float rate; int alpha, unused, count, handle; } State4BF0;
void func_L00_003E4BF0(char *object)
{
    Vec4BF0 center, offset, query, direction;
    struct { Vec4BF0 point; char pad[8]; unsigned char type, flags; short id; int unused; int active; } hit;
    int allocation;
    int *timer;
    State4BF0 *data = *(State4BF0 **)(object+0x68);
    float scale;
    if (*(unsigned char *)(object+0x20) && !func_002B4038(*(short *)(object+0xAA),data->handle)) goto destroy;
    func_00300190(object+0x10,object+0x10);
    switch (*(unsigned char *)(object+0x20)) {
    case 0: {
        int i;
        char *mem;
        *(unsigned char *)(object+0x20)=1;
        data->phase=0;
        data->timer=20;
        data->rate=2.0f/3.0f;
        data->alpha=127;
        data->count=111;
        data->handle=func_L00_00329E90(object,0,&allocation);
        mem=func_L00_0032A088(*(short *)(object+0xAA),data->handle);
        D_L00_001B2B50=mem;
        D_L00_001B2B54=(char *)func_L00_003E4B80((int)(mem+0x50));
        D_L00_001B2B58[0]=(int *)func_L00_003E4B80((int)(D_L00_001B2B54+0xA000));
        i=0;
        do { D_L00_001B2B58[0][i]=0; i++; } while(i<144);
        { char *p = D_L00_001B2B54+319*128+124;
        for(i=319;i>=0;i--,p-=128) *(int *)p=0; }
        *(int *)(D_L00_001B2B50_1+0x30)=0;
        qcopy(center,object+0x10);
        func_002AFFD8(object+0x10,offset,1);
        func_00282CC0(center,object+0x10,offset);
        func_002AC728(object,center,-1,2.0f,20.0f);
        func_L00_003E64F8(object,20,object+0x10,data,1.0f/6.0f);
        func_L00_003E5340(object,object+0x10);
        qcopy(query,center);
        query[3]=2.0f;
        if(func_00283DB8(query,100.0f)!=-1) {
            D_L00_001B8C80.amount=0.45f;
            D_L00_001B8C80.timer=40;
            D_L00_001B8C80.state=0;
        }
    }
    case 1: {
        int count;
        int i;
        data->count-=5;
        if(data->count<0) data->count=0;
        data->phase+=data->rate;
        timer=&data->timer;
        scale=1.0f-func_00283CE0(*timer)/func_00283CE0(20);
        scale*=8.0f;
        count=func_00277F48(object+0x10,0,object,0,scale+0.001f);
        for(i=0;i<count;i++) {
            if((func_002AB1F0(D_L00_001C3280[i]) || (*(unsigned short *)(D_L00_001C3280[i]+0x34)&0x4000)) && D_L00_001C3280[i]!=D_00189E20.target && *(short *)(D_L00_001C3280[i]+0xAA)!=0xA5A) {
                func_00282CF0(direction,D_L00_001C3280[i]+0x10,object+0x10);
                func_00282F20(direction,direction,1.0f);
                func_00282F20(&hit,&hit,1.0f);
                func_002A8C00(((Weapon4BF0 *)((unsigned int)D_L00_00262570 + D_00139568[0x2A] * sizeof(Weapon4BF0)))->damage,&hit,object,0x830000,direction);
                *(TI4BF0 *)hit.point = *(TI4BF0 *)direction;
                hit.flags=3; hit.type=5; hit.active=1;
                hit.point[3]=5627.925f;
                hit.id=*(short *)(D_L00_001C3280[i]+0xAA);
                func_002A8E20(D_L00_001C3280[i],&hit);
                func_0032D758(D_L00_001C3280[i],71,*(int *)(object+0xB8));
            }
        }
        if(func_00282948(timer)) {
            *(unsigned char *)(object+0x20)=2;
            data->timer=40;
        }
        break;
    }
    case 2:
        data->phase+=data->rate;
        scale=func_00283CE0(data->timer)*0.025f;
        if(data->timer==20) func_L00_003E5340(object,object+0x10);
        if(func_00282948(&data->timer)) {
            if(data->alpha) --data->alpha;
            else { data->alpha=0; *(unsigned char *)(object+0x20)=6; }
        } else data->alpha=func_00283CF0(func_00283CE0(127)*scale);
        break;
    case 6:
        data->rate-=0.016666668f;
        if(data->rate<1.0f/12.0f) data->rate=1.0f/12.0f;
        data->phase+=data->rate;
        if(!*(int *)(D_L00_001B2B50_1+0x38)) {
destroy:
            func_L00_003E5330();
            func_0029F338(object); return;
        }
        break;
    }
    D_L00_001B05D8-=0.04f;
    if(D_L00_001B05D4 < -8.0f) D_L00_001B05D4+=8.0f;
    if(D_L00_001B05D8 < -8.0f) D_L00_001B05D8+=8.0f;
    func_L00_003E6628(object);
    ref_L00_003E4BF0_00(func_L00_003E5650,object);
}
