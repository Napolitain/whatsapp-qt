#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>

#include "Constants.hpp"
#include "WebProfile.hpp"
#include "WhatsAppView.hpp"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    // Prepare a folder in AppDataLocation for persistent data
    const QString dataDir = QStandardPaths::writableLocation(
                                QStandardPaths::AppDataLocation) + QDir::separator() + APP_NAME;
    QDir().mkpath(dataDir);


    // Create profile with custom user agent
    WebProfile webProfile(&app, dataDir);
    auto *profile = webProfile.profile();

    // Create page with profile
    QWebEnginePage *page = new QWebEnginePage(profile);

    // Create our custom view
    WhatsAppView *view = new WhatsAppView();
    view->setPage(page);
    view->setUrl(QUrl(URL));
    view->resize(1400, 1000);
    view->show();

    // Create tray icon
    const QIcon appIcon(ICON);
    QApplication::setWindowIcon(appIcon);

    Tray tray(appIcon, view);
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

