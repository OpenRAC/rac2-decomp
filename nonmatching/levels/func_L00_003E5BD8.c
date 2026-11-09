/* 9 November 2026 (o150, S/pseudo sweep): bucket hash (14029+R+K)%S checked for every odd S 11..2999 and object/index pseudos 80..399: the six stack addresses alone fit only S=111,217,235,239,371,381,403,415,455,... (all but 111 need max_cuid >= 434, i.e. ~+190 insns); S=111 needs object+192's base pseudo 98..110 and index 98..126. Confirmed with a forced-S=111 cc1: object read through a function-scope copy declared after 13+ other register pseudos, and index declared after it, gives 0 diff lines (a full match), so S=111 plus that pseudo layout is the whole fix. New code-neutral reductions (masked diff 0): `short *e = (short *)((char *)D_L00_002983B0 + (index*16 + i*4));` with e[0]/e[1] is -2 (every other entry-pointer spelling, e.g. D[index][i], swaps the addu operands); with the gs[3] local, 242 -> 237. Still 14..17 insns short; `float one`, colour pointer, colour temporary, vertex pointer, short index locals: code changes or no reduction. No check.py run. */
/* 9 November 2026 (o143, set-once constant lever): not applied. Each set-once constant local read in a loop adds one insn at gcse, but this body needs S=111 (about 20 fewer insns, notes below); no larger S reaches 0 (forced 11..401). */
/* 9 November 2026 (Codex, structured views and inline helpers): 249 new C
 * variants compiled in the existing container with -O2 -G8 -ffunction-sections
 * -ffast-math. All 122 object/data/table/workspace variants produce complete
 * objects identical to this draft: member views, data unions and aggregate
 * stack workspaces do not change PRE's 121 buckets. Of 127 combinations of
 * seven inline operation groups, 15 retain 1108 bytes and the same 19 offsets;
 * eight retain 1108 bytes with 26 differences; the others change size. Some
 * helpers reduce the table to 119 or 117 buckets, but change the final code.
 * A no-dump compile produces the same complete object as -dG. Placement.derive
 * rejects all 81 US/US2/PAL places at +0x4c, each with 19 nonrelocated word
 * differences. No linked build: the source remains nonmatching. These views
 * and helper boundaries do not supply the needed pre-GCSE reduction; investigate
 * another source operation shape rather than more layout-only combinations.
 */
