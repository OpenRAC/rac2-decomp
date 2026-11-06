/* Authored controls for the optional width-ordered quad-slot saves; no game code. */
extern int call(int);

/* Control: $s0 and $ra are both saved at the slot's full width, so $ra stays on top.
   It comes first: register_precision changes the save mode for the rest of the unit. */
int same_width(int x)
{
    return call(x) + x;
}

/* $ra is narrowed to 64 bits: with the option its save goes below the $s0 save. */
int narrow_ra(int x) __attribute__((register_precision(ra, 64)));
int narrow_ra(int x)
{
    return call(x) + x;
}
