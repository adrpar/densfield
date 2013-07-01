Copyright 2009-2013, Steffen Knollmann, Adrian M. Partl


These are the build instruction for densfield.


Basic build
===========

Use the provides ./configure script to generate Makefile.config and
config.h.  You may also create them by hand, use the according .in as an
example.

Please specify any options you want to set at the configure script. See
advanced options below for further information.

Then `make' will build the program and leave you with the executables
in src/.


Advanced option
===============

All advanced code options are exported through the configure script.
Please run ./configure --help to get a list and descriptions of the
various options.

Important configure options:
----------------------------

Optional features:
  --with-openmp         Uses the OpenMP directives.  Default: no.
  --with-mapping-cic    If this is used, the standard TSC mapping is
                        replaced by a CIC mapping.  Default: no
                        (using TSC).
  --with-mapping-sph    This will use a more accurate treatment
                        of gas particles, i.e. their properties will
                        be mapped using the SPH kernel.  Default: no.

Code properties:
  --enable-fortran-records  Using this will write proper Fortran records
                            instead of simple C blocks.  This means that
                            before and after every data block a 4 byte
                            blocklength will be written.  Default: yes.
  --enable-double           This switches on the usage of double
                            precision floating point variables instead
                            of single precision for fields and particle
                            properties.  Default: No.
                     
Extra features:
  --enable-debug                 Activates the debugging flags and
                                 forces the compiler flags to build 
                                 debugging symbols.  Default: no.
  --enable-profile               Will built the code with profiling
                                 output for usage with performance
                                 analysis tools.  Default: no.
  --ndim=VALUE                   Sets the dimensionality of the code.
                                 Only allowed value is 3 at the moment.
                                 Default: 3.
  --maxbasesize=VALUE            Sets the maximal extend of the particle
                                 assignment (for SPH mapping).  Default: 55.
  --sphkernelsizesmall=VALUE     Size for the smallest SPH Kernel sampling.
                                 Default: 3.
  --sphkernelsizemedium=VALUE    Size of the medium SPH Kernel sampling.
                                 Default: 7.
  --sphkernelsizebig=VALUE       Size of the largest SPH Kernel sampling.
                                 Default: 15.
  --sphkernel-subsampling=VALUE  Number of subsamples used to calculate
                                 the SPH kernel bins. Default: 8.
  --grid-undefined-value=VALUE   If an undefined value occurs in the
                                 grid use VALUE to represent it.  This
                                 can happen for velocity fields in cells
                                 than receive no contribution from any
                                 particle (oversampled fields).  The
                                 default is to represent the undefined
                                 value with NaN, but that might confuse
                                 analysis tools, so you may specify
                                 another value to use instead.  VALUE
                                 must be a floating point value and most
                                 likely you want 0.0.
                                 Default: NaN.


Code Documentation
==================

You may also build the internal code documenation by running `make doc'.
This will utilize doxygen to prepare a html documenation in doc/ref/html
and also generate latex files in doc/ref/latex which can be compiled to
generate a PDF of the documentation.  Note that this is most like not of
use for the normal user.
