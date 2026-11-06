#include "common.h"

typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
typedef struct { float x,y,z,w; } V4_F213135aa;
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
extern int D_001A72D0;
extern int D_001A7350[2];
extern u8 D_001A7BB1;
extern int ref_00300AA8_00;
extern TextureUpload ref_00300AA8_01[64];
extern float nativeProjection[16] SDATA(ref_00300AA8_02);
extern float ref_00300AA8_02[16] __attribute__((sda));
typedef struct { char pad[0xB0]; float size[2]; char padB8[0x148]; float scale[2]; } NativeDrawView;
extern NativeDrawView ref_00300AA8_03;
extern ParticleWord ref_00300AA8_06 SDATA(ref_00300AA8_06);
/* The DMA packet cursor: the DMA controller reads the packets the cursor advances over,
   so the queue is volatile. */
extern volatile unsigned int * volatile D_001B22A8;
extern volatile unsigned int *nativeQueue SDATA(D_001B22A8);
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
    ScratchVertex *scratch;
    u8 *quad;
    /* Packet words the DMA controller reads once the chain is kicked. */
    volatile u32 *packet, *tagPacket;
    volatile NativeCompactU64 *payload;
    NativeCompactU64 *source;
    NativeCompactU64 command;
    int index, quadIndex, oldCursor, page, width, height, queued, vertex;
    unsigned int shift;
    if (!(flags >> 24)) return;
    for (index=0; index<header->textureCount; ++index) {
        NativeCompactU64 tex0_word;
        long width_bits, palette_bits;
        int one=1; /* set here, ahead of the clamp: both shifts use it */
        texture=&header->textures[index];
        width=(short)texture->compact.field0C;
        shift=width-6;
        oldCursor=D_001A72D0>>8;
        page=D_001A72D0+0x400;
        height=page>>8;
        queued=ref_00300AA8_00;
        if ((int)shift<0) shift=0;
        shift=one << shift;
        tex0_word=(NativeCompactU64)(int)shift<<14;
        tex0_word|=height;
        width_bits=((long)((NativeCompactU64)texture->compact.field0C<<48)>>22)|0x01300000;
        tex0_word|=width_bits;
        width+=(short)texture->compact.field0E;
        tex0_word|=(long)((NativeCompactU64)texture->compact.field0E<<48)>>18;
        palette_bits=(NativeCompactU64)oldCursor<<37;
        palette_bits|=(NativeCompactU64)1<<34;
        tex0_word|=palette_bits;
        tex0_word|=(NativeCompactU64)1<<63;
        /* width stays one register; the copy keeps page as the first addend. */
        width=one<<width;
        shift=width;
        width=page+shift;
        D_001A72D0=width;
        texture->compact.field00=tex0_word;
        if (queued<64) {
            upload=&ref_00300AA8_01[queued];
            upload->source=header->texels+(unsigned short)texture->compact.field0A*16;
            upload->oldPage=oldCursor;
            upload->reserved04=0;
            /* Written through the row offset, as the RAC1 upload queue does. */
            *(u8 **)((u8 *)ref_00300AA8_01+queued*16+8)=header->texels+(unsigned short)texture->compact.field08*16;
            upload->width=texture->compact.field0C;
            upload->height=texture->compact.field0E;
            upload->newPage=height;
            ref_00300AA8_00=queued+1;
        }
    }
    func_00300910();
    func_00282D30(transform+12,transform+12,166.66600036621094f);
    nativeProjection[0]=ref_00300AA8_03.scale[0]/ref_00300AA8_03.size[0];
    ref_00300AA8_02[9]=-(ref_00300AA8_03.scale[1]/ref_00300AA8_03.size[1]);
    if (D_001A7BB1) ref_00300AA8_02[9]*=0.7500000596046448f;
    func_00283788(matrix,nativeProjection,transform);
    matrix[12]+=(float)D_001A7350[0]+x*16.0f;
    matrix[13]+=(float)D_001A7350[1]+y*16.0f;
    /* PS2 scratchpad identity matrix and expanded skinning records. */
    func_00283388((float *)0x70001fc0);
    if (header->frameCount) func_00300748((NativeSpawnHeader *)header,(char *)0x70002000,frame);
    if (!header->packed) func_0029D258(header->vertices,matrix,header->vertexCount,flags);
    else func_0029D398(header->vertices,matrix,header->vertexCount,header->tint,flags);
    scratch=(ScratchVertex *)0x70000000;
    command=0x80000004cc007ffbULL;
    quad=header->quads;
    for (quadIndex=0; quadIndex<header->quadCount; ++quadIndex,quad+=4) {
        if (*(int *)quad>>8 == -1) {
            if ((short)quad[0]<header->textureCount) command=header->textures[quad[0]].compact.field00;
            else command=0x80000004cc007ffbULL;
            --quadIndex;
        } else {
            nativeQueue[0]=0x10000008;
            D_001B22A8[1]=0;
            D_001B22A8[2]=0;
            D_001B22A8[3]=0x50000008;
            tagPacket=D_001B22A8+4;
            D_001B22A8=tagPacket;
            qcopy((void *)tagPacket,&ref_00300AA8_06);
            packet=tagPacket+4;
            D_001B22A8=packet;
            payload=(volatile NativeCompactU64 *)packet;
            payload[0]=command;
            payload[1]=0x5c;
            vertex=quad[0];
            source=&scratch[vertex].color;
            payload[2]=*source++; payload[3]=source[0]; payload[4]=source[1];
            vertex=quad[1];
            source=&scratch[vertex].color;
            payload[5]=*source++; payload[6]=source[0]; payload[7]=source[1];
            vertex=quad[3];
            source=&scratch[vertex].color;
            payload[8]=*source++; payload[9]=source[0]; payload[10]=source[1];
            vertex=quad[2];
            source=&scratch[vertex].color;
            payload[11]=*source++; payload[12]=source[0]; payload[13]=source[1];
            D_001B22A8+=0x1c;
        }
    }
}
