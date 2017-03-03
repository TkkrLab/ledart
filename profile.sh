#/usr/bin/bash
valgrind --tool=callgrind --callgrind-out-file=callgrind.out build/ledart --showFps && kcachegrind callgrind.out

