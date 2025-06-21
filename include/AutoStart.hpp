#pragma once

#include <QString>

class AutoStart {
public:
	static bool enable(const QString &appName, const QString &execPath, const QString &iconPath = QString());

	static bool disable(const QString &appName);

	static bool isEnabled(const QString &appName);
};
