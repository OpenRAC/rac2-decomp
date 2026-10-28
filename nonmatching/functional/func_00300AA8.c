/* functional: medium. From the near miss (1188 vs 1200 bytes, frame size differs only): same stores and calls in order. Its externals are named by their retail addresses; the projection floats and the GIF tag retail reaches $gp-relative are D_001AD870 (gp - 0x1780) and D_001AD830 (gp - 0x17C0). */
/*
 * Retained handwritten near miss; historical evidence only.
 * No linked-image equality or complete retail semantics is established.
 * Compiler: game EE-GCC 2.9-ee-991111b (project profile).
 * Profile: -O2 -G0 -ffunction-sections (reported default game profile).
 * Reported final C / retail: 1188 / 1200 bytes; size equality is not a match.
 * us: 0/28 placements; 1188/1200 bytes.
 * us2: 0/28 placements; 1188/1200 bytes.
 * pal: 0/28 placements; 1188/1200 bytes.
 * Residual: Renderer allocation/frame mismatch; real scratchpad addresses, native header, upload rows and output packets retained.
 * Reopening condition: Reopen only after independent source, data-layout, ABI or compiler evidence specifically explains the residual above; then test that single hypothesis. Do not repeat tied source forms or flag sweeps.
 * Where listed, tools/check.py measurements predate retention; no compilation was rerun for this copy.
 */

/* Nonmatching manual reconstruction, 2026-10-23.
 * 00300AA8: 1188 bytes versus retail 1200; frame 0xB0 (retail 0xA0).
 * Profile: default -O2 -G0 -ffunction-sections.
 * All carrying US/US2/PAL checks returned zero matches and exit 1;
 * catalogue absence is recorded separately and never counted as success.
 * Complete texture upload and GIF payload construction. DMA queue qualifiers are the existing declaration from00300618-g8.c, not a new barrier. The frame/allocation differs.
 * Reopen only with new measured source/type/scheduling evidence. No artificial
 * barriers, register pins, generated decompiler C or omitted behavior were used.
 */

typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct { float x,y,z,w; } V4_F213135aa;
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

typedef unsigned long long NativeCompactU64;
typedef union {
    s32 field00[4];
    struct {
        NativeCompactU64 field00;
        short field08;
        short field0A;
        unsigned short field0C;
        unsigned short field0E;
    } compact;
} NativeCompactRow16;
typedef struct {
    char pad00[4];
    short field04;
    char pad06[2];
    short field08;
    short field0A;
    char pad0C[0x14];
    u32 field20;
} NativeSpawnHeader;
extern void func_00300748(NativeSpawnHeader *, char *, float);
extern void func_00283388(float *);
/* Partial native draw header through the packed-vertex tint field. */
typedef struct {
    short vertexCount, quadCount, boneCount, textureCount, frameCount, boneStride;
    float scale;
    void *vertices;
    u8 *quads;
    NativeCompactRow16 *textures;
    u8 *texels;
    void *bones;
    int packed;
    u32 tint;
} NativeDrawHeaderView;
typedef struct {
    u8 *source;
    unsigned short reserved04, oldPage;
    u8 *secondSource;
    u8 width, height;
    unsigned short newPage;
} TextureUpload;
typedef struct { NativeCompactU64 color, coordinate, position, reserved18; } ScratchVertex;
extern int D_001A72D0 __attribute__((sda));
extern int D_001A7350[2];
extern u8 D_001A7BB1 __attribute__((sda));
extern int D_001B15FC;
extern TextureUpload D_001B9340[64];
extern float D_001AD870[16];
extern float D_001B90F0[2], D_001B9240[2];
extern ParticleWord D_001AD830;
/* The queue retains the qualifiers of its existing renderer declaration. */
extern volatile unsigned int * volatile D_001B22A8;
extern void func_00300910(void);
extern void func_00282D30(void *, void *, float);
extern void func_00283788(void *, void *, void *);
extern void func_0029D258(void *, void *, int, int);
extern void func_0029D398(void *, void *, int, u32, int);

