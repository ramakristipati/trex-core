#!/bin/bash

arch=$1

cd $(dirname $0)

#arch="${arch:-x86}"
arch="${arch:-x86_64}"
export TREX_MARCH=$arch

rm -f build_dpdk
ln -s build_dpdk_$TREX_MARCH build_dpdk

./b configure --no-mlx=1
./b build $*
rm -f ../scripts/so/libzmq.so.5
cp -f ../external_libs/zmq-$TREX_MARCH/libzmq.so ../scripts/so/libzmq.so.5
