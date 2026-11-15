#include "common.h"
#include "structs.h"

extern int clock_bcd_to_decimal_byte(int);

typedef struct { char b[0xC]; } Cfg12;

extern Cfg12 r1_D_00153D40 NOT_SDA;

/* Qwen draft (branch qwen/autonomy, bb52125e), checked by tools/check.py */
void snd_queue_command(int, int, int, long, int);

   /* current buffer */
extern short r1_D_0015EDC4;

/* rac1-decomp src/core/0012CC90.c: func_0012D500 */
/* Convert the sceCdCLOCK fields (second..year) in place with the helper
   above. Exact under 2.9-ee, which saves $16 before $31 as retail does;
   2.95.3 saved them the other way round (4/104), the prologue-order
   residual that pointed at the SDK compiler in the first place. */
/* Turns every field of a clock record from BCD into normal numbers. */
void clock_bcd_to_decimal(unsigned char *p) {
    p[7] = clock_bcd_to_decimal_byte(p[7]);
    p[6] = clock_bcd_to_decimal_byte(p[6]);
    p[5] = clock_bcd_to_decimal_byte(p[5]);
    p[3] = clock_bcd_to_decimal_byte(p[3]);
    p[2] = clock_bcd_to_decimal_byte(p[2]);
    p[1] = clock_bcd_to_decimal_byte(p[1]);
}
extern void clock_decimal_to_bcd(unsigned char *p);
extern int clock_decimal_to_bcd_byte(int);

/* Turns every field of a clock record from normal numbers back into BCD. */
void clock_decimal_to_bcd(unsigned char *clock) {
    clock[7] = clock_decimal_to_bcd_byte(clock[7]);
    clock[6] = clock_decimal_to_bcd_byte(clock[6]);
    clock[5] = clock_decimal_to_bcd_byte(clock[5]);
    clock[3] = clock_decimal_to_bcd_byte(clock[3]);
    clock[2] = clock_decimal_to_bcd_byte(clock[2]);
    clock[1] = clock_decimal_to_bcd_byte(clock[1]);
}


/* rac1-decomp src/core/0012CC90.c: func_0012D5D0 */
/*
 * Tick the sceCdCLOCK at s (binary fields: [5] day, [6] month, [7] year)
 * forward by one day, with a working copy of the 12-byte month-length
 * table r1_D_00153D40 (February stretched to 29 when year & 3 == 0), the
 * month rolling 12 -> 1 and the year 99 -> 0.
 *
 * The leap test reads the year into an int. Retail loads the year twice
 * (for the leap test, and again at the year roll-over); 2.9-ee's GCSE
 * would reuse a first byte-typed load for the second (SIZE 184/180, and
 * the whole reason this function once looked like 2.95.3 code). An int
 * load is a zero-extending load, a different expression to GCSE, so
 * the later byte load stays. (This C is exact under 2.95.3 as well.)
 */
/* Moves a clock date forward by one day, handling month length, leap years and year wrap. */
void clock_advance_day(unsigned char *s) {
    Cfg12 days;
    unsigned char m;
    int y = s[7];

    days = r1_D_00153D40;
    s[5] = s[5] + 1;
    if ((y & 3) == 0) {
        days.b[1] = 0x1D;
    }
    if (s[5] > days.b[s[6] - 1]) {
        s[5] = 1;
        s[6] = s[6] + 1;
        m = s[6];
        if (m == 13) {
            if (s[7] == 0x63) {
                s[7] = 0;
            } else {
                s[7] = s[7] + 1;
            }
            s[6] = 1;
        }
    }
}

