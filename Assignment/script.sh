#!/bin/sh
wget https://cdn.kernel.org/pub/linux/kernel/v5.x/linux-5.19.8.tar.xz
tar -xvJf linux-5.19.8.tar.xz
patch -p0 < diff
cd linux-5.19.8
wget https://raw.githubusercontent.com/gopi487krishna/ArtixConfig/main/config-rev-9-gold
cp config-rev-9-gold .config
make menuconfig 
make -j2
make modules_install
sudo cp -v arch/x86_64/boot/bzImage /boot/vmlinuz-linuxpatched
sudo mkinitcpio -k 5.19.8 -g /boot/initramfs-linuxpatched.img
sudo cp System.map /boot/System.map-linuxpatched
sudo cp /boot/System.map-linuxpatched System.map
sudo grub-mkconfig -o /boot/grub/grub.cfg