#!/bin/sh

set -e

BOARD_DIR="$(dirname $0)"
BOOT_PARTITION_DIR="$1"
GENIMAGE_TMP="${BUILD_DIR}/genimage.tmp"

# Provide custom boot files
cp "${BOARD_DIR}"/boot/* "${BOOT_PARTITION_DIR}"/rpi-firmware

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

exit $?