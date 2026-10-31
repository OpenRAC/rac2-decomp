/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * 1976/1984 bytes; frame 0x100 retained, long particle-loop allocation and trig/random call argument schedule differ.
 * Reopen with measured lexical-lifetime/source-loop evidence; plain/debug profile trials tie.
 * ABI/bounds: Six complete 16-byte vectors; particle from/to fourth components are initialized for the real 002BAA28 reader. Query helpers retain six/seven GPR and three/two FP banks; collision helper returns int. Particle helper returns a pointer.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"
typedef float AttackVector[4] __attribute__((aligned(16)));
extern float func_00282E80(void *,void *),func_00283248(float,float);
extern float func_00283BE0(float,float),func_00283B98(float,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern int func_L01_003120A8(void *,void *,void *,int,float,float,int,int,int);
extern void func_002AF000(void *,float,float,float);
extern int func_001163B0(void),func_00283CF0(float);
extern float func_002A7878(float,float);
extern unsigned char *func_002BAA28(void *,void *,void *,int,int,int,int,int,int);

/* Enemy attack trace and its two particle bursts. Endpoint vectors include the
 * fourth components consumed by func_002BAA28; none is a three-float buffer. */
void func_L01_003DC078(unsigned char *m,int skip_particles)
{
    AttackVector position, end, offset, from, to, particle_position;
    unsigned char *p=*(unsigned char **)(m+0x68), *target=*(unsigned char **)(p+0x2f0), *particle;
    float vertical, horizontal;
    int first_color,last_color,kind,duration,size,mode,i;
    vertical=func_00283BE0(func_00283248(func_00282E80(m+0x10,target+0x10),
        *(float *)(target+0x18)-*(float *)(m+0x18)),*(float *)(m+0xf4));
    if(vertical>0.3490659f) vertical=0.3490659f;
    else if(vertical< -0.3490659f) vertical= -0.3490659f;
    vertical=func_00283B98(vertical,*(float *)(m+0xf4));
    horizontal=*(float *)(m+0xf8);
    func_0029FCC0(m,0,position);
    func_00282F20(offset,m+0xc0,-0.4f); func_00282CC0(position,position,offset);
    func_00282F20(offset,m+0xe0,0.3f); func_00282CC0(position,position,offset);
    if(*(short *)(target+0xaa)==0xb1a) {
        func_002A8C28(m,position,0x4000001,0,1,0,1.0f,(float)p[0x34],1.0f);
        return;
    }
    if(*(unsigned char **)(p+0x3f0)) {
        particle=*(unsigned char **)(p+0x3f0);
        if(particle[0]==2 && particle[1]!=128) {
            float distance=func_00282E80(position,particle+0x10);
            if(*(float *)(p+0x3f4)<distance) *(float *)(p+0x3f4)=distance;
        } else { *(void **)(p+0x3f0)=0; *(float *)(p+0x3f4)=3.0f; }
        func_002AF000(end,*(float *)(p+0x3f4),horizontal,vertical);
        func_00282CC0(end,end,position);
        func_L01_003120A8(m,position,end,0x4000001,(float)p[0x34],1.0f,0,1,0);
        func_002A8C28(m,end,0x4000001,0,1,0,0.3f,(float)p[0x34],1.0f);
    }
    if(skip_particles) return;
    from[3]=0.2f; to[3]=1.0f;
    for(i=1;i>=0;--i) {
        mode=func_001163B0()&1;
        first_color=0x50608040; last_color=0x10608040;
        if(!mode && (func_001163B0()&1)) first_color=last_color=0x30304020;
        qcopy(particle_position,position);
        particle_position[0]+=func_002A7878(-0.18f,0.18f);
        particle_position[1]+=func_002A7878(-0.18f,0.18f);
        particle_position[2]+=func_002A7878(-0.18f,0.18f);
        func_002AF000(from,0.15f,horizontal,vertical);
        from[2]+=func_002A7878(0.0075000002980232239f,0.0091666672378778458f);
        func_002AF000(to,0.008333334f,
            func_00283B98(horizontal,func_002A7878(-9.0f,9.0f)*0.017453294f),vertical);
        to[2]+=func_002A7878(-0.030000001192092896f,-0.036666668951511383f);
        kind=func_00283CF0(func_002A7878(2,4));
        duration=func_00283CF0(func_002A7878(20,24));
        size=func_00283CF0(func_002A7878(30,36));
        particle=func_002BAA28(particle_position,from,to,first_color,last_color,kind,duration,size,-1);
        if(particle) {
            if(!*(void **)(p+0x3f0)) *(void **)(p+0x3f0)=particle;
            if(mode) particle[3]=0x48;
        }
    }
    from[3]=0.05f; to[3]=0.09f;
    for(i=2;i>=0;--i) {
        mode=func_001163B0()&1;
        first_color=0x8050ff30; last_color=0x3050ff30;
        if(!mode && (func_001163B0()&1)) { first_color=0x80306000; last_color=0x30304000; }
        qcopy(particle_position,position);
        particle_position[0]+=func_002A7878(-0.24f,0.24f);
        particle_position[1]+=func_002A7878(-0.24f,0.24f);
        particle_position[2]+=func_002A7878(-0.24f,0.24f);
        func_002AF000(from,0.16666667f,
            func_00283B98(horizontal,func_002A7878(-18.0f,18.0f)*0.017453294f),vertical);
        from[2]+=func_002A7878(0.005833333358168602f,0.01250000111758709f);
        func_002AF000(to,0.008333334f,
            func_00283B98(horizontal,func_002A7878(-4.0f,4.0f)*0.017453294f),vertical);
        to[2]+=func_002A7878(-0.014000000432133675f,-0.030000001192092896f);
        kind=func_00283CF0(func_002A7878(2,4));
        duration=func_00283CF0(func_002A7878(20,24));
        size=func_00283CF0(func_002A7878(100,120.00000762939453f));
        particle=func_002BAA28(particle_position,from,to,first_color,last_color,kind,duration,size,-1);
        if(particle && mode) particle[3]=0x48;
    }
}
