#!/bin/sh
# Define environment variables used by Harlequin Embedded SDK make files
BUILD_DIR=`dirname "$0"`
ENV_DIR=$(echo ${BUILD_DIR%/*})
CV_DOXYGEN_1_6_2=$ENV_DIR/CV_variables/CV_DOXYGEN_1_6_2/doxygen_1.6.2 ; export CV_DOXYGEN_1_6_2
CV_GCC_4_5_3=/usr/bin/gcc-4.5; export CV_GCC_4_5_3
CV_GCC_4_5_3_CPLUSPLUS=/usr/bin/g++-4.5 ; export CV_GCC_4_5_3_CPLUSPLUS
CV_GCC_4_5_3_CPP=/usr/bin/cpp-4.5 ; export CV_GCC_4_5_3_CPP
CV_GRAPHVIZ_2=$ENV_DIR/CV_variables/CV_GRAPHVIZ_2 ; export CV_GRAPHVIZ_2
CV_JAM_2_2_5_6=$ENV_DIR/CV_variables/CV_JAM_2_2_5_6/jam_2_2_5_6 ; export CV_JAM_2_2_5_6
CV_PERL_5_005_02=/usr/bin/perl ; export CV_PERL_5_005_02
CV_SIGNTOOL_1_0=$ENV_DIR/CV_variables/CV_SIGNTOOL_1_0/signtol ; export CV_SIGNTOOL_1_0
CV_ZIP_2_3_1=$ENV_DIR/CV_variables/CV_ZIP_2_3_1/bin ; export CV_ZIP_2_3_1
