#include "WebProfile.hpp"

WebProfile::WebProfile(QObject *parent, const QString &dataDir) {
	m_profile = new QWebEngineProfile(QStringLiteral("MyWhatsAppProfile"), parent);
	m_profile->setHttpUserAgent(
		"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
		"(KHTML, like Gecko) Chrome/137.0.0.0 Safari/537.36");
	m_profile->setPersistentCookiesPolicy(QWebEngineProfile::ForcePersistentCookies);
	m_profile->setCachePath(dataDir + "/cache");
	m_profile->setPersistentStoragePath(dataDir + "/storage");
}

QWebEngineProfile *WebProfile::profile() const {
	return m_profile;
}
