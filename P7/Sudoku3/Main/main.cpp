#include "window.h"
#include <QWidget>
#include "sudoku.h"
#include <QApplication>
#include <QTextStream>
#include <QFileInfo>
#include <QVector>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;

    window.show();

    sudoku_grid board(3);

    window.set_grid(&board);

    return app.exec();
}
