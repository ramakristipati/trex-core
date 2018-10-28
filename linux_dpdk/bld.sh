#!/bin/bash

arch=$1;shift

cd $(dirname $0)

arch="${arch:-x86_64}"
CONFIG_OPTS=

# sudo apt-get install linux-libc-dev:i386

if [ "$arch" = "aarch64" ]; then
  # sudo apt install g++-aarch64-linux-gnu
  # sudo apt install gcc-aarch64-linux-gnu
  # extract zlib1g_1.2.8.dfsg-2ubuntu4.1_arm64.deb to /lib
  # extract zlib1g-dev_1.2.8.dfsg-2ubuntu4.1_arm64.deb /usr/lib
  CONFIG_OPTS="$CONFIG_OPTS --cross=aarch64-linux-gnu-"
fi
CONFIG_OPTS="$CONFIG_OPTS --march=$arch"

rm -f build_dpdk
ln -s build_dpdk_$arch build_dpdk

[ -d build_dpdk_$arch ] || mkdir build_dpdk_$arch

./b configure $CONFIG_OPTS --no-mlx=1
./b build $* 2>&1 | tee compile.log
rm -f ../scripts/so/libzmq.so.5
cp -f ../external_libs/zmq-$arch/libzmq.so ../scripts/so/libzmq.so.5
