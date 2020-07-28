#!/bin/sh

set -u

# Replace /var/log symlink to /tmp by a real directory (so logs are kept across reboots)
rm -rf "${TARGET_DIR}"/var/log
ln -s /media/data/var/log "${TARGET_DIR}"/var/log

# Append data partition to fstab if it not present yet
DATA_PARTITION=$(grep "/dev/mmcblk0p4" "${TARGET_DIR}"/etc/fstab)
if [ -z "$DATA_PARTITION" ]
then
	echo "/dev/mmcblk0p4	/media/data	ext4	defaults,noatime	0	0" >> "${TARGET_DIR}"/etc/fstab
fi
