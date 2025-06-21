#include "Tray.hpp"

#include <qcoreapplication.h>
#include <QMenu>

#include "Constants.hpp"

Tray::Tray(const QIcon &icon, const QWidget *mainWindow, QObject *parent) {
	m_trayIcon = new QSystemTrayIcon(icon, parent);

	m_tray_menu = new QMenu;

	m_action_show = m_tray_menu->QWidget::addAction("Show");
	QObject::connect(m_action_show, &QAction::triggered, mainWindow, &QWidget::show);

	m_action_hide = m_tray_menu->QWidget::addAction("Hide");
	QObject::connect(m_action_hide, &QAction::triggered, mainWindow, &QWidget::hide);

	m_tray_menu->addSeparator();

	m_action_quit = m_tray_menu->QWidget::addAction("Quit");
	QObject::connect(m_action_quit, &QAction::triggered, parent, &QCoreApplication::quit);

	m_trayIcon->setContextMenu(m_tray_menu);
	m_trayIcon->setToolTip(APP_NAME);
	m_trayIcon->show();
}

bool Tray::isTrayVisible() const {
	return m_trayIcon->isVisible();
}

void Tray::showIconMessage(const QString &title, const QString &message) const {
	m_trayIcon->showMessage(title, message, QSystemTrayIcon::Information, 3000);
}
