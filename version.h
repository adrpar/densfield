// Copyright (C) 2009, 2010, Steffen Knollmann
// Released under the terms of the GNU General Public License version 3.


#ifndef VERSION_H
#define VERSION_H

#define PACKAGE_NAME             "densfield"
#define PACKAGE_OWNER            "Adrian M. Partl"
#define PACKAGE_BUG_EMAIL        "adrianlpartl.net"
#define PACKAGE_VERSION_MAJOR    0
#define PACKAGE_VERSION_MINOR    3
#define PACKAGE_VERSION_MICRO    5
#define PACKAGE_VERSION_REVISION "\ncommit b1eebfc9ec2cf991bd444cef775c573c7c5ef3b1"
#define PACKAGE_COPYRIGHT_YEAR   "2009, 2010"

#define PRINT_VERSION_INFO(f)                                         \
    fprintf((f), "This is %s %i.%i.%i   %s\n\n"                       \
                 "Copyright (C) %s, %s\n"                             \
                 "This is free software; see the source for copying " \
                 "conditions.  There is NO \n"                        \
                 "warranty; not even for MERCHANTABILITY or FITNESS " \
                 "FOR A PARTICULAR PURPOSE.\n\n"                      \
                 "Please send bugreports to %s.\n\n",                 \
            PACKAGE_NAME,                                             \
            PACKAGE_VERSION_MAJOR,                                    \
            PACKAGE_VERSION_MINOR,                                    \
            PACKAGE_VERSION_MICRO,                                    \
            PACKAGE_VERSION_REVISION,                                 \
            PACKAGE_COPYRIGHT_YEAR,                                   \
            PACKAGE_OWNER,                                            \
            PACKAGE_BUG_EMAIL);

#endif
