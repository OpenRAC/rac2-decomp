#include "common.h"

#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) Vec;
typedef struct {
    char pad0[0x730]; float basis[12];
    char pad760[0x1230-0x760]; int buttons;
    char pad1234[0x1244-0x1234]; int itemState;
    char pad1248[0x2290-0x1248]; char *object; int current;
    int pad2298; unsigned int control;
    char pad22a0[0x24ec-0x22a0]; short direction;
    char pad24ee[0x2534-0x24ee]; int timer;
} Hero;
typedef struct { char pad[0x360]; unsigned short kills, pad362; unsigned int best, levels; } Stats;
typedef struct { int present; unsigned char type; char pad[219]; } Upgrade;
typedef struct { float color[4]; float pos[3]; float radius; } Light;
typedef struct { float pos[4]; char *target; float total, left; short timer, seen;
    char pad20[0x44-0x20]; int delay; float yaw,pitch; } Ray;
typedef struct { char pad0[0x74]; unsigned char playing; char pad75[0x88-0x75]; char *owner; } Voice;
extern Hero D_00189E20;
extern Stats D_0018C360;
typedef struct { unsigned char pad0[0x10]; unsigned char current; unsigned char pad11[0x48-0x11]; unsigned char equipped; } Inventory;
extern Inventory D_00139568;
extern char D_00188660[];
extern Upgrade D_L00_00262570[];
extern char D_L00_001B8C80[];
extern Light D_L00_001C6F40[];
extern int D_001A7390 MACRO_ADDR, D_001A79F0 MACRO_ADDR;
extern unsigned char D_001A7A60[32] __attribute__((sda));
extern int D_00138320 __attribute__((nosda));
extern int D_L00_001B2C74 MACRO_ADDR;
extern int D_L00_001B2C78 MACRO_ADDR;
extern int D_L00_001B2C7C MACRO_ADDR;

