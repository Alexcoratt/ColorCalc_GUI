#include "mainwindow.h"
#include <iostream>

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <namedfield.h>

#include <BaseConfigManager.hpp>
#include <JSONConfigManager.hpp>

#define BASE_CONFIG_FILE "color_calc.conf"

int main(int argc, char *argv[])
{
    if (argc > 2) {
        printf("Usage: %s <base_config_file>\n", argv[0]);
        return -1;
    }

    std::string baseConf;
    if (argc == 1)
        baseConf = BASE_CONFIG_FILE;
    else
        baseConf = argv[1];

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "ColorCalc_GUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    BaseConfigManager conf(baseConf);
    JSONConfigManager configManager{conf.getConfigFileName(), conf.getQuiet()};

    MainWindow w(&configManager);
    w.show();

    return a.exec();
}
