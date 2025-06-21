#pragma once

#include <QWebEngineProfile>
#include <QString>
#include <QObject>

class WebProfile {
	QWebEngineProfile *m_profile;

public:
	WebProfile(QObject *parent, const QString &dataDir);

	QWebEngineProfile *profile() const;
};
