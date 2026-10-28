/* func_0032FFD8 - 376 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   boot: 380 bytes, expected 376
     0032FFDC  lui         $v0, 0x0                     | sd          $s0,
   0x60($sp)
     0032FFE0  sd          $s4, 0x80($sp)               | sd          $s3,
   0x78($sp)
     0032FFE4  sd          $s3, 0x78($sp)               | lui         $s0,
   0x23
     0032FFE8  daddu       $s4, $a0, $zero              | daddu       $s3,
   $a0, $zero
     0032FFEC  addiu       $s3, $v0, 0x0                | addiu       $s0,
   $s0, 0x7700
     0032FFF0  sd          $s0, 0x60($sp)               | sd          $s1,
   0x68($sp)
     0032FFF4  sd          $s1, 0x68($sp)               | addiu       $v1,
   $s3, 0xC0
     0032FFF8  addiu       $v1, $s4, 0xC0               | sd          $s2,
   0x70($sp)
     0032FFFC  sd          $s2, 0x70($sp)               | sd          $s4,
   0x80($sp)
     00330010  addiu       $s0, $sp, 0x30               | addiu       $s1,
   $sp, 0x30
     00330014  addiu       $v1, $s4, 0xD0               | addiu       $v1,
   $s3, 0xD0
     0033001C  sq          $v0, 0x0($s0)                | sq          $v0,
   0x0($s1)
     00330028  addiu       $s2, $sp, 0x10               | addiu       $s4,
   $sp, 0x10
     00330030  daddu       $a0, $s2, $zero              | daddu       $a0,
   $s4, $zero
     0033003C  addiu       $s1, $sp, 0x20               | addiu       $s2,
   $sp, 0x20
     00330044  daddu       $a0, $s1, $zero              | daddu       $a0,
   $s2, $zero
     0033004C  daddu       $a1, $s0, $zero              | daddu       $a1,
   $s1, $zero
     00330050  addiu       $v1, $s3, 0x40               | addiu       $v1,
   $s0, 0x40
     0033005C  addiu       $a0, $s3, 0x50               | addiu       $a0,
   $s0, 0x50
     00330060  lq          $v0, 0x0($s2)                | lq          $v0,
   0x0($s4)
     00330068  addiu       $v1, $s3, 0x60               | addiu       $v1,
   $s0, 0x60
     0033006C  lq          $v0, 0x0($s1)                | lq          $v0,
   0x0($s2)
     00330074  addiu       $a0, $s3, 0x70               | addiu       $a0,
   $s0, 0x70
     00330078  lq          $v0, 0x0($s0)                | lq          $v0,
   0x0($s1)
     00330080  addiu       $s2, $sp, 0x50               | addiu       $s3,
   $s3, 0x10
     00330084  addiu       $s1, $sp, 0x40               | addiu       $s4,
   $sp, 0x50
     00330088  addiu       $s4, $s4, 0x10               | addiu       $s2,
   $sp, 0x40
     0033008C  daddu       $s0, $zero, $zero            | daddu       $s1,
   $zero, $zero
     00330090  andi        $a2, $s0, 0x1                | slti        $v0,
   $s1, 0x4
     00330098  sra         $a1, $s0, 1                  | beqz        $v0, . +
   4 + (0x9 << 2)
     0033009C  sll         $a2, $a2, 4                  | sra         $a1,
   $s1, 1
     003300A0  sll         $a1, $a1, 4                  | andi        $a2,
   $s1, 0x1
     003300A4  addiu       $a2, $a2, 0x20               | sll         $a2,
   $a2, 4
     003300A8  slti        $v0, $s0, 0x4                | sll         $a1,
   $a1, 4
     003300AC  addu        $a1, $sp, $a1                | addiu       $a2,
   $a2, 0x20
     003300B0  addu        $a2, $sp, $a2                | addu        $a1,
   $sp, $a1
     003300B4  daddu       $a0, $s3, $zero              | addu        $a2,
   $sp, $a2
     003300B8  beqz        $v0, . + 4 + (0x3 << 2)      | jal
   func_282CC0
     003300BC  addiu       $s0, $s0, 0x1                | daddu       $a0,
   $s0, $zero
     003300C0  jal         func_000000                  | lwc1        $f12,
   0x1980($gp)
   func_0032FFD8: 0 of 1 places match (src/game/0032EB28-g8-qcopy.c)
   masked diff lines: 76
   380 vs 376 bytes. File flags tried: -G8 -frac2-qcopy -frac2-qcopy-barrier
   (new file 0032EB28-g8-qcopy.c) and plain qcopy in 0032EB28-g8.c: same
   output. Needs: retail alloc dst=s0,i=s1,e=s2,obj=s3,f=s4 (mine
   i=s0,e=s1,f=s2,dst=s3,obj=s4); retail keeps args of if(i<4) call after the
   beqz (mine speculates them above it); mine lui v0 + addiu s3,v0 for
   D_00237700. Tried decl order, for(;;i++,dst+=16), array indexing G[i],
   MACRO_ADDR. */

#include "include_asm.h"
typedef int TQ __attribute__((mode(TI)));

/* Functions of 0032EB28.c that need both the small-data profile (-G8) and the quadword
   copy with its scheduling barrier. */
extern float D_001B09A0 __attribute__((sda));
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

/* func_0032FFD8 builds the eight vectors at D_00237700 from the two vectors at object+0xC0
   and object+0xD0, their negated counterparts and the object's matrix at object+0x10. */
extern char D_00237700[];
extern float D_001B099C __attribute__((sda));
extern float D_001B2830;
extern void func_00282D30(void *, void *, float);

typedef float Vec4[4] __attribute__((aligned(16)));

void func_0032FFD8(char *object)
{
    char *dst = D_00237700;
    Vec4 v[4];
    Vec4 e, f;
    int i;

    *(TQ *)(v[0]) = *(TQ *)(object + 0xC0);
    *(TQ *)(v[3]) = *(TQ *)(object + 0xD0);
    func_00282D30(v[1], v[0], -1.0f);
    func_00282D30(v[2], v[3], -1.0f);
    *(TQ *)(dst + 0x40) = *(TQ *)(v[0]);
    *(TQ *)(dst + 0x50) = *(TQ *)(v[1]);
    *(TQ *)(dst + 0x60) = *(TQ *)(v[2]);
    *(TQ *)(dst + 0x70) = *(TQ *)(v[3]);
    object += 0x10;
    for (i = 0; i < 8; i++, dst += 0x10) {
        if (i < 4)
            func_00282CC0(dst, v[i >> 1], v[2 + (i & 1)]);
        func_00282F20(dst, dst, D_001B09A0);
        func_00282CC0(dst, dst, object);
        func_00282F20(e, &D_001B2830, -D_001B099C);
        func_00282CC0(dst, dst, e);
        func_00282CC0(f, e, object);
    }
}
