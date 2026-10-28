/* func_L11_004471A8 - 436 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   11_joba: 432 bytes, expected 436
     004471D0  beqz        $v0, . + 4 + (0x5A << 2)     | beqz        $v0, . +
   4 + (0x5B << 2)
     004471D8  sh          $v0, 0x1FC($s2)              | lw          $a0,
   0x29BC($gp)
     004471E0  lw          $a0, 0x0($gp)                | sh          $v0,
   0x1FC($s2)
     004471E8  lui         $v0, 0x0                     | lui         $v1,
   0x19
     004471EC  addiu       $s0, $sp, 0x10               | addiu       $v1,
   $v1, -0x6160
     004471F0  addiu       $v0, $v0, 0x0                | lq          $v0,
   0x0($v1)
     004471F4  daddu       $a0, $s1, $zero              | sq          $v0,
   0x0($sp)
     004471F8  lq          $v1, 0x0($v0)                | addiu       $s0,
   $sp, 0x10
     00447200  sq          $v1, 0x0($sp)                | daddu       $a0,
   $s1, $zero
     00447240  daddu       $a1, $s0, $zero              | lwc1        $f0,
   0x8($sp)
     00447248  lwc1        $f1, 0x8($sp)                | daddu       $a1,
   $s0, $zero
     004472C8  lwc1        $f1, 0x8($v0)                | lwc1        $f0,
   0x8($v0)
     004472D4  mtc1        $at, $f0                     | mtc1        $at, $f1
     004472D8  por         $v0, $zero, $zero            | nop
     004472DC  add.s       $f0, $f1, $f0                | add.s       $f0,
   $f0, $f1
     004472E4  sq          $v0, 0x20($sp)               | lwc1        $f0,
   0x29C0($gp)
     004472E8  lwc1        $f0, 0x0($gp)                | por         $v0,
   $zero, $zero
     004472FC  lui         $at, 0x3F80                  | sq          $v0,
   0x20($sp)
     00447300  mtc1        $at, $f14                    | daddu       $a2,
   $sp, $zero
     00447304  daddu       $a2, $sp, $zero              | mul.s       $f0,
   $f0, $f1
     00447308  mul.s       $f0, $f0, $f1                | lui         $at,
   0x3F80
     0044730C  lui         $at, 0x4409                  | mtc1        $at,
   $f14
     00447310  ori         $at, $at, 0x8000             | lui         $at,
   0x4409
     00447314  mtc1        $at, $f15                    | ori         $at,
   $at, 0x8000
     00447318  swc1        $f0, 0x28($sp)               | mtc1        $at,
   $f15
     0044731C  lq          $v0, 0x20($sp)               | swc1        $f0,
   0x28($sp)
     00447320  sq          $v0, 0x10($sp)               | lq          $v0,
   0x20($sp)
     00447324  lbu         $v1, 0x34($s2)               | sq          $v0,
   0x10($sp)
     00447328  mtc1        $v1, $f13                    | lbu         $v1,
   0x34($s2)
     0044732C  nop                                      | mtc1        $v1,
   $f13
     00447330  cvt.s.w     $f13, $f13                   | nop
     00447334  jal         func_000000                  | cvt.s.w     $f13,
   $f13
     00447338  lwc1        $f12, 0x20($s2)              | jal
   func_45FDB0
     0044733C  ld          $s0, 0x30($sp)               | lwc1        $f12,
   0x20($s2)
     00447340  ld          $s1, 0x38($sp)               | ld          $s0,
   0x30($sp)
     00447344  ld          $s2, 0x40($sp)               | ld          $s1,
   0x38($sp)
     00447348  ld          $ra, 0x48($sp)               | ld          $s2,
   0x40($sp)
     0044734C  lwc1        $f20, 0x50($sp)              | ld          $ra,
   0x48($sp)
     00447350  jr          $ra                          | lwc1        $f20,
   0x50($sp)
     00447354  addiu       $sp, $sp, 0x60               | jr          $ra
   func_L11_004471A8: 0 of 1 places match
   (src/levels/11_joba/L11_004471A8-zp-g8.c)
   masked diff lines: 41
   Flags: -O2 -G8 -ffunction-sections -frac2-zero-ti-por -frac2-zero-ti-
   barrier (new unit L11_004471A8-zp-g8.c). 432 vs 436 bytes. Remaining: (1)
   retail does lw a0,0x29BC(gp) before the sh in the jal delay; (2) first TI
   copy: retail lq v0/addr v1, mine addr v0/data v1; (3) z merge: retail z in
   f0, 5.0f in f1 with nop before add and por AFTER the add; mine fills the
   nop with por. Path 1 'a1' recompute in path 2 (addiu a1,sp,0x10) is missing
   in mine. */

#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union Vec4 { Quadword bits; float value[4]; } Vec4;

extern int func_00282978(void *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float *func_L11_004417E8(char *);
extern void func_L11_0045FDB0(char *, void *, void *, float, float, float, float);
extern char D_00189EA0[];
extern unsigned short D_L11_001B19A8 __attribute__((sda));
extern int D_L11_001B19AC __attribute__((sda));
extern float D_L11_001B19B0 __attribute__((sda));
extern float D_L11_001B19B4 __attribute__((sda));

/* Picks a spawn point around the object and launches the effect from it. */
void func_L11_004471A8(char *object) {
    char *state = *(char **)(object + 0x68);
    float pos[4];
    float step[4];
    Vec4 velocity;
    float angle;
    float height;

    if (func_00282978(state + 0x1FC)) {
        *(unsigned short *)(state + 0x1FC) = D_L11_001B19A8;
        if (func_002A77E0(D_L11_001B19AC) == 0) {
            Quadword origin = *(Quadword *)D_00189EA0;

            *(Quadword *)pos = origin;
            func_00282CF0(step, pos, func_L11_004417E8(object));
            step[2] = 0.0f;
            func_00282F20(step, step, D_L11_001B19B4);
            func_00282CC0(pos, step, func_L11_004417E8(object));
            height = pos[2];
        } else {
            angle = func_002A7878(-3.1415927f, 3.1415927f);
            pos[0] = func_L11_004417E8(object)[0] + D_L11_001B19B4 * func_00283180(angle);
            pos[1] = func_L11_004417E8(object)[1] + D_L11_001B19B4 * func_00283198(angle);
            height = func_L11_004417E8(object)[2];
        }
        pos[2] = 5.0f + height;
        velocity.bits = 0;
        velocity.value[2] = D_L11_001B19B0 * 0.016666668f;
        *(Quadword *)step = velocity.bits;
        func_L11_0045FDB0(object, step, pos, *(float *)(state + 0x20),
                          (float)*(unsigned char *)(state + 0x34), 1.0f, 550.0f);
    }
}
