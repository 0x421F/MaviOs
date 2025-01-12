#!/bin/bash

set -e

# Constants
KERNEL_VER="linux-5.10.76.tar.xz"
GLIBC_VER="glibc-2.38.tar.gz"
BUSYBOX_VER="busybox-1.37.0.tar.bz2"
PWD_DIR="$(pwd)"
KERNEL_DIR="$PWD/mavi/$(echo $KERNEL_VER | sed 's/\.tar\.xz//')"
GLIBC_DIR="$PWD/mavi/$(echo $GLIBC_VER | sed 's/\.tar\.gz//')"
BUSYBOX_DIR="$PWD/mavi/$(echo $BUSYBOX_VER | sed 's/\.tar\.bz2//')"
SYSROOT_DIR="$PWD/mavi/sysroot"
MAVI_DIR="$PWD/mavi"
ISO_DIR="$PWD/mavi/iso"

# Install dependencies
get_deps() {
  sudo apt-get install   \
    fakeroot             \
    build-essential      \
    ncurses-dev xz-utils \
    libssl-dev           \
    bc                   \
    flex                 \
    libelf-dev           \
    bison
}

# Prepare build directory
build_init() {
  rm -rf $MAVI_DIR
  mkdir $MAVI_DIR
}

# Build kernel
build_kernel() {
  cd $MAVI_DIR
  wget "https://cdn.kernel.org/pub/linux/kernel/v5.x/$KERNEL_VER"
  tar -xvf $KERNEL_VER
  cd $KERNEL_DIR
  make x86_64_defconfig -j $(nproc)
  make bzImage -j $(nproc)
}

# Build glibc
build_glibc() {
  cd $MAVI_DIR
  wget http://ftp.gnu.org/gnu/libc/$GLIBC_VER
  tar -xvf $GLIBC_VER
  cd $GLIBC_DIR
  mkdir build
  mkdir GLIBC
  cd build
  ../configure --prefix=
  make -j $(nproc)
  make install DESTDIR=../GLIBC -j 2
}

# Build sysroot
build_sysroot() {
  cd $MAVI_DIR
  mkdir -p sysroot/usr
  cp -r $GLIBC_DIR/GLIBC/* sysroot
  cp -r GLIBC/include/* sysroot/include/
  cp -r GLIBC/lib/* sysroot/lib/
  rsync -a /usr/include sysroot
  ln -s ../include sysroot/usr/include
  ln -s ../lib sysroot/usr/lib
}

# Build busybox
build_busybox() {
  cd $MAVI_DIR
  wget "https://busybox.net/downloads/busybox-1.37.0.tar.bz2"
  tar -xvjf $BUSYBOX_VER
  cd $BUSYBOX_DIR
  make defconfig
  sed -i "s|.*CONFIG_SYSROOT.*|CONFIG_SYSROOT=\"../sysroot\"|" .config
  sed -i "s|.*CONFIG_EXTRA_CFLAGS.*|CONFIG_EXTRA_CFLAGS=\"-L../sysroot/lib\"|" .config
  make -j $(nproc)
}

# Install core
build_rootfs() {
  cd $PWD_DIR
  wget https://github.com/0x421F/MaviOs/releases/download/0.1/root.zip
  unzip root.zip
  cd $MAVI_DIR
  rm -rf rootfs
  mkdir rootfs
  cp -r $PWD_DIR/root/* $MAVI_DIR/rootfs
  cp -r $BUSYBOX_DIR/BUSYBOX/* $MAVI_DIR/rootfs
  cp $SYSROOT_DIR/lib/libm.so.6 $MAVI_DIR/rootfs/lib/libm.so.6
  cp $SYSROOT_DIR/lib/libc.so.6 $MAVI_DIR/rootfs/lib/libc.so.6
  cp $SYSROOT_DIR/lib/libresolv.so.2 $MAVI_DIR/rootfs/lib/libresolv.so.2
  cp $SYSROOT_DIR/lib/ld-linux-x86-64.so.2 $MAVI_DIR/rootfs/lib/ld-linux-x86-64.so.2
  cp $SYSROOT_DIR/bin/ldd $MAVI_DIR/rootfs/bin/ldd
  sed -i 's/bash/sh/' $MAVI_DIR/rootfs/bin/ldd
  cd $MAVI_DIR/rootfs && ln -s lib lib64
  rm $MAVI_DIR/rootfs/linuxrc
  set +e
  strip -g \
  $MAVI_DIR/rootfs/bin/* \
  $MAVI_DIR/rootfs/sbin/* \
  $MAVI_DIR/rootfs/lib/* \
  2>/dev/null
  set -e
  rm -rf $PWD_DIR/root
  rm $PWD_DIR/root.zip
}

# Create ISO file
build_iso() {
  cd $MAVI_DIR
  rm -rf $ISO_DIR
  mkdir -p $ISO_DIR/boot/grub
  cd $MAVI_DIR/rootfs
  find . | cpio -o -H newc | gzip > $ISO_DIR/boot/root.cpio.gz
  cp $KERNEL_DIR/arch/x86/boot/bzImage $ISO_DIR/boot/bzImage
  cp $PWD_DIR/config/grub.cfg $ISO_DIR/boot/grub/grub.cfg
  grub-mkrescue -o $PWD_DIR/mavi.iso $ISO_DIR
}

# Main
get_deps
build_init
build_kernel
build_glibc
build_sysroot
build_busybox
build_rootfs
build_iso
