#include "WhatsAppView.hpp"

WhatsAppView::WhatsAppView(QWidget *parent) : QWebEngineView(parent) {
}

void WhatsAppView::setTrayIcon(Tray &tray) {
	m_tray = &tray;
}

void WhatsAppView::closeEvent(QCloseEvent *event) {
	if (m_tray && m_tray->isTrayVisible()) {
		event->ignore();
		this->hide();
		m_tray->showIconMessage("WhatsApp", "Application minimized to tray.");
	} else {
		event->accept();
	}
}
