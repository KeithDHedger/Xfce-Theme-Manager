#!/bin/bash

./remakesourcelist
aclocal
autoheader
touch NEWS README AUTHORS ChangeLog
automake --add-missing --copy
autoconf
./configure $@

