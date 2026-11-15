#include "include_asm.h"
#include "names.h"

extern int func_00115544(const char *, const char *);

/* Returns the given value if two strings match, otherwise zero. */
void *func_00120390(const char *first, const char *second, void *value) {
    return strcmp_00115544(first, second) ? 0 : value;
}
/* Does nothing. */
void func_001203C0(void) {
}

extern void *func_00115F28(unsigned int);
extern int func_00115484(unsigned char *, int, int);
extern void func_00120368(void);

/* Allocates and clears a new 24-byte record for exception handling. */
char *func_001203C8(void) {
    char *record = Malloc(24);
    if (record == 0) CallTerminateHandler();
    memset((unsigned char *)record, 0, 24);
    *(char **)(record + 4) = record + 16;
    return record;
}

extern char *(*D_00135D38)(void);

/* Returns the current exception state record. */
char *func_00120420(void) {
    return D_00135D38();
}

/* Returns the exception type information part of the current exception state. */
char *func_00120448(void) {
    return D_00135D38() + 8;
}

extern char *func_00120498(void);

/* Switches to the fallback exception state getter and returns the state. */
char *func_00120470(void) {
    D_00135D38 = GetStaticExceptionContext;
    return D_00135D38();
}

extern int D_00141800;
extern char D_001417F0[];
extern char D_00141808[];

/* Returns the single shared exception state record, setting it up on first use. */
char *func_00120498(void) {
    if (D_00141800 == 0) {
        D_00141800 = 1;
        memset((unsigned char *)D_001417F0, 0, 16);
        *(char **)(D_001417F0 + 4) = D_00141808;
    }
    return D_001417F0;
}

/* Returns the handler-chain part of the current exception state. */
char *func_00120500(void) {
    return D_00135D38() + 4;
}

/* Reads one small field from an exception record. */
int func_00120800(short *record) {
    return record[3];
}

/* Reads another small field from an exception record. */
int func_00120808(short *record) {
    return record[2];
}



extern void *func_00120A30(int, void *, int);
extern void *func_001153D4(void *, const void *, unsigned int);

/* Copies one saved register slot from one stack frame record to another. */
void *func_00120AB8(int index, void *source, void *destination) {
    void *from = GetSavedRegisterAddress(index, source, 0);
    void *to = GetSavedRegisterAddress(index, destination, 0);
    unsigned int size = index < 31 ? 16 : index <= 63 ? 4 : 8;
    return memcpy_001153D4(to, from, size);
}

/* Does nothing; a hook that runs when only cleanup handlers are left. */
void func_00120BC8(void)
{
}

/* libgcc _eh.o: throw_helper, the common grunt work of a throw, from the
   L_eh section of GCC's libgcc2.c (GPL version 2-or-later with the libgcc
   linking exception; the source is the public archive the qualified
   compiler is built from, gnu-ee-binutils-gcc-1.1, gcc/libgcc2.c). Its
   neighbours in the same object are in this file: func_001203C0 is
   __empty, func_00120368 is __terminate, func_00120BC8 is
   __unwinding_cleanup, and next_stack_level, get_reg_addr, copy_reg,
   find_exception_handler and old_find_exception_handler live in
   src/core/00120B38.c, src/core/00120A30.c (with func_00120AB8 here),
   src/core/001208E8.c and src/core/00120810.c.

   `frame_state` is frame.h's with FIRST_PSEUDO_REGISTER 79 (the archive's
   own config/mips/mips.h) and the 64-bit `long` of this ABI: 0x2F0 bytes,
   the block move both `saved_ustruct = *udata` and `memcpy (udata,
   my_udata, sizeof (*udata))` expand at +0x104 and +0x204.
   in_reg_window is the file's `return 0` variant (no INCOMING_REGNO on
   this target), so its two guards fold away and leave no code. */

typedef signed long long s64;

#define FIRST_PSEUDO_REGISTER 79

typedef struct frame_state
{
  void *cfa;
  void *eh_ptr;
  long cfa_offset;
  long args_size;
  long reg_or_offset[FIRST_PSEUDO_REGISTER+1];
  unsigned short cfa_reg;
  unsigned short retaddr_column;
  char saved[FIRST_PSEUDO_REGISTER+1];
} frame_state;

struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};

typedef struct exception_descriptor
{
  void *runtime_id_field;
} exception_descriptor;

#define NEW_EH_RUNTIME ((void *) -2)

#define REG_SAVED_REG 2

