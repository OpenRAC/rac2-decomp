/* func_PAL_L22_00418B08, the PAL copy of func_L22_00413B70: the same C, where rename func_L22_003398B8 becomes func_PAL_L22_0033BBB0; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_002BCB00 becomes func_PAL_002BD790; rename func_L08_0034A078 becomes func_PAL_L08_0034C4A8; lit 1.0f becomes 1.2f. */
#include "common.h"
typedef union { unsigned int q __attribute__((mode(TI))); struct { float x,y,z,w; } f; } V413;
typedef struct {
    V413 velocity;
    int charge, age;
    char pad18[0x14];
    short light, triggered;
    V413 orientation;
    short kind, pad42;
    int override;
    char pad48[8];
    V413 direction;
} State413;
typedef struct { float inner, outer; char pad[8]; V413 position; } Light413;
typedef struct { char pad[0x98]; float angle; char gap[0x21F4]; int owner; char gap2[0x20]; unsigned char mode; } Player413;
extern Player413 D_00189E20;
extern int D_L22_001B1564 __attribute__((sda)), D_L22_001B1568 __attribute__((sda));
extern int D_L22_001B155C __attribute__((sda)), D_L22_001B1560 __attribute__((sda));
extern float D_L22_001B1544 __attribute__((sda)), D_L22_001B1548 __attribute__((sda));
extern int D_L22_001A8FF0 MACRO_ADDR;
typedef struct { int enabled; unsigned int color; unsigned long long counter; } ChargeFx413;
extern ChargeFx413 D_L22_001A8AC0[] __attribute__((sda));
extern int D_L22_001A8AB0;
extern int D_L22_001B1C48;
extern float D_L22_001A93E4;
extern char D_L22_001C4140[];
/* sda: one la macro per use, so its address is not kept across the loop. */
extern char D_L22_001A8F20[] __attribute__((sda));
/* Unsized view: read through a separate lui rather than the small-data lw macro. */
extern unsigned char *D_L22_001FF82C[];
extern Light413 D_L22_001C7E00[];
extern float func_00283CE0(int), func_002A7878(float,float), func_00283180(float), func_00283198(float);
extern int func_00283CF0(float), func_002A7820(int,int), func_002A77E0(int);
extern void func_00282F20(void*,void*,float), func_00282CD8(void*,void*,void*);
extern void func_PAL_L22_0033BBB0(int,void*,void*);
extern void func_L22_00334F78(void*,int,int,int,int,float,float);
extern short func_00291308(void*,int,float,float);
extern int func_L00_0035F5A0(int,int,int);
extern void func_002E59F8(int), func_00291450(int), func_0029F338(int);
extern void func_00282D30(void*,void*,float),func_002AFFD8(void*,void*,int),func_L00_00325600(void*,void*,int);
extern void func_00282DD8(void*,void*,void*),func_00283958(void*,void*),func_00283738(void*,void*,void*);
extern float func_00282DF0(void*),func_00282C10(float);
extern int func_00277F48(void*,int,void*,int,float);
extern void func_002A9850(void*,void*,void*,int,int,int,int,int,float,float,float);
extern void func_PAL_L00_003FB330(void*,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void func_L04_00358868(void*,int,int,int,float),func_002A7988(void*,float,float);
extern void func_PAL_002BD790(void*,void*,int,int,int,int,int,int,int,float);
extern char *func_PAL_L08_0034C4A8(void*,void*,int,void*);

void func_PAL_L22_00418B08(unsigned char *obj)
{
    struct { V413 velocity, random, position, scaled, matrix[3], rotation, normalized, temp; } frame;
    State413 *state;
    int *handle = &D_L22_001B1568;
    int i, j, hit, color;
    float radius, spread, fade, factor;
    char *particle, *sub;
    if (*(int *)(obj+0xB8) == D_00189E20.owner) handle=&D_L22_001B1564;
    state = *(State413 **)(obj+0x68);
    switch (obj[0x20]) {
    case 0: {
        float charge;
        if (state->triggered && (D_00189E20.mode==2 || !state->kind)) {
            if (!state->charge && handle==&D_L22_001B1568) {
                D_L22_001A8AC0[0].enabled=1;
                D_L22_001A8AC0[0].color=0xFFFF00;
            }
            charge=func_00283CE0(++state->charge)*0.039473683f;
            if (charge>1.0f) charge=1.0f;
            charge *= charge * (state->kind ? 10.0f : 5.0f);
            for (j=0;j<func_00283CF0(charge);j++) {
                int loop_r,loop_g,loop_b;
                frame.random.q=0;
                frame.random.f.x=func_002A7878(-1.0f,1.0f);
                frame.random.f.y=func_002A7878(-1.0f,1.0f);
                frame.random.f.z=func_002A7878(-1.0f,1.0f);
                frame.velocity.q=frame.random.q;
                if (state->kind) { loop_r=0x4F;loop_g=0xAF;loop_b=0xFF; }
                else { loop_r=0x6F;loop_g=0x1F;loop_b=0xF; }
                loop_g=func_002A7820(loop_r,loop_g);
                loop_b=func_002A7820(loop_r,loop_b);
                if (loop_b>255) loop_b=255;
                if (loop_g>255) loop_g=255;
                func_00282F20(&frame.velocity,&frame.velocity,func_002A7878(15.0f,30.0f));
                func_00282CD8(&frame.random,&frame.velocity,obj+0x10);
                {
                    int high=(loop_g<<8)|0x7F000000;
                    func_PAL_L22_0033BBB0((loop_b<<16)|high|loop_r,&frame.velocity,obj);
                }
            }
            if (state->charge<50) {
                int alpha=D_L22_001A8AC0[0].color>>24;
                if (!D_L22_001A8AC0[0].counter && alpha==255) alpha=37;
                if (alpha<36) alpha++; else alpha=37;
                D_L22_001A8AC0[0].counter=0x1F00000042ULL;
                D_L22_001A8AC0[0].color=(D_L22_001A8AC0[0].color&0xFFFF00)|(alpha<<24);
            } else D_L22_001A8AC0[0].color |= 0xFF000000;
            if (state->light != -1) {
                float light_charge;
                float inner, outer;
                D_L22_001C7E00[state->light].position.f.x=*(float *)(obj+0x10);
                D_L22_001C7E00[state->light].position.f.y=*(float *)(obj+0x14);
                D_L22_001C7E00[state->light].position.f.z=*(float *)(obj+0x18);
                { int n=state->charge;
                if (n>50) n=50;
                if (n<0) n=0;
                D_L22_001C7E00[state->light].position.f.w=func_00283CE0(n)*0.14f; }
                light_charge=func_00283CE0(state->charge)*0.039473683f;
                if (light_charge>1) light_charge=1;
                func_L22_00334F78(&D_L22_001C7E00[state->light].position,
                    func_002A7820(15,47)&255,func_002A7820(47,63)&255,func_002A7820(63,127)&255,17,light_charge*840000.0f,0.0f);
                D_L22_001C7E00[state->light].inner=func_002A7878(D_L22_001C7E00[state->light].inner*0.8f,
                    (D_L22_001C7E00[state->light].position.f.w+D_L22_001C7E00[state->light].position.f.w)*0.14285715f);
                outer=D_L22_001C7E00[state->light].outer*0.8f;
                inner=D_L22_001C7E00[state->light].inner;
                D_L22_001C7E00[state->light].outer=func_002A7878(inner < outer ? inner : outer,inner);
            } else if (!(D_L22_001B1C48&3)) {
                state->light=func_00291308(obj+0x10,0,0.0f,0.0f);
            }
        } else {
            D_L22_001A8AB0=0;
            D_L22_001A8AC0[0].enabled=0;
            state->charge=0;
            func_L00_0035F5A0(22,0,0);
            if (state->kind) {
                if (D_L22_001B155C != -1) {
                    func_002E59F8(D_L22_001B155C);
                    D_L22_001B155C=func_L00_0035F5A0(21,0,0);
                }
            } else if (D_L22_001B1560 != -1) {
                func_002E59F8(D_L22_001B1560);
                D_L22_001B1560=func_L00_0035F5A0(21,0,0);
            }
            if (!D_L22_001A8FF0) {
                state->velocity.f.x=func_00283180(D_00189E20.angle)*0.8000001f;
                state->velocity.f.y=func_00283198(D_00189E20.angle)*0.8000001f;
                state->velocity.f.z=0;
                obj[0x20]=1;
                state->age=0;
            } else {
                func_00282D30(state,obj+0xC0,2.0f);
                obj[0x20]=1;
                state->age=0;
            }
        }
    break;
    }
    case 1: {
        float extra = 3.5f;
        radius=func_00283CE0(state->age)*0.40000004f+1.3f;
        ++state->age;
        func_002AFFD8(obj+0x10,&frame.position,1);
        spread=radius+extra;
        if (state->kind) func_00282F20(&frame.scaled,obj+0xC0,2.0f);
        else func_00282F20(&frame.scaled,obj+0xC0,extra);
        func_00282F20(&frame.normalized,&frame.position,1.0f);
        func_00282DD8(&frame.rotation,obj+0xE0,&frame.normalized);
        if (state->kind) factor=D_L22_001B1548; else factor=D_L22_001B1544;
        func_00282D30(&frame.rotation,&frame.rotation,factor);
        fade=func_00282DF0(&frame.rotation);
        frame.rotation.f.w=-func_00282C10(1.0f-fade*fade);
        func_00283958(&frame.rotation,frame.matrix);
        func_00283738(obj+0xC0,frame.matrix,obj+0xC0);
        if (state->override) {
            if (state->kind) func_00282D30(&frame.scaled,&state->direction,0.8000001f);
            else func_00282D30(&frame.scaled,&state->direction,1.2f);
            func_00282F20(&frame.temp,&frame.scaled,1.0f);
            qcopy(obj+0xC0, &frame.temp);
        }
        state->velocity.q=frame.scaled.q;
        if (state->light!=-1) {
            Light413 *lights = D_L22_001C7E00;
            lights[state->light].position.f.w *= 0.27999997f;
            if (lights[state->light].position.f.w<0.0001f) {
                func_00291450(state->light);
                state->light=-1;
            }
        }
        if (state->age>=43 || D_00189E20.mode!=2) {
            if (*(int *)(obj+0xB8)==D_00189E20.owner) {
                if(D_L22_001B155C!=-1) {func_002E59F8(D_L22_001B155C);D_L22_001B155C=-1;}
            } else if(D_L22_001B1560!=-1) {func_002E59F8(D_L22_001B1560);D_L22_001B1560=-1;}
            func_0029F338(*handle);
            *handle=0;
            return;
        } else {
            func_00282CD8(&frame.position,obj+0x10,state);
            if (*(float *)(obj+0x10)<2 || *(float *)(obj+0x10)>1021 ||
                *(float *)(obj+0x14)<2 || *(float *)(obj+0x14)>1021 ||
                *(float *)(obj+0x18)<2 || *(float *)(obj+0x18)>1021) {
                if (*(int *)(obj+0xB8)==D_00189E20.owner) {
                    if(D_L22_001B155C!=-1) {func_002E59F8(D_L22_001B155C);D_L22_001B155C=-1;}
                } else if(D_L22_001B1560!=-1) {func_002E59F8(D_L22_001B1560);D_L22_001B1560=-1;}
                func_0029F338(*handle);
                *handle=0;
                return;
            } else if (state->kind) {
                hit=func_00277F48(obj+0x10,16,obj,0,radius);
                frame.position.q=((V413 *)(obj+0x10))->q;
                func_002A9850(obj,&frame.position,D_L22_001C4140,hit,0,0x8B0000,2,1,D_L22_001A93E4,1.0f,1.0f);
                if (hit) func_PAL_L00_003FB330(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1.0f,20.0f);
                {
                /* Block scopes keep these local to one basic block, as retail allocates them. */
                float effect=spread*105000.0f, diameter;
                int count=42-state->age;
                if(count>4) count=4;
                diameter=spread+spread;
                {
                int b=func_002A7820(63,127);
                int g=func_002A7820(47,63);
                int r=func_002A7820(15,47);
                int high=(g<<8)|0x4F000000;
                func_L04_00358868(obj,(b<<16)|high|r,count,-1,effect);
                }
                func_002A7988(&frame.velocity,spread*0.020000001f,diameter*0.020000001f);
                {
                int b=func_002A7820(63,127);
                int g=func_002A7820(47,63);
                int r=func_002A7820(15,47);
                int high=(g<<8)|0x7F000000;
                func_PAL_002BD790(obj+0x10,&frame.velocity,(b<<16)|high|r,0x4F7F4F2F,37,1,*D_L22_001FF82C[0],-1,0,210000.0f);
                }
                }
                i=5;
                do {
                    func_002A7988(&frame.velocity,spread*0.020000001f,(spread+spread)*0.020000001f);
                    func_002A7988(&frame.random,0.0f,spread*0.5f);
                    func_00282CD8(&frame.position,&frame.random,obj+0x10);
                    particle=func_PAL_L08_0034C4A8(&frame.random,&frame.velocity,127,obj);
                    /* reorg merges the two decrements into the test's delay slot. */
                    if(particle) {
                        *(float *)(particle+12)=func_002A7878(6000,32000)*spread*0.4f;
                        --i;
                    } else --i;
                } while(i>=0);
                for(i=0;i<8;i++) {
                    particle=func_PAL_L08_0034C4A8(obj+0x10,D_L22_001A8F20,127,obj);
                    if(particle) {
                        sub=particle+0x20;
                        if(i==2 && !func_002A77E0(8)) *(float *)(particle+12)=180000;
                        else *(float *)(particle+12)=func_002A7878(80000,120000);
                        *(short *)(particle+10)=2;
                        *(float *)(particle+12)*=spread;
                        fade=func_00283CE0(2);
                        color=0x7F7F7F;
                        *(short *)(sub+0x16)=3;
                        *(int *)(sub+0x18)=color;
                        *(float *)(sub+0x10)=1.0f/fade;
                    }
                }
            } else {
                hit=func_00277F48(obj+0x10,16,*(void **)(obj+0xB8),0,radius);
                frame.position.q=((V413 *)(obj+0x10))->q;
                func_002A9850(obj,&frame.position,D_L22_001C4140,hit,0,0x8B0007,2,1,D_L22_001A93E4,1,1);
                if(hit) func_PAL_L00_003FB330(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1,20);
                {
                float effect=spread*105000.0f;
                int count=42-state->age;
                if(count>4)count=4;
                {
                int r=func_002A7820(15,47);
                int g=func_002A7820(47,63);
                int b=func_002A7820(63,127);
                int high=(g<<8)|0x4F000000;
                func_L04_00358868(obj,(r<<16)|high|b,count,-1,effect);
                }
                }
                func_002A7988(&frame.velocity,spread*0.020000001f,(spread+spread)*0.020000001f);
                {
                int r=func_002A7820(15,47);
                int g=func_002A7820(31,47);
                int b=func_002A7820(63,127);
                int high=(g<<8)|0x7F000000;
                func_PAL_002BD790(obj+0x10,&frame.velocity,(r<<16)|high|b,0x4F1F1F7F,37,1,*D_L22_001FF82C[0],-1,0,210000);
                }
            }
        }
    }
    }
    if(D_L22_001A8FF0) {
        func_002AFFD8(obj+0x10,&state->orientation,0);
        func_L00_00325600(obj+0xC0,&state->orientation,0);
    }
    state->triggered=0;
}
