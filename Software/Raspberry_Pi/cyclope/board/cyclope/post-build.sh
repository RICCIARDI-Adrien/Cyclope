#!/bin/sh

set -u

# Create partitions mount point
mkdir -p "${TARGET_DIR}"/media/boot
mkdir -p "${TARGET_DIR}"/media/data

# Redirect Dropbear configuration to data partition
rm -rf "${TARGET_DIR}"/etc/dropbear
ln -s /media/data/etc/dropbear "${TARGET_DIR}"/etc/dropbear

# Replace /var/log symlink to /tmp by a real directory (so logs are kept across reboots)
rm -rf "${TARGET_DIR}"/var/log
ln -s /media/data/var/log "${TARGET_DIR}"/var/log

# Append boot partition to fstab if it not present yet
DATA_PARTITION=$(grep "/dev/mmcblk0p1" "${TARGET_DIR}"/etc/fstab)
if [ -z "$DATA_PARTITION" ]
then
	echo "/dev/mmcblk0p1	/media/boot	vfat	defaults	0	0" >> "${TARGET_DIR}"/etc/fstab
fi

# Append data partition to fstab if it not present yet
DATA_PARTITION=$(grep "/dev/mmcblk0p4" "${TARGET_DIR}"/etc/fstab)
if [ -z "$DATA_PARTITION" ]
then
	echo "/dev/mmcblk0p4	/media/data	ext4	defaults,noatime	0	0" >> "${TARGET_DIR}"/etc/fstab
fi

# Remove Lidar serial port tty if not removed yet
sed -i '/# Put a getty on the serial port/d' "${TARGET_DIR}"/etc/inittab
sed -i '/console::respawn:\/sbin\/getty -L  console 0 vt100 # GENERIC_SERIAL/d' "${TARGET_DIR}"/etc/inittab
