#
#     PELESS TABBED TEXT FILE LISTER.
#     Copyright (C) 2004,2007,2012 Paul Elliott
#     
#     This file is part of peless.
# 
#     peless is free software; you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation; either version 3 of the License, or
#     (at your option) any later version.
# 
# 
#     peless is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
# 
# 
#     You should have received a copy of the GNU General Public License
#     along with peless; if not, write to the Free Software
#     Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#m4 macros needed to configure, link boost
ACLOCAL_AMFLAGS         = -I m4 -I /usr/share/aclocal
# program we want built
bin_PROGRAMS = peless

#subdirectory for internationalization.
SUBDIRS=po

INTLTOOL_FILES = intltool-extract.in intltool-merge.in intltool-update.in

#DEPS_CFLAGS from gtkmm, others boost
peless_CXXFLAGS = $(DEPS_CFLAGS) $(BOOST_CPPFLAGS) -O2 -g  -DPELESS_LOCALEDIR=\"${PELESS_LOCALEDIR}\"
#boost link flags
peless_LDFLAGS = $(BOOST_LDFLAGS)
# gtkmm, boost libraries.
peless_LDADD=$(DEPS_LIBS)  $(BOOST_FILESYSTEM_LIB) $(BOOST_REGEX_LIB) $(BOOST_SYSTEM_LIB)

# sources required for peless
peless_SOURCES = peless.cc gmore.cc search.cc gmore.hh inittime.hh internat.hh search.hh ucompose.hpp

man1_MANS = peless.1

#extra files
EXTRA_DIST = philo.txt INTERNATIONALIZATION    peless.png peless.xpm   peless.1   intltool-extract.in intltool-merge.in intltool-update.in po/LINGUAS po/POTFILES.in po/Makefile.in.in m4/empty_dir


#clean this created file after each make
CLEANFILES=peless.desktop  peless.desktop.in

DISTCLEANFILES = peless-1.125.tar.bz2 peless-1.125.tar.gz intltool-extract intltool-merge intltool-update po/.intltool-merge-cache peless.desktop.in

# place peless.png, peless.xpm in its proper place.
pixmapdir = @datadir@/pixmaps
pixmap_DATA = peless.png peless.xpm

# create and place peless.desktop
desktopdir = @datadir@/applications
desktop_in_files = peless.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@





