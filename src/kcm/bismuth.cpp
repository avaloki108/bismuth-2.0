/**
 * SPDX-FileCopyrightText: 2021 Mikhail Zolotukhin <mail@gikari.com>
 *
 * SPDX-License-Identifier: MIT
 */

#include "bismuth.h"
#include "bismuth_config.h"
#include "kwin_interface.h"

#include <QDBusInterface>
#include <QDebug>

#include <KAboutData>
#include <KLocalizedString>
#include <KPluginFactory>
#include <qstringliteral.h>

K_PLUGIN_CLASS_WITH_JSON(BismuthSettings, "metadata.json")

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
BismuthSettings::BismuthSettings(QObject *parent, const KPluginMetaData &data)
    : KCModule(parent, data)
#else
BismuthSettings::BismuthSettings(QObject *parent, const QVariantList &args)
    : KQuickAddons::ManagedConfigModule(parent, args)
#endif
    , m_config(new Bismuth::Config(this))
{
    KAboutData *aboutData = new KAboutData(QStringLiteral("kcm_bismuth"),
                                           i18nc("@title", "Window Tiling"),
                                           QStringLiteral("1.0"),
                                           QStringLiteral(""),
                                           KAboutLicense::LicenseKey::Custom,
                                           i18nc("@info:credit", "Copyright 2021 Mikhail Zolotukhin <mail@gikari.com>"));

    aboutData->addAuthor(i18nc("@info:credit", "Author"), i18nc("@info:credit", "Author"), QStringLiteral("author@domain.com"));

    setAboutData(aboutData);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    setButtons(Help | Apply | Default);
#endif

    qmlRegisterAnonymousType<Bismuth::Config>("org.kde.bismuth.private", 1);
}

Bismuth::Config *BismuthSettings::config() const
{
    return m_config;
}

void BismuthSettings::save()
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    KCModule::save();
#else
    KQuickAddons::ManagedConfigModule::save();
#endif
    reloadKWinScript();
}

void BismuthSettings::reloadKWinScript() const
{
    OrgKdeKwinScriptingInterface kwinInterface(QStringLiteral("org.kde.KWin"), QStringLiteral("/Scripting"), QDBusConnection::sessionBus());

    // Unload Bismuth, so that it can reload its configuration
    kwinInterface.unloadScript(QStringLiteral("bismuth")).waitForFinished(); // Sync call
    // Load unloaded scripts
    kwinInterface.start(); // Async call
}

#include "bismuth.moc"
