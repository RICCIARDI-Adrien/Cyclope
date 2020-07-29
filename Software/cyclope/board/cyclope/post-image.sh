#!/bin/sh

set -e

BOARD_DIR="$(dirname $0)"
BOOT_PARTITION_DIR="$1"
GENIMAGE_TMP="${BUILD_DIR}/genimage.tmp"
FIRMWARE_UPDATE_FILE_NAME="cyclope.tar"

# Provide custom boot files
cp "${BOARD_DIR}"/boot/* "${BOOT_PARTITION_DIR}"/rpi-firmware

# Create data partition manually because genimage is only able to create FAT file systems with content
# Create empty partition
dd if=/dev/zero of="${BOOT_PARTITION_DIR}"/data.ext4 bs=1M count=500
# Create file system skeleton to embed to generated file system
rm -rf "${BOOT_PARTITION_DIR}"/data
mkdir -p "${BOOT_PARTITION_DIR}"/data/etc/wpa_supplicant
mkdir -p "${BOOT_PARTITION_DIR}"/data/var/log
mkfs.ext4 -L data -d "${BOOT_PARTITION_DIR}"/data "${BOOT_PARTITION_DIR}"/data.ext4

# Pass an empty rootpath. genimage makes a full copy of the given rootpath to
# ${GENIMAGE_TMP}/root so passing TARGET_DIR would be a waste of time and disk
# space. We don't rely on genimage to build the rootfs image, just to insert a
# pre-built one in the disk image.
trap 'rm -rf "${ROOTPATH_TMP}"' EXIT
ROOTPATH_TMP="$(mktemp -d)"

rm -rf "${GENIMAGE_TMP}"

genimage \
	--rootpath "${ROOTPATH_TMP}"   \
	--tmppath "${GENIMAGE_TMP}"    \
	--inputpath "${BINARIES_DIR}"  \
	--outputpath "${BINARIES_DIR}" \
	--config "${BOARD_DIR}/genimage.cfg"

# Generate firmware update file
printf "\033[33mGenerating firmware update file...\033[0m\n"
cd "${BOOT_PARTITION_DIR}"
rm -f "${FIRMWARE_UPDATE_FILE_NAME}"
# Add rootfs
tar --dereference --append -f "${FIRMWARE_UPDATE_FILE_NAME}" rootfs.ext4
# Add boot partition files to a dedicated directory
mkdir -p boot
cp bcm2710-rpi-3-b.dtb bcm2710-rpi-3-b-plus.dtb bcm2710-rpi-cm3.dtb boot
cp -r rpi-firmware/* boot
# Do not copy cmdline.txt as this file is modified by the firmware update code to select the newly burned rootfs
rm -f boot/cmdline.txt
cp zImage boot
tar --append -f "${FIRMWARE_UPDATE_FILE_NAME}" boot
# Compress it
printf "\033[33mCompressing firmware update file...\033[0m\n"
rm -f "${FIRMWARE_UPDATE_FILE_NAME}".gz
gzip "${FIRMWARE_UPDATE_FILE_NAME}"

printf "\033[32mBuild succeeded.\033[0m\n"

exit $?