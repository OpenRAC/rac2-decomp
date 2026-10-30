/* Manual reconstruction, 2026-10-23; retained, not linked.
 * Profile: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * us: 16_snivelak: 1040 bytes, expected 968; func_L16_0041CF80: 0 of 1 places match (src/levels/16_snivelak/L16_0041CF80-qcopy.c)
 * us2: 16_snivelak: 1040 bytes, expected 968; func_L16_0041CF80: 0 of 1 places match (src/levels/16_snivelak/L16_0041CF80-qcopy.c)
 * pal: 16_snivelak: 1040 bytes, expected 968; func_L16_0041CF80: 0 of 1 places match (src/levels/16_snivelak/L16_0041CF80-qcopy.c)
 * 1040/968 bytes in all three releases. A two-pass loop produced 680 bytes; explicit retail-ordered passes produced 1040. Packet setup, UV loops and temporary-vector allocation remain different. Reopen with original render packet/source-loop evidence; no handwritten-assembly claim.
 */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; unsigned long long header[4]; } BeamPacket;
typedef struct { BeamPacket packet; Vector128 firstSide,secondSide,direction,end,scratch; } BeamWorkspace;
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern unsigned long long func_0027C878(int);
extern void func_00280B90(void *,void *,int);
extern char D_L16_001B9B00[];
extern float D_L16_001B1EA8[4][2];
void func_L16_0041CF80(char *object)
{
    BeamWorkspace local;
    float *direction=(float *)&local.direction;
    int i;
    direction[0]=func_00283180(*(float *)(object+0xf8))*25.0f;
    direction[1]=func_00283198(*(float *)(object+0xf8))*25.0f;
    direction[2]=0.0f;
    func_00282CC0(&local.end,object+0x10,&local.direction);
    func_00282CF0(&local.firstSide,object+0x10,D_L16_001B9B00);
    func_00282CF0(&local.secondSide,&local.end,D_L16_001B9B00);
    func_00282DD8(&local.firstSide,&local.firstSide,&local.direction);
    func_00282F20(&local.firstSide,&local.firstSide,0.15f);
    func_00282DD8(&local.secondSide,&local.secondSide,&local.direction);
    func_00282F20(&local.secondSide,&local.secondSide,0.15f);
    local.packet.header[1]=func_0027C878(14);
    local.packet.header[2]=0xff9000000260ULL;
    local.packet.header[3]=0x8000000048ULL;
    local.packet.header[0]=0;
    for(i=0;i<4;i++) local.packet.colors[i]=0x80243278u;
    for(i=0;i<4;i++) { local.packet.uv[i][0]=D_L16_001B1EA8[i][0]; local.packet.uv[i][1]=D_L16_001B1EA8[i][1]; }
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
    local.packet.header[1]=func_0027C878(14);
    local.packet.header[2]=0xff9000000260ULL;
    local.packet.header[3]=0x8000000048ULL;
    local.packet.header[0]=0;
    for(i=0;i<4;i++) local.packet.colors[i]=0x80808080u;
    for(i=0;i<4;i++) { local.packet.uv[i][0]=D_L16_001B1EA8[i][0]; local.packet.uv[i][1]=D_L16_001B1EA8[i][1]; }
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
