#!/bin/sh
xgettext -o test.pot -k"_L" -k"_LC:1c,2" -s -c --package-name=moFileReader --from-code=UTF-8 test.cpp