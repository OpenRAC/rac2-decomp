/* Museum vehicle update: collision damage, activation, driving and respawn.
 * func_PAL_L30_00410A38, the PAL copy of func_L30_0040B9D8: the same C, where the hit timer,
 * the throttle steps, the speed threshold, the turn rate and the respawn delay are scaled to
 * 50 Hz and the activation prompt id becomes 0x12EA. */
#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
typedef struct { char pad[10]; unsigned short offset; char pad2[4]; } PaletteRow;
typedef struct {
 char pad0[0x80]; unsigned int position[4], rotation[4];
 char padA0[0xD0-0xA0]; unsigned int copyD0[4],copyE0[4];
 char padF0[0x33C-0xF0]; char *ground; int groundFlag;
 char pad344[0x1830-0x344]; char *vehicle; short vehicleId;
 char pad1836[6]; float health, maxHealth; int pad1844, healthPercent;
 char pad184C[0x1FB0-0x184C]; int cameraX; float cameraY;
 char pad1FB8[0x2290-0x1FB8]; char *hero; int state; int pad2298,mode;
 char pad22A0[0x24CC-0x22A0]; int heroHealth;
} VehicleHeroState;
extern VehicleHeroState g_hero_state;
extern struct { char pad[0x1A0]; int held, pressed; } g_pad_state;
extern int D_00138324;
extern int D_L30_001A8F00 __attribute__((sda));
extern int D_L30_001B18A8 __attribute__((sda));
extern float D_L30_001B179C __attribute__((sda));
extern float D_L30_001B17B0 __attribute__((sda));
extern float D_L30_001B16CC __attribute__((sda));
extern float D_L30_001B16D0 __attribute__((sda));
extern float D_L30_001B16D4 __attribute__((sda));
extern float D_L30_001B16D8 __attribute__((sda));
extern float D_L30_001B16DC __attribute__((sda));
extern float D_L30_001B16E0 __attribute__((sda));
extern float D_L30_001B17E8 __attribute__((sda));
extern float D_L30_001B17EC __attribute__((sda));
extern float D_L30_001B17B8 __attribute__((sda));
extern float D_L30_001B16F4 __attribute__((sda));
extern int D_L30_001B1780 __attribute__((sda));
extern int D_L30_001B180C __attribute__((sda));
extern int D_L30_001B1704 __attribute__((sda));
extern int D_L30_001B1708 __attribute__((sda));
extern char *D_L30_001B17B4 __attribute__((sda));
extern char *D_L30_001B1808 __attribute__((sda));
extern char *D_L30_001B27C4;
extern void DrawMuseumStatusGauge(char *);
extern unsigned short D_L30_001BE9C0[][8];
extern char D_L30_0025CEB0[], D_L30_001B9DC0[];
extern char *part_find_owned_effect_slot(char *,int,int);
extern void func_PAL_002AC290(char *,void *), func_PAL_002AC3C0(char *,void *);
extern float vec_length_xy(void *), func_002A0558(char *,char *), FastAddRotations(float,float), math_fast_sin_or_cos_b(float), fast_vec_dist(void *,void *);
extern int TryClaimNotice(int,int,int), math_random_int_below(int), flag_set_first_pending(char *);
extern int func_PAL_L00_002C4480(int,int);
extern void func_PAL_L30_00411310(char *,int), func_PAL_L00_002D2668(int,int,float), moby_mark_in_range(char *);
extern void moby_set_state(char *,int,int), moby_transform_joint_to_world(char *,int,void *), moby_update_ground_check(char *), gfx_add_draw_callback_third(void (*)(char *),void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void moby_scale_owner_words_by_angles(char *,void *,void *,float,float,float);
extern void *memcpy(void *,const void *,unsigned int);
typedef struct {
 float velocity[4]; char pad10[16]; float pitch,yaw,roll,pad2C;
 float spawn[4]; char pad40[8]; float phase, bob, yawRate, pitchRate, height, pad5C, health;
 int classIndex; union { float throttle; int bits; } power;
 char pad6C[2]; unsigned char hitTimer; char pad6F[0x80-0x6F];
 unsigned char flash[16]; char *lastHit; int flags, alpha, count;
} VehicleVars;
typedef struct {
 char pad0[0x10]; float position[4]; unsigned char state; char pad21[3];
 char *classData; char pad28[4]; float damage; unsigned char color, visible;
 char pad32[0x68-0x32]; VehicleVars *vars; char pad6C[3]; unsigned char delay;
 char pad70[0x96-0x70]; unsigned short timer; int flags, animation;
 char padA0[8]; unsigned char hitFlag; char padA9[0xF0-0xA9]; float rotation[4];
} MuseumVehicle;
/* dead-test helper allowed by owner ruling (master precedent).
 * As in label_y, the dead test preserves a block until reload; flow2 removes it.
 * The returned health is always the level's initial vehicle health. */
static __inline__ float initial_health(void)
{
    float health;
    if (D_L30_001A8F00)
        health = 1.0f;
    health = D_L30_001B17B0;
    return health;
}

void func_PAL_L30_00410A38(MuseumVehicle *obj) {
    VehicleVars *s; char *hit;

    char activate;
    float k, scaled, rollRate, yawRate, pitchRate, bob;
    unsigned int pos[4] __attribute__((aligned(16)));
    s=obj->vars;
    if (obj->state) {
        obj->position[2]=s->height;
        hit=part_find_owned_effect_slot(obj,1,0);
        if (hit && P(hit,0x20) && *(short *)(P(hit,0x20)+0xAA)!=0xF2F && *(short *)(P(hit,0x20)+0xAA)!=0x942) {
            if (*(short *)(P(hit,0x20)+0xAA)!=0xFFF && (P(hit,0x20)!=s->lastHit || !s->hitTimer)) {
                B(s,0x87)=0xD2;B(s,0x88)=0xD2;B(s,0x89)=0xD2;
                func_PAL_002AC290(obj,&s->flash);
                s->health-=F(hit,0x2C);
                g_hero_state.health=s->health;
                if (s->health<=0.0f) obj->state=5;
                s->lastHit=P(hit,0x20);
                s->hitTimer=((s32)(D_L30_001B18A8) * 5 + 2) / 6;
            }
        }
        obj->hitFlag=0xFF;
    } else s->height=obj->position[2];
    func_PAL_002AC3C0(obj,&s->flash);

    obj->damage=F(obj->classData,0x24)*D_L30_001B179C;
    if (g_hero_state.vehicle==obj) g_hero_state.healthPercent=(int)(g_hero_state.health/D_L30_001B17B0*200.0f);
    activate=0;
    switch (obj->state) {
    case 0: {
        char *palette; int copied;
        palette=D_L30_001B27C4+((PaletteRow *)((s->classIndex+D_L30_001B1780)*16+(char *)D_L30_001BE9C0))->offset*16;
        D_L30_001B1808=palette;copied=D_L30_001B180C;
        s->alpha=255; s->flags=0;
        if (!copied) memcpy(D_L30_0025CEB0,palette,0x400);
        D_L30_001B180C=1;
        qcopy(&s->spawn,obj->position); qzero_nc(s);
        g_hero_state.maxHealth=g_hero_state.health=s->health=initial_health();
        obj->state=1;
        s->power.bits=0;s->count=0;
        break; }
    case 1:
        if (vec_length_xy(s)>0.0050000004f) func_PAL_L30_00411310(obj,0);
        if (g_hero_state.state==28 || g_hero_state.state==22 || g_hero_state.state==57 || g_hero_state.state==111 ||
            g_hero_state.mode==2 || g_hero_state.mode==4 || g_hero_state.mode==3 || g_hero_state.mode>=13 ||
            g_hero_state.mode==7 || g_hero_state.mode==10 || g_hero_state.mode==16 || g_hero_state.mode==5 || g_hero_state.state==98 ||
            g_hero_state.heroHealth<=0 || D_L30_001A8F00 || !g_hero_state.groundFlag) break;
        if (g_hero_state.ground && (*(short *)(g_hero_state.ground+0xAA)==0x13E || *(short *)(g_hero_state.ground+0xAA)==0x46F)) break;
        if (func_002A0558(obj,g_hero_state.hero)<D_L30_001B16CC && g_hero_state.state!=49) {
            int v=TryClaimNotice(7,0x12ea,1)!=0;
            if (g_pad_state.pressed&16) activate=v;
        }
        if (activate) {
            func_PAL_L00_002C4480(49,0);func_PAL_L00_002D2668(D_L30_001B1704,0,15.0f);
            qcopy(g_hero_state.rotation,obj->rotation);qcopy(g_hero_state.position,obj->position);
            g_hero_state.vehicle=obj;obj->state=3;obj->flags=0;I(g_hero_state.hero,0x9C)=-1;
        }
        break;
    case 3:
        if (g_pad_state.held&4) {
            s->power.throttle-=D_L30_001B17E8*1.2f;
            if (!math_random_int_below(9) || (g_pad_state.pressed&4)) moby_mark_in_range(obj);
        } else s->power.throttle+=D_L30_001B17EC*1.2f;
        if (D_L30_001B1708!=D_L30_001B1704 && D_L30_001B1704!=-1) func_PAL_L00_002D2668(D_L30_001B1704,0,15.0f);
        func_PAL_L30_00411310(obj,1);
        if (s->power.throttle>1.0f) s->power.throttle=1.0f; else if (s->power.throttle<0.0f) s->power.throttle=0.0f;
        if (g_hero_state.vehicle==obj) {
            if (g_pad_state.pressed&16) moby_set_state(obj,4,-1);
            qcopy(g_hero_state.copyD0,g_hero_state.copyE0);
        }
        break;
    case 4:
        if (flag_set_first_pending(obj)) {
            g_hero_state.cameraX=0;g_hero_state.cameraY=-1.0f;func_PAL_L00_002C4480(11,1);
            g_hero_state.vehicle=0;g_hero_state.vehicleId=-1;
        }
        obj->flags=0;I(g_hero_state.hero,0x9C)=0;func_PAL_L30_00411310(obj,0);
        { unsigned int timer=obj->timer; unsigned int old=timer++; obj->timer=timer;
        if (old>=26) {obj->flags=I(obj->classData,0x10);obj->state=1;} }
        break;
    case 6: break;
    case 5:
        obj->flags=I(obj->classData,0x10);I(g_hero_state.hero,0x9C)=0;
        func_PAL_L00_002C4480(0,1);moby_transform_joint_to_world(obj,0,pos);
        func_PAL_002AC718(obj,s,pos,0.0f,0.0f,10,3,16,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,1,-1,0,0x810001);
        qcopy(obj->position,&s->spawn);g_hero_state.vehicleId=-1;g_hero_state.vehicle=0;obj->state=0;
        break;
    }
    scaled=s->power.throttle;
    k=0.0003490659f;
    scaled=D_L30_001B16D4*(scaled*k);
    s->height=obj->position[2];
    s->phase=FastAddRotations(s->phase,scaled);
    bob=math_fast_sin_or_cos_b(s->phase)*D_L30_001B16D0*s->power.throttle;
    rollRate=D_L30_001B16D8; yawRate=D_L30_001B16DC; pitchRate=D_L30_001B16E0;
    s->bob=bob;
    obj->position[2]+=s->bob*s->power.throttle;
    moby_scale_owner_words_by_angles(obj,&s->yawRate,&s->pitchRate,rollRate*0.017453294f,yawRate*(s->power.throttle*k),pitchRate*(s->power.throttle*k));
    obj->rotation[2]=s->roll;obj->rotation[0]=FastAddRotations(obj->rotation[0],s->pitch);obj->rotation[1]=FastAddRotations(obj->rotation[1],s->yaw);
    if (obj->state==3) {moby_transform_joint_to_world(obj,(int)D_L30_001B17B4,g_hero_state.position);{char *h=(char *)&g_hero_state;F(h,0x88)+=D_L30_001B17B8;}qcopy(g_hero_state.rotation,obj->rotation);
        gfx_add_draw_callback_third(DrawMuseumStatusGauge,obj);
    }
    if (obj->visible && fast_vec_dist(obj->position,D_L30_001B9DC0)<64.0f) {moby_update_ground_check(obj);obj->delay=60;}
}
