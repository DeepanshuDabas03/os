#!/bin/sh
mkdir kernel2
cd kernel2
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.19.8.tar.xz
tar -xvJf linux-5.19.8.tar.xz
cd linux-5.19.8
make mrproper
wget https://raw.githubusercontent.com/gopi487krishna/ArtixConfig/main/config-rev-9-gold
cp config-rev-9-gold .config
make menuconfig
make -j2
make modules_install
sudo cp -v arch/x86_64/boot/bzImage /boot/vmlinuz-linuxB
sudo mkinitcpio -k 5.19.8 -g /boot/initramfs-linuxB.img
sudo cp System.map /boot/System.map-B
sudo cp /boot/System.map-B System.map
sudo grub-mkconfig -o /boot/grub/grub.cfg
