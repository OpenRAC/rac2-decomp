/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high, v0717; USA v1.01, -O2 -G8 -ffunction-sections.
 * Best: 1088/1088 bytes, 0/2 placements; first mismatch +0x30.
 * A real 4x4 matrix closes basis-pointer allocation and call setup. Separate
 * UV assignments and reversed first-pair color assignments close packet stores.
 * Typed object/controller fields close the first call's store delay slot.
 * Remaining: mesh-loop counter/output/color register allocation, XYZ scalar-copy
 * scheduling, and inner/outer ring counter allocation. Explicit countdown and
 * moving-pointer mesh loops worsen code. Flat/structured mesh arrays tie;
 * temporary/direct/named-union XYZ copies tie. Ten checker invocations including
 * one declaration-rewrite compile error. Next: original loop/index types and
 * vector-copy source evidence; all declarations are retained below.
 */
#include "common.h"
typedef struct { float x,y,z; } RenderXYZ;
extern RenderXYZ D_L22_00255920[];
extern float D_L22_002A1260[][4];
extern char D_L22_002A2480[],D_L22_002A33A0[],D_L22_002A2DA0[],D_L22_001B9C80[];
extern float D_L22_001B0CA0 __attribute__((sda));
extern float D_L22_001B0CA4 __attribute__((sda));
extern float D_L22_001B0C50 __attribute__((sda));
extern int D_L22_001B0CDC __attribute__((sda));
extern int D_L22_001B0CC8 __attribute__((sda));
extern int D_L22_001B0CCC __attribute__((sda));
extern int D_L22_001B0CD0 __attribute__((sda));
extern int D_L22_001B0CD4 __attribute__((sda));
extern int D_L22_001B0CD8 __attribute__((sda));
extern int D_L22_001B0CE4 __attribute__((sda));
extern int D_L22_001B0CF4 __attribute__((sda));
extern float D_L22_001B0CE8 __attribute__((sda));
extern float D_L22_001B0CEC __attribute__((sda));
extern float D_L22_001B0D00 __attribute__((sda));
extern float func_00283B98(float,float),func_00283198(float);
extern unsigned long func_0027C878(int);
extern void func_002FC560(int,unsigned long);
extern void func_00282D30(void*,void*,float),func_00282CC0(void*,void*,void*),func_00282CF0(void*,void*,void*),func_00282F20(void*,void*,float),func_00282DD8(void*,void*,void*),func_002830C0(void*,void*,void*);
extern void func_00280328(void),func_00281810(int,void*,void*,void*,int),func_00280B90(void*,void*,int);
extern int func_00283CF0(float);
typedef struct { char pad[0x4C]; float phase; } RingController;
typedef struct { char pad[0x10]; float x,y,z; char pad2[0x68-0x1C]; RingController *controller; char pad3[0xE0-0x6C]; float axis[4]; } RingObject;
void func_L22_003FC338(RingObject *o) {
    struct { float verts[4][4]; int colors[4]; float uv[8]; unsigned long state[4]; } packet;
    float matrix[4][4],t[4],n[4],v[4];
    int col[290];
    float tmp[4];
    RingController *ctl=o->controller;
    int i;
    float alpha=1.0f;
    float sine;
    unsigned long bits;
    float x,y,z;
    ctl->phase=func_00283B98(ctl->phase,D_L22_001B0CA0);
    packet.state[1]=func_0027C878(D_L22_001B0CDC);
    packet.state[2]=0xFF9000000260UL;
    bits=(unsigned long)D_L22_001B0CC8|((unsigned long)D_L22_001B0CCC<<2);
    bits|=(unsigned long)D_L22_001B0CD0<<4;
    bits|=(unsigned long)D_L22_001B0CD4<<6;
    bits|=(unsigned long)D_L22_001B0CD8<<32;
    packet.state[3]=bits;
    packet.state[0]=0;
    func_002FC560(0x47,0x53001);
    z=o->z;
    y=o->y;
    x=o->x;
    matrix[3][0]=x;
    matrix[3][1]=y;
    matrix[3][2]=z;
    matrix[3][3]=1.0f;
    sine=func_00283198(ctl->phase);
    func_00282D30(t,o->axis,D_L22_001B0C50+D_L22_001B0CA4*sine);
    func_00282CC0(matrix[3],matrix[3],t);
    func_00282CF0(n,D_L22_001B9C80,matrix[3]);
    func_00282F20(matrix[0],n,1.0f);
    func_00282DD8(matrix[1],matrix[0],o->axis);
    func_00282F20(matrix[1],matrix[1],1.0f);
    func_00282DD8(matrix[2],matrix[1],matrix[0]);
    packet.colors[0]=packet.colors[1]=packet.colors[2]=packet.colors[3]=D_L22_001B0CE4;
    func_002FC560(6,func_0027C878(D_L22_001B0CDC));
    func_002FC560(0x42,0x8000000044UL);
    func_002FC560(8,0);
    func_002FC560(0x14,0xFF9000000260UL);
    func_002FC560(0x4a,0);
    func_00280328();
    for(i=0;
    i<290;
    i++){
        func_00282D30(tmp,D_L22_002A1260[i],D_L22_001B0CEC);
        func_002830C0(v,tmp,matrix[0]);
        D_L22_00255920[i].x=v[0];
        D_L22_00255920[i].y=v[1];
        D_L22_00255920[i].z=v[2];
        col[i]=packet.colors[0];
    }
    func_00281810(0x94,D_L22_00255920,col,D_L22_002A2480,1);
    func_00281810(0x6d,D_L22_00255920+146,col+146,D_L22_002A2480+0x490,1);
    func_00281810(0x24,D_L22_00255920+254,col+254,D_L22_002A2480+0x7f0,1);
    packet.state[1]=func_0027C878(11);
    packet.state[3]=0x8000000048UL;
    {
        int color=(func_00283CF0(alpha*64.0f+128.0f)<<24)|D_L22_001B0CF4;
        packet.colors[1]=color;
        packet.colors[0]=color;
        packet.colors[3]=0;
        packet.colors[2]=0;
    }
    {
        int ring=0;
        int int_j;
        do {
            for(int_j=0;
            int_j<4;
            int_j++){
                int idx=((short*)D_L22_002A33A0)[ring*4+int_j];
                if(int_j>=2)func_00282D30(packet.verts[int_j],D_L22_002A2DA0+idx*16,D_L22_001B0CE8*D_L22_001B0D00);
                else func_00282D30(packet.verts[int_j],D_L22_002A2DA0+idx*16,D_L22_001B0CE8);
            }
            packet.uv[0]=0.5f;
            packet.uv[1]=0.5f;
            packet.uv[2]=0.5f;
            packet.uv[3]=0.5f;
            packet.uv[4]=0.5f;
            packet.uv[5]=1.0f;
            packet.uv[6]=0.5f;
            packet.uv[7]=1.0f;
            func_00280B90(packet.verts,matrix[0],0);
            ring++;
        }
        while(ring<32);
    }
    func_002FC560(0x47,0x5360b);
}
