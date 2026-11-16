#include "include_asm.h"
#include "names.h"

extern int func_00115544(const char *, const char *);

/* Returns the given value if two strings match, otherwise zero. */
void *str_select_if_equal(const char *first, const char *second, void *value) {
    return func_00115544(first, second) ? 0 : value;
}
/* Does nothing. */
void empty_function(void) {
}

extern void *malloc(unsigned int);
extern void *memset(unsigned char *, int, int);
extern void call_terminate_handler(void);

/* Allocates and clears a new 24-byte record for exception handling. */
char *eh_alloc_context(void) {
    char *record = malloc(24);
    if (record == 0) call_terminate_handler();
    memset((unsigned char *)record, 0, 24);
    *(char **)(record + 4) = record + 16;
    return record;
}

extern char *(*g_eh_context_getter)(void);

/* Returns the current exception state record. */
char *eh_get_context(void) {
    return g_eh_context_getter();
}

/* Returns the exception type information part of the current exception state. */
char *func_00120448(void) {
    return g_eh_context_getter() + 8;
}

extern char *eh_get_static_context(void);

/* Switches to the fallback exception state getter and returns the state. */
char *eh_set_default_context_getter(void) {
    g_eh_context_getter = eh_get_static_context;
    return g_eh_context_getter();
}

extern int g_eh_static_context_init;
extern char g_eh_static_context[];
extern char g_eh_static_context_data[];

/* Returns the single shared exception state record, setting it up on first use. */
char *eh_get_static_context(void) {
    if (g_eh_static_context_init == 0) {
        g_eh_static_context_init = 1;
        memset((unsigned char *)g_eh_static_context, 0, 16);
        *(char **)(g_eh_static_context + 4) = g_eh_static_context_data;
    }
    return g_eh_static_context;
}

/* Returns the handler-chain part of the current exception state. */
char *eh_get_handler_chain(void) {
    return g_eh_context_getter() + 4;
}

/* Reads one small field from an exception record. */
int eh_get_record_field3(short *record) {
    return record[3];
}

/* Reads another small field from an exception record. */
int eh_get_record_field2(short *record) {
    return record[2];
}



extern void *eh_get_saved_register_addr(int, void *, int);
extern void *func_001153D4(void *, const void *, unsigned int);

/* Copies one saved register slot from one stack frame record to another. */
void *eh_copy_saved_register(int index, void *source, void *destination) {
    void *from = eh_get_saved_register_addr(index, source, 0);
    void *to = eh_get_saved_register_addr(index, destination, 0);
    unsigned int size = index < 31 ? 16 : index <= 63 ? 4 : 8;
    return func_001153D4(to, from, size);
}

/* Does nothing; a hook that runs when only cleanup handlers are left. */
void eh_unwinding_cleanup(void)
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

extern void call_terminate_handler(void);
extern void eh_unwinding_cleanup(void);
extern void *eh_find_handler(void *, void *, void *, int, int *);
extern void *eh_find_old_handler(void *, void *);
extern frame_state *eh_next_stack_level(void *, frame_state *, frame_state *);

/* Walks up the call stack looking for the code that handles a thrown exception and prepares to jump to it. */
void *eh_throw_helper(struct eh_context *eh, void *pc, frame_state *my_udata,
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
      udata = eh_next_stack_level (pc, udata, sub_udata);
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
          handler = eh_find_handler (eh->table_index, udata->eh_ptr,
                                   eh_info, 1, &cleanup);
          eh->table_index = (void *)0;
        }
      else
        if (new_eh_model)
          handler = eh_find_handler (pc, udata->eh_ptr, eh_info,
                                   0, &cleanup);
        else
          handler = eh_find_old_handler (pc, udata->eh_ptr);

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
        s64 value = *(s64 *)eh_get_saved_register_addr (udata->retaddr_column, udata,
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
        eh_unwinding_cleanup ();
    }

  /* If we haven't found a handler by now, this is an unhandled
     exception.  */
  if (! handler)
    call_terminate_handler ();

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
	  udata = eh_next_stack_level (pc, udata, sub_udata);
	  sub_udata = p;

	  for (i = 0; i < FIRST_PSEUDO_REGISTER; ++i)
	    if (i != udata->retaddr_column && udata->saved[i])
	      eh_copy_saved_register (i, udata, my_udata);

	  {
	    s64 value = *(s64 *)eh_get_saved_register_addr (udata->retaddr_column, udata,
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

