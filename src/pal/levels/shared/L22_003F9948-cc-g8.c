/* func_PAL_L22_003F9948, the PAL copy of func_L22_003F54B8: the same C. */

typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
/* The resident global is an array here on purpose: with a scalar declaration
 * cc1 folds the load and reuses the destination as the address base, while the
 * retail materialises the address in its own register first -- declaring the
 * symbol as an array and indexing it [0] restores the two-instruction form
 * (`lui $v1,%hi; lw $a1,%lo($v1)`). */
/* The four resident words sit at the level-22 addresses; in the other program that carries
 * func_L22_003B9358 they are elsewhere, so they take per-program names. */
   /* the level-22 word D_L22_001AFA08 */

   /* the level-22 word D_L22_001AFA00 */

   /* the level-22 word D_L22_001AFA0C */

   /* the level-22 word D_L22_001AFA04 */

/* Drops the resident slot the argument's record selects: the slot word is released and stamped
 * -1, and the object the slot holds is torn down when its id is 0x5F3 and it has not started
 * (the two resident words it owns are cleared first, and its stored index is released when it is
 * not -1). An object with any other id only clears the slot. */
/* func_PAL_L22_003F9948 sets up the motion that func_L22_003F5580 runs: the heading of the
 * object's variables is a coin toss of +/- pi/2 added to the angle of the vector from the
 * object to a level point (after func_002AFDD8), the phase step is a rate in degrees per
 * second turned into radians per frame (pi / 180 / 60), and the amplitude is a level
 * value. The point and both values take per-program names.
 */
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, int);
extern int func_002A77E0(int);
extern f32 func_00283248(f32, f32);
extern f32 func_00283B98(f32, f32);

typedef struct {
    u8 pad[0xB0];
    f32 heading;     /* 0xB0 */
    u8 pad_b4[8];
    f32 amplitude;   /* 0xBC */
    f32 phase_step;  /* 0xC0 */
    f32 phase;       /* 0xC4 */
} SwayVars;

extern char ref_L22_003F54B8_00[];
extern f32 ref_L22_003F54B8_01 __attribute__((sda));
extern f32 ref_L22_003F54B8_02 __attribute__((sda));

void func_PAL_L22_003F9948(u8 *obj) {
    SwayVars *vars = *(SwayVars **)(obj + 0x68);
    f32 delta[4];

    func_00282CF0(delta, ref_L22_003F54B8_00, obj + 0x10);
    func_002AFDD8(obj, delta, delta, 0);
    vars->heading = func_002A77E0(2) ? 1.5707964f : -1.5707964f;
    vars->heading = func_00283B98(vars->heading, func_00283248(delta[0], delta[1]));
    vars->phase_step = ref_L22_003F54B8_01 * 0.0003490659f;
    vars->amplitude = ref_L22_003F54B8_02;
    vars->phase = 0.0f;
}

/* func_L22_003F5580 is another function of this unit that reaches a level word through
 * $gp; the scale factor it multiplies is at a different address in the other program that
 * carries the function, so it takes a per-program name.
 */
extern f32 func_00283B98(f32, f32);
/* Scales the controller of the object: when the controller is idle its position is copied to
 * the object, otherwise the controller's values are scaled and written back.
 */
typedef unsigned short u16;

/* The resident object the point is derived from, the word that picks one of two threshold
   pairs, the four threshold words (read through $gp) and, for the two id lists, the table of
   lists and the base of the 32-byte records each one indexes (read bare: `lui`/`lw` in one
   register). */
/* Switches the object on (+0xCC set) when its position (+0xE0) comes within a threshold of the
   point func_002AFFD8 derives from D_L22_001B9C80 (func_00282DB0 measures it), and off when it
   moves beyond it; the threshold is interpolated between two words by the index at +0x14
   (divided by 14), the pair of words depending on D_L22_001A8F00 == 4. Only a change does
   anything more: switching off clears bit 2 of byte +0x1E of every record of the id list at
   +0x10 and bit 0 of byte +0x16 of every record of the list at +0x16; switching on sets those
   bits (a list index below zero means no list). */
/* func_L22_003FC338: draws a pulsing ring around an object.  The 290-vertex
 * mesh is scaled, transformed by a basis built from the object's axis and
 * written to the shared vertex buffer as three strips; then 32 quads are drawn
 * from the ring's index table, the outer two corners pushed out by a factor. */
typedef struct { f32 x, y, z; } RingVertex;
extern RingVertex D_L22_00255920[];
extern void func_00282CF0(void *, void *, void *);