/* rac1-decomp src/core/0012CC90.c: func_0012D688 */
/*
 * Tick the sceCdCLOCK at s back by one day: the same month-length table,
 * the day counting down to 0 rolls the month back (1 -> 12) and the year
 * with it (0 -> 99), then the day is reloaded from the table.
 *
 * Levers: the leap test on an int copy of the year, as in func_00131850
 * (2.9-ee's GCSE otherwise reuses the first year load: 61/164);
 * `s[5] = s[5] - 1;` before the leap block (a block boundary gives
 * retail's reload of s[5]); the month as `if (--s[6] == 0)` (stores the
 * raw decrement and tests the masked copy in another register); the
 * year as an if/else with one store per arm, which cross-jumping merges
 * into retail's single `sb`. Exact under both compilers.
 */
/* Moves a clock date back by one day, handling month length, leap years and year wrap. */
void clock_rewind_day(unsigned char *s) {
    Cfg12 days;
    int y = s[7];

    days = r1_D_00153D40;
    s[5] = s[5] - 1;
    if ((y & 3) == 0) {
        days.b[1] = 0x1D;
    }
    if (s[5] == 0) {
        if (--s[6] == 0) {
            if (s[7] == 0) {
                s[7] = 0x63;
            } else {
                s[7] = s[7] - 1;
            }
            s[6] = 0xC;
        }
        s[5] = days.b[s[6] - 1];
    }
}

/* rac1-decomp src/core/0012CC90.c: func_0012D730 */
/*
 * Advance the hour ([3]); at 24 it wraps to 0 and the day ticks forward.
 * Retail's call is a bare tail `j func_00131850` on the wrap path only,
 * with a plain `jr $ra` on the other: a conditional sibling call, which
 * 2.9-ee emits from this plain C. (Under 2.95.3, which has no sibling
 * calls, it was 8 bytes over.)
 */
/* Moves a clock forward by one hour, and by one day when it passes midnight. */
void clock_advance_hour(unsigned char *s) {
    s[3] = s[3] + 1;
    if (s[3] == 0x18) {
        s[3] = 0;
        clock_advance_day(s);
    }
}

/* rac1-decomp src/core/0012CC90.c: func_0012D760 */
/* The backward analog: the hour counts down, and at 0 it becomes 23 and
   the day ticks back, again through a conditional tail call. */
/* Moves a clock back by one hour, and by one day when it passes midnight. */
void clock_rewind_hour(unsigned char *s) {
    unsigned char v = s[3];
    if (v != 0) {
        s[3] = v - 1;
        return;
    }
    s[3] = 0x17;
    clock_rewind_day(s);
}

extern void clock_advance_hour(unsigned char *);
extern void clock_rewind_hour(unsigned char *);

/* Moves a clock forward or back by a number of minutes. */
void clock_add_minutes(unsigned char *clock, int offset) {
    int minutes;
    clock_bcd_to_decimal(clock);
    minutes = clock[2] + offset;
    if (minutes >= 0) {
        while (minutes > 60) {
            clock_advance_hour(clock);
            minutes -= 60;
        }
    } else {
        do {
            minutes += 60;
            clock_rewind_hour(clock);
        } while (minutes < 0);
    }
    clock[2] = minutes;
    clock_decimal_to_bcd(clock);
}

extern int console_get_model_id(void);
extern int console_get_info_flag(void);
extern void clock_add_minutes(unsigned char *, int);

/* Converts a clock to local time by adding the console time zone and summer time offset. */
void clock_to_local_time(unsigned char *clock) {
    int offset;
    int zone = console_get_model_id();
    offset = console_get_info_flag();
    offset *= 60;
    offset -= 540;
    clock_add_minutes(clock, zone + offset);
}

ASM_FUNC("asm/core", func_00131AE8);

/* The exit thunk of symbol_addrs: eight bytes that jump to exit with $4
   forced to 0 in the delay slot, so the status the caller passes is discarded
   and the program always exits with 0. The call is a tail call, and the
   compiler puts the argument in the jump's delay slot. */
extern void exit_program(int);

/* Exits the program and always reports status 0. */
void exit_ignoring_status(int ignored_status) {
    exit_program(0);
}

