#include "window.h"
#include "sudoku.h"
#include <QApplication>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;

    window.show();

    std::vector<std::vector<int>> grid = load_sudoku("../sudoku.txt");
    sudoku_grid* board = new sudoku_grid(grid);

    window.set_grid(board);

    board->solve();

    return app.exec();
}
