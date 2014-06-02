#m4 macros needed to configure, link boost
ACLOCAL_AMFLAGS = -I m4
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
peless_LDADD=$(DEPS_LIBS)  $(BOOST_FILESYSTEM_LIB) $(BOOST_REGEX_LIB)

# sources required for peless
peless_SOURCES = peless.cc gmore.cc search.cc gmore.hh inittime.hh internat.hh search.hh ucompose.hpp

man1_MANS = peless.1

#extra files
EXTRA_DIST = philo.txt INTERNATIONALIZATION    peless.png peless.xpm  peless.spec.fc6  peless.1 peless.spec.man2007 peless.spec.OpenSuSE-10.2 peless.spec.data.OpenSuSE-10.2   peless.spec.data.fc6   peless.spec.data.man2007 peless.spec.fixed m4/ax_boost_base.m4 m4/ax_boost_filesystem.m4 m4/ax_boost_regex.m4 intltool-extract.in intltool-merge.in intltool-update.in po/LINGUAS po/POTFILES.in po/Makefile.in.in peless.spec.version


#clean this created file after each make
CLEANFILES=peless.desktop peless.spec.OpenSuSE-10.2 peless.spec.version peless.spec.fc6 peless.spec.man2007 peless.desktop.in

DISTCLEANFILES = peless-1.125.tar.bz2 peless-1.125.tar.gz intltool-extract intltool-merge intltool-update po/.intltool-merge-cache peless.desktop.in

# place peless.png, peless.xpm in its proper place.
pixmapdir = @datadir@/pixmaps
pixmap_DATA = peless.png peless.xpm

# create and place peless.desktop
desktopdir = @datadir@/applications
desktop_in_files = peless.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)
@INTLTOOL_DESKTOP_RULE@

peless.spec.version:
	echo "%define _version @PACKAGE_VERSION@" >peless.spec.version
	echo -n "%define _release 0." >>peless.spec.version
	date -u +%y%m%d >>peless.spec.version


peless.spec.OpenSuSE-10.2:	peless.spec.version peless.spec.fixed peless.spec.data.OpenSuSE-10.2
	cat peless.spec.version peless.spec.data.OpenSuSE-10.2 peless.spec.fixed >peless.spec.OpenSuSE-10.2

peless.spec.fc6:	peless.spec.version peless.spec.fixed peless.spec.data.fc6
	cat peless.spec.version peless.spec.data.fc6 peless.spec.fixed >peless.spec.fc6

peless.spec.man2007:	peless.spec.version peless.spec.fixed peless.spec.data.man2007
	cat peless.spec.version peless.spec.data.man2007 peless.spec.fixed >peless.spec.man2007


 dist-hook:	peless.spec.OpenSuSE-10.2 peless.spec.fc6 peless.spec.man2007

