/* Copyright (C) 2018 Matthew Fluet.
 * Copyright (C) 1999-2008 Henry Cejtin, Matthew Fluet, Suresh
 *    Jagannathan, and Stephen Weeks.
 * Copyright (C) 1997-2000 NEC Research Institute.
 *
 * MLton is released under a HPND-style license.
 * See the file MLton-LICENSE for details.
 */

#if (defined (MLTON_GC_INTERNAL_TYPES))

typedef struct GC_objptr_sequence {
  GC_sequenceCounter counter;
  GC_sequenceLength length;
  GC_header header;
  objptr objs[1];
} __attribute__ ((packed)) *GC_objptr_sequence;

// assertion for sequence type
COMPILE_TIME_ASSERT(GC_objptr_sequence__obj_packed,
                    offsetof(struct GC_objptr_sequence, objs) == GC_SEQUENCE_METADATA_SIZE);

#endif // (defined (MLTON_GC_INTERNAL_TYPES))

#if (defined (MLTON_GC_INTERNAL_FUNCS))

static inline GC_objptr_sequence allocate_objptr_seq (GC_state s, GC_header h, GC_sequenceLength argct);

#endif // (defined (MLTON_GC_INTERNAL_FUNCS))