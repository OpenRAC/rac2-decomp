#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 vertices[4]; unsigned int colors[4]; float uv[4][2]; unsigned long long header[4]; } BeamPacket;
typedef struct { BeamPacket packet; Vector128 firstSide,secondSide,direction,end,scratch; } BeamWorkspace;
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern unsigned long long func_0027C878(int);
extern void func_00280B90(void *,void *,int);
extern char D_L19_001B9A40[];
extern float D_L19_001B1DE8[] __attribute__((sda));
extern float D_L19_001B1DEC[] __attribute__((sda));

/* Draws the object's 25-unit beam along its heading: a wide tinted quad, then a narrow white core. */
void func_L19_00420B48(char *object)
{
    BeamWorkspace local;
    int i, j;
    func_00282F20(&local.direction,object+0xe0,*(float *)(*(char **)(object+0x68)+0xc));
    func_00282CC0(&local.end,object+0x10,&local.direction);
    func_00282CF0(&local.firstSide,object+0x10,D_L19_001B9A40);
    func_00282CF0(&local.secondSide,&local.end,D_L19_001B9A40);
    func_00282DD8(&local.firstSide,&local.firstSide,&local.direction);
    func_00282F20(&local.firstSide,&local.firstSide,0.15f);
    func_00282DD8(&local.secondSide,&local.secondSide,&local.direction);
    func_00282F20(&local.secondSide,&local.secondSide,0.15f);
    local.packet.header[1]=func_0027C878(14);
    local.packet.header[2]=0xff9000000260ULL;
    local.packet.header[3]=0x8000000048ULL;
    local.packet.header[0]=0;
    local.packet.colors[0] = local.packet.colors[1] = local.packet.colors[2] = local.packet.colors[3] = 0x80243278u;
    for (i = 0; i < 4; i++) {
        local.packet.uv[i][0] = D_L19_001B1DE8[i * 2];
        local.packet.uv[i][1] = D_L19_001B1DEC[i * 2];
    }
    func_00282CF0(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[0]=local.scratch;
    func_00282CC0(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[1]=local.scratch;
    func_00282CF0(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[2]=local.scratch;
    func_00282CC0(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[3]=local.scratch;
    func_00280B90(&local.packet,0,0);
    func_00282CF0(&local.firstSide,object+0x10,D_L19_001B9A40);
    func_00282CF0(&local.secondSide,&local.end,D_L19_001B9A40);
    func_00282DD8(&local.firstSide,&local.firstSide,&local.direction);
    func_00282F20(&local.firstSide,&local.firstSide,0.05f);
    func_00282DD8(&local.secondSide,&local.secondSide,&local.direction);
    func_00282F20(&local.secondSide,&local.secondSide,0.05f);
    local.packet.header[1]=func_0027C878(14);
    local.packet.header[2]=0xff9000000260ULL;
    local.packet.header[3]=0x8000000048ULL;
    local.packet.header[0]=0;
    local.packet.colors[0] = local.packet.colors[1] = local.packet.colors[2] = local.packet.colors[3] = 0x80808080u;
    for (j = 0; j < 4; j++) {
        local.packet.uv[j][0] = D_L19_001B1DE8[j * 2];
        local.packet.uv[j][1] = D_L19_001B1DEC[j * 2];
    }
    func_00282CF0(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[0]=local.scratch;
    func_00282CC0(&local.scratch,object+0x10,&local.firstSide);
    local.packet.vertices[1]=local.scratch;
    func_00282CF0(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[2]=local.scratch;
    func_00282CC0(&local.scratch,&local.end,&local.secondSide);
    local.packet.vertices[3]=local.scratch;
    func_00280B90(&local.packet,0,0);
}
