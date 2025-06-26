#pragma once

#include <QSystemTrayIcon>
#include <QIcon>
#include <QWidget>
#include <QObject>

class Tray final : public QObject {
	Q_OBJECT

	QSystemTrayIcon *m_trayIcon;
	QMenu *m_tray_menu;
	QAction *m_action_show;
	QAction *m_action_hide;
	QAction *m_action_quit;

	// Autostart action
	QAction *m_action_autostart;
	QString m_appName;
	QString m_execPath;
	QString m_iconPath;

private slots:
	void toggleAutostart();

public:
	Tray(const QIcon &icon, const QWidget *mainWindow, const QString &iconPath, QObject *parent = nullptr);

	[[nodiscard]] bool isTrayVisible() const;

	void showIconMessage(const QString &title, const QString &message) const;
};
