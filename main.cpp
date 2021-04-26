#include <QApplication>
#include <QLoggingCategory>

#include "UI/ParametersWindow.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // включение вывода отладочной информации
    // QLoggingCategory::setFilterRules("*.debug=true");

    // Вызов главного окна программы
    auto* pw = new ParametersWindow();
    pw->show();

    // Выходим
    return QApplication::exec();
}