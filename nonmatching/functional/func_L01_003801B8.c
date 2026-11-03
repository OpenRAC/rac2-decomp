/* functional: high. SAME on 4 level-01 calls. The 1800-byte matching draft as it is (register allocation and scheduling differ). Unrun blocks read against retail: D_L01_001AEF20 -= 1.0 when it passes 1.0, and D_L01_001AEF24 = 0 when it passes 1.0. 0x808080 is the quad's grey RGB (0x80 = 1.0) under the computed alpha, not an address. Index tables D_L01_001AEEE0/E4/E8/EC, D_L01_00290030/0C0/108 and D_L01_001B9380 are the addresses retail forms. */
/* func_L01_003801B8: draws a level-01 moby's effect: three rotating textured quads (texture 24, scrolling UVs, palette by mode) then one expanding fading quad (texture 27). */
/* sol-high attempt, USA v1.01, default game -O2 -G8 -ffunction-sections.
 * Best check: 1820 bytes / 1800 retail, 0 of 17 places match.
 * Compile by moving this definition to a dedicated *-g8.c unit and removing
 * its INCLUDE_ASM marker from src/levels/shared/L01_002A7248.c.
 * All required declarations follow. The 144-byte packet, four transformed
 * vectors, Euler vector, 48-byte rotation matrix, four input vectors and
 * four constructor temporaries produce the retail 0x220-byte frame.
 *
 * Improvements over the earlier 1868-byte draft: sda scalar declarations
 * retain GP timer reads; SDATA gives the measured GP table address without
 * inventing the index table extent; captured indices plus unsigned byte
 * offsets yield the retail xori/addiu/movn color selection. Keeping stack
 * objects in one frame recovers the entity/state saved-register pair and
 * much of the first vertex arithmetic schedule. The alpha shift is unsigned.
 *
 * Remaining: the matrix pointer is kept in s5, index pointer 0 is spilled,
 * and the palette base is rematerialized; retail keeps index 0 in s5 and
 * the palette in s7 and spills index 3. The extra spill shifts count and
 * vector-pointer slots. Packet initialization, constructor zero/copy order,
 * FP scheduling and final color stores also differ. Grouping the four
 * temporary clears removes a second por (1824 -> 1820) but clears them
 * earlier than retail. Interleaving constructor copies gives 1824 bytes
 * with worse copy scheduling; returning a vector union gives 1844 bytes
 * and unwanted ld/sd copies. Arrays instead of individual frame fields and
 * -fno-rerun-loop-opt reproduce the 1824-byte scalar-clear draft exactly.
 * regalloc.py verified diagnostic and baseline objects were byte-identical:
 * matrix invariant refs=9/live=326, palette refs=9/live=334, index pointer 0
 * refs=9/live=376 (1824-byte draft). Reopen with a supported lifetime or
 * constructor-layout hypothesis rather than another cosmetic spelling.
 * No linked build was run; this remains a near miss, not a match.
 */
