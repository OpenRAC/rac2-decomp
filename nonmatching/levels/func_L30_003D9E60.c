/* func_L30_003D9E60 - 440 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   003D9F84  addiu       $a0, $zero, 0x200            | daddu       $s0, $v0,
   $zero
     003D9F8C  daddu       $s0, $v0, $zero              | addiu       $a0,
   $zero, 0x200
     003D9F94  dsll        $s0, $s0, 26                 | lui         $a1,
   0x1A
     003D9F98  lui         $a0, 0x0                     | lw          $a1,
   0x72D8($a1)
     003D9F9C  lw          $a0, 0x0($a0)                | dsll        $s0,
   $s0, 26
     003D9FA0  dsll        $v0, $v0, 30                 | sll         $v1,
   $v1, 16
     003D9FA4  sll         $v1, $v1, 16                 | sra         $v1,
   $v1, 22
     003D9FA8  ori         $a1, $zero, 0x8000           | dsra        $a1,
   $a1, 8
     003D9FAC  dsll        $a1, $a1, 23                 | dsll        $v1,
   $v1, 14
     003D9FB0  ori         $a1, $a1, 0x48               | dsll        $v0,
   $v0, 30
     003D9FB4  sra         $v1, $v1, 22                 | or          $a1,
   $a1, $v1
     003D9FB8  dsra        $a0, $a0, 8                  | addiu       $a2,
   $zero, 0x60
     003D9FBC  dsll        $v1, $v1, 14                 | or          $a1,
   $a1, $s0
     003D9FC0  addiu       $a2, $zero, 0x60             | ori         $v1,
   $zero, 0x8000
     003D9FC4  or          $a0, $a0, $v1                | dsll        $v1,
   $v1, 23
     003D9FC8  sd          $a1, 0x88($sp)               | ori         $v1,
   $v1, 0x48
     003D9FCC  or          $a0, $a0, $s0                | or          $a1,
   $a1, $v0
     003D9FD8  or          $a0, $a0, $v0                | sd          $a1,
   0x78($sp)
     003D9FDC  lui         $at, 0x3DA3                  | addiu       $a0,
   $s2, 0x10
     003D9FE0  ori         $at, $at, 0xD70A             | lui         $at,
   0x3DA3
     003D9FE4  mtc1        $at, $f13                    | ori         $at,
   $at, 0xD70A
     003D9FE8  sd          $a0, 0x78($sp)               | mtc1        $at,
   $f13
     003D9FF0  addiu       $a0, $s2, 0x10               | sd          $a2,
   0x80($sp)
     003D9FF4  sd          $a2, 0x80($sp)               | sd          $v1,
   0x88($sp)
   func_L30_003D9E60: 0 of 1 places match
   (src/levels/30_insomniac_museum/L30_003D9E60-g8.c)
   masked diff lines: 24
   Size 440 ok. Needs new file with cflags '-O2 -G8 -ffunction-sections
   -Wa,-G32' (32-byte table via gp). Remaining: tag OR chain accumulates in a0
   (retail a1), f88 constant built early in a1 (retail late in v1). Tried
   store permutations, tag local, stores before calls. */

#include "common.h"

/* Needs the small-data profile with the assembler's -G32: the 32-byte table is reached
   as `addiu $a2,$gp,0x19A0`. */

typedef struct {
    float matrix[16];
    u32 color[4];
    float uv[8];
    u64 f70;
    u64 tag;
    u64 f80;
    u64 f88;
} QuadBlock;

extern float D_001B0990[8] __attribute__((sda));
extern int D_001B2758;
extern short D_001A6480[];
extern int D_001A72D8;
extern long func_00282A18(int);
extern void func_L30_003D9CA8(void *, QuadBlock *, float, float);

void func_L30_003D9E60(char *object) {
    QuadBlock b;
    int t = D_001B2758 >> 1;
    long first;
    long second;

    b.uv[0] = D_001B0990[t & 7];
    t += 2;
    b.uv[1] = D_001B0990[t & 7];
    t += 3;
    b.uv[2] = D_001B0990[t & 7];
    t++;
    b.uv[3] = 1.0f - D_001B0990[t & 7];
    t++;
    b.uv[4] = 1.0f - D_001B0990[t & 7];
    t += 2;
    b.uv[5] = D_001B0990[t & 7];
    t++;
    b.uv[6] = 1.0f - D_001B0990[t & 7];
    t++;
    b.uv[7] = 1.0f - D_001B0990[t & 7];
    b.color[3] = 0x60808080;
    b.color[0] = 0x60808080;
    b.color[1] = 0x60808080;
    b.color[2] = 0x60808080;
    first = func_00282A18(D_001A6480[0xAC]);
    second = func_00282A18(0x200);
    b.tag = (long long)D_001A72D8 >> 8;
    b.tag |= (long long)(D_001A6480[0xAC] >> 6) << 14;
    b.tag |= (long long)first << 26;
    b.tag |= (long long)second << 30;
    b.f80 = 0x60;
    b.f88 = 0x4000000048ULL;
    b.f70 = 0;
    func_L30_003D9CA8(object + 0x10, &b, 6.0f, 0.08f);
}
