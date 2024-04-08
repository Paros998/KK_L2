# Install script for directory: C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/GSL")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Users/part4/AppData/Local/Programs/CLion/bin/mingw/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gsl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/libgsl.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gsl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/libgslcblas.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gsl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/gsl" TYPE FILE FILES
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_inline.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_machine.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_math.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_minmax.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_mode.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_nan.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_pow_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_precision.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_types.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/gsl_version.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/blas/gsl_blas.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/blas/gsl_blas_types.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_complex_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_complex_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_block_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/block/gsl_check_range.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/bspline/gsl_bspline.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/bst/gsl_bst.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/bst/gsl_bst_avl.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/bst/gsl_bst_rb.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/bst/gsl_bst_types.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/cblas/gsl_cblas.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/cdf/gsl_cdf.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/cheb/gsl_chebyshev.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/combination/gsl_combination.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/complex/gsl_complex.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/complex/gsl_complex_math.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/const/gsl_const.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/const/gsl_const_cgs.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/const/gsl_const_cgsm.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/const/gsl_const_mks.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/const/gsl_const_mksa.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/const/gsl_const_num.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/deriv/gsl_deriv.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/dht/gsl_dht.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/diff/gsl_diff.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/eigen/gsl_eigen.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/err/gsl_errno.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/err/gsl_message.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_dft_complex.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_dft_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_fft.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_fft_complex.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_fft_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_fft_halfcomplex.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_fft_halfcomplex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_fft_real.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fft/gsl_fft_real_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/filter/gsl_filter.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/fit/gsl_fit.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/histogram/gsl_histogram.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/histogram/gsl_histogram2d.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/ieee-utils/gsl_ieee_utils.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/integration/gsl_integration.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/interpolation/gsl_interp.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/interpolation/gsl_interp2d.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/interpolation/gsl_spline.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/interpolation/gsl_spline2d.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/linalg/gsl_linalg.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_complex_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_complex_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/matrix/gsl_matrix_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/min/gsl_min.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/monte/gsl_monte.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/monte/gsl_monte_miser.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/monte/gsl_monte_plain.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/monte/gsl_monte_vegas.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/movstat/gsl_movstat.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multifit/gsl_multifit.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multifit/gsl_multifit_nlin.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multifit_nlinear/gsl_multifit_nlinear.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multilarge/gsl_multilarge.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multilarge_nlinear/gsl_multilarge_nlinear.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multimin/gsl_multimin.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multiroots/gsl_multiroots.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/multiset/gsl_multiset.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/ntuple/gsl_ntuple.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/ode-initval/gsl_odeiv.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/ode-initval2/gsl_odeiv2.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permutation.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_complex_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_complex_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_complex_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_complex_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_matrix_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_complex_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_complex_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/permutation/gsl_permute_vector_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/poly/gsl_poly.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/qrng/gsl_qrng.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/randist/gsl_randist.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/rng/gsl_rng.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/roots/gsl_roots.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/rstat/gsl_rstat.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/siman/gsl_siman.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_heapsort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sort/gsl_sort_vector_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spblas/gsl_spblas.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_airy.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_bessel.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_clausen.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_coulomb.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_coupling.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_dawson.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_debye.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_dilog.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_elementary.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_ellint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_elljac.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_erf.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_exp.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_expint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_fermi_dirac.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_gamma.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_gegenbauer.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_hermite.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_hyperg.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_laguerre.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_lambert.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_legendre.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_log.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_mathieu.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_pow_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_psi.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_result.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_sincos_pi.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_synchrotron.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_transport.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_trig.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_sf_zeta.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/specfunc/gsl_specfunc.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/splinalg/gsl_splinalg.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_complex_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_complex_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/spmatrix/gsl_spmatrix_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/statistics/gsl_statistics_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sum/gsl_sum.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/sys/gsl_sys.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/test/gsl_test.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_char.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_complex.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_complex_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_complex_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_complex_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_float.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_int.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_long.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_long_double.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_short.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_uchar.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_uint.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_ulong.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/vector/gsl_vector_ushort.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/wavelet/gsl_wavelet.h"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/wavelet/gsl_wavelet2d.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gsl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/gsl.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gsl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/gsl-config")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gsl" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/gsl-2.7/gsl-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/gsl-2.7/gsl-targets.cmake"
         "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/CMakeFiles/Export/be3280bb442f4242bb46ea3e6d171e46/gsl-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/gsl-2.7/gsl-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/gsl-2.7/gsl-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/gsl-2.7" TYPE FILE FILES "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/CMakeFiles/Export/be3280bb442f4242bb46ea3e6d171e46/gsl-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/gsl-2.7" TYPE FILE FILES "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/CMakeFiles/Export/be3280bb442f4242bb46ea3e6d171e46/gsl-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gsl" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/gsl-2.7" TYPE FILE FILES
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/cmake/gsl-config.cmake"
    "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/cmake/gsl-config-version.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/part4/Desktop/studia2/KK/KK_L2/libs/GSL/gsl-master/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
