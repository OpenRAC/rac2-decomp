/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Closer C4, 1 November 2026: 1248/1260 under -O2 -G8 -ffunction-sections with plain data NOT_SDA, 80 rows, most of them a rotation
 * (retail s3 = src, s4 = the D_00189E20 high then D_0018B334, s5 = hero). The tuning floats are an if/else: with `f = a; if (...) f = b`
 * cse skips the then-block and keeps 0.02f in f20, where retail rebuilds it in f2. Left: D_L00_001A7FE4 as `lui at` / lwc1, FE0 through
 * $gp in a delay slot; the 0.00029 constant stays in f0 (mul.s f12,f1,f0); the rotation.
 */
/* GPT-6.1 Sol high worker, USA v1.01, 29 October 2026.
 * Default game profile: -O2 -G0 -ffunction-sections.
 * check.py: 1244/1260 bytes, 0/27 places. No linked build run.
 * Typed root fields recover the initial root-base setup. Separately named
 * scalar fields and rebased root pointers recover more later address shapes.
 * Remaining: s3/s4/s5 allocation, 0.02f retained in f20 instead of rebuilt,
 * FP argument setup, and pointer lifetimes. The documented block-order and
 * unsplit-edge options did not improve this draft; -G8 emitted 1276 bytes.
 * An unsuffixed double comparison adds runtime helper calls, not a remedy.
 * All required declarations are below; keep the canonical callee interface.
 */
#include "common.h"
typedef int Quad1269 __attribute__((mode(TI)));
typedef struct {
    float origin[4];
    char pad0010[0x70];
    float position[4];
    char pad0090[0xC0];
    float velocity[4];
    char pad0160[0x14];
    float speed;
    char pad0178[0x5B8];
    float transform[12];
    Quad1269 vector760;
    Quad1269 vector770;
    char pad0780[0xAA0];
    char *object;
    char pad1224[0xC];
    int flags;
    char pad1234[8];
    unsigned char visible;
    char pad123D[0xB];
    int weapon;
    char pad124C[0x254];
    float transitionPos[4];
    float transitionRot[4];
    float rotation[4];
    char pad14D0[0x28];
    float blend;
    float blendVelocity;
    char pad1500[4];
    float offsetVelocity;
    float offset;
    float offsetTarget;
    float angle;
    float angleVelocity;
    char pad1518[0xD78];
    int owner;
} Hero5940;
extern Hero5940 D_00189E20;

