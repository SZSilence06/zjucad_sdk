#ifndef ZJUCAD_VERS_COMP_PETSC_H_
#define ZJUCAD_VERS_COMP_PETSC_H_

//! use the latest interface

#ifndef PETSC_VERSION_GT
#define PETSC_VERSION_(MAJOR,MINOR,SUBMINOR) \
((PETSC_VERSION_MAJOR == (MAJOR)) && \
(PETSC_VERSION_MINOR == (MINOR)) && \
(PETSC_VERSION_SUBMINOR == (SUBMINOR)) && \
(PETSC_VERSION_RELEASE  == 1))

#define PETSC_VERSION_LT(MAJOR,MINOR,SUBMINOR) \
(PETSC_VERSION_RELEASE == 1 && \
(PETSC_VERSION_MAJOR < (MAJOR) || \
(PETSC_VERSION_MAJOR == (MAJOR) && \
(PETSC_VERSION_MINOR < (MINOR) || \
(PETSC_VERSION_MINOR == (MINOR) && \
(PETSC_VERSION_SUBMINOR < (SUBMINOR)))))))

#define PETSC_VERSION_LE(MAJOR,MINOR,SUBMINOR) \
(PETSC_VERSION_LT(MAJOR,MINOR,SUBMINOR) || \
PETSC_VERSION_(MAJOR,MINOR,SUBMINOR))

#define PETSC_VERSION_GT(MAJOR,MINOR,SUBMINOR) \
(!PETSC_VERSION_LE(MAJOR,MINOR,SUBMINOR))
#endif

#if PETSC_VERSION_GT(3, 1, 0)
#define vec_destroy(v) VecDestroy(v)
#define mat_destroy(m) MatDestroy(m)
#define KSP_destroy(k) KSPDestroy(k)
#else
#define vec_destroy(v) VecDestroy(*v)
#define mat_destroy(m) MatDestroy(*m)
#define KSP_destroy(k) KSPDestroy(*k)
#endif

#if PETSC_VERSION_GT(3, 2, 0)
#define vec_create_seq_with_array(comm, bs, n, a, v) \
  VecCreateSeqWithArray(comm, bs, n, a, v)
#else
#define vec_create_seq_with_array(comm, bs, n, a, v) \
  VecCreateSeqWithArray(comm, n, a, v)
#endif

#if PETSC_VERSION_LT(3, 5, 0)
#  define KSPSetOperators_SAME_PC(ksp, A, B) KSPSetOperators(ksp, A, B, SAME_PRECONDITIONER)
#else
#  define KSPSetOperators_SAME_PC(ksp, A, B) \
  KSPSetOperators(ksp, A, B); \
  KSPSetReusePreconditioner(ksp, PETSC_TRUE)
#endif

#endif
