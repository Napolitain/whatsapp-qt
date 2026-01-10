#include "AppRegistration.hpp"

#include <qcoreapplication.h>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>
#include <QString>

#include "Constants.hpp"

static bool isRunningInSnap() {
	return qEnvironmentVariableIsSet("SNAP");
}

bool AppRegistration::registerApp() {
	// Skip registration in snap - snap provides desktop integration
	if (isRunningInSnap()) {
		return true;
	}
	// 1. Copy icon
	const QString iconDir = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)
	                        + "/icons/hicolor/256x256/apps";
	QDir().mkpath(iconDir);
	const QString iconTargetPath = iconDir + "/" + APP_NAME + ".png";
	if (!QFile::copy(ICON_RES, iconTargetPath) && !QFile::exists(iconTargetPath))
		return false;

	// 2. Create .desktop file
	const QString desktopDir = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);
	QDir().mkpath(desktopDir);
	const QString desktopFile = desktopDir + "/" + APP_NAME + ".desktop";
	QFile file(desktopFile);
	if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
		QTextStream out(&file);
		out << "[Desktop Entry]\n";
		out << "Type=Application\n";
		out << "Name=" << APP_NAME << "\n";
		out << "Exec=" << QCoreApplication::applicationFilePath() << "\n";
		out << "Icon=" << APP_NAME << "\n";
		out << "Terminal=false\n";
		out << "Categories=Network;InstantMessaging;\n";
		file.close();
		// Set executable permissions
		QFile::setPermissions(desktopFile, QFile::ReadOwner | QFile::WriteOwner | QFile::ExeOwner |
		                                   QFile::ReadGroup | QFile::ExeGroup | QFile::ReadOther | QFile::ExeOther);
		return true;
	}
	return false;
}

bool AppRegistration::unregisterApp() {
	if (isRunningInSnap()) {
		return true;
	}
	const QString desktopFile = QDir::homePath() + "/.local/share/applications/" + APP_NAME + ".desktop";
	const QString iconFile = QDir::homePath() + "/.local/share/icons/hicolor/256x256/apps/" + APP_NAME + ".png";
	const bool ok1 = QFile::remove(desktopFile);
	const bool ok2 = QFile::remove(iconFile);
	return ok1 || ok2;
}

bool AppRegistration::isRegistered() {
	if (isRunningInSnap()) {
		return true;
	}
	const QString desktopFile = QDir::homePath() + "/.local/share/applications/" + APP_NAME + ".desktop";
	const QString iconFile = QDir::homePath() + "/.local/share/icons/hicolor/256x256/apps/" + APP_NAME + ".png";
	return QFile::exists(desktopFile) && QFile::exists(iconFile);
}
