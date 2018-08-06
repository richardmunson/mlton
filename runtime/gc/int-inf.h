/* Copyright (C) 2012,2014 Matthew Fluet.
 * Copyright (C) 1999-2008 Henry Cejtin, Matthew Fluet, Suresh
 *    Jagannathan, and Stephen Weeks.
 * Copyright (C) 1997-2000 NEC Research Institute.
 *
 * MLton is released under a HPND-style license.
 * See the file MLton-LICENSE for details.
 */

#if (defined (MLTON_GC_INTERNAL_TYPES))

/* Layout of intInfs.  
 * Note, the value passed around is a pointer to the obj member.
 */
struct GC_intInf_obj {
  mp_limb_t isneg;
  mp_limb_t limbs[1];
};
typedef struct GC_intInf {
  GC_sequenceCounter counter;
  GC_sequenceLength length;
  GC_header header;
  struct GC_intInf_obj obj;
} __attribute__ ((packed)) *GC_intInf;

// assertions for intInf types
COMPILE_TIME_ASSERT(GC_intInf__obj_packed,
                    offsetof(struct GC_intInf, obj) ==
                    sizeof(GC_sequenceCounter)
                    + sizeof(GC_sequenceLength)
                    + sizeof(GC_header));
COMPILE_TIME_ASSERT(GC_intInf_obj__isneg_packed,
                    offsetof(struct GC_intInf_obj, isneg) ==
                    0);
COMPILE_TIME_ASSERT(GC_intInf_obj__limbs_packed,
                    offsetof(struct GC_intInf_obj, limbs) ==
                    0 + sizeof(mp_limb_t));

#endif /* (defined (MLTON_GC_INTERNAL_TYPES)) */

#if (defined (MLTON_GC_INTERNAL_FUNCS))

COMPILE_TIME_ASSERT(sizeof_mp_limb_t__is_four_or_eight, 
                    (sizeof(mp_limb_t) == 4 || sizeof(mp_limb_t) == 8));
#define GC_INTINF_HEADER ( \
        CHAR_BIT * sizeof(mp_limb_t) == 32 ? \
        GC_WORD32_VECTOR_HEADER : ( \
        CHAR_BIT * sizeof(mp_limb_t) == 64 ? \
        GC_WORD64_VECTOR_HEADER : ( 0 ) ) )

COMPILE_TIME_ASSERT(sizeof_mp_limb_t__compat__sizeof_objptr,
                    sizeof(objptr) <= sizeof(mp_limb_t) ?
                    sizeof(mp_limb_t) % sizeof(objptr) == 0 :
                    sizeof(objptr) % sizeof(mp_limb_t) == 0);

#define LIMBS_PER_OBJPTR ( \
        sizeof(mp_limb_t) >= sizeof(objptr) ? \
        1 : (int)(sizeof(objptr) / sizeof(mp_limb_t)))

PRIVATE void initIntInf (GC_state s);

static inline int intInf_limbsInternal (GC_state s, objptr arg);
static inline void fillIntInfArg (GC_state s, objptr arg, __mpz_struct *res, 
                                  mp_limb_t space[LIMBS_PER_OBJPTR + 1]);
static inline void initIntInfRes (GC_state s, __mpz_struct *res, size_t bytes);
static inline GC_objptr_sequence initIntInfRes_2 (GC_state s,
                                                  __mpz_struct *lres, __mpz_struct *rres,
                                                  // total bytes needed by all args
                                                  // kept separately from other sizes for assertion
                                                  size_t tot_bytes,
                                                  size_t l_bytes);
static inline objptr finiIntInfRes (GC_state s, __mpz_struct *res, size_t bytes);
static inline objptr finiIntInfRes_2 (GC_state s,
                                      __mpz_struct *l_res, __mpz_struct *r_res,
                                      size_t l_bytes, size_t r_bytes,
                                      GC_objptr_sequence finals);

#endif /* (defined (MLTON_GC_INTERNAL_FUNCS)) */

#if (defined (MLTON_GC_INTERNAL_BASIS))

PRIVATE objptr IntInf_binop (GC_state s, objptr lhs, objptr rhs, size_t bytes,
                             void(*binop)(__mpz_struct *resmpz,
                                          const __mpz_struct *lhsspace,
                                          const __mpz_struct *rhsspace));

PRIVATE objptr IntInf_binop_2 (GC_state s,
                                objptr lhs, objptr rhs,
                                size_t tot_bytes,
                                void(*result_limbs)(int left_arg_limbs,
                                                    int right_arg_limbs,
                                                    int *left_result_limbs,
                                                    int *right_result_limbs),
                                void(*binop)(__mpz_struct *l_res_mpz,
                                             __mpz_struct *r_res_mpz,
                                             const __mpz_struct *lhsspace,
                                             const __mpz_struct *rhsspace));
PRIVATE objptr IntInf_unop (GC_state s, objptr arg, size_t bytes,
                            void(*unop)(__mpz_struct *resmpz,
                                        const __mpz_struct *argspace));
PRIVATE objptr IntInf_shop (GC_state s, objptr arg, Word32_t shift, size_t bytes,
                            void(*shop)(__mpz_struct *resmpz,
                                        const __mpz_struct *argspace,
                                        unsigned long shift));
PRIVATE Int32_t IntInf_cmpop (GC_state s, objptr lhs, objptr rhs,
                              int(*cmpop)(const __mpz_struct *lhsspace,
                                          const __mpz_struct *rhsspace));
PRIVATE objptr IntInf_strop (GC_state s, objptr arg, Int32_t base, size_t bytes,
                             char*(*strop)(char *str,
                                           int base,
                                           const __mpz_struct *argspace));

/*
 * Functions that compute numbers of resulting limbs from passed in results
 * These are passed to operations that return multiple results and therefore
 * must be made visible to runtime/basis/IntInf/int-inf.c
 */
PRIVATE void nonCeilDRLimbs(int n_limbs, int d_limbs, int *r1_limbs, int *r2_limbs);
PRIVATE void ceilDRLimbs(int n_limbs, int d_limbs, int *r1_limbs, int *r2_limbs);

#endif /* (defined (MLTON_GC_INTERNAL_BASIS)) */
