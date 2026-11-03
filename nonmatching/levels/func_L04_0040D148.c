/* 3 November 2026: complete renderer storage; still not matching.
 * Profile: -O2 -G0 -ffunction-sections -g. US and US2: 1568/1584 bytes,
 * 0/2 places each; no carried PAL identity. Four complete, aligned matrix
 * rows and union-backed packet vertices follow the matched neighboring trail's
 * storage model. Both storage changes leave the baseline instruction listing
 * unchanged. Packed alpha now shifts as unsigned 32-bit data.
 * The 0x190 frame versus retail's 0x180, vertex-address spills and loop
 * hoists remain. Reopen with a measured matrix-base/vertex-address lifetime
 * witness. Equal instructions under these storage views are not a match.
 */
/* Tier: sol-high. USA v1.01, -O2 -G0 -ffunction-sections -g.
 * Best and final check.py: 1568 bytes / 1584 expected, 0 of 2 places match
 * (Barlow and Joba). All required declarations are included below.
 *
 * The incomplete sda array restores retail's two absolute counter loads.
 * Separate cosine temporaries restore lon0/lon1/cos0 to f22/f21/f20;
 * both cosine calls precede UV arithmetic, and the Y UV stores precede
 * colors. The frame is still 0x190 instead of 0x180: GCSE PRE hoists the
 * three vertex addresses, spilling the first two at sp+0xd0/sp+0xd4 and
 * keeping the third in fp, where retail retains the matrix base instead.
 * The loop pass also hoists 1, pi/2, 2*pi and 0.5 to different scopes.
 *
 * Current-toolchain measurements: original draft 1556; adding -g 1564;
 * paired cosine evaluation and packet stores 1568. -G8/nosda,
 * -fno-rerun-loop-opt, -fno-strength-reduce and -fno-force-mem did not
 * fix the hoists. -fno-gcse removed the vertex-address spills but gave
 * 1528 bytes and a 0x170 frame; explicit matrix/position pointers gave
 * 1536 bytes and a 0x180 frame with substantially different allocation.
 * -fno-expensive-optimizations gave 1604 bytes. A do/while rewrite tied
 * the for loops; an outer goto gave 1548 bytes and worse allocation.
 * FP-first blend argument interleaving did not change the early f12
 * assignment across the alpha branch. Do not repeat these trials without
 * new input. Next useful experiment: identify a related matched renderer
 * whose source/profile preserves the matrix base and rematerializes vertex
 * addresses. No linked build was run; the src marker was restored.
 */
