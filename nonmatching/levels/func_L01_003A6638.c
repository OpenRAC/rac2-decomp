/* 2 November 2026: lawful retained reconstruction, not a match.
 * Removed ten deliberately dead initial values used only to alter the
 * compiler PRE hash-table count. Every actual first-use state assignment
 * remains. Current default G8/zero-ti-por/debug check: 2276/2276 bytes,
 * 0/1 USA v1.01 placement, first difference +0x1B4 (spill-slot ordering).
 * Three additional controls named real used material/attack constants,
 * angular/timestep constants, or both. None recovered the retail slots:
 * integer-only remains nonmatching; the two float forms emit 2272 bytes,
 * with the float-only form also growing the frame to 0x240.
 * The earlier exact-byte dead-initializer diagnostic is privately preserved
 * and provides no accepted C credit. Reopen on genuine PRE-copy lifetimes.
 * Use -O2 -G8 -ffunction-sections -frac2-zero-ti-por -g in a separate unit.
 */
#include "common.h"
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
typedef int OozlaQuad __attribute__((mode(TI)));
extern float D_L01_001AF870 __attribute__((sda));
extern float D_L01_001AF874 __attribute__((sda));
extern int D_L01_001AF878 __attribute__((sda));
extern float D_L01_001AF87C __attribute__((sda));
extern float D_L01_001AF880 __attribute__((sda));
extern float D_L01_001AF894 __attribute__((sda));
extern float D_L01_001AF898 __attribute__((sda));
extern float D_L01_001AF89C __attribute__((sda));
extern float D_L01_001AF8A0 __attribute__((sda));
extern float D_L01_001AF8A8 __attribute__((sda));
extern float D_L01_001AF8AC __attribute__((sda));
extern float D_L01_001AF8B0 __attribute__((sda));
extern float D_L01_001AF8BC __attribute__((sda));
extern float D_L01_001AF8C0 __attribute__((sda));
extern float D_L01_001AC580[] MACRO_ADDR;
extern u8 D_00139568[];
extern char D_00138180[];
typedef struct { u8 pad[0x1A4]; u32 flags; } OozlaInput;
typedef struct { u8 pad[0x50]; float speed; u8 gap[0x1C]; float material; u8 tail[0x6C]; } OozlaMaterial;
extern OozlaMaterial D_L01_002637A0[];
extern u8 D_L01_001BF900[];
extern u8 D_L01_001C3980[];
extern int D_L01_001A8A44;
extern void func_002A7470(void *,int,int,int);
extern void func_L01_003A6448(float *,float *);
extern float func_00283B98(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_L01_003A65B0(void *);
extern float func_00282DF0(void *);
extern void func_L01_003A64F0(void *,void *);
extern void func_00283410(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282C48(float);
extern void func_00282D30(void *,void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_00282DB0(void *,void *);
extern float func_002831B0(float);
extern void func_00283658(void *,void *);
extern void func_00283678(void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00283788(void *,void *,void *);
extern void func_002AB6D8(void *,void *);
extern void func_00283698(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_L00_002EE4D8(void *,void *,float);
extern void func_002ABBB8(void *,void *,int,int,int,int,int,int,int,int,int,int,float,float,float,float,float,float,float);
extern int func_00277F48(void *,int,void *,int,float);
extern void func_002A9850(void *,void *,void *,int,int,int,int,int,float,float,float);
extern int func_00282948(void *);
extern void func_003355A8(int);
extern void func_L01_002BEB90(int,int);
extern void func_0029F338(void *);
extern void func_002A9288(void *,float);
void func_L01_003A6638(u8 *object)
{
    float previous[4], velocity[4], position[4];
    union {
        struct {
            float rotation[16];
            union {
                float basis[16];
                struct { float first[4], vector[4], temporary[8]; } rows;
            } orientation;
            float matrix[16];
        } transform;
        struct { float pad[4], inverse[16]; } inverse_view;
    } workspace;
#define rotation workspace.transform.rotation
#define inverse workspace.inverse_view.inverse
#define basis workspace.transform.orientation.basis
#define vector workspace.transform.orientation.rows.vector
#define temporary workspace.transform.orientation.rows.temporary
#define matrix workspace.transform.matrix
    float start[4], angles[4], finish[4], shift[4], offset[4], hit[4], normal[4], force[4], adjustment[4], edge[4];
    float horizontal, vertical;
    float maximum, speed, progress, sign, angle, half, cosine;
    u8 *state = *(u8 **)(object+0x68);
    int collision, count, blocked, level, level2;
    qcopy(previous, (object+0x10));
    switch (object[0x20]) {
    case 0:
        F(state,0x44) = F(state,0x18);
        object[0x20] = 1;
        if (object[0x43] != 1) func_002A7470(object,1,0,10);
        break;
    case 1:
        func_L01_003A6448(&horizontal,&vertical);
        F(state,0x18) = F(state,0x44) = func_00283B98(F(state,0x44),D_L01_001AF870*(horizontal*0.00029088825f));
        level = D_00139568[0x20];
        maximum = ((OozlaMaterial *)((u32)D_L01_002637A0 + level*sizeof(OozlaMaterial)))->speed*0.016666668f;
        F(state,0x4C) += (vertical*maximum-F(state,0x4C))*D_L01_001AF880;
        speed = F(state,0x4C)/maximum;
        F(object,0x48) = speed+speed+horizontal;
        func_00282F20(velocity,D_L01_001AC580,F(state,0x4C));
        func_00283098(velocity,velocity,object+0xC0);
        velocity[2] += F(state,0x54);
        func_00282CC0(position,object+0x10,velocity);
        qcopy((object+0x10), position);
        func_L01_003A65B0(object);
        if (F(state,0x4C) < 0.0f) F(state,0x4C) = -func_00282DF0(velocity);
        else F(state,0x4C) = func_00282DF0(velocity);
        func_L01_003A64F0(object,state);
        *(OozlaQuad *)angles = 0;
        angles[2] = D_L01_001AF870*(horizontal*0.00029088825f);
        *(OozlaQuad *)start = *(OozlaQuad *)angles;
        qzero_nc(rotation);
        qzero_nc(basis);
        qzero_nc(matrix);
        func_00283410(rotation,start);
        progress = 0.0f;
        collision = 0;
        while (progress <= D_L01_001AF8A0 && !collision) {
            sign = vertical < 0.0f ? -1.0f : 1.0f;
            func_00282F20(angles,object+0xE0,D_L01_001AF87C);
            func_00282CC0(angles,angles,object+0x10);
            func_00282F20(shift,object+0xC0,D_L01_001AF8AC*progress*sign);
            func_00282CC0(angles,angles,shift);
            func_00282F20(offset,object+0xE0,D_L01_001AF8A8);
            func_00282CF0(finish,object+0x10,offset);
            func_00282D30(normal,velocity,func_00282C48(vertical));
            half = D_L01_001AF8A0*0.5f;
            func_00282D30(shift,normal,(D_L01_001AF8BC*(half-progress))/half);
            func_00282CC0(finish,finish,shift);
            collision = func_002761F8(angles,finish,0,object,0);
            progress += 1.0f;
        }
        if (collision) {
            qcopy(hit, (D_L01_001BF900+0x20));
            func_00282F20(normal,object+0xE0,1.0f);
            func_00282F20(force,D_L01_001BF900+0x40,1.0f);
            cosine = func_00282DB0(normal,force);
            angle = 1.5707964f-func_002831B0(cosine);
            if (D_L01_001AF8C0*0.017453294f < angle) {
                qcopy((object+0x10), previous);
            } else {
                func_00282F20(adjustment,D_L01_001BF900+0x40,D_L01_001AF894);
                func_00282F20(angles,object+0xE0,D_L01_001AF87C);
                func_00282CF0(finish,object+0x10,angles);
                func_00282CC0(angles,angles,object+0x10);
                blocked = func_002761F8(angles,finish,0,object,0);
                if (blocked) {
                    func_00282F20(edge,D_L01_001BF900+0x40,D_L01_001AF898);
                    func_00282CC0(adjustment,adjustment,edge);
                }
                func_00282F20(edge,object+0xE0,D_L01_001AF89C);
                func_00282CC0(adjustment,adjustment,edge);
                func_00283658(basis,object+0xC0);
                func_00282F20(temporary,adjustment,-1.0f);
                func_00282DD8(vector,temporary,basis);
                func_00282DD8(basis,vector,temporary);
                func_00283788(matrix,basis,rotation);
                func_002AB6D8(matrix,object+0xF0);
                func_00282CF0(edge,hit,object+0x10);
                func_00282F20(edge,edge,
                    D_L01_001AF8B0*0.016666668f < func_00282DF0(edge)
                    ? D_L01_001AF8B0*0.016666668f : func_00282DF0(edge));
                func_00282CC0(object+0x10,object+0x10,edge);
                F(state,0x54) = 0.0f;
            }
        } else {
            qcopy((object+0x10), previous);
            func_00283658(basis,object+0xC0);
            func_00283678(object+0xC0,matrix);
            func_00283788(matrix,basis,rotation);
            func_00283678(object+0xC0,matrix);
        }
        func_L01_003A65B0(object);
        func_00283698(inverse,object+0xC0);
        func_00282CF0(rotation,object+0x10,previous);
        func_002830C0(rotation,rotation,inverse);
        func_L00_002EE4D8(rotation,rotation,func_00282C48(F(state,0x4C)));
        func_00283098(rotation,rotation,object+0xC0);
        func_00282CC0(object+0x10,previous,rotation);
        if (((OozlaInput *)D_00138180)->flags & 0x20) {
            func_002ABBB8(object,velocity,0,10,3,16,1,1,1,-1,0,0x810001,0.0f,0.0f,4.0f,2.0f,0.0f,1.0f,20.0f);
            count = func_00277F48(object+0x10,16,object,0,D_L01_001AF874);
            *(OozlaQuad *)vector = *(OozlaQuad *)(object+0x10);
            level2 = D_00139568[0x20];
            func_002A9850(object,vector,D_L01_001C3980,count,0,0x830000,3,2,((OozlaMaterial *)((u32)D_L01_002637A0 + level2*sizeof(OozlaMaterial)))->material,1.0f,1.0f);
            I(state,0x40) = D_L01_001AF878;
            I(object,0x98) = 0;
            *(u16 *)(object+0x34) = (*(u16 *)(object+0x34) | 0x41)&0xEFFF;
            D_L01_001A8A44 = 0;
            object[0x20] = 2;
        }
        if (F(object,0x10)<2.0f || F(object,0x10)>1021.0f || F(object,0x14)<2.0f || F(object,0x14)>1021.0f || F(object,0x18)<2.0f || F(object,0x18)>1021.0f) {
            func_0029F338(object);
            return;
        }
        break;
    case 2:
        if (func_00282948(state+0x40)) {
            func_003355A8(0);
            func_L01_002BEB90(0,1);
            func_0029F338(object);
            return;
        }
        break;
    }
    func_002A9288(object,D_L01_001AF87C);
}
