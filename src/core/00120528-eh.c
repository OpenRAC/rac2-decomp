/* libgcc _eh.o: __sjthrow, __sjpopnthrow and __eh_rtime_match, which follow each other
   in retail (the catalogue sees the three as one function), from the L_eh section of
   GCC's libgcc2.c, carried from rac3-decomp's src/boot_elf/core/libgcc/_eh.c
   (func_001269B0), the same instructions there. Built with -fexceptions, as libgcc
   builds _eh.o, and with inhibit_libc (no fprintf). __terminate is func_00120368,
   __get_eh_info func_00120448 and get_eh_context the pointer D_00135D38 (00120390.c).
   GPL-2.0-or-later with the libgcc linking exception below. No proprietary SDK source
   is used. */
/* More subroutines needed by GCC output code on some machines.  */
/* Compile this one with gcc.  */
/* Copyright (C) 1989, 92-98, 1999 Free Software Foundation, Inc.

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/* As a special exception, if you link this library with other files,
   some of which are compiled with GCC, to produce an executable,
   this library does not by itself cause the resulting executable
   to be covered by the GNU General Public License.
   This exception does not however invalidate any other reasons why
   the executable file might be covered by the GNU General Public License.  */

#define NULL ((void *) 0)
#define inhibit_libc

#define __terminate func_00120368
#define __get_eh_info func_00120448
#define __sjthrow func_00120528
#define get_eh_context D_00135D38

struct eh_context
{
  void *handler_label;
  void **dynamic_handler_chain;
  void *info;
  void *table_index;
};

typedef void * (*__eh_matcher) (void *, void *, void *);

typedef struct __eh_info
{
  __eh_matcher match_function;
  short language;
  short version;
} __eh_info;

extern void __terminate (void);
extern void **__get_eh_info (void);
extern struct eh_context *(*get_eh_context) (void);

/* This is used to throw an exception when the setjmp/longjmp codegen
   method is used for exception handling.

   We call __terminate if there are no handlers left.  Otherwise we run the
   cleanup actions off the dynamic cleanup stack, and pop the top of the
   dynamic handler chain, and use longjmp to transfer back to the associated
   handler.  */

extern void __sjthrow (void) __attribute__ ((__noreturn__));

/* Throws an exception by running cleanups, then jumping to the next handler, or stops if none is left. */
void
func_00120528 ()
{
  struct eh_context *eh = (*get_eh_context) ();
  void ***dhc = &eh->dynamic_handler_chain;
  void *jmpbuf;
  void (*func)(void *, int);
  void *arg;
  void ***cleanup;

  /* The cleanup chain is one word into the buffer.  Get the cleanup
     chain.  */
  cleanup = (void***)&(*dhc)[1];

  /* If there are any cleanups in the chain, run them now.  */
  if (cleanup[0])
    {
      double store[200];
      void **buf = (void**)store;
      buf[1] = 0;
      buf[0] = (*dhc);

      /* try { */
#ifdef DONT_USE_BUILTIN_SETJMP
      if (! setjmp (&buf[2]))
#else
      if (! __builtin_setjmp (&buf[2]))
#endif
	{
	  *dhc = buf;
	  while (cleanup[0])
	    {
	      func = (void(*)(void*, int))cleanup[0][1];
	      arg = (void*)cleanup[0][2];

	      /* Update this before running the cleanup.  */
	      cleanup[0] = (void **)cleanup[0][0];

	      (*func)(arg, 2);
	    }
	  *dhc = buf[0];
	}
      /* catch (...) */
      else
	{
	  __terminate ();
	}
    }
  
  /* We must call terminate if we try and rethrow an exception, when
     there is no exception currently active and when there are no
     handlers left.  */
  if (! eh->info || (*dhc)[0] == 0)
    __terminate ();
    
  /* Find the jmpbuf associated with the top element of the dynamic
     handler chain.  The jumpbuf starts two words into the buffer.  */
  jmpbuf = &(*dhc)[2];

  /* Then we pop the top element off the dynamic handler chain.  */
  *dhc = (void**)(*dhc)[0];

  /* And then we jump to the handler.  */

#ifdef DONT_USE_BUILTIN_SETJMP
  longjmp (jmpbuf, 1);
#else
  __builtin_longjmp (jmpbuf, 1);
#endif
}

/* Run cleanups on the dynamic cleanup stack for the current dynamic
   handler, then pop the handler off the dynamic handler stack, and
   then throw.  This is used to skip the first handler, and transfer
   control to the next handler in the dynamic handler stack.  */

extern void __sjpopnthrow (void) __attribute__ ((__noreturn__));

/* Runs cleanups, removes the top handler and throws again. */
__attribute__ ((section (".text.func_00120528"))) void
__sjpopnthrow ()
{
  struct eh_context *eh = (*get_eh_context) ();
  void ***dhc = &eh->dynamic_handler_chain;
  void (*func)(void *, int);
  void *arg;
  void ***cleanup;

  /* The cleanup chain is one word into the buffer.  Get the cleanup
     chain.  */
  cleanup = (void***)&(*dhc)[1];

  /* If there are any cleanups in the chain, run them now.  */
  if (cleanup[0])
    {
      double store[200];
      void **buf = (void**)store;
      buf[1] = 0;
      buf[0] = (*dhc);

      /* try { */
#ifdef DONT_USE_BUILTIN_SETJMP
      if (! setjmp (&buf[2]))
#else
      if (! __builtin_setjmp (&buf[2]))
#endif
	{
	  *dhc = buf;
	  while (cleanup[0])
	    {
	      func = (void(*)(void*, int))cleanup[0][1];
	      arg = (void*)cleanup[0][2];

	      /* Update this before running the cleanup.  */
	      cleanup[0] = (void **)cleanup[0][0];

	      (*func)(arg, 2);
	    }
	  *dhc = buf[0];
	}
      /* catch (...) */
      else
	{
	  __terminate ();
	}
    }

  /* Then we pop the top element off the dynamic handler chain.  */
  *dhc = (void**)(*dhc)[0];

  __sjthrow ();
}

/* Support code for all exception region-based exception handling.  */

/* Asks the type matcher whether the thrown exception fits the given type. */
__attribute__ ((section (".text.func_00120528"))) int
__eh_rtime_match (void *rtime)
{
  void *info;
  __eh_matcher matcher;
  void *ret;

  info = *(__get_eh_info ());
  matcher = ((__eh_info *)info)->match_function;
  if (! matcher)
    {
#ifndef inhibit_libc
      fprintf (stderr, "Internal Compiler Bug: No runtime type matcher.");
#endif
      return 0;
    }
  ret = (*matcher) (info, rtime, (void *)0);
  return (ret != NULL);
}
