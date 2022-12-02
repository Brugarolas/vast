// RUN: vast-cc --from-source %s | FileCheck %s
// RUN: vast-cc --from-source %s > %t && vast-opt %t | diff -B %t -

void plus(int arg1, int arg2) {

    // CHECK: [[R:%[0-9]+]] = hl.mul [[V1:%[0-9]+]], [[V2:%[0-9]+]] : !hl.int
    int res = arg1 * arg2;
}