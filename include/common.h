#ifndef COMMON_H
#define COMMON_H

/* Shared with rac1-decomp's include/common.h: the same types, markers and attributes. */
#include "include_asm.h"
#include "names.h"   /* readable names for func_ symbols */

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

typedef signed char        s8;
typedef signed short       s16;
typedef signed int         s32;
typedef signed long long   s64;

typedef float              f32;
typedef double             f64;

/* A global the compiler must not address $gp-relative (it is not in the small-data area). */
#define NOT_SDA __attribute__((section(".data")))
/* A global in the small-data area, addressed $gp-relative. */
#define MACRO_ADDR __attribute__((section(".sdata")))
/* Explicit GP address view, bound to the same canonical storage by
 * tools/sdata_aliases.py. Keep the real type/extent (or an incomplete array);
 * its assembler small-address metadata is not a C object bound.
 */
#define SDATA(sym) __asm__(#sym "__gp") MACRO_ADDR

#include "ps2_hw.h"

/* Approved EE transfer helpers, adapted from rac1-decomp (GPL-3.0).
 * Both addresses must be
 * 16-byte aligned. Each helper really reads/writes memory; the clobber keeps
 * surrounding C accesses correct. Arbitrary source barriers remain forbidden.
 */
static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}

static __inline__ void qzero(void *dst) {
    __asm__ __volatile__("sq $0,0x0(%0)" : : "r"(dst) : "memory");
}

/* rac1-decomp's qzero: the same store with no clobbers at all, so the asm is a bare
 * volatile ASM_OPERANDS. cse flushes everything it knows at one, so an address used
 * before it is built again (a fresh lui) after it. Use it only where retail rebuilds.
 */
static __inline__ void qzero_nc(void *dst) {
    __asm__ __volatile__("sq $0,0x0(%0)" : : "r"(dst));
}

/*
 * The EE `sync` instruction, which no C construct emits. From RAC1's include/common.h, where
 * libgraph units call it.
 */
static __inline__ void CpuSync(void) { __asm__ __volatile__("sync"); }

/* Enable EE interrupts, as in rac1-decomp's shared hardware primitives. */
static __inline__ void CpuEnableInt(void) { __asm__ __volatile__("ei"); }

/* RAC1's non-clobbering variant: callers must establish that surrounding C
 * accesses do not depend on the copied memory. Keep qcopy as the default.
 */
static __inline__ void qcopy_nc(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2");
}

/* Call an object's update hook fn(arg) when fn is not null. Same asm as current
 * rac1-decomp's src/game/moby/mobyutil.c (update_visible_resident_objects), where the
 * original also used inline asm: GCC 2.95 reorg leaves both delay slots (beq, jalr)
 * empty only next to asm (reorg.c stop_search_p), as retail does.
 * Allowed by owner ruling, 8 November 2026.
 */
static __inline__ void call_hook(void *fn, void *arg) {
    int r;
    __asm__ volatile("beq %1,$0,1f\n\tmove $4,%2\n\tjal $31,%1\n1:"
                     : "=r"(r)
                     : "r"(fn), "r"(arg)
                     : "$4", "$31", "memory");
}

#endif /* COMMON_H */
