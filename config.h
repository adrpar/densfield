/* config.h generated from config.h.in by configure */

// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.

#ifndef CONFIG_H
#define CONFIG_H


/*--- Code Features (to be adjusted by the configure script) ------------*/
#undef WITH_OPENMP
#undef WITH_MAPPING_SPH
#undef WITH_MAPPING_CIC
#define ENABLE_FORTRAN_RECORDS 1
#undef ENABLE_DOUBLE
#undef ENABLE_DEBUG


/*--- Constants (to be set by the configure script) ---------------------*/
#define NDIM                  3
#define MAXBASESIZE           55
#define SPHKERNELSIZESMALL    3
#define SPHKERNELSIZEMEDIUM   7
#define SPHKERNELSIZEBIG      15
#define SPHKERNEL_SUBSAMPLING 8
#undef GRID_UNDEFINED_VALUE


/*--- Consequences of the Code Features (do NOT change) -----------------*/
#ifdef ENABLE_DEBUG
#  undef NDEBUG
#  define DEBUG
#  define XMEM_TRACK_MEM
#else
#  define NDEBUG
#  undef DEBUG
#  undef XMEM_TRACK_MEM
#endif

#if (defined _OPENMP & !defined WITH_OPENMP)
#  error Please reconfigure using --with-openmp.
#endif
#ifdef WITH_OPENMP
#  ifndef _OPENMP
#    undef WITH_OPENMP
#  endif
#endif

#ifdef ENABLE_DOUBLE
typedef double fpv_t;
#  define FPV_C(a) a
#  define SCNfpv "lf"
#  define PRIfpv "g"
#else
typedef float fpv_t;
#  define FPV_C(a) a ## f
#  define SCNfpv "f"
#  define PRIfpv "g"
#endif

#if (NDIM == 2)
#  define POW_NDIM(a) ((a) * (a))
#elif (NDIM == 3)
#  define POW_NDIM(a) ((a) * (a) * (a))
#else
#  error NDIM must be 2 or 3
#endif


#endif
