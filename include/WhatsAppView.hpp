#pragma once

#include <QWebEngineView>
#include <QCloseEvent>

#include "Tray.hpp"

class WhatsAppView : public QWebEngineView {
	Q_OBJECT

	Tray *m_tray;

protected:
	void closeEvent(QCloseEvent *event) override;

public:
	explicit WhatsAppView(QWidget *parent = nullptr);

	void setTrayIcon(Tray &tray);
};