/* Original assembly: `addiu $v1,$zero,0x23; syscall`, a thread-exit stub whose address crt0 passes to the thread syscall; the compiler cannot emit syscall. */
ASM_FUNC("asm/core", func_00131CB0);

/* func_00131D98 is defined in 00131D98.c. */

/* func_00131DE8 is defined in 00131DE8.c (game compiler). */

/* func_00132028 is in its own -g8 unit. */

/* func_00132318 and func_001326D8 are in 00132318-g8.c. */

/* func_001325E0 is defined in 00131780-g8.c. */


/* Sends a sound command (id 6) with one value. */
void snd_send_cmd6(int value) {
    int payload[4];
    payload[0] = value;
    snd_queue_command(6, 4, (int)payload, 0, 0);
}

/* Sends a sound command (id 9) with two values. */
void snd_send_cmd9(int first, int second) {
    int payload[4];
    payload[0] = first;
    payload[1] = second;
    snd_queue_command(9, 8, (int)payload, 0, 0);
}

typedef struct { char bytes[24]; } CommandParameters24;

/* Sends a sound command (id 96) with a value and an optional block of settings. */
void snd_send_cmd96_with_settings(int value, const CommandParameters24 *parameters) {
    struct {
        int value;
        CommandParameters24 parameters;
    } payload;
    payload.value = value;
    if (parameters != 0)
        payload.parameters = *parameters;
    else
        *(int *)&payload.parameters = -1;
    snd_queue_command(96, 28, (int)&payload, 0, 0);
}

/* Sends a sound command (id 11) with one value. */
void snd_send_cmd11_one_value(int value) {
    int payload[4];
    payload[0] = value;
    snd_queue_command(11, 4, (int)payload, 0, 0);
}


/* Sends a sound command (id 78) with three values. */
void snd_send_cmd78(int first, int second, int third) {
    int payload[4];
    payload[0] = first;
    payload[1] = second;
    payload[2] = third;
    snd_queue_command(78, 12, (int)payload, 0, 0);
}




/* Sends a sound command (id 22) with one value. */
void snd_send_cmd22(int value) {
    int payload[4];
    payload[0] = value;
    snd_queue_command(22, 4, (int)payload, 0, 0);
}

/* Sends a sound command (id 23) with one value. */
void snd_send_cmd23(int param_1) {
  int auStack_20[4];

  auStack_20[0] = param_1;
  snd_queue_command(0x17, 4, (int)auStack_20, 0, 0);
  return;
}

/* Sends a sound command (id 25) with one value and two extra settings. */
void snd_send_cmd25_with_settings(int value, long fourth, int fifth) {
    int payload[4];
    payload[0] = value;
    snd_queue_command(25, 4, (int)payload, fourth, fifth);
}



/* func_00132C48 is in its own -g8 unit. */

/* func_00132DF0 is defined in 00132DF0-g8.c. */


/* rac1-decomp src/core/989snd.c: func_0012EC30 */
/* snd_UnkFunction_0012eaf0 */
/* Sets the sound current buffer flag to 1. */
void snd_set_current_buffer_flag(void) {
    *(int *)&r1_D_0015EDC4 = 1;
}




/* Sends a sound command (id 46) with one value. */
void snd_send_cmd46(int value) {
    int payload[4];
    payload[0] = value;
    snd_queue_command(46, 4, (int)payload, 0, 0);
}

/* Sends a sound command (id 50) with one value and two extra settings. */
void snd_send_cmd50_with_settings(int value, long fourth, int fifth) {
    int payload[4];
    payload[0] = value;
    snd_queue_command(50, 4, (int)payload, fourth, fifth);
}

/* Sends a sound command (id 79) with one value and two extra settings. */
void snd_send_cmd79_with_settings(int value, long fourth, int fifth) {
    int payload[4];
    payload[0] = value;
    snd_queue_command(79, 4, (int)payload, fourth, fifth);
}
