/* libgcc _eh.o: find_exception_handler, from the L_eh section of GCC's libgcc2.c,
   carried from rac3-decomp's src/boot_elf/core/libgcc/_eh.c (func_00126D70), the same
   instructions there. The types are eh-common.h's. Built with -fexceptions, as libgcc
   builds _eh.o. GPL-2.0-or-later with the libgcc linking exception below. No
   proprietary SDK source is used. */
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

typedef struct exception_table
{
  void *start_region;
  void *end_region;
  void *exception_handler;
  void *match_info;              /* runtime type info */
} exception_table;

typedef struct exception_lang_info
{
  short language;
  short version;
} exception_lang_info;

typedef struct exception_descriptor
{
  void *runtime_id_field;
  exception_lang_info lang;
  exception_table table[1];
} exception_descriptor;

typedef void * (*__eh_matcher) (void *, void *, void *);

typedef struct __eh_info
{
  __eh_matcher match_function;
  short language;
  short version;
} __eh_info;

/* find_exception_handler finds the correct handler, if there is one, to
   handle an exception.
   returns a pointer to the handler which controlled should be transferred
   to, or NULL if there is nothing left.
   Parameters:
   PC - pc where the exception originates. If this is a rethrow, 
        then this starts out as a pointer to the exception table
	entry we wish to rethrow out of.
   TABLE - exception table for the current module.
   EH_INFO - eh info pointer for this exception.
   RETHROW - 1 if this is a rethrow. (see incoming value of PC).
   CLEANUP - returned flag indicating whether this is a cleanup handler.
*/
/* Looks up the exception handler that covers a code address and says whether it is only a cleanup. */
void * func_001208E8 (void *pc, exception_descriptor *table, 
                        __eh_info *eh_info, int rethrow, int *cleanup)
{

  void *retval = NULL;
  *cleanup = 1;
  if (table)
    {
      int pos = 0;
      /* The new model assumed the table is sorted inner-most out so the
         first region we find which matches is the correct one */

      exception_table *tab = &(table->table[0]);

      /* Subtract 1 from the PC to avoid hitting the next region */
      if (rethrow) 
        {
          /* pc is actually the region table entry to rethrow out of */
          pos = ((exception_table *) pc) - tab;
          pc = ((exception_table *) pc)->end_region - 1;

          /* The label is always on the LAST handler entry for a region, 
             so we know the next entry is a different region, even if the
             addresses are the same. Make sure its not end of table tho. */
          if (tab[pos].start_region != (void *) -1)
            pos++;
        }
      else
        pc--;
      
      /* We can't do a binary search because the table is in inner-most
         to outermost address ranges within functions */
      for ( ; tab[pos].start_region != (void *) -1; pos++)
        { 
          if (tab[pos].start_region <= pc && tab[pos].end_region > pc)
            {
              if (tab[pos].match_info)
                {
                  __eh_matcher matcher = eh_info->match_function;
                  /* match info but no matcher is NOT a match */
                  if (matcher) 
                    {
                      void *ret = (*matcher)((void *) eh_info, 
                                             tab[pos].match_info, table);
                      if (ret) 
                        {
                          if (retval == NULL)
                            retval = tab[pos].exception_handler;
                          *cleanup = 0;
                          break;
                        }
                    }
                }
              else
                {
                  if (retval == NULL)
                    retval = tab[pos].exception_handler;
                }
            }
        }
    }
  return retval;
}
