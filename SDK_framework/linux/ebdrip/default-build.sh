#!/bin/sh
$PWD/build.sh release depend ebdrip -t linux-pentium -va pdls=all -va minimal=1 -va corefeatures=none -va ICUbuiltin=1 -va cpp_compiler=gcc_4_5_3 -va ebd_pdfout=epdfouty -va rebuild=sw
