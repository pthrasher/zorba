#!/bin/bash -f
cd context
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../exprtree
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../functions
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../listeners
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../native_impl
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../parser
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../runtime
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../store
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../types
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../util
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local
cd ../values
if (!(test -d Build)); then
	mkdir Build;
fi;
make all -f Makefile.local