/* 9 November 2026 (o81, PRE slot solve): fresh -dG dump: 121 buckets, max_cuid 242 (insns at gcse), spilled PRE regs in bucket order sp+16(10) object+192(27) sp+48(42) sp+64(58) sp+80(74) sp+84(78) index+1(79) sp+208(81). Retail order object+192, sp+80, sp+84, sp+208, index+1, sp+16, sp+48, sp+64: brute force over S 11..599 and object/index pseudos 80..260 finds only S=111 (max_cuid 220..223, need 19..22 fewer insns) with the object+192 base pseudo >= 98 (ours 84); then 217/235/239. Not a small change; no C tried. */
/* 9 November 2026 (Sonnet round, s48): re-measured 1108/1108, 0 masked / 19 unmasked rows (stack slots only). Switch singles and pairs (same list): only -fno-gcse and -fno-rerun-loop-opt change it, both far worse (916/208). do-while(0) groups of 1-3 statements (108 variants): none better. Set-once `float one = 1.0f` local (retail keeps 1.0f in $f22) used for matrix[0][0], matrix[1][1] and the two 1.0f args: 36-47 rows, worse; only the two args: 36. */
/* 8 November 2026 (Sonnet round, lesson 49 + declaration sweep): re-measured 1108/1108, 20 differing words, all stack offsets. Inlining vertex_index/uv_index (1124 bytes, 217 words) or data (1100 bytes) breaks the code, so those locals are real. `char *object = object_` copy (before q or after the arrays), a block around the loop: 20 words (tie). Every single declaration move among matrix/normal/center/edge1/edge2/index/data: no gain. Permuter (-j2, 1500 s): only junk (undefined new_var/inline_fn). */
/* 8 November 2026 (gcse table size): the five EE cc1 builds here (ours, 991111a, 991111-01, 991111b-r4, SN 2.95.2 273a) give the same PRE table size on this source, so the sizing rule is shared. Forced sizes 11..401: no size gives 0 (best 133: 8 diffs, 111: 15; ours 121: 20), so the table size alone does not close it. */
/* 7 November 2026 (opus, DrLegitamate): the spill slots are fully explained.
 * The eight spilled loop invariants are sp+16, sp+48, sp+64, sp+80, sp+84, sp+208, object+192
 * and index+1. Their slots follow gcse's expression-table bucket order, with bucket =
 * (14001 + regno + constant) % n and n = max_cuid / 2 | 1 (this draft: max_cuid 242, n = 121).
 * Retail's order is object+192, sp+80, sp+84, sp+208, index+1, sp+16, sp+48, sp+64. Among
 * the stack addresses, near this size only n = 111 gives that order (the next counts are
 * 217, 235, 239). A scratch cc1 forcing 111 buckets on this draft, with `object` read through
 * a local copy (`char *object = object_;`, any position among the locals after q) and 15 or
 * more extra function-scope pseudos before `index`, gives every stack offset of retail. The
 * rest of the output is identical to this draft, so that is a full match.
 * Natural source therefore has about 20 fewer insns at gcse (max_cuid 220..223) and still
 * the same final code. Not found: an exhaustive search of 65,536 combinations of 16
 * equivalent spellings (row, entry, vertex and uv pointers, ternary colour, colour and alpha
 * temporaries, loop forms, hoisted object+192, typed object copy, late declarations) keeps
 * the code only at 121 buckets; every spelling that changes max_cuid changes the code.
 * Every single flag and every pair of the project's flags: no change.
 * One lean spelling found: building gs[3] in a local and storing it once keeps the code
 * identical and lowers max_cuid from 242 to 239 (gs[1] through a local, data read as
 * ((float *)data)[4], late declarations, vertex pointers and a hoisted object+192 are
 * code-neutral but do not lower it). About 17 more such insns are still to be found; a
 * 100,000-sample random search over 21 spellings found no other code-preserving reduction.
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 1108/1108 bytes, 0/27 placements; first difference 0x4c.
 * Profile: -O2 -G8 -ffunction-sections -ffast-math.
 * Stored-address getters follow their matched signed32 return contracts, with explicit pointer
 * casts at the actual uses. Physical EE widths and argument-bank order are preserved; this
 * repair leaves the retained allocation/scheduling residual unchanged.
 * Earlier measurements below are historical where superseded by this note.
 */
/* GPT-6.1 Sol high, v0825, 2026-10-29: USA v1.01, 1108/1108
 * bytes, 0/27 placements. Profile: -O2 -G8 -ffunction-sections -ffast-math.
 * Exactly 19 stack-slot offsets differ; all other instructions match apart
 * from relocations. All required declarations follow.
 * Explicit compound updates to q.gs[3] reproduce retail's left-associated
 * register packing without the obsolete -frac2-no-reduce-tree-depth flag.
 * The single expression instead rebalances the OR tree and changes setup.
 * Retail spills object+0xC0/center/index+1/colors at 0x114/0x120/0x124/0x130;
 * here they are 0x118/0x130/0x12C/0x120. A local packing accumulator gives
 * the same final bytes; a nested late index and object aliases still leave
 * 19 offset differences. Current staged profiles enter GCSE with a 121-
 * bucket expression table; the old draft's recorded 111-bucket model does
 * not apply directly. No linked build. Next: recover natural source that
 * changes PRE address ordering while preserving the register-packing tree.
 */
