#!/bin/bash
OLDPATH="$(pwd)"
MYPATH="$(cd -P -- "$(dirname -- "$0")" && pwd -P)"
BUILD="$1"
if test -z ${BUILD}; then
	BUILD="Debug"
fi
#QMAKE="$(which qmake)"
#QMAKE="/usr/local/Trolltech/Qt-4.7.4/bin/qmake"
QMAKE="${HOME}/QtSDK/Desktop/Qt/473/gcc/bin/qmake"

BUILD_DIR="${MYPATH}/build"

cd ${MYPATH}
/usr/bin/cmake -H${MYPATH} -B${BUILD_DIR} -DCMAKE_BUILD_TYPE=${BUILD} -DQT_QMAKE_EXECUTABLE=${QMAKE}
make -C ${BUILD_DIR} -j4 VERBOSE=1 all
cd ${OLDPATH}
