// Copyright (C) 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.


#ifndef IO_LOGGING_DEFS_H
#define IO_LOGGING_DEFS_H


/*--- Exported defines --------------------------------------------------*/
#define IO_LOGGING_NEW_ENTRY "\n\n--- NEW ENTRY STARTS HERE ---\n\n"
#define IO_LOGGING_STOP      "\nLogging stopped.\n\n"

#ifdef WITH_MPI
#  define IO_LOGGING_LOGO                                     \
    "\tPPPP           AA      M   M    I    GGGG      AA  \n" \
    "\tP  PP        A   A    MM MM    I    G        A   A \n" \
    "\tPPPP  ===   AAAAA    M M M    I    G GGG    AAAAA  \n" \
    "\tP          A   A    M   M    I    G   G    A   A   \n" \
    "\tP         A   A    M   M    I     GGG     A   A    "
#else
#  define IO_LOGGING_LOGO                           \
    "\t     AA      M   M    I    GGGG      AA  \n" \
    "\t   A   A    MM MM    I    G        A   A \n" \
    "\t  AAAAA    M M M    I    G GGG    AAAAA  \n" \
    "\t A   A    M   M    I    G   G    A   A   \n" \
    "\tA   A    M   M    I     GGG     A   A    "
#endif

#define IO_LOGGING_BAR \
    "========================================================================"

#define IO_LOGGING_BAR2 \

//#define IO_LOGGING_PART_PRE      "\n\n\n" IO_LOGGING_BAR "\n"
//#define IO_LOGGING_PART_POST     "\n" IO_LOGGING_BAR "\n"
#define IO_LOGGING_PART_PRE      "\n\n\n"
#define IO_LOGGING_PART_POST     "\n"
#define IO_LOGGING_PART_NUM_PRE  "PART "
#define IO_LOGGING_PART_NUM_POST ":\t"

//#define IO_LOGGING_SECTION_PRE      "\n\n" IO_LOGGING_BAR "\n"
//#define IO_LOGGING_SECTION_POST     "\n" IO_LOGGING_BAR "\n"
#define IO_LOGGING_SECTION_PRE      "\n\n"
#define IO_LOGGING_SECTION_POST     "\n"
#define IO_LOGGING_SECTION_NUM_PRE  ""
#define IO_LOGGING_SECTION_NUM_POST "  "

//#define IO_LOGGING_SUBSECTION_PRE      "\n" IO_LOGGING_BAR2 "\n"
//#define IO_LOGGING_SUBSECTION_POST     "\n" IO_LOGGING_BAR2 "\n"
#define IO_LOGGING_SUBSECTION_PRE      "\n"
#define IO_LOGGING_SUBSECTION_POST     "\n"
#define IO_LOGGING_SUBSECTION_NUM_PRE  ""
#define IO_LOGGING_SUBSECTION_NUM_POST "  "


#endif
