#
#
AC_INIT([Xfce-Theme-Manager],[0.3.5],[PROJ],[Xfce-Theme-Manager])

AC_CONFIG_HEADER([config.h])
AC_PROG_CXX

AM_INIT_AUTOMAKE

AC_PROG_CC
AC_HEADER_STDC

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AM_PROG_CC_C_O

CXXFLAGS=-Wall
AC_SUBST(CXXFLAGS)

CFLAGS=-Wall
AC_SUBST(CFLAGS)

GTK_MODULES="gtk+-2.0 >= 2.24.0"
PKG_CHECK_MODULES(GTK, $GTK_MODULES)
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

GLIB_MODULES="glib-2.0 >= 2.30.0"
PKG_CHECK_MODULES(GLIB, $GLIB_MODULES)
AC_SUBST(GLIB_CFLAGS)
AC_SUBST(GLIB_LIBS)

XCURSOR_MODULES="xcursor"
PKG_CHECK_MODULES(XCURSOR, $XCURSOR_MODULES)
AC_SUBST(XCURSOR_CFLAGS)
AC_SUBST(XCURSOR_LIBS)

XFCE4UI_MODULES="libxfce4ui-1 >= 4.8.0"
PKG_CHECK_MODULES(XFCE4UI, $XFCE4UI_MODULES,AC_DEFINE([GOT_LIBXFCEUI], [], [Description]),echo "INFORMATION ... Not using Xfce4 dialog header")

AC_SUBST([XFCE4UI_CFLAGS])
AC_SUBST([XFCE4UI_LIBS])

XFCONF_MODULES="libxfconf-0 >= 4.8.1"
PKG_CHECK_MODULES(XFCONF, $XFCONF_MODULES)
AC_SUBST(XFCONF_CFLAGS)
AC_SUBST(XFCONF_LIBS)

AC_CHECK_PROG(UNZIP, unzip ,true,false)
if test $UNZIP = false; then
	AC_MSG_WARN([No unzip program found! You will not be able to drag 'n' drop zip files!])
fi


desktopversion=`xfdesktop --version|head -n 1|awk '{print $5}'|awk -F "," '{print $1}'|awk -F "." '{print $2}'`
if test $desktopversion = 11; then
	AC_DEFINE([_411_], [], [xfdesktop 4.11.1])
fi

AC_OUTPUT(Makefile Xfce-Theme-Manager/app/Makefile)

