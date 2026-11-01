/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Claude Opus 5.5 xhigh, v2027, 2026-11-01: 1756/1740 bytes, 0/1 USA places.
 * Profile: -O2 -G8 -ffunction-sections, separate unit L15_00437B68-g8.c; the
 * older -fno-strength-reduce is no longer needed. All declarations follow.
 * Bytes are further from 1740 than the 1728 draft this replaces, but the
 * structure is closer: frame 0x150 and slots, height loops, i=s2, the second
 * saved induction in fp, a spilled CORNER (not face), and the reversed L2/L3
 * corner loops all come out of the compiler as in retail.
 * Why this form:
 * - for(i=0;i<121;i++) height: check_dbra_loop gives retail's 0x78/bgez, and
 *   LCM ISO blocks PRE's i+1 hoist after the second loop only, as in retail.
 * - loop.c: threshold 61 with calls, -3 per move, D scanned first, so 6 is
 *   tested at 58. Moved in pass 1 => corner*6 is a pass-1 giv => reversal.
 *   Pass-1 counts L1/L2=L3/L4: this form 62/58/68; all cursors 59/55/65; all
 *   natural 65/61/71 (L2/L3 stop reversing). Retail reverses L2/L3 only.
 * - natural packet.uv[corner][n] stores are mem/s, so the mem/f D_L15_001B1878
 *   load schedules above them as in retail; float* cursor stores block it.
 * Remaining:
 * 1. Corner is t1, retail t0. In L4, -1 (r546) stays local and takes a2, so the
 *    D_L15_001B1878 load takes t0. Retail's -1 looks hoisted and rematerialised
 *    by reload. L4 rerun: 3 moves => threshold 52, our count 53, one too many;
 *    the mask must then fail at 49, so retail's rerun count is 50-52.
 * 2. s4..s7 are u,v,vertex,colors; retail is vertex,u,v,colors. Retail's init
 *    order colors,v,u,vertex is the reverse-body order of reduced givs, which
 *    suggests all four streams are natural; that needs 3 fewer L2 pass-1 insns.
 * 3. Retail's first mask store at 0xD4 is deleted (delete_output_reload) and
 *    ours is not: an extra sw and nop. Probably follows from allocation.
 * 4. Reload registers after the call, and PRE order of the sp+0x40/50/54 copies
 *    (retail stores 0xDC,0xE0,0xD8; ours 0xD8 first). Recheck after 1 and 2.
 * Tried: index-first (corner+D_L15_002B74E0[i])->field folds i*24+D into madd,
 * 1668 bytes. A row pointer outside the inner loop would lose retail's separate
 * D and D+2/D+4 bases. No insn is redundant in the L4 rerun body; each short
 * read is 3 insns at loop time (extendhisi2 force_not_mem), local or not.
 * Untested: a different declaration of the index table, which could change
 * the address RTL and so the count. No linked build was run: no C match.
 */

#include "common.h"

