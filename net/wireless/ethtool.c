#include <linux/utsname.h>
#include <net/cfg80211.h>
#include "core.h"
#include "rdev-ops.h"

void cfg80211_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct wireless_dev *wdev;
	struct device* wd;

	if (WARN_ON(!dev))
		return;

	wdev = dev->ieee80211_ptr;
	if (WARN_ON(!wdev))
		return;

	if (WARN_ON(!info))
		return;

	if (WARN_ON(!wdev->wiphy))
		return;

	wd = wiphy_dev(wdev->wiphy);
	if (WARN_ON(!info))
		return;

	strlcpy(info->driver, wd->driver->name, sizeof(info->driver));

	strlcpy(info->version, init_utsname()->release, sizeof(info->version));

	if (wdev->wiphy->fw_version[0])
		strlcpy(info->fw_version, wdev->wiphy->fw_version,
			sizeof(info->fw_version));
	else
		strlcpy(info->fw_version, "N/A", sizeof(info->fw_version));

	strlcpy(info->bus_info, dev_name(wd), sizeof(info->bus_info));
}
EXPORT_SYMBOL(cfg80211_get_drvinfo);