extern char D_L00_001B8FF0[], D_L00_001B8DC0_data[], D_L00_001BF220[];
extern unsigned char D_001A7A44 NOT_SDA;
extern int D_L00_001B19C8 NOT_SDA;
extern float D_L00_001A7FE0 __attribute__((sda)); extern float D_L00_001A7FE4 NOT_SDA;
extern float D_L00_001A7CE0 __attribute__((sda)), D_L00_001A7CE4 __attribute__((sda));
extern Quad1269 D_L00_001B8DD0;
extern int func_L00_002ADED8(int);
extern void func_002A0F48(void*);
extern char *func_L00_002F3DA8(int);
extern void func_00283658(void*,void*);
extern int func_L00_002D6418(void);
extern void func_002AA2E8(float*,float,float);
extern float D_0018B334 NOT_SDA;
extern float D_0018B328 NOT_SDA;
extern float func_00283B98(float,float), func_00283198(float);
extern void func_002830C0(void*,void*,void*), func_00282CC0(void*,void*,void*);
extern void func_00283410(void*,void*), func_00283738(void*,void*,void*);
extern void func_002AB6D8(void*,void*), func_002A91F0(void*,void*);
extern void func_002AA548(float*,float*,float,float,float,float);
extern void func_00283098(void*,void*,void*), func_00282D08(void*,void*,void*,float);
extern void func_00283810(void*,void*,void*,float), func_00283958(void*,void*);
extern void func_00282D30(void*,void*,float), func_00282F20(void*,void*,float);
extern int func_002761F8(void*,void*,int,int,int);
extern float func_00282E48(void*,void*);
extern void func_00283678(void*,void*);
void func_L00_002D5940(void) {

 char *obj=D_00189E20.object, *src;
 float m[12], v[4], rot[16], offset[4], temp[4], a[4], b[4];
 float f, height;
 int state;
 Hero5940 *hero;
 if (!obj) return;
 if (*(short*)(obj+0xaa)==0x47) {
  if (!D_00189E20.visible && !*(unsigned char*)(obj+0x20)) { obj[0x31]=0; *(unsigned short*)(obj+0x34)|=1; }
  else {obj[0x31]=1; *(unsigned short*)(obj+0x34)&=~1;}
  return;
 }
 if (func_L00_002ADED8(0)) {
  *(unsigned short*)(obj+0x34)|=1; obj[0x31]=0;
  if (*(void(**)(void*))(obj+0x64)) (*(void(**)(void*))(obj+0x64))(obj);
  func_002A0F48(obj); return;
 }
 src=func_L00_002F3DA8(D_00189E20.weapon);
 func_00283658(m,D_L00_001B8FF0);
 qcopy_nc(v,D_L00_001B8FF0-0x230);
 v[3]=1.0f;
 qcopy_nc(offset,src);
 offset[0]+=D_00189E20.offset;
 if (D_001A7A44 && !func_L00_002D6418()) offset[1]=-offset[1];
 if (D_00189E20.speed<=0.02f) f=D_L00_001A7FE0; else f=D_L00_001A7FE4;
 func_002AA2E8(&D_0018B334,f*0.0002908882452175021f,0.006981317885220051f);
 hero = (Hero5940 *)((char *)&D_0018B334 - 0x1514);
 hero->angle=func_00283B98(hero->angle,hero->angleVelocity);
 offset[2]+=func_00283198(hero->angle)*0.02f;
 func_002830C0(obj+0x10,offset,m);
 if (!func_L00_002D6418()) func_00282CC0(obj+0x10,obj+0x10,&hero->velocity);
 func_00283410(rot,src+0x10);
 func_00283738(obj+0xc0,m,rot);
 func_002AB6D8(obj+0xc0,obj+0xf0);
 func_002A91F0(&hero->rotation,obj+0xf0);
 if (hero->blend<1.0f) {
  func_002AA548(&hero->blend,&hero->blendVelocity,1.0f,D_L00_001A7CE0*0.016666667f,D_L00_001A7CE4*0.00027777778f,D_L00_001A7CE0*0.016666667f);
  func_00283098(temp,&hero->transitionPos,hero);
  func_00282CC0(temp,temp,&hero->position);
  func_00282D08(obj+0x10,temp,obj+0x10,hero->blend);
  func_002A91F0(a,obj+0xf0);
  func_00283810(b,&hero->transitionRot,a,hero->blend);
  func_00283958(b,obj+0xc0);
 }
 obj[0x31]=1; *(unsigned short*)(obj+0x34)&=~1;
 func_002A0F48(obj);
 if ((D_L00_001B19C8^1)&1) {
  height=*(float*)(obj+0xc)*0.0009765625f;
  func_00282D30(temp,obj,0.0009765625f);
  func_00282F20(a,obj+0xd0,height*-1.2f);
  func_00282CC0(a,a,temp);
  if (func_002761F8(D_L00_001B8DC0_data,a,0,hero->owner,0)) {
   f=(hero->offset-height)+func_00282E48(D_L00_001BF220,temp);
   hero->offsetTarget=f;
   if (f>0.0f) hero->offsetTarget=0.0f;
   else if (f< -1.5f) hero->offsetTarget=-1.5f;
  } else hero->offsetTarget=0;
 }
 hero = (Hero5940 *)((char *)&D_0018B328 - 0x1508);
 func_002AA548(&D_0018B328,&hero->offsetVelocity,hero->offsetTarget,0.0041666669f,0.0041666669f,0.083333336f);
 func_00283678(&hero->transform,m);
 qcopy_nc(&hero->vector760,m);
 qcopy_nc(&hero->vector770,&D_L00_001B8DD0);
 state=func_L00_002D6418();
 if (state) hero->flags|=5;
 if (*(void(**)(void*))(obj+0x64)) (*(void(**)(void*))(obj+0x64))(obj);
 if (state) hero->flags&=~5;
}
