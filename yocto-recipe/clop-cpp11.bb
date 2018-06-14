###############################################################################
##                                                                           ##
##            Yocto-recipe to building shared-library for the                ##
##                 command-line-option-parser for C++11                      ##
##                                                                           ##
##---------------------------------------------------------------------------##
## Author:   Ulrich Becker                                                   ##
## File:     clop-cpp11.bb                                                   ##
## Date:     13.06.2018                                                      ##
## Revision:                                                                 ##
###############################################################################

SUMMARY          = "Shared-library of the command-line-option-parser for C++11"

SECTION          = "libs"
S                = "${WORKDIR}/git"
LICENSE          = "MIT"
LIC_FILES_CHKSUM = "file://${S}/LICENSE;md5=3582c1bb9adaf6b1c1de362125b97f9f"
SRC_URI          = "git://github.com/UlrichBecker/command_line_option_parser_cpp11.git;branch=master"
SRCREV           = "${AUTOREV}"
PV               = "1.0-git${SRCPV}"
PR               = "r0"

TARGET_CC_ARCH   += "${LDFLAGS}"

FILES_${PN}      += "${libdir}/lib*.so.*"
FILES_${PN}-dev  += "${libdir}/lib*.so"
FILES_${PN}-dev  += "${includedir}/*.hpp"

do_compile() {
   oe_runmake -C ${S}/src
}

do_install() {
   mkdir -p ${D}${includedir}
   mkdir -p ${D}${libdir}
   oe_runmake -C ${S}/src HEADDER_DIR=${D}${includedir} LIB_DIR=${D}${libdir} install
}

#=================================== EOF ======================================
