#include <QApplication>
#include <QPushButton>

#include <MPK_Sound/include/MainWindow.hpp>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ruff::sound::MainWindow window;
    window.show();
    return a.exec();
}
