#include "window.h"
#include <QPainter>
#include <QLabel>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QTextStream>
#include <QMessageBox>
#include <QGridLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>
#include <QGroupBox>
#include <QTime>
#include <map>
#include <vector>


using namespace std;

// Main window class
Window::Window(QWidget *parent) : QWidget(parent)
{
   // set a minimum size for the window
   setMinimumSize(700,700);
   setWindowTitle("Sudoku");

   // create widgets....
   QVBoxLayout *vbox = new QVBoxLayout(this);
   vbox -> setSpacing(1);
   QHBoxLayout *hbox = new QHBoxLayout(this);
   hbox -> setSpacing(1);

   QPushButton *open = new QPushButton("Open",this);
   open -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   connect(open, &QPushButton::clicked, this, &Window::openSudo);

   QPushButton *close = new QPushButton("Close",this);
   close -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   connect(close, &QPushButton::clicked, qApp, &QApplication::quit);

   QPushButton *solve = new QPushButton("Solve",this);
   solve -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   connect(solve, &QPushButton::clicked, this, &Window::solveSudo);

   QPushButton *save = new QPushButton("Save",this);
   save -> setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   connect(save, &QPushButton::clicked, this, &Window::saveSudo);

   text = new QLabel(" Click on the 'open' button to start a new game.",this);
   text -> setFont(QFont("Purisa",8));

   time = new QLabel("", this);
   time -> setText("Time: " + QTime(0,0).toString("m:s"));


   hbox -> addWidget(open,0,Qt::AlignLeft);
   hbox -> addWidget(close,0,Qt::AlignLeft);
   hbox -> addWidget(solve,0,Qt::AlignLeft);
   hbox -> addWidget(save,0,Qt::AlignLeft);
   hbox -> addStretch(1);
   hbox -> addWidget(time,0,Qt::AlignRight|Qt::AlignTop);



   vbox -> addLayout(hbox);
   vbox -> addSpacing(5);
   vbox -> addWidget(text);
   vbox -> addStretch(1);
   setLayout(vbox);

}

void Window::openSudo()
{
    text -> setText("Enjoy playing this game.");
    grid = new sudoku_grid(load_sudoku("../sudoku.txt"));
    set_grid(grid);
    QTime qtime = QTime::currentTime();
    startTime = QTime(0,0,0).secsTo(qtime);
    startTimer(1000);
    run = true;
    repaint();
}
void Window::solveSudo()
{
    grid->output();
    grid_solved.output();
   if(*grid == grid_solved){
        run = false;
        QString timeDiff = QString::number(diff/60)+ " minutes " + QString::number(diff%60) + " seconds to solve this.";
        text -> setText("Congradulation for solving this sudoku!It takes you " + timeDiff);
   }else{
        text -> setText("Try harder...");
   }
    repaint();
}

void Window::saveSudo(){
    QString filename = "../saveSudoku.txt";
    store_sudoku(grid->get_grid(),filename);
    text -> setText("Saved");
}

void Window::set_grid(sudoku_grid* new_grid)
{
    grid = new_grid;
    grid_solved = *grid;
    grid_solved.solve();
    viewer = sudoku_grid_viewer(grid);
    controller = sudoku_grid_controller(grid);
}


void Window::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    viewer.display_grid(&painter, 5, 2, width(), height());
}

void Window::timerEvent(QTimerEvent *event)
{
    if(run==true){
        Q_UNUSED(event);
        QTime qtime = QTime::currentTime();
        int temp = QTime(0,0,0).secsTo(qtime);
        diff = temp - startTime;
        QString timeDiff = "Time: " + QString::number(diff/60)+ ":" + QString::number(diff%60);
        time -> setText(timeDiff);
    }else{
           time -> setText("Time: " + QTime(0,0).toString("m:s"));
    }
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    controller.manage_grid_click(event->x(), event->y(), height(), width());
    repaint();
}

