# SPDX-FileCopyrightText: 2022 Mikhail Zolotukhin <mail@gikari.com>
# SPDX-License-Identifier: MIT

project(bismuth-core)

add_library(bismuth_core SHARED)
add_library(Bismuth::Core ALIAS bismuth_core)

ecm_qt_declare_logging_category(
  BISMUTH_LOG
  HEADER
  logger.hpp
  IDENTIFIER
  Bi
  CATEGORY_NAME
  org.kde.bismuth
  DEFAULT_SEVERITY
  Debug
  EXPORT
  Bismuth
  DESCRIPTION
  "Bismuth Plasma Tiling Extension")

add_subdirectory(kconf_update)

target_sources(bismuth_core PRIVATE qml-plugin.cpp ts-proxy.cpp controller.cpp
                                    qmldir ${BISMUTH_LOG})

if(QT_MAJOR_VERSION EQUAL 6)
  target_link_libraries(
    bismuth_core
    PRIVATE Qt6::Core
            Qt6::Quick
            Qt6::Qml
            KF6::ConfigCore
            KF6::ConfigWidgets
            KF6::GlobalAccel
            KF6::I18n)
else()
  target_link_libraries(
    bismuth_core
    PRIVATE Qt5::Core
            Qt5::Quick
            Qt5::Qml
            KF5::ConfigCore
            KF5::ConfigWidgets
            KF5::GlobalAccel
            KF5::I18n)
endif()

kconfig_add_kcfg_files(bismuth_core GENERATE_MOC "config.kcfgc")

ecm_qt_install_logging_categories(
  EXPORT Bismuth FILE bismuth.categories DESTINATION
  ${KDE_INSTALL_LOGGINGCATEGORIESDIR})

install(FILES "qmldir" DESTINATION "${KDE_INSTALL_QMLDIR}/org/kde/bismuth/core")

install(TARGETS bismuth_core
        DESTINATION "${KDE_INSTALL_QMLDIR}/org/kde/bismuth/core")
