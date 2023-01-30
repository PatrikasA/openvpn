include $(TOPDIR)/rules.mk

PKG_NAME:=ovpn_tel
PKG_RELEASE:=1
PKG_VERSION:=1.0.0

include $(INCLUDE_DIR)/package.mk

define Package/ovpn_tel
		CATEGORY:=Base system
		TITLE:=ovpn_tel
		DEPENDS:=+libubus +libubox +libblobmsg-json
endef

define Package/ovpn_tel/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ovpn_tel $(1)/usr/bin
	$(INSTALL_BIN) ./files/ovpn_tel.init $(1)/etc/init.d/ovpn_tel
endef

$(eval $(call BuildPackage,ovpn_tel))
