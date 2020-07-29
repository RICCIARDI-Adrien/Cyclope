#!/bin/sh

set -u

# Create partitions mount point
mkdir -p "${TARGET_DIR}"/media/boot
mkdir -p "${TARGET_DIR}"/media/data

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
