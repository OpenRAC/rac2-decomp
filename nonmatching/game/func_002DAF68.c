/* func_002DAF68 - 584 bytes.  Worker attempt, 27 October 2026 (draft below).

   580 B vs 584. Control flow and constants all decoded and correct (draw
   dialog frame; func_0028F278 args:
   tex,x<<4,y<<4,7,7,w<<4,h<<4,u,v=0,alpha=0x80).
   Diffs: regalloc of x/y/w/h locals: retail s7=x s6=y s4=w s5=h; mine s7=x
   s4=y s5=w s6=h. Retail derives &D_001C4FA0 in v1 (lui a1/addiu) for first
   reads and s3 later; branch order in retail: equal case (0x32...) falls
   through, mine same after swap. mode test is 5/10/15/<0x15/==0x18.
   Tried: base char* vs struct cast, branch swap, decl order. */

/* in src/game/002D5E98.c replacing the INCLUDE_ASM; the later "extern char *D_001F2854;" at the func_002DB.. area must be removed (declared once here) */
extern char *D_001F2854;
extern char D_0025E680[];
extern int D_00261998[];
extern int D_001B1598;
extern void func_002FC560(int, int);
extern void func_0028F278(long long, int, int, int, int, int, int, int, int, int);

typedef struct { char pad[0x230]; int mode; int index; char pad238[0x268 - 0x238]; long long tex0; char pad270[8]; long long tex1; } Dialog2DAF68;
int func_002DAF68(void)
{
    int sizes[4];
    int x;
    int y;
    int w;
    int h;
    int kind;
    int inset;
    int offset;
    int mode;

    if (((Dialog2DAF68 *)&D_001C4FA0)->index < 0)
        return 0;
    mode = ((Dialog2DAF68 *)&D_001C4FA0)->mode;
    if (mode != 5 && mode != 10 && mode != 15 && mode >= 0x15 && mode != 0x18)
        return 0;
    sizes[0] = 0;
    if (D_001F2854 == D_0025E680) {
        sizes[1] = 0x32;
        sizes[2] = 0x26;
        sizes[3] = 0x19;
        x = 0x1D;
        y = 0x4D;
        w = 0xBF;
        h = 0xB2;
    } else {
        sizes[1] = 0x26;
        sizes[2] = 0x1C;
        sizes[3] = 0x14;
        x = 0x1E;
        y = 0x4C;
        w = 0x99;
        h = 0x8C;
    }
    offset = D_001B1598 + ((Dialog2DAF68 *)&D_001C4FA0)->index * 0x2AB;
    kind = D_00261998[((Dialog2DAF68 *)&D_001C4FA0)->index];
    inset = sizes[kind];
    func_002FC560(0x47, 0);
    func_002FC560(8, 0);
    if (kind == 0) {
        func_0028F278(((Dialog2DAF68 *)&D_001C4FA0)->tex0, x << 4, y << 4, 7, 7, w << 4, h << 4, 0, 0, 0x80);
    } else {
        func_0028F278(((Dialog2DAF68 *)&D_001C4FA0)->tex0, (x + inset) << 4, (y + inset) << 4, 7, 7,
                      (w - inset * 2) << 4, (h - inset * 2) << 4, offset % 2048, 0, 0x80);
        func_002FC560(8, 5);
        func_0028F278(((Dialog2DAF68 *)&D_001C4FA0)->tex1, x << 4, y << 4, 7, 7, w << 4, h << 4, 0, 0, 0x80);
    }
    func_002FC560(0x47, 0x360B);
    return 4;
}