#include "common.h"
typedef unsigned int B1202Quad __attribute__((mode(TI)));
typedef union { B1202Quad bits; float f[4]; } RenderVector;
typedef struct { RenderVector vertex[4]; unsigned int color[4]; float uv[4][2]; unsigned long long primitive,texture,mode,flags; } B1202Packet;
extern int D_L04_001B2008[] __attribute__((sda));
extern float func_00283CE0(int),func_00283D00(float,float),func_00283198(float),func_00283180(float),func_00283C28(float),func_00283B98(float,float);
extern unsigned int func_00283D38(unsigned int,unsigned int,float);
extern void func_00283410(void *,void *),func_00282F20(void *,void *,float);
extern unsigned long long func_0027C878(int);
extern void func_002AF000(void *,float,float,float),func_00280B90(void *,void *,int);
extern void func_L04_0040DCA8(void *,float,float,float,float,int,unsigned int,int);
extern void func_L00_003F8280(void *,float,float,float,float,float,int,int);
void func_L04_0040D148(unsigned char *m,int alpha)
{
    B1202Packet packet;
    float matrix[4][4] __attribute__((aligned(16)));
    unsigned char *p=*(unsigned char **)(m+0x68);
    float wave,offset,lat0,lat1,lon0,lon1,u0,u1,v0,v1,cos0,cos1;
    unsigned int color;
    int i,j;
    wave=func_00283198(func_00283D00(func_00283CE0(D_L04_001B2008[0]),180.0f)*0.0055555557f*6.283186f);
    wave=(wave+1.0f)*0.5f;
    if(alpha==-1) color=func_00283D38(0x1fb43264,0x1f502800,wave);
    else {
        if(alpha<0) alpha=0;
        color=func_00283D38(0x1fb43264,((unsigned int)alpha<<24)|0x502800,wave);
    }
    offset=func_00283D00(func_00283CE0(D_L04_001B2008[0]),30.0f)*0.033333335f;
    func_00283410(matrix,m+0xf0);
    *(B1202Quad *)(matrix[3])=*(B1202Quad *)(m+0x10);
    func_00282F20(matrix[0],matrix[0],0.4f);
    func_00282F20(matrix[1],matrix[1],0.35f);
    func_00282F20(matrix[2],matrix[2],0.35f);
    packet.texture=func_0027C878(21);
    packet.mode=0xff9000000260ULL;
    packet.flags=0x8000000048ULL;
    packet.primitive=0;
    for(i=0;i<10;i++) {
        lat0=func_00283CE0(i)*3.141593f/func_00283CE0(10)-1.5707965f;
        lat1=func_00283CE0(i+1)*3.141593f/func_00283CE0(10)-1.5707965f;
        v0=(func_00283198(lat0)+1.0f)*0.5f;
        v1=(func_00283198(lat1)+1.0f)*0.5f;
        for(j=0;j<10;j++) {
            lon0=func_00283C28(func_00283CE0(j)*6.283186f/func_00283CE0(10));
            lon1=func_00283C28(func_00283CE0(j+1)*6.283186f/func_00283CE0(10));
            cos0=func_00283180(lon0);
            cos1=func_00283180(lon1);
            u0=offset+(cos0+1.0f)*0.5f;
            u1=offset+(cos1+1.0f)*0.5f;
            packet.uv[1][1]=v0;packet.uv[0][1]=v0;
            packet.uv[3][1]=v1;packet.uv[2][1]=v1;
            packet.color[3]=color;packet.color[2]=color;packet.color[1]=color;packet.color[0]=color;
            packet.uv[3][0]=u1;
            packet.uv[2][0]=u0;packet.uv[0][0]=u0;
            packet.uv[1][0]=u1;
            func_002AF000(packet.vertex[0].f,1.0f,lon0,lat0);
            func_002AF000(packet.vertex[1].f,1.0f,lon1,lat0);
            func_002AF000(packet.vertex[2].f,1.0f,lon0,lat1);
            func_002AF000(packet.vertex[3].f,1.0f,lon1,lat1);
            packet.vertex[0].f[3]=1.0f;packet.vertex[1].f[3]=1.0f;packet.vertex[2].f[3]=1.0f;packet.vertex[3].f[3]=1.0f;
            func_00280B90(&packet,matrix,0);
        }
    }
    *(float *)(p+0x4b4)=func_00283B98(*(float *)(p+0x4b4),0.01f);
    *(float *)(p+0x4b8)=func_00283B98(*(float *)(p+0x4b8),-0.007f);
    *(float *)(p+0x4bc)=func_00283B98(*(float *)(p+0x4bc),0.007f);
    *(float *)(p+0x4c0)=func_00283B98(*(float *)(p+0x4c0),*(float *)(p+0x30c)*0.1f);
    if(alpha==-1) {
        func_L04_0040DCA8(m+0x10,0.495f,0.35f,*(float *)(p+0x4b4),*(float *)(m+0xf4),*(int *)(p+0x648),0x0fc8c8c8,1);
        func_L04_0040DCA8(m+0x10,0.495f,0.35f,*(float *)(p+0x4b8),*(float *)(m+0xf4),*(int *)(p+0x648),0x0fc8c8c8,1);
        func_L04_0040DCA8(m+0x10,0.385f,0.35f,*(float *)(p+0x4bc),*(float *)(m+0xf4),54,0x28969600,1);
    } else {
        if(alpha<0) alpha=0;
        color=((unsigned int)alpha<<24)|0xc8c8c8;
        func_L04_0040DCA8(m+0x10,0.495f,0.35f,*(float *)(p+0x4b4),*(float *)(m+0xf4),*(int *)(p+0x648),color,1);
        func_L04_0040DCA8(m+0x10,0.495f,0.35f,*(float *)(p+0x4b8),*(float *)(m+0xf4),*(int *)(p+0x648),color,1);
        func_L04_0040DCA8(m+0x10,0.385f,0.35f,*(float *)(p+0x4bc),*(float *)(m+0xf4),54,((unsigned int)alpha<<24)|0x969600,1);
    }
    func_L00_003F8280(m+0x10,0.32f,0.5f,*(float *)(p+0x4c0),0.0f,0.0f,*(int *)(p+0x644),0);
}

