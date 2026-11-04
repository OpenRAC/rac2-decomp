/* func_PAL_L05_0037C968, the PAL copy of func_L05_0037A218: the same C, where 30 becomes 25;
   func_L05_0037AC80 becomes func_PAL_L05_0037D3D0; func_L05_0037DA58 becomes
   func_PAL_L05_00380258. */
#include "common.h"
typedef struct {
    float position[4], previous[4], origin[4], target[4], velocity[4];
    u8 *object;
    float distance;
    int flags,color,effect,mode;
    float rate,spin,life;
    u8 pad74[12];
} L05Projectile;
extern L05Projectile D_L05_00221DD0[];
extern int D_L05_00221D10[];
extern void *D_L05_00225DD0[];
extern void (*D_L05_00225ED0[])(void *);
extern int D_L05_001A8F00;
extern int D_L05_001AC4D4 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern u8 D_00188660[];
typedef struct { u8 pad[0x160]; float slow; int pad164,frames,flags; } L05ImpactState;
extern L05ImpactState D_L05_001B9580;
typedef struct { int on; int pad; float pos[4]; } L05Hit;
extern L05Hit D_L05_001BFB18;
extern u8 D_L05_001A8F20[] MACRO_ADDR;
extern int func_L00_004272A0(void);
extern s32 func_002ED688(u8 *);
extern float func_002A7878(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282E48(void *,void *);
extern int func_002A77E0(int);
extern int func_002E5DA0(int,int,char *,int);
extern void func_PAL_L05_0037D3D0(float);
extern int func_00283DB8(void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern void func_PAL_L05_00380258(void *,int,int,int);
extern void func_002A8F70(void *,void *,int,void *,void *,float);
extern float func_002A7940(void);
extern void func_00281EB8(void *,int,int,int,float,float,float);
extern void func_L05_0037D7D8(void *,void *,u32,int,float);
/* Update active object callbacks, then advance and resolve the projectile pool. */
void func_PAL_L05_0037C968(void *unused)
{
    float step[4],check[4];
    float scale,speed,angle;
    u8 *state,*target,*sound;
    L05Projectile *record; float *pos;
    int i,j;
    (void)unused;
    if (D_L05_001A8F00 == 2) return;
    for (i=0;i<func_L00_004272A0();i++) {
        if (D_L05_00225ED0[i]) D_L05_00225ED0[i](D_L05_00225DD0[i]);
    }
    for (j=0;j<128;j++) {
        unsigned int base = (unsigned int)D_L05_00221DD0;
        unsigned int offset = j * sizeof(L05Projectile);
        record = (L05Projectile *)(base + offset);
        if (!record->object) continue;
        pos = record->position;
        state = (u8 *)func_002ED688(record->object);
        if (D_L05_00221D10[0x2C/4] == 1 || *(int *)(state+0x110) == 0 || record->distance >= 350.0f) {
            record->object = 0;
            continue;
        }
        scale = func_002A7878(1.1f,0.6f);
        speed = record->life;
        func_00282F20(step,record->velocity,scale*speed);
        func_00282CC0(record->position,record->position,step);
        func_00282CC0(record->previous,record->previous,step);
        record->distance += scale*speed;
        if (record->flags == 0 && record->mode && func_00282E48(record->position,*(u8 **)(state+0x120)+0x10) < record->rate) {
            D_L05_001B9580.frames = 25;
            D_L05_001B9580.slow = 0.05f;
            D_L05_001B9580.flags = 0;
            if (func_002A77E0(6) && (target=*(u8 **)(state+0x120)) && *(s16 *)(target+0xAA) == 0xFBF) {
                sound = D_00188660+D_L05_001AC4D4*0x70;
                if ((*(u8 **)(sound+0x88) != target || !sound[0x74]) && D_001A79F0 != 10)
                    D_L05_001AC4D4 = func_002E5DA0(14,0,(char *)target,0xFBF);
            }
            func_PAL_L05_0037D3D0(1.0f);
            record->flags = 1;
            record->object = 0;
        }
        if (record->effect && *(u8 **)(state+0x120) && func_00282E48(record->position,*(u8 **)(state+0x120)+0x10) < 32.0f) {
            qcopy(check, pos);
            check[3] = 1.0f;
            if (func_00283DB8(check,256.0f) != -1 && func_002761F8(record->previous,record->position,0,0,0)) {
                func_PAL_L05_00380258(D_L05_001BFB18.pos,20,record->color,60);
                if (D_L05_001BFB18.on)
                    func_002A8F70(*(u8 **)(state+0x120),record->object,0x10000,D_L05_001BFB18.pos,D_L05_001A8F20,0.25f);
                record->object = 0;
            }
        }
        angle = func_002A7940();
        func_00281EB8(record->position,0x31,record->color,1,0.35f,0.0f,angle);
        func_L05_0037D7D8(record->position,record->previous,0x807F7F7F,14,record->spin*0.05f);
        func_L05_0037D7D8(record->position,record->previous,record->color,14,record->spin*0.1f);
    }
}
