/* 30 October 2026 retained reconstruction; game compiler,
 * -O2 -G0 -ffunction-sections. USA v1.01, v2.00 and PAL: 960/968 bytes,
 * 0/1 placements each. The complete 144-byte packet and five 16-byte vectors
 * are retained. Packet fields use EE 64-bit long; pointers remain 32 bits.
 * Straight color stores, independent UV-column streams, a scalar direction
 * view and ordinary TI stack copies replace the old overlong lowering.
 * Retail spills the UV destination pointer and uses frame 0x150; this source
 * keeps frame 0x140. Setup order and allocation still differ. A texture local
 * and separate pass counters tie the 960-byte result. Reopen with the packet
 * cursor's true source lifetime, preserving all packet/header fields.
 * Historical 1040-byte qcopy-profile form: alternatives/func_L16_0041CF80-form-01.c.
 */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef union { Vector128 q; struct { float x,y,z,w; } v; } BeamVector;
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; long f70, f78, f80, flags; } BeamPacket;
typedef struct { BeamPacket packet; Vector128 firstSide,secondSide; BeamVector direction; Vector128 end,scratch; } BeamWorkspace;
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern unsigned long long func_0027C878(int);
extern void func_00280B90(void *,void *,int);
extern char D_L16_001B9B00[];
extern float D_L16_001B1EA8[] MACRO_ADDR;
extern float D_L16_001B1EAC[] MACRO_ADDR;
void func_L16_0041CF80(char *object)
{
    BeamWorkspace local;
    int i;
    float *u, *v, *outU, *outV;
    local.direction.v.x=func_00283180(*(float *)(object+0xf8))*25.0f;
    local.direction.v.y=func_00283198(*(float *)(object+0xf8))*25.0f;
    local.direction.v.z=0.0f;
    func_00282CC0(&local.end,object+0x10,&local.direction);
    func_00282CF0(&local.firstSide,object+0x10,D_L16_001B9B00);
    func_00282CF0(&local.secondSide,&local.end,D_L16_001B9B00);
    func_00282DD8(&local.firstSide,&local.firstSide,&local.direction);
    func_00282F20(&local.firstSide,&local.firstSide,0.15f);
    func_00282DD8(&local.secondSide,&local.secondSide,&local.direction);
    func_00282F20(&local.secondSide,&local.secondSide,0.15f);
    local.packet.f78=func_0027C878(14);
    local.packet.f80=0xff9000000260ULL;
    local.packet.flags=0x8000000048ULL;
    local.packet.f70=0;
    local.packet.colors[0]=0x80243278u;
    local.packet.colors[1]=0x80243278u;
    local.packet.colors[2]=0x80243278u;
    local.packet.colors[3]=0x80243278u;
    u=D_L16_001B1EA8; v=D_L16_001B1EAC;
    outU=&local.packet.uv[0][0]; outV=&local.packet.uv[0][1];
    for(i=3;i>=0;i--) { *outU=*u; *outV=*v; u+=2; v+=2; outU+=2; outV+=2; }
    func_00282CF0(&local.scratch,object+0x10,&local.firstSide);
    *(Vector128 *)&local.packet.vertices[0]=*(Vector128 *)&local.scratch;
    func_00282CC0(&local.scratch,object+0x10,&local.firstSide);
    *(Vector128 *)&local.packet.vertices[1]=*(Vector128 *)&local.scratch;
    func_00282CF0(&local.scratch,&local.end,&local.secondSide);
    *(Vector128 *)&local.packet.vertices[2]=*(Vector128 *)&local.scratch;
    func_00282CC0(&local.scratch,&local.end,&local.secondSide);
    *(Vector128 *)&local.packet.vertices[3]=*(Vector128 *)&local.scratch;
    func_00280B90(&local.packet,0,0);
    func_00282CF0(&local.firstSide,object+0x10,D_L16_001B9B00);
    func_00282CF0(&local.secondSide,&local.end,D_L16_001B9B00);
    func_00282DD8(&local.firstSide,&local.firstSide,&local.direction);
    func_00282F20(&local.firstSide,&local.firstSide,0.05f);
    func_00282DD8(&local.secondSide,&local.secondSide,&local.direction);
    func_00282F20(&local.secondSide,&local.secondSide,0.05f);
    local.packet.f78=func_0027C878(14);
    local.packet.f80=0xff9000000260ULL;
    local.packet.flags=0x8000000048ULL;
    local.packet.f70=0;
    local.packet.colors[0]=0x80808080u;
    local.packet.colors[1]=0x80808080u;
    local.packet.colors[2]=0x80808080u;
    local.packet.colors[3]=0x80808080u;
    u=D_L16_001B1EA8; v=D_L16_001B1EAC;
    outU=&local.packet.uv[0][0]; outV=&local.packet.uv[0][1];
    for(i=3;i>=0;i--) { *outU=*u; *outV=*v; u+=2; v+=2; outU+=2; outV+=2; }
    func_00282CF0(&local.scratch,object+0x10,&local.firstSide);
    *(Vector128 *)&local.packet.vertices[0]=*(Vector128 *)&local.scratch;
    func_00282CC0(&local.scratch,object+0x10,&local.firstSide);
    *(Vector128 *)&local.packet.vertices[1]=*(Vector128 *)&local.scratch;
    func_00282CF0(&local.scratch,&local.end,&local.secondSide);
    *(Vector128 *)&local.packet.vertices[2]=*(Vector128 *)&local.scratch;
    func_00282CC0(&local.scratch,&local.end,&local.secondSide);
    *(Vector128 *)&local.packet.vertices[3]=*(Vector128 *)&local.scratch;
    func_00280B90(&local.packet,0,0);
}
