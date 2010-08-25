\ doccall.fth 2.4 94/08/13
\ Copyright 1985-1990 Bradley Forthware

\ Shared code for ccall interface.  This file is used in conjunction with
\ ccall.fth.  The 2 files are separate because the code in this file must
\ be resident, while the code in ccall.fth can be transient.
\
\ do-ccall is a shared subroutine which is called from code generated by
\ "ccall".  The calling sequence looks like:
\
\     <code to transfer arguments from the stack to registers>
\     sethi  %hi(c_entry_point), %l0
\     call   do-ccall
\     or     %l0, %lo(c_entry_point), %l0
\     <code to push results, if any, on the stack>

label do-ccall		\ Subroutine address in %l0, return address in %o7

   sp   'user saved-sp   nput	\ Save for callbacks
   rp   'user saved-rp   nput	\ Save for callbacks

   %o7    %l1  move		\ Exchange %l0 and %o7
   %l0    %o7  move
   %l1    %l0  move

   \ Save the globals in case C changes them
   %g1    %l1  move
   %g2    %l2  move
   %g3    %l3  move
   %g4    %l4  move
   %g5    %l5  move
   %g6    %l6  move
   %o7 0  %o7  jmpl
   %g7    %l7  move	\ Delay slot

   \ Restore the globals
   %l1    %g1  move
   %l2    %g2  move
   %l3    %g3  move
   %l4    %g4  move
   %l5    %g5  move
   %l6    %g6  move
   %l0 8  %g0  jmpl	\ Return
   %l7    %g7  move
end-code
