//
// Created by Maxime Boucher on 6/21/25.
//
#include "AutoStart.hpp"

#include "AutoStart.hpp"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>

#ifdef Q_OS_WIN
#include <windows.h>
#include <shlobj.h>
#endif

bool AutoStart::enable(const QString &appName, const QString &execPath, const QString &iconPath) {
#ifdef Q_OS_LINUX
    const QString autostartDir = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/autostart";
    QDir().mkpath(autostartDir);
    const QString desktopFile = autostartDir + "/" + appName + ".desktop";
    QFile file(desktopFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out << "[Desktop Entry]\n";
        out << "Type=Application\n";
        out << "Exec=" << execPath << "\n";
        out << "Hidden=false\n";
        out << "NoDisplay=false\n";
        out << "X-GNOME-Autostart-enabled=true\n";
        out << "Name=" << appName << "\n";
        if (!iconPath.isEmpty()) {
            out << "Icon=" << iconPath << "\n";
        }
        file.close();
        return true;
    }
    return false;
#elif defined(Q_OS_WIN)
    wchar_t* path = nullptr;
    if (SHGetKnownFolderPath(FOLDERID_Startup, 0, nullptr, &path) != S_OK)
        return false;
    QString shortcutPath = QString::fromWCharArray(path) + "\\" + appName + ".lnk";
    CoTaskMemFree(path);

    // Create shortcut using Windows COM interfaces (omitted for brevity)
    // Use IShellLink and IPersistFile to create the .lnk file
    // For a full implementation, see Microsoft docs or QtWinExtras

    // Placeholder: return false to indicate not implemented
    return false;
#elif defined(Q_OS_MAC)
    QString plistDir = QDir::homePath() + "/Library/LaunchAgents";
    QDir().mkpath(plistDir);
    QString plistFile = plistDir + "/com." + appName.toLower() + ".plist";
    QFile file(plistFile);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        out << "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" "
               "\"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n";
        out << "<plist version=\"1.0\">\n<dict>\n";
        out << "  <key>Label</key>\n  <string>com." << appName.toLower() << "</string>\n";
        out << "  <key>ProgramArguments</key>\n  <array>\n";
        out << "    <string>" << execPath << "</string>\n";
        out << "  </array>\n";
        out << "  <key>RunAtLoad</key>\n  <true/>\n";
        out << "</dict>\n</plist>\n";
        file.close();
        return true;
    }
    return false;
#else
    return false;
#endif
}

bool AutoStart::disable(const QString &appName) {
#ifdef Q_OS_LINUX
    const QString desktopFile = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
                                + "/autostart/" + appName + ".desktop";
    return QFile::remove(desktopFile);
#elif defined(Q_OS_WIN)
    wchar_t* path = nullptr;
    if (SHGetKnownFolderPath(FOLDERID_Startup, 0, nullptr, &path) != S_OK)
        return false;
    QString shortcutPath = QString::fromWCharArray(path) + "\\" + appName + ".lnk";
    CoTaskMemFree(path);
    return QFile::remove(shortcutPath);
#elif defined(Q_OS_MAC)
    QString plistFile = QDir::homePath() + "/Library/LaunchAgents/com." + appName.toLower() + ".plist";
    return QFile::remove(plistFile);
#else
    return false;
#endif
}

bool AutoStart::isEnabled(const QString &appName) {
#ifdef Q_OS_LINUX
    const QString desktopFile = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)
                                + "/autostart/" + appName + ".desktop";
    return QFile::exists(desktopFile);
#elif defined(Q_OS_WIN)
    wchar_t* path = nullptr;
    if (SHGetKnownFolderPath(FOLDERID_Startup, 0, nullptr, &path) != S_OK)
        return false;
    QString shortcutPath = QString::fromWCharArray(path) + "\\" + appName + ".lnk";
    CoTaskMemFree(path);
    return QFile::exists(shortcutPath);
#elif defined(Q_OS_MAC)
    QString plistFile = QDir::homePath() + "/Library/LaunchAgents/com." + appName.toLower() + ".plist";
    return QFile::exists(plistFile);
#else
    return false;
#endif
}
