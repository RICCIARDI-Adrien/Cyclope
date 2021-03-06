################################################################################
#
# cyclope-controller
#
################################################################################

CYCLOPE_CONTROLLER_VERSION = 1.1

# Sources are provided within the package
CYCLOPE_CONTROLLER_SITE_METHOD = local
CYCLOPE_CONTROLLER_SITE = $(BR2_EXTERNAL_CYCLOPE_PATH)/package/cyclope-controller/src

define CYCLOPE_CONTROLLER_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) $(TARGET_CONFIGURE_OPTS) -C $(@D)
endef

define CYCLOPE_CONTROLLER_INSTALL_TARGET_CMDS
	$(INSTALL) -m 0755 $(@D)/cyclope-controller $(TARGET_DIR)/usr/sbin
	$(INSTALL) -m 0755 $(CYCLOPE_CONTROLLER_PKGDIR)/S80cyclope-controller $(TARGET_DIR)/etc/init.d
endef

$(eval $(generic-package))
