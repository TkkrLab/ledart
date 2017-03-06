#/usr/bin/bash
scons && valgrind --tool=callgrind --callgrind-out-file=callgrind.out build/ledart --showFps && kcachegrind callgrind.out