#include "common.h"
typedef float RenderVec[4] __attribute__((aligned(16)));
typedef union { RenderVec f; int q __attribute__((mode(TI))); } RenderVector;
typedef struct {
    RenderVec p[4]; u32 color[4]; float uv[8];
    u64 zero, texture, enabled, state;
} RenderPacket;
extern float D_L01_001B9380[];
extern float D_L01_001AEF20 __attribute__((sda));
extern float D_L01_001AEF24 __attribute__((sda));
extern int D_L01_001AEEE0[] SDATA(D_L01_001AEEE0);
extern int D_L01_001AEEE4[], D_L01_001AEEE8[], D_L01_001AEEEC[];
extern RenderVec D_L01_00290030[];
extern float D_L01_002900C0[][2];
extern u32 D_L01_00290108[];
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern u64 func_0027C878(int);
extern void func_00280B90(void *, int, int);
void func_L01_003801B8(char *m)
{
    struct {
        RenderPacket packet;
        RenderVec v0,v1,v2,v3,angle;
        float matrix[12] __attribute__((aligned(16)));
        RenderVector a,b,c,d,ta,tb,tc,td;
    } frame;
    char *vars = *(char **)(m + 0x68);
    int *i0;
    int *i1;
    int *i2;
    int *i3;
    int count;
    int idx0,idx1,idx2,idx3;
    u32 color;
    float t;
    frame.angle[0]=0; frame.angle[1]=0; frame.angle[2]=D_L01_001B9380[0x158/4];
    func_002833F0(frame.matrix, frame.angle);
    D_L01_001AEF20 += 0.01f;
    if (D_L01_001AEF20 > 1.0f) D_L01_001AEF20 -= 1.0f;
    frame.packet.enabled=1;
    frame.packet.state=0x4000000044ULL;
    frame.packet.zero=0;
    frame.packet.texture=func_0027C878(24);
    i0=D_L01_001AEEE0; i1=D_L01_001AEEE4; i2=D_L01_001AEEE8; i3=D_L01_001AEEEC;
    count=3;
    do {
        count--;
        func_00283098(frame.v0,D_L01_00290030[*i0],frame.matrix);
        func_00283098(frame.v1,D_L01_00290030[*i1],frame.matrix);
        func_00283098(frame.v2,D_L01_00290030[*i2],frame.matrix);
        func_00283098(frame.v3,D_L01_00290030[*i3],frame.matrix);
        frame.packet.p[0][0]=*(float *)(m+0x10)+frame.v0[0]**(float *)(vars+0x90);
        frame.packet.p[0][1]=*(float *)(m+0x14)+frame.v0[1]**(float *)(vars+0x90);
        frame.packet.p[0][2]=(*(float *)(m+0x18)+frame.v0[2])-1.0f;
        frame.packet.p[1][0]=*(float *)(m+0x10)+frame.v1[0]**(float *)(vars+0x90);
        frame.packet.p[1][1]=*(float *)(m+0x14)+frame.v1[1]**(float *)(vars+0x90);
        frame.packet.p[1][2]=(*(float *)(m+0x18)+frame.v1[2])-1.0f;
        frame.packet.p[2][0]=*(float *)(m+0x10)+frame.v2[0]**(float *)(vars+0x90);
        frame.packet.p[2][1]=*(float *)(m+0x14)+frame.v2[1]**(float *)(vars+0x90);
        frame.packet.p[2][2]=(*(float *)(m+0x18)+frame.v2[2])-1.0f;
        frame.packet.p[3][0]=*(float *)(m+0x10)+frame.v3[0]**(float *)(vars+0x90);
        frame.packet.p[3][1]=*(float *)(m+0x14)+frame.v3[1]**(float *)(vars+0x90);
        frame.packet.p[3][2]=(*(float *)(m+0x18)+frame.v3[2])-1.0f;
        idx0=*i0;
        { u32 offset=idx0*4; if (*(int *)(vars+0x94)==2) offset+=36; frame.packet.color[0]=*(u32 *)((char *)D_L01_00290108+offset); }
        idx1=*i1;
        { u32 offset=idx1*4; if (*(int *)(vars+0x94)==2) offset+=36; frame.packet.color[1]=*(u32 *)((char *)D_L01_00290108+offset); }
        idx2=*i2;
        { u32 offset=idx2*4; if (*(int *)(vars+0x94)==2) offset+=36; frame.packet.color[2]=*(u32 *)((char *)D_L01_00290108+offset); }
        idx3=*i3;
        { u32 offset=idx3*4; if (*(int *)(vars+0x94)==2) offset+=36; frame.packet.color[3]=*(u32 *)((char *)D_L01_00290108+offset); }
        frame.packet.uv[0]=D_L01_002900C0[idx0][0]; frame.packet.uv[1]=D_L01_002900C0[idx0][1]+D_L01_001AEF20;
        frame.packet.uv[2]=D_L01_002900C0[idx1][0]; frame.packet.uv[3]=D_L01_002900C0[idx1][1]+D_L01_001AEF20;
        frame.packet.uv[4]=D_L01_002900C0[idx2][0]; frame.packet.uv[5]=D_L01_002900C0[idx2][1]+D_L01_001AEF20;
        frame.packet.uv[6]=D_L01_002900C0[idx3][0]; frame.packet.uv[7]=D_L01_002900C0[idx3][1]+D_L01_001AEF20;
        i0+=4; i1+=4; i2+=4; i3+=4;
        func_00280B90(&frame.packet,0,1);
    } while (count>=0);
    frame.packet.texture=func_0027C878(27);
    D_L01_001AEF24+=0.01f;
    if (D_L01_001AEF24>1.0f) D_L01_001AEF24=0;
    t=D_L01_001AEF24;
    frame.ta.q=0;
    frame.tb.q=0;
    frame.tc.q=0;
    frame.td.q=0;
    frame.ta.f[0]=-t*(*(float *)(vars+0x90)*1.2f);
    frame.ta.f[1]=-t*(*(float *)(vars+0x90)*1.2f);
    frame.ta.f[2]=t*1.4f+1.1f;
    frame.tb.f[0]=t*(*(float *)(vars+0x90)*1.2f);
    frame.tb.f[1]=-t*(*(float *)(vars+0x90)*1.2f);
    frame.tb.f[2]=(t*1.4f+1.1f)-0.2f;
    frame.tc.f[0]=-t*(*(float *)(vars+0x90)*1.2f);
    frame.tc.f[1]=t*(*(float *)(vars+0x90)*1.2f);
    frame.tc.f[2]=t*1.4f+1.1f;
    frame.td.f[0]=t*(*(float *)(vars+0x90)*1.2f);
    frame.td.f[1]=t*(*(float *)(vars+0x90)*1.2f);
    frame.td.f[2]=(t*1.4f+1.1f)-0.2f;
    frame.a.q=frame.ta.q; frame.b.q=frame.tb.q; frame.c.q=frame.tc.q; frame.d.q=frame.td.q;
    frame.angle[0]=0;frame.angle[1]=0;frame.angle[2]=D_L01_001B9380[0x158/4];
    func_002833F0(frame.matrix,frame.angle);
    func_00283098(frame.v0,&frame.a,frame.matrix);
    func_00283098(frame.v1,&frame.b,frame.matrix);
    func_00283098(frame.v2,&frame.c,frame.matrix);
    func_00283098(frame.v3,&frame.d,frame.matrix);
    color=((u32)(int)((1.0f-D_L01_001AEF24)*128.0f)<<24)|0x808080;
    frame.packet.p[0][0]=*(float *)(m+0x10)+frame.v0[0];frame.packet.p[0][1]=*(float *)(m+0x14)+frame.v0[1];frame.packet.p[0][2]=(*(float *)(m+0x18)+frame.v0[2])-1;
    frame.packet.p[1][0]=*(float *)(m+0x10)+frame.v1[0];frame.packet.p[1][1]=*(float *)(m+0x14)+frame.v1[1];frame.packet.p[1][2]=(*(float *)(m+0x18)+frame.v1[2])-1;
    frame.packet.p[2][0]=*(float *)(m+0x10)+frame.v2[0];frame.packet.p[2][1]=*(float *)(m+0x14)+frame.v2[1];frame.packet.p[2][2]=(*(float *)(m+0x18)+frame.v2[2])-1;
    frame.packet.p[3][0]=*(float *)(m+0x10)+frame.v3[0];frame.packet.p[3][1]=*(float *)(m+0x14)+frame.v3[1];frame.packet.p[3][2]=(*(float *)(m+0x18)+frame.v3[2])-1;
    frame.packet.color[3]=color; frame.packet.color[2]=color; frame.packet.color[1]=color; frame.packet.color[0]=color;
    frame.packet.uv[0]=0;frame.packet.uv[1]=0;frame.packet.uv[2]=1;frame.packet.uv[3]=0;frame.packet.uv[4]=0;frame.packet.uv[5]=1;frame.packet.uv[6]=1;frame.packet.uv[7]=1;
    func_00280B90(&frame.packet,0,1);
}