extern void func_00120368(void);
extern void func_00120BC8(void);
extern void *func_001208E8(void *, void *, void *, int, int *);
extern void *func_00120810(void *, void *);
extern frame_state *func_00120B38(void *, frame_state *, frame_state *);

/* Walks up the call stack looking for the code that handles a thrown exception and prepares to jump to it. */
void *func_00120BD0(struct eh_context *eh, void *pc, frame_state *my_udata,
		    frame_state **udata_p)
{
  frame_state *udata = *udata_p;
  frame_state ustruct;
  frame_state *sub_udata = &ustruct;
  void *saved_pc = pc;
  void *handler;
  void *handler_p;
  void *pc_p;
  frame_state saved_ustruct;
  int new_eh_model;
  int cleanup = 0;
  int only_cleanup = 0;
  int rethrow = 0;
  int saved_state = 0;
  void *eh_info = eh->info;

  /* Do we find a handler based on a re-throw PC? */
  if (eh->table_index != (void *) 0)
    rethrow = 1;

  handler = (void *) 0;
  for (;;)
    {
      frame_state *p = udata;
      udata = NextStackLevel (pc, udata, sub_udata);
      sub_udata = p;

      /* If we couldn't find the next frame, we lose.  */
      if (! udata)
	break;

      if (udata->eh_ptr == 0)
        new_eh_model = 0;
      else
        new_eh_model = (((exception_descriptor *)(udata->eh_ptr))->
                                          runtime_id_field == NEW_EH_RUNTIME);

      if (rethrow)
        {
          rethrow = 0;
          handler = FindExceptionHandler (eh->table_index, udata->eh_ptr,
                                   eh_info, 1, &cleanup);
          eh->table_index = (void *)0;
        }
      else
        if (new_eh_model)
          handler = FindExceptionHandler (pc, udata->eh_ptr, eh_info,
                                   0, &cleanup);
        else
          handler = FindOldExceptionHandler (pc, udata->eh_ptr);

      /* If we found one, we can stop searching, if its not a cleanup.
         for cleanups, we save the state, and keep looking. This allows
         us to call a debug hook if there are nothing but cleanups left. */
      if (handler)
	if (cleanup)
	  {
	    if (!saved_state)
	      {
		saved_ustruct = *udata;
		handler_p = handler;
		pc_p = pc;
		saved_state = 1;
		only_cleanup = 1;
	      }
	  }
	else
	  {
	    only_cleanup = 0;
	    break;
	  }

      /* Otherwise, we continue searching.  We subtract 1 from PC to avoid
	 hitting the beginning of the next region.  */
      {
        s64 value = *(s64 *)GetSavedRegisterAddress (udata->retaddr_column, udata,
					    (int)sub_udata);
        pc = (void *)((int)value - 1);
      }
    }

  if (saved_state)
    {
      udata = &saved_ustruct;
      handler = handler_p;
      pc = pc_p;
      if (only_cleanup)
        UnwindingCleanup ();
    }

  /* If we haven't found a handler by now, this is an unhandled
     exception.  */
  if (! handler)
    CallTerminateHandler ();

  eh->handler_label = handler;

  if (pc == saved_pc)
    /* We found a handler in the throw context, no need to unwind.  */
    udata = my_udata;
  else
    {
      int i;

      /* Unwind all the frames between this one and the handler by copying
	 their saved register values into our register save slots.  */

      /* Remember the PC where we found the handler.  */
      void *handler_pc = pc;

      /* Start from the throw context again.  */
      pc = saved_pc;
      memcpy (udata, my_udata, sizeof (*udata));

      while (pc != handler_pc)
	{
	  frame_state *p = udata;
	  udata = NextStackLevel (pc, udata, sub_udata);
	  sub_udata = p;

	  for (i = 0; i < FIRST_PSEUDO_REGISTER; ++i)
	    if (i != udata->retaddr_column && udata->saved[i])
	      CopySavedRegister (i, udata, my_udata);

	  {
	    s64 value = *(s64 *)GetSavedRegisterAddress (udata->retaddr_column, udata,
						(int)sub_udata);
	    pc = (void *)((int)value - 1);
	  }
	}

      /* But we do need to update the saved return address register from
	 the last frame we unwind, or the handler frame will have the wrong
	 return address.  */
      if (udata->saved[udata->retaddr_column] == REG_SAVED_REG)
	{
	  i = udata->reg_or_offset[udata->retaddr_column];
	}
    }
  /* udata now refers to the frame called by the handler frame.  */

  *udata_p = udata;
  return handler;
}

/* func_00120F00 lives in 00120F00-unwind.c. */

/* func_001210E0 lives in 001210E0-unwind.c. */

