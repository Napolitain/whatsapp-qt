#include <QApplication>
#include <QMenu>
#include <QIcon>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <glog/logging.h>

#include "Constants.hpp"
#include "WebProfile.hpp"
#include "WhatsAppView.hpp"
#include "AppRegistration.hpp"

int main(int argc, char *argv[]) {
    // Initialize Google Log
    google::InitGoogleLogging(argv[0]);

    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    if (!AppRegistration::isRegistered()) {
        LOG(INFO) << "Registering application";
        AppRegistration::registerApp();
    }

    // Prepare a folder in AppDataLocation for persistent data
    const QString dataDir = QStandardPaths::writableLocation(
                                QStandardPaths::AppDataLocation) + QDir::separator() + APP_NAME;
    QDir().mkpath(dataDir);


    // Create profile with custom user agent
    const WebProfile webProfile(&app, dataDir);
    const auto profile = webProfile.profile();

    // Create page with profile
    const auto page = new QWebEnginePage(profile);

    // Create our custom view
    const auto view = new WhatsAppView();
    view->setPage(page);
    view->setUrl(QUrl(URL));
    view->resize(1400, 1000);
    view->show();

    // Create tray icon
    const QIcon appIcon(ICON_RES);
    QApplication::setWindowIcon(appIcon);

    Tray tray(appIcon, view, ICON_RES);
    view->setTrayIcon(tray);

    // Handle notifications permission request
    QObject::connect(page, &QWebEnginePage::featurePermissionRequested,
                     [&](const QUrl &securityOrigin, const QWebEnginePage::Feature feature) {
                         if (feature == QWebEnginePage::Notifications) {
                             page->setFeaturePermission(
                                 securityOrigin,
                                 QWebEnginePage::Notifications,
                                 QWebEnginePage::PermissionGrantedByUser
                             );
                         }
                     }
    );

    return QApplication::exec();
}

