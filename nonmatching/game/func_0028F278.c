/* func_0028F278 - 396 bytes.  Worker attempt, 27 October 2026 (draft below).

   check.py: 392 bytes vs 396 expected (1 insn short), many scheduling/reg
   diffs.
   Retail has "daddu t6,t5,zero" (copy of stack arg v before dsll 16) and
   keeps v in t5 for the later (v + (1<<(vshift+4))); mine shifts v in place,
   no copy.
   Retail loads stack args (lw 0x20/0x28 sp) before first sw; mine later.
   Retail reloads D_001B22A8 (lui/lw) 4 times, I do too.
   Signature guess: (s64 tex,int x,int y,int ushift,int vshift,int w,int h,int
   u,int v,int alpha). Tried: inline exprs, early locals rgba/uv0/uv1, uv0
   operand order. No volatile used. */

/* in src/game/0028E440.c (-G8); needs extern int D_001A7350, D_001A7354 */
extern char *D_001B22A8;
extern int D_001B187C;

void func_0028F278(long long tex, int x, int y, int ushift, int vshift, int w, int h, int u, int v, int alpha)
{
    char *p;
    char *q;
    long long rgba = ((long long)alpha << 24) | 0x7F7F7F;
    long long uv0 = ((long long)v << 16) | u;

    *(int *)(D_001B22A8 + 0) = 0x10000005;
    *(int *)(D_001B22A8 + 4) = 0;
    *(int *)(D_001B22A8 + 8) = 0;
    *(int *)(D_001B22A8 + 12) = 0x50000005;
    p = D_001B22A8;
    q = p + 16;
    D_001B22A8 = q;
    *(long long *)(p + 16) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    *(long long *)(q + 16) = tex;
    *(long long *)(q + 24) = 0x156;
    *(long long *)(q + 32) = rgba;
    *(long long *)(q + 40) = uv0;
    *(long long *)(q + 48) = (x + D_001A7350 - 8) | ((long long)(y + D_001A7354 - 8) << 16) | ((long long)D_001B187C << 32);
    *(long long *)(q + 56) = (u + (1 << (ushift + 4))) | ((long long)(v + (1 << (vshift + 4))) << 16);
    *(long long *)(q + 64) = (x + w + D_001A7350 - 8) | ((long long)(y + h + D_001A7354 - 8) << 16) | ((long long)D_001B187C << 32);
    *(long long *)(q + 72) = 0;
    D_001B22A8 = D_001B22A8 + 0x50;
}
