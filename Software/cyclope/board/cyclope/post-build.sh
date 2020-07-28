#!/bin/sh

set -u
set -e

# Replace /var/log symlink to /tmp by a real directory (so logs are kept across reboots)
rm -rf "${TARGET_DIR}"/var/log
ln -s /media/data/var/log "${TARGET_DIR}"/var/log