#include "common.h"
typedef float RenderVec5BD8[4] __attribute__((aligned(16)));
typedef struct {
    RenderVec5BD8 vertices[4];
    int colors[4];
    float uv[4][2];
    unsigned long gs[4];
} Quad5BD8;
extern int D_L00_001B0600 __attribute__((sda));
extern int D_L00_001B0604 __attribute__((sda));
extern int D_L00_001B0608 __attribute__((sda));
extern int D_L00_001B060C __attribute__((sda));
extern int D_L00_001B0610 __attribute__((sda));
extern int D_L00_001B0614 __attribute__((sda));
extern int D_L00_001B0618 __attribute__((sda));
extern float D_L00_001B061C __attribute__((sda));
extern float D_L00_001B05D4 __attribute__((sda));
extern float D_L00_001B05D8 __attribute__((sda));
extern char *D_L00_001B2B50 __attribute__((sda));
extern int *D_L00_001B2B58 MACRO_ADDR;
extern short D_L00_002983B0[][4][2];
extern RenderVec5BD8 D_L00_002976D0[];
extern float D_L00_00299130[][2];
extern RenderVec5BD8 D_L00_001B8DC0;
extern unsigned long func_0027C878(int);
extern void func_00282C88(void *);
extern void func_00282D30(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern float func_00282E20(void *);
extern float func_002A7798(float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern char * func_L00_003E6778(char *,int,float,float,void *);
extern void func_00280B90(void *,int,int);
void func_L00_003E5BD8(char *object)
{
    Quad5BD8 q;
    RenderVec5BD8 matrix[3];
    RenderVec5BD8 normal, center, edge1, edge2;
    int index;
    char *data = *(char **)(object + 0x68);
    q.gs[1] = func_0027C878(D_L00_001B0614);
    q.gs[3] = (unsigned long)D_L00_001B0600 | ((unsigned long)D_L00_001B0604 << 2);
    q.gs[3] |= (unsigned long)D_L00_001B0608 << 4;
    q.gs[3] |= (unsigned long)D_L00_001B060C << 6;
    q.gs[3] |= (unsigned long)D_L00_001B0610 << 32;
    q.gs[2] = 0xFF9000000260UL;
    q.gs[0] = 0;
    q.colors[0] = q.colors[1] = q.colors[2] = q.colors[3] = D_L00_001B0618 + (*(int *)(data+28) << 24);
    func_00282C88(matrix[0]);
    func_00282C88(matrix[1]);
    func_00282C88(matrix[2]);
    matrix[0][0] = 1.0f;
    matrix[1][1] = 1.0f;
    matrix[2][2] = *(float *)(data+16)*0.865f;
    index=0;
    do {
        int i;
        for (i=0;i<4;i++) {
            int vertex_index = D_L00_002983B0[index][i][0];
            int uv_index = D_L00_002983B0[index][i][1];
            func_00282D30(q.vertices[i],D_L00_002976D0[vertex_index],D_L00_001B061C);
            q.uv[i][0] = D_L00_00299130[uv_index][0] + D_L00_001B05D4;
            q.uv[i][1] = D_L00_00299130[uv_index][1] + D_L00_001B05D8;
            if (D_L00_002976D0[vertex_index][2] == -0.001052f)
                q.colors[i] = D_L00_001B0618;
            else
                q.colors[i] = D_L00_001B0618 | (*(int *)(data+28)<<24);
        }
        func_00283098(q.vertices[0],q.vertices[0],matrix);
        func_00283098(q.vertices[1],q.vertices[1],matrix);
        func_00283098(q.vertices[2],q.vertices[2],matrix);
        func_00283098(q.vertices[3],q.vertices[3],matrix);
        func_00282C88(center);
        for(i=0;i<4;i++) {
            q.uv[i][0] -= q.vertices[i][2]*0.125f;
            q.vertices[i][0] *= func_002A7798(q.vertices[i][2]) + 2.0f;
            q.vertices[i][1] *= func_002A7798(q.vertices[i][2]) + 2.0f;
            func_00283098(q.vertices[i],q.vertices[i],object+192);
            q.vertices[i][0] += *(float *)(object+16);
            q.vertices[i][1] += *(float *)(object+20);
            q.vertices[i][2] += *(float *)(object+24);
            func_00282CC0(center,center,q.vertices[i]);
        }
        func_00282D30(center,center,0.25f);
        func_00282CF0(normal,center,D_L00_001B8DC0);
        func_00282F20(normal,normal,1.0f);
        func_00282CF0(edge1,q.vertices[2],q.vertices[0]);
        func_00282CF0(edge2,q.vertices[2],q.vertices[1]);
        func_00282DD8(center,edge1,edge2);
        func_00282F20(center,center,1.0f);
        if(func_00282DB0(normal,center)>0.0f)
            func_00280B90(&q,0,0);
    } while(++index<215);
}
