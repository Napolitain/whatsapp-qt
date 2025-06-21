#pragma once

#include <QSystemTrayIcon>
#include <QIcon>
#include <QWidget>
#include <QObject>

class Tray : public QObject {
	Q_OBJECT

	QSystemTrayIcon *m_trayIcon;
	QMenu *m_tray_menu;
	QAction *m_action_show;
	QAction *m_action_hide;
	QAction *m_action_quit;

public:
	Tray(const QIcon &icon, const QWidget *mainWindow, QObject *parent = nullptr);

	[[nodiscard]] bool isTrayVisible() const;

	void showIconMessage(const QString &title, const QString &message) const;
};
