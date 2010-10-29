# Initialize
AC_PREREQ([2.65])
AC_INIT([GLoop], [0.96], [adb1413@rit.edu], , [http://gander.sourceforge.net])
AC_CONFIG_SRCDIR([src/common.h])
AC_CONFIG_HEADERS([config.h:config.in])
AC_CANONICAL_SYSTEM
AC_PROG_CXX
AC_LANG([C++])
AC_PROG_INSTALL
AC_PROG_SED
if test -z $SED; then
	echo "--------------------------------------------------"
	echo " Sed is required to build GLoop.                  "
	echo "--------------------------------------------------"
fi
PKG_PROG_PKG_CONFIG

# Check for GNU Make
echo -n "Checking for GNU Make..."
make_command=""
for i in "$MAKE" make gmake gnumake; do
	if (sh -c "$i --version" 2>/dev/null | grep GNU >/dev/null); then
		make_command=$i;
		break;
	fi
done
if test -z $make_command; then
	echo " no"
	echo "-------------------------------------------------------"
	echo " GNU Make is required to build GLoop.                  "
	echo " Please visit http://www.gnu.org/software/make/        "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
else
	echo " yes"
fi

# Checks for libraries
AC_SEARCH_LIBS([cos], [m])
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([sqrt])
AC_C_INLINE
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Check for EDO
error_no_edo() {
	echo "-------------------------------------------------------"
	echo " EDO is needed to build GLoop                          "
	echo " Visit 'http://gander.sourceforge.net'                 "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
AC_CHECK_HEADER([edo/common.h], , [error_no_edo])

# Check for GLawt
warning_no_glawt() {
	echo "-------------------------------------------------------"
	echo " GLawt is needed to build GLoop tests.                 "
	echo " Visit 'http://gander.sourceforge.net'                 "
	echo "-------------------------------------------------------"
}
AC_CHECK_HEADER([glawt/common.h], , [warning_no_glawt])

# Check for images
images_help='No support for loading 2D images as textures.'
AC_ARG_ENABLE(images, AS_HELP_STRING([--disable-images], [$images_help]))
error_no_pixbufs() {
	echo "-------------------------------------------------------"
	echo " GDK Pixbufs are needed to load images for textures.   "
	echo " Try 'sudo apt-get install libgtkmm-2.4-dev'           "
	echo " Or visit 'http://www.gtkmm.org/'                      "
	echo " Alternatively, add '--disable-images' to ignore.      "
	echo "-------------------------------------------------------"
	(exit 1); exit 1;
}
if test "x$enable_images" != 'xno'; then
	echo -n "checking for gdkmm-2.4... "
	PKG_CHECK_EXISTS([gdkmm-2.4], [echo "yes"], [error_no_pixbufs])
	AC_DEFINE([HAVE_PIXBUFS], [1], [Define to 1 if GDK Pixbufs are available.])
else
	echo "-------------------------------------------------------"
	echo " You chose to disable images.                          "
	echo " Loading images for textures will not be available.    "
	echo "-------------------------------------------------------"
fi

# OS-specific compiler switches
if test $build_os = "mingw32"; then
	extra_ldflags="-Wl,--enable-auto-import"
	if test -z "$LDFLAGS"; then
		LDFLAGS="$extra_ldflags"
	else
		LDFLAGS="$LDFLAGS $extra_ldflags"
	fi
fi

# Prefixes
baseprefix=`basename $prefix`
baseprefix_low=`echo $baseprefix | tr '[[:upper:]]' '[[:lower:]]'`
if test $baseprefix_low = $PACKAGE_TARNAME; then
	datadir='${datarootdir}'
	docdir='${prefix}'/doc
else
	datadir='${datarootdir}'/$PACKAGE_TARNAME
	docdir='${datarootdir}'/doc/$PACKAGE_TARNAME
fi
htmldir='${docdir}'/html

# Finish
AC_CONFIG_FILES([Makefile doc/Makefile])
PKG_CHECK_MODULES([DEPS], [gtkmm-2.4 gtkglextmm-1.2])
AC_OUTPUT

echo \
"--------------------------------------------------------------
 ${PACKAGE_NAME} ${PACKAGE_VERSION}

 prefix      ${prefix}
 datarootdir ${datarootdir}
 datadir     ${datadir}
 docdir      ${docdir}
 htmldir     ${htmldir}
 CXX         ${CXX}
 CXXFLAGS    ${CXXFLAGS}
 LDFLAGS     ${LDFLAGS}
 LIBS        ${LIBS}
 DEFS        ${DEFS}
 
 Now type 'make' then 'sudo make install'
--------------------------------------------------------------"
