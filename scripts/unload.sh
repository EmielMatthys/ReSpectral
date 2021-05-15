#!/usr/bin/env bash

line=$(pidof $1)
arr=($line)
inst=0

if [ ${#arr[@]} == 0 ]; then
  echo Process isn\'t running!
  exit
fi

if [ $inst -gt ${#arr[@]} ] || [ $inst == ${#arr[@]} ]; then
  echo wrong index!
  exit
fi

if ! [ -f "$2" ]; then
  echo $2 file does not exist!
  exit
fi

proc=${arr[$inst]}

echo Running instances: "${arr[@]}"
echo Attaching to "$proc"

gdb -n -q -batch \
  -ex "attach $proc" \
  -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
  -ex "set \$dlclose = (int(*)(void*)) dlclose" \
  -ex "set \$lib = \$dlopen(\"$2\", 6)" \
  -ex "call \$dlclose(\$lib)" \
  -ex "call \$dlclose(\$lib)" \
  -ex "call (char*) dlerror()" \
  -ex "detach" \
  -ex "quit" 