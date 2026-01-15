# SPDX-FileCopyrightText: 2021 Mikhail Zolotukhin <mail@gikari.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.16)

project(bismuth-kcm)

add_library(kcm_bismuth MODULE)

if(QT_MAJOR_VERSION EQUAL 6)
  qt6_add_dbus_interface(kwin_dbus_srcs org.kde.KWin.xml kwin_interface)
else()
  qt_add_dbus_interface(kwin_dbus_srcs org.kde.KWin.xml kwin_interface)
endif()

target_sources(kcm_bismuth PRIVATE bismuth.cpp ${kwin_dbus_srcs})

if(QT_MAJOR_VERSION EQUAL 6)
  target_link_libraries(
    kcm_bismuth
    PRIVATE Qt6::Core
            Qt6::DBus
            Qt6::Quick
            KF6::CoreAddons
            KF6::I18n
            KF6::KCMUtils
            KF6::KCMUtilsQuick
            KF6::ConfigCore
            KF6::ConfigWidgets)
else()
  target_link_libraries(
    kcm_bismuth
    PRIVATE Qt5::Core
            Qt5::DBus
            KF5::CoreAddons
            KF5::I18n
            KF5::QuickAddons
            KF5::ConfigCore
            KF5::ConfigGui)
endif()

kconfig_add_kcfg_files(kcm_bismuth GENERATE_MOC "bismuth_config.kcfgc")
kcoreaddons_desktop_to_json(kcm_bismuth "package/metadata.desktop")

install(TARGETS kcm_bismuth DESTINATION ${KDE_INSTALL_PLUGINDIR}/kcms)

if(QT_MAJOR_VERSION EQUAL 6)
  install(
    FILES package/metadata.desktop
    RENAME kcm_bismuth.desktop
    DESTINATION ${KDE_INSTALL_APPDATA_DIR})
else()
  install(
    FILES package/metadata.desktop
    RENAME kcm_bismuth.desktop
    DESTINATION ${KDE_INSTALL_KSERVICES5DIR})
endif()

kpackage_install_package(package kcm_bismuth kcms)

add_subdirectory(icons)
