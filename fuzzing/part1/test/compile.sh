#!/bin/bash
clang -emit-llvm -S -fno-discard-value-names -c -o simple$1.ll simple$1.c -g
opt -load ../build/InstrumentPass.so -Instrument -S simple$1.ll -o simple$1.instrumented.ll
clang -o simple$1 ../lib/runtime.c simple$1.instrumented.ll
./simple$1
