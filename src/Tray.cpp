#include "Tray.hpp"

#include <qcoreapplication.h>
#include <QMenu>
#include <fmt/base.h>

#include "AutoStart.hpp"
#include "Constants.hpp"

Tray::Tray(const QIcon &icon, const QWidget *mainWindow, QObject *parent) {
	m_trayIcon = new QSystemTrayIcon(icon, parent);

	m_tray_menu = new QMenu;

	m_action_show = m_tray_menu->addAction("Show");
	connect(m_action_show, &QAction::triggered, mainWindow, &QWidget::show);

	m_action_hide = m_tray_menu->addAction("Hide");
	connect(m_action_hide, &QAction::triggered, mainWindow, &QWidget::hide);

	m_action_autostart = m_tray_menu->addAction("Autostart");
	connect(m_action_autostart, &QAction::triggered, this, &Tray::toggleAutostart);

	m_tray_menu->addSeparator();

	m_action_quit = m_tray_menu->QWidget::addAction("Quit");
	connect(m_action_quit, &QAction::triggered, mainWindow, &QCoreApplication::quit);

	m_trayIcon->setContextMenu(m_tray_menu);
	m_trayIcon->setToolTip(APP_NAME);
	m_trayIcon->show();

	// Set initial text
	m_action_autostart->setText(
		AutoStart::isEnabled(m_appName) ? "✅ Autostart" : "Autostart"
	);
}

void Tray::toggleAutostart() {
	bool enabled = AutoStart::isEnabled(m_appName);
	if (enabled) {
		AutoStart::disable(m_appName);
	} else {
		AutoStart::enable(m_appName, m_execPath, m_iconPath);
	}

	m_action_autostart->setText(
		AutoStart::isEnabled(m_appName) ? "✅ Autostart" : "Autostart"
	);
}

bool Tray::isTrayVisible() const {
	return m_trayIcon->isVisible();
}

void Tray::showIconMessage(const QString &title, const QString &message) const {
	m_trayIcon->showMessage(title, message, QSystemTrayIcon::Information, 3000);
}