extern int D_L00_001B0E30 __attribute__((sda));
extern float D_L00_001B0E3C __attribute__((sda));
extern float D_L00_001B0E48 __attribute__((sda));
extern int D_L00_001B2C70 __attribute__((sda));
extern int D_L00_001A903C;
extern float func_0029F530(void *);
extern int func_00282948(void *);
extern void func_00282978(void *);
extern void func_002A7470(void *,int,int,int);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_L00_002C42E0(int,int);
extern void func_00283678(void *,void *);
extern void func_00283698(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00283248(float,float);
extern float func_00282E20(void *);
extern char *func_L00_004051C8(void *,void *,void *,void *);
extern char *func_002AB1F0(void *);
extern float func_00283CE0(int);
extern void func_00290010(int,int,int,float);
extern int func_002E5E58(int,int,void *);
extern void func_002B0A18(int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_L00_00408800(void *);
extern void func_L00_00406150(void *);
extern int func_00291308(void *,float,float,unsigned int);
extern void func_00282F20(void *,void *,float);
extern int func_002E59B0(void *,int);
extern void func_00291450(int);
extern void func_002E59F8(int);
extern void func_002A75E0(void *,int,int,int,int);

/* Updates the Black Sheepinator (moby class 3757): while the button is held, it fires the beam, locks onto a target and turns it into a sheep when the charge runs out. */
void func_L00_00405808(char *object)
{
    Vec offset;
    Vec direction;
    Vec matrix[3];
    Vec basis[4];
    Ray *state=*(Ray **)(object+0x68);
    char *target, *info; Light *entry;
    int special=0;
    float rate, value;
    int index;
    int boosted;
    int near;
    if (gHeroState.itemState==3) special=1;
    if (!B(object,0x20)) {
        B(object,0x20)=1;
        D_L00_001B2C74=-1;
        D_L00_001B2C7C=-1;
        D_L00_001B2C78=0;
    }
    /* RAC1 also gates the beam on near; here nothing reads it, so only the call survives. */
    near=1;
    if (!B(object,0x43) && GetMobyAnimationValue(object)<6.0f) near=0;
    {
    Hero *player=&gHeroState;
    int permitted=1;
    if (player->current==29) { if (!FastFloatHelperD(&player->timer)) permitted=0; }
    else gHeroState.timer=40;
    FastDecTimer(&state->timer);
    if ((unsigned int)gHeroState.control<2 && (D_00138320&gHeroState.buttons) && permitted) {
        if (B(object,0x43)!=2) StartAnimationBlended(object,2,0,0);
        if (!state->seen) {
            state->seen=1;
            if (D_0018C360.kills<65535) D_0018C360.kills++;
            if ((unsigned int)D_001A7390>D_0018C360.best) D_0018C360.best=D_001A7390;
            D_0018C360.levels = (D_0018C360.levels | (1<<gCurrentMapIndex)) | 0x80000000;
        }
        if (!state->timer) state->timer=15;
        *(Quad *)&offset=0;
        offset.x=0.15f; offset.y=-1.0f; offset.z=0.06f; offset.w=1.0f;
        matrix_mul_vec3(&offset,&offset,object+0xc0);
        FastVecAdd(state,object+0x10,&offset);
        if (gHeroState.current==1) SetHeroAction_L00(29,1);
        *(Quad *)&direction=0;
        if (gHeroState.current==29 && (U(gHeroState.object,0x34)&1)) {
            copy_matrix3x4(matrix,D_L00_001B8C80);
            matrix_from_basis_rows(basis,matrix);
            direction.z=1.0f;
            transform_vector(&direction,&direction,basis);
        } else if (gHeroState.direction==1) FastVecScale(&direction,object+0xd0,-1.0f);
        else {
            direction.x=1.0f;
            matrix_mul_vec3(&direction,&direction,gHeroState.basis);
        }
        state->yaw=FastMatrixHelperA(direction.x,direction.y);
        value=vec_length_xy(&direction);
        state->pitch=FastMatrixHelperA(value,direction.z);
        *(Quad *)matrix=*(Quad *)state;
        target=FindSheepinatorTarget(object,matrix,&state->yaw,&state->pitch);
        FastFloatHelperD(&state->delay);
        if (state->target) {
            if (B(state->target,0x20)==254) goto clear_target;
            if (B(state->target,0x20)==253) {
clear_target:
                state->target=0; state->delay=0;
            }
        }
        if (target || state->delay) {
            if (target) {
                info=GetMobyPrivateValue0(target);
                if (target!=state->target && !state->delay) {
                    state->target=target;
                    state->total=IntToFloat(H(info,4));
                    state->left=F(info,0);
                    state->delay=30;
                    if (state->total<=1.0f) state->left=0;
                }
            }
            {
            Inventory *inventory=&gItemSlotToRecord;
            Upgrade *upgrades=gWeaponTable_L00;
            rate=1.0f;
            if (upgrades[inventory->equipped].type) rate=1.33f;
            boosted=upgrades[inventory->current].present!=0 && upgrades[inventory->current].type==3;
            }
            D_L00_001B0E3C=boosted?50.0f:12.5f;
            state->left-=D_L00_001B0E3C*(rate*0.016666668f);
            if (state->left<0.0f) state->left=0.0f;
            D_L00_001B0E48=state->left/state->total;
        } else D_L00_001B0E48=1.0f;
        ShowGaugePopup(1,0x60000000,0,D_L00_001B0E48);
        if (state->target && state->left<=0.0f) {
            int oclass=H(state->target,0xaa);
            if (gCurrentMapIndex==12 && oclass==4020 /* Mutant Test-Squirrel */) {
                if (++D_L00_001B0E30>=16 && !D_001A7A60[22]) {
                    D_001A7A60[22]=1; PlaySoundFromGlobalBank(1,0,0); SetEntryValueByIndex(4659,-1); D_L00_001A903C=1;
                }
            }
            PlayMobySound(3,0,object);
            SpawnDarkSheepFromObject(state->target); state->target=0;
        }
        UpdateSheepinatorBeamShape(object);
        if (D_L00_001B2C74==-1) D_L00_001B2C74=AddPointLight(object+0x10,7.5f,0.0f,0x207f7f);
        if (D_L00_001B2C74>=0) {
            D_L00_001B2C78=20;
            vec_scale_to_length(matrix,object+0xd0,-0.5f);
            FastVecAdd(&matrix[1],state,matrix);
            { Light *light=&D_L00_001C6F40[D_L00_001B2C74];
            float x=matrix[1].x, y=matrix[1].y, z=matrix[1].z; light->pos[0]=x; light->pos[1]=y; light->pos[2]=z; light->radius=7.5f; }
        }
        if (!IsVoicePlayingForOwner(object,D_L00_001B2C7C)) D_L00_001B2C7C=PlayMobySound(1,4,object);
    } else {
        state->target=0; state->seen=0; state->delay=0; D_L00_001B2C70=1;
        if (D_L00_001B2C74>=0) {
            vec_scale_to_length(&offset,object+0xd0,-0.5f);
            FastVecAdd(&direction,state,&offset);
            entry=&D_L00_001C6F40[D_L00_001B2C74];
            { float x=direction.x, y=direction.y, z=direction.z; entry->pos[0]=x; entry->pos[1]=y; entry->pos[2]=z; entry->radius=7.5f; }
            value=IntToFloat(D_L00_001B2C78)*0.05f;
            entry=&D_L00_001C6F40[D_L00_001B2C74];
            entry->color[0]=value; entry->color[1]=value; entry->color[2]=value*0.25f;
            if (FastFloatHelperD(&D_L00_001B2C78)) { FreePointLight(D_L00_001B2C74); D_L00_001B2C74=-1; }
        }
    if (D_L00_001B2C74>=0 && !D_L00_001B2C78) { FreePointLight(D_L00_001B2C74); D_L00_001B2C74=-1; }
    index=D_L00_001B2C7C;
    if (index>=0) {
        if (index!=-1 && ((Voice *)(gSoundState+index*112))->owner==object && ((Voice *)(gSoundState+index*112))->playing) StopSoundVoice(index);
        D_L00_001B2C7C=-1;
    }
    if (B(object,0x60)&2) StartAnimationBlendedWithFlags(object,1,0,1,0);
    }
    }
    if (special && D_L00_001B2C74>=0) { FreePointLight(D_L00_001B2C74); D_L00_001B2C74=-1; }
}