#include "include_asm.h"
typedef struct { float x,y,z,w; } GornVec __attribute__((aligned(16)));
typedef struct { GornVec vertex[4]; unsigned int color[4]; float uv[4][2]; long long tag[4]; GornVec matrix[4]; } GornPacket;
typedef struct { short position,uv,color; } GornCorner;
extern GornVec D_L15_002B6D50[];
extern GornCorner D_L15_002B74E0[][4];
extern float D_L15_002B7E40[][2];
extern unsigned int D_L15_002B8688[];
extern int D_L15_001B1870 __attribute__((sda));
extern int D_L15_001B1878 __attribute__((sda));
extern long long func_0027C878(int);
extern void func_00282D30(void *,const void *,float);
extern void func_00280B90(void *,void *,int);
void func_L15_00437B68(char *object,int preview)
{
    GornPacket packet;
    char *state;
    int i,corner,alpha;
    int position_index,uv_index,color_index;
    unsigned int color;
    state=*(char **)(object+0x68);
    packet.tag[1]=func_0027C878(72);
    packet.tag[2]=0xFF9000000260LL;
    packet.tag[3]=0x8000000044LL;
    packet.tag[0]=0;
    qcopy(&packet.matrix[0], (object+0xC0));
    qcopy(&packet.matrix[1], (object+0xD0));
    qcopy(&packet.matrix[2], (object+0xE0));
    packet.matrix[3].x=*(float *)(object+0x10);
    packet.matrix[3].y=*(float *)(object+0x14);
    packet.matrix[3].z=*(float *)(object+0x18);
    packet.matrix[3].w=1.0f;
    packet.color[0]=packet.color[1]=packet.color[2]=packet.color[3]=0x80808080;
    *(float *)(state+4)-=0.00045f;
    if (*(float *)(state+4)<=-8.0f) *(float *)(state+4)+=8.0f;
    if (preview) {
for(i=0;i<121;i++) D_L15_002B6D50[i].z=300.0f;
    for(i=0;i<100;i++) {
        unsigned int *colors=packet.color;GornVec *vertex=packet.vertex;
        for(corner=0;corner<4;corner++) {
            position_index=D_L15_002B74E0[i][corner].position; uv_index=D_L15_002B74E0[i][corner].uv; color_index=D_L15_002B74E0[i][corner].color;
            func_00282D30(vertex,&D_L15_002B6D50[position_index],1.0f);
            packet.uv[corner][0]=D_L15_002B7E40[uv_index][0]+*(float *)(state+4);
            packet.uv[corner][1]=D_L15_002B7E40[uv_index][1];
            *colors=(D_L15_002B8688[color_index]&0xFFFFFF)|0x7F000000;
            vertex++;colors++;
        }
        func_00280B90(&packet,0,0);
    }
        return;
    }
for(i=0;i<121;i++) D_L15_002B6D50[i].z=800.0f;
    for(i=0;i<100;i++) {
        unsigned int *colors=packet.color;GornVec *vertex=packet.vertex;
        for(corner=0;corner<4;corner++) {
            position_index=D_L15_002B74E0[i][corner].position; uv_index=D_L15_002B74E0[i][corner].uv; color_index=D_L15_002B74E0[i][corner].color;
            func_00282D30(vertex,&D_L15_002B6D50[position_index],1.0f);
            packet.uv[corner][0]=D_L15_002B7E40[uv_index][0]+*(float *)(state+4);
            packet.uv[corner][1]=D_L15_002B7E40[uv_index][1];
            *colors=D_L15_002B8688[color_index];
            vertex++;colors++;
        }
        func_00280B90(&packet,0,0);
    }
for(i=0;i<121;i++) D_L15_002B6D50[i].z=1200.0f;
    for(i=0;i<100;i++) {
        unsigned int *colors=packet.color;GornVec *vertex=packet.vertex;
        for(corner=0;corner<4;corner++) {
            position_index=D_L15_002B74E0[i][corner].position; uv_index=D_L15_002B74E0[i][corner].uv; color_index=D_L15_002B74E0[i][corner].color;
            func_00282D30(vertex,&D_L15_002B6D50[position_index],1.0f);
            packet.uv[corner][0]=D_L15_002B7E40[uv_index][0]+*(float *)(state+4);
            packet.uv[corner][1]=D_L15_002B7E40[uv_index][1];
            *colors=D_L15_002B8688[color_index];
            vertex++;colors++;
        }
        func_00280B90(&packet,0,0);
    }
    if (D_L15_001B1870) {
for(i=0;i<121;i++) D_L15_002B6D50[i].z=405.0f;
    for(i=0;i<100;i++) {
        unsigned int *colors=packet.color;GornVec *vertex=packet.vertex;
        for(corner=0;corner<4;corner++) {
            position_index=D_L15_002B74E0[i][corner].position; uv_index=D_L15_002B74E0[i][corner].uv; color_index=D_L15_002B74E0[i][corner].color;
            func_00282D30(vertex,&D_L15_002B6D50[position_index],1.0f);
            packet.uv[corner][0]=D_L15_002B7E40[uv_index][0]+*(float *)(state+4);
            packet.uv[corner][1]=D_L15_002B7E40[uv_index][1];
            color=D_L15_002B8688[color_index];
    alpha=((int)color>>24)-D_L15_001B1878;
    if (alpha<0) alpha=0;
    *colors=(color&0xFFFFFF)|((unsigned int)alpha<<24);
            vertex++;colors++;
        }
        func_00280B90(&packet,0,0);
    }
    }
}
