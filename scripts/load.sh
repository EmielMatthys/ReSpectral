#!/usr/bin/env bash

param1=$1
param2=$2

echo param 1: $param1
echo param 2: $param2

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

if [ -f "$2" ]; then
  echo $2 file exists!
else
  echo $2 file does not exist
  exit
fi

proc=${arr[$inst]}

echo Running instances: "${arr[@]}"
echo Attaching to "$proc"

gdb -n -q -batch \
  -ex "attach $proc" \
  -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
  -ex "call \$dlopen(\"$2\", 1)" \
  -ex "call (char*) dlerror()" \
  -ex "detach" \
  -ex "quit"

# set $dlopen = (void*(*)(char*, int)) dlopen
# call $dlopen("/home/emiel/Documents/cpp/SpectralHook/build/libSpectralHook.so", 1)
