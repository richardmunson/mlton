(* Copyright (C) 2002-2007 Henry Cejtin, Matthew Fluet, Suresh
 *    Jagannathan, and Stephen Weeks.
 *
 * MLton is released under a HPND-style license.
 * See the file MLton-LICENSE for details.
 *)

signature MLTON_INT_INF =
   sig
      type t

      val areSmall: t * t -> bool
      val ceilDiv: t * t -> t
      val ceilDivMod: t * t -> t * t
      val ceilMod: t * t -> t
      val gcd: t * t -> t
      val isSmall: t -> bool

      structure BigWord : WORD
      structure SmallInt : INTEGER
      datatype rep =
         Big of BigWord.word vector
       | Small of SmallInt.int
      val rep: t -> rep
      val fromRep: rep -> t option
   end
