################################################################################
#
# cyclope-controller
#
################################################################################

CYCLOPE_CONTROLLER_VERSION = 1.0

# Sources are provided within the package
CYCLOPE_CONTROLLER_SITE_METHOD = local
CYCLOPE_CONTROLLER_SITE = $(BR2_EXTERNAL_CYCLOPE_PATH)/package/cyclope-controller/src

$(eval $(generic-package))
