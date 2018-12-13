#!/bin/sh
xgettext -o test.pot -k_ -k"_LC:1c,2" -s -c --package-name=moFileReader test.cpp