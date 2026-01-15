/**
 * SPDX-FileCopyrightText: 2021 Mikhail Zolotukhin <mail@gikari.com>
 *
 * SPDX-License-Identifier: MIT
 */
#pragma once

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <KCModule>
#else
#include <KQuickAddons/ManagedConfigModule>
#endif

#include "bismuth_config.h"

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
class BismuthSettings : public KCModule
#else
class BismuthSettings : public KQuickAddons::ManagedConfigModule
#endif
{
    Q_OBJECT

    Q_PROPERTY(Bismuth::Config *config READ config CONSTANT)

public:
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    BismuthSettings(QObject *parent, const KPluginMetaData &data);
#else
    BismuthSettings(QObject *parent, const QVariantList &args);
#endif
    virtual ~BismuthSettings() override = default;

    Bismuth::Config *config() const;

public Q_SLOTS:
    void save() override;

private:
    void reloadKWinScript() const;

    Bismuth::Config *m_config;
};
