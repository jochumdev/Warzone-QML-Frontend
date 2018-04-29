#!/bin/bash
# vim: set et sts=4 sw=4 encoding=utf-8:

OLDPATH="$(pwd)"
MYPATH="$(cd -P -- "$(dirname -- "$0")" && pwd -P)"
BUILD="$1"
if test -z ${BUILD}; then
    BUILD="Debug"
fi
QMAKE="$(which qmake)"

BUILD_DIR="${MYPATH}/build/${BUILD,,}"

cd ${MYPATH}
/usr/bin/cmake -H${MYPATH} -B${BUILD_DIR} -DCMAKE_BUILD_TYPE=${BUILD} -DQT_QMAKE_EXECUTABLE=${QMAKE}
make -C ${BUILD_DIR} -j8 VERBOSE=1 all
RESULT=$?
cd ${OLDPATH}
exit ${RESULT}
