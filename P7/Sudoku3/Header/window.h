#ifndef WINDOW_H
#define WINDOW_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <vector>
#include <map>
#include "sudoku.h"

using namespace std;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    void set_grid(sudoku_grid* new_grid);
protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

public slots:
    void openSudo();
    void solveSudo();
    void mouseReleaseEvent(QMouseEvent *event) override;
    void saveSudo();

private:
    QLabel *text;
    QLabel *time;
    int startTime, diff;
    bool run;
    sudoku_grid *grid;
    sudoku_grid grid_solved;
    sudoku_grid_viewer viewer;
    sudoku_grid_controller controller;
};

#endif
