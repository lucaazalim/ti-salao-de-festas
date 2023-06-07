clear

if make -B -f "makefile-tests"; then
    ./bin/tests
fi