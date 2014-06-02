#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.51)
 AC_INIT(peless, 1.252)
 AC_CONFIG_SRCDIR([peless.cc])
 AC_CONFIG_HEADER([config.h])
 AM_INIT_AUTOMAKE([dist-bzip2])

#required for internationalization
IT_PROG_INTLTOOL([0.35.0])


GETTEXT_PACKAGE=peless
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["$GETTEXT_PACKAGE"], [The domain to use with gettext])
AM_GLIB_GNU_GETTEXT

PELESS_LOCALEDIR=[${datadir}/locale]
AC_SUBST(PELESS_LOCALEDIR)

AC_ARG_WITH(dtcat,[ --with-dtcat=categories to use in peless.desktop],
	[PELESS_DTCAT=$with_dtcat],
	[PELESS_DTCAT='GTK;Utility;'])

AC_SUBST(PELESS_DTCAT)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC


AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h])


#find out of C functions gettext dgettext ect. exist
#this will define (or not) HAVE_GETTEXT, HAVE_DGETTEXT, in config.h
AC_CHECK_FUNCS(gettext dgettext dcgettext bindtextdomain textdomain)

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL

# Checks for library functions.

# This gets info about gtkmm and puts it into vars
# DEPS_CFLAGS (compile time)
# DEPS_LIBS   (Link time)

PKG_CHECK_MODULES(DEPS, gtkmm-2.4 >= 2.4.0 gconfmm-2.6 >= 2.6.0)
#PKG_CHECK_MODULES(DEPS, gtkmm-2.0 >= 2.2.8)

#use boost. by default /usr /usr/local and /opt directories will be searched for boost
AX_BOOST_BASE([1.32.1])
#use the boost filesystem library
AX_BOOST_FILESYSTEM
#use the boost regex library.
AX_BOOST_REGEX
#maybe use boost system
AX_BOOST_SYSTEM


#make this data visible in Makefile.am
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)



# require a makefile
# po/Makefile.in required for internationalization
# peless.desktop created in 2 steps substitutions in peless.desktop.in.in ->peless.desktop.in
# internationalization peless.desktop.in -> peless.desktop
AC_OUTPUT(po/Makefile.in peless.desktop.in Makefile)