/* Upload referenced textures, transform the native vertices and submit each quad. */
void func_00300AA8(char *object, float x, float y, int flags, float frame, float *transform)
{
    NativeDrawHeaderView *header=(NativeDrawHeaderView *)object;
    float matrix[16] __attribute__((aligned(16)));
    NativeCompactRow16 *texture;
    TextureUpload *upload;
    ScratchVertex *scratch=(ScratchVertex *)0x70000000;
    u8 *quad;
    volatile u32 *packet;
    NativeCompactU64 *payload;
    NativeCompactU64 command;
    int index, oldCursor, page, width, height, shift, queued, vertex;
    if (!(flags >> 24)) return;
    for (index=0; index<header->textureCount; ++index) {
        texture=&header->textures[index];
        oldCursor=D_001A72D0;
        page=oldCursor+0x400;
        width=(short)texture->compact.field0C;
        height=(short)texture->compact.field0E;
        shift=width-6;
        if (shift<0) shift=0;
        D_001A72D0=page+(1U<<((width+height)&31));
        queued=D_001B15FC;
        texture->compact.field00=(NativeCompactU64)(long)(page>>8)
            | (NativeCompactU64)(1U<<(shift&31))<<14
            | (NativeCompactU64)((long)((NativeCompactU64)texture->compact.field0C<<48)>>22)
            | 0x01300000UL
            | (NativeCompactU64)((long)((NativeCompactU64)texture->compact.field0E<<48)>>18)
            | (NativeCompactU64)(long)(oldCursor>>8)<<37
            | 0x400000000ULL | 0x8000000000000000ULL;
        if (queued<64) {
            upload=&D_001B9340[queued];
            upload->oldPage=(u32)oldCursor>>8;
            upload->reserved04=0;
            upload->source=header->texels+(unsigned short)texture->compact.field0A*16;
            D_001B15FC=queued+1;
            upload->secondSource=header->texels+(unsigned short)texture->compact.field08*16;
            upload->width=texture->compact.field0C;
            upload->newPage=(u32)page>>8;
            upload->height=texture->compact.field0E;
        }
    }
    func_00300910();
    func_00282D30(transform+12,transform+12,166.66600036621094f);
    D_001AD870[0]=D_001B9240[0]/D_001B90F0[0];
    D_001AD870[9]=-(D_001B9240[1]/D_001B90F0[1]);
    if (D_001A7BB1) D_001AD870[9]*=0.7500000596046448f;
    func_00283788(matrix,D_001AD870,transform);
    matrix[13]+=(float)D_001A7350[1]+y*16.0f;
    matrix[12]+=(float)D_001A7350[0]+x*16.0f;
    /* PS2 scratchpad identity matrix and expanded skinning records. */
    func_00283388((float *)0x70001fc0);
    if (header->frameCount) func_00300748((NativeSpawnHeader *)header,(char *)0x70002000,frame);
    if (!header->packed) func_0029D258(header->vertices,matrix,header->vertexCount,flags);
    else func_0029D398(header->vertices,matrix,header->vertexCount,header->tint,flags);
    command=0x80000004cc007ffbULL;
    quad=header->quads;
    for (index=0; index<header->quadCount; ++index,quad+=4) {
        if (*(int *)quad>>8 == -1) {
            if ((short)quad[0]<header->textureCount) command=header->textures[quad[0]].compact.field00;
            else command=0x80000004cc007ffbULL;
            --index;
        } else {
            D_001B22A8[0]=0x10000008;
            D_001B22A8[1]=0;
            D_001B22A8[2]=0;
            D_001B22A8[3]=0x50000008;
            packet=D_001B22A8;
            *(ParticleWord *)(packet+4)=D_001AD830;
            D_001B22A8=packet+8;
            *(NativeCompactU64 *)(packet+8)=command;
            *(NativeCompactU64 *)(packet+10)=0x5c;
            payload=(NativeCompactU64 *)(packet+12);
            vertex=quad[0];
            payload[0]=scratch[vertex].color; payload[1]=scratch[vertex].coordinate; payload[2]=scratch[vertex].position;
            vertex=quad[1];
            payload[3]=scratch[vertex].color; payload[4]=scratch[vertex].coordinate; payload[5]=scratch[vertex].position;
            vertex=quad[3];
            payload[6]=scratch[vertex].color; payload[7]=scratch[vertex].coordinate; payload[8]=scratch[vertex].position;
            vertex=quad[2];
            payload[9]=scratch[vertex].color; payload[10]=scratch[vertex].coordinate; payload[11]=scratch[vertex].position;
            D_001B22A8+=0x1c;
        }
    }
}
