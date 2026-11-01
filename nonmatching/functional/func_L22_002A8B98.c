/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* GPT-6.1 Sol high worker, 29 October 2026, pinned upstream game compiler.
   Default -O2 -G0 -ffunction-sections. 172/172 bytes, 0/2 USA v1.01 places;
   final check first differs at +0x60. Only three stores differ: retail stores
   speed0, speed1, flag; this candidate stores flag, speed0, speed1.
   Reordering the duplicate float assignments fixes all FP register allocation.
   Raw byte-pointer accesses, an unsigned-char flag, and an inline comparison
   preserve the same final store rotation. Moving flag earlier only moves it
   earlier in the generated block. Allocator dumps confirm the rotation already
   exists before reload. Next: independently evidenced initialization grouping
   or a matching RAC1 counterpart, without barriers or selective volatility.
   All required declarations are included. Not linked or counted. */

extern int D_001A79F0[] __attribute__((sda));
extern int D_001A73A0[] __attribute__((sda));
extern char D_L22_001B1920[];
extern void func_L00_002D24B8(void);
extern void func_L22_002C9898(int, int);
extern void func_L00_003B09F8(void);
typedef struct {
 char pad0[0x250]; float speed0, speed1, tuning0, tuning1;
 char pad260[4]; float tuning2;
 char pad268[0xC24-0x268]; float scale;
 char padC28[0x1888-0xC28]; void *counts;
 char pad188C[0x2294-0x188C]; int state;
 char pad2298[0x24F0-0x2298]; unsigned char flag;
} InitState;
extern InitState D_00189E20;
void func_L22_002A8B98(void) {
 int flag = D_001A79F0[0] == 0x1A;
 InitState *p = &D_00189E20;
 p->speed0 = 0.8f;
 p->speed1 = 0.7f;
 p->tuning2 = 0.45f;
 p->tuning0 = 0.8f;
 p->tuning1 = 0.7f;
 p->scale = 1.0f;
 p->flag = flag;
 D_001A73A0[0] = 0;
 p->state = 0;
 func_L00_002D24B8();
 func_L22_002C9898(0, 1);
 func_L00_003B09F8();
 p->counts = D_L22_001B1920;
}
