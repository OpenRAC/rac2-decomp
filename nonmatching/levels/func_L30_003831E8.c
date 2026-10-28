/* func_L30_003831E8 - 428 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   00383254  subu        $a3, $s7, $a1                | subu        $s0, $s5,
   $v0
     00383258  subu        $s0, $s5, $v0                | slt         $v0,
   $s5, $s0
     0038325C  slt         $v0, $s5, $s0                | bnez        $v0, . +
   4 + (0x3B << 2)
     00383260  bnez        $v0, . + 4 + (0x3A << 2)     | sw          $v1,
   0x4($sp)
     00383264  sw          $v1, 0x4($sp)                | sll         $a0,
   $s5, 1
     00383268  sll         $a0, $s5, 1                  | addiu       $v1,
   $zero, 0x60
     0038326C  addiu       $v0, $zero, 0x60             | subu        $a0,
   $a0, $s0
     00383270  subu        $a0, $a0, $s0                | mult        $t3,
   $s0, $v1
     00383274  mult        $t1, $s0, $v0                | mult        $a0,
   $a0, $v1
     00383278  mult        $a0, $a0, $v0                | subu        $v0,
   $s7, $a1
     0038327C  addu        $v1, $s7, $a3                | addu        $v1,
   $s7, $v0
     00383280  mult        $fp, $a3, $a3                | mult        $fp,
   $v0, $v0
     00383290  addiu       $s6, $v0, 0x0                | addu        $s3,
   $t3, $a1
     00383294  addu        $s4, $t1, $a1                | addiu       $s6,
   $v0, 0x3A60
     00383298  addu        $s3, $t1, $v1                | addu        $s4,
   $a0, $a1
     0038329C  addu        $s2, $a0, $a1                | addu        $s2,
   $a0, $v1
     003832A0  addu        $s1, $a0, $v1                | addu        $s1,
   $t3, $v1
     003832E4  addu        $v0, $s4, $a0                | addu        $v0,
   $s3, $a0
     00383304  addu        $v0, $s2, $a0                | addu        $v0,
   $s4, $a0
     00383308  addu        $v1, $s3, $a0                | addu        $v1,
   $s1, $a0
     0038331C  addu        $a0, $s1, $a0                | addu        $a0,
   $s2, $a0
     00383328  negu        $a1, $v1                     | negu        $v0, $v1
     00383330  swc1        $f1, 0x0($a0)                | addu        $s4,
   $s4, $v0
     00383334  addu        $s2, $s2, $a1                | addu        $s2,
   $s2, $v0
     00383338  addiu       $s3, $s3, 0x60               | swc1        $f1,
   0x0($a0)
     0038333C  addiu       $s4, $s4, 0x60               | addiu       $s1,
   $s1, 0x60
     00383348  addu        $s1, $s1, $a1                | addiu       $s3,
   $s3, 0x60
   func_L30_003831E8: 0 of 1 places match
   (src/levels/30_insomniac_museum/L30_0032AAF0-g8.c)
   masked diff lines: 27
   Size right (428). Only register numbers/order differ: retail cell pointers
   s3=(x,y) s4=(mx,y) s1=(x,cy+dy) s2=(mx,cy+dy), mine s4,s2,s3,s1; temps
   t3/v1 vs t1/v0; dy kept in a3. Mirror col must be cx+dx (cx-x) to get 4
   strength-reduced pointers; 2*cx-x gives only 2 (436 bytes). scale*sqrt(...)
   operand order matters. Tried store order permutations, cell local vs
   repeated helper, madd appears if dy*dy spilled. */

/* goes in L30_0032AAF0-g8.c (needs its -G8 profile; remove the INCLUDE_ASM marker) */
extern int D_001AEBB8 __attribute__((sda));
extern char D_00233A60[];
extern int func_00283CF0(float);
extern float func_00282C10(float);

/* The cell (x, y) of the current 24x24 layer. */
static __inline__ float *layer_cell(int x, int y) {
    return (float *)(D_00233A60 + (x * 0x60 + y * 4 + D_001AEBB8 * 0x900));
}

/* Raises a disc of the 24x24 height layers: for every cell of one quadrant it takes the
   height of a sphere of radius `radius` and keeps the larger of that and what the cell
   holds, then writes it to the cell and its three mirror cells. */
void func_L30_003831E8(int cx, int cy, float radius, float scale) {
    int n = func_00283CF0(radius);
    int y;
    int x;
    float r2 = radius * radius * 2.0f;

    for (y = cy - n; y <= cy; y++) {
        int dy = cy - y;

        for (x = cx - n; x <= cx; x++) {
            int dx = cx - x;
            float d = func_00282C10((float)(dx * dx + dy * dy));
            float h = scale * func_00282C10(r2 - d * d);
            int mx = cx + dx;

            if (h < *layer_cell(x, y))
                h = *layer_cell(x, y);
            *layer_cell(x, y) = h;
            *layer_cell(mx, y) = h;
            *layer_cell(x, cy + dy) = h;
            *layer_cell(mx, cy + dy) = h;
        }
    }
}
