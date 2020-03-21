#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPointF>
#include <iostream>
#include <QStaticText>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->setEnabled(0);
    connect(this, &MainWindow::pPaintPuzzle, this, &MainWindow::sPaintPuzzle);
    layout = nullptr;
    puzzleOnBoard = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    /*QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);*/
    if(layout == nullptr)
        return;
    /*static const QPointF points[4] = {
            QPointF(10.0, 80.0),
            QPointF(20.0, 10.0),
            QPointF(80.0, 30.0),
            QPointF(90.0, 70.0)
    };*/
    int randomOffset;
    QPointF *points;
    painter.setPen(Qt::darkBlue);
    int avgX=0;
    int avgY=0;

    for(auto p: layout->getPuzzles()) {
        points=p.asQPointF(0.6, 100, 100);
        //painter.setPen(p.getColor());
        painter.drawPolygon(points, p.pointsCount());
        avgX=0;
        avgY=0;
        for(int i=0; i < p.pointsCount(); i++){
            QStaticText qStaticText = QStaticText(QString(i));
            randomOffset = qrand() % 15;
            painter.drawText(points[i].x()+randomOffset, points[i].y()+randomOffset, QString::number(i));
            avgX = avgX + points[i].x();
            avgY = avgY + points[i].y();
        }
        painter.drawText( avgX/p.pointsCount(), avgY/p.pointsCount(), QString::fromStdString(p.getId()));

    }


    points = layout->asQPointF(0.6, 100, 100);
    painter.setPen(Qt::red);
    painter.drawPolygon(points, layout->pointsCount());
    for(int i=0; i < layout->pointsCount(); i++){
        QStaticText qStaticText = QStaticText(QString(i));
        randomOffset = qrand() % 15;
        painter.drawText(points[i].x()+randomOffset, points[i].y()+randomOffset, QString::number(i));
    }

    points = layout->asQPointFEnlarged(0.6, 100, 100);
    painter.setPen(Qt::darkRed);
    painter.drawPolygon(points, layout->pointsCount());
    for(int i=0; i < layout->pointsCount(); i++){
        QStaticText qStaticText = QStaticText(QString(i));
        randomOffset = qrand() % 15;
        painter.drawText(points[i].x()+randomOffset, points[i].y()+randomOffset, QString::number(i));
    }


    painter.setPen(Qt::darkMagenta);
    painter.setFont(QFont("Arial", 15));
    painter.drawText(rect(), Qt::AlignCenter, QString::number(layout->getPuzzles().size())
                                             +QString(" ")
                                             +QString::number(layout->getSumArea()));

    for(auto p: puzzlesOnBoard){
        points=p.asQPointF(0.6, 800, 100);
        //painter.setPen(p.getColor());
        painter.drawPolygon(points, p.pointsCount());
    }




}

void MainWindow::sPaintPuzzle() {
    //std::cout << "from main window" << "sPaintPuzzle" << std::endl;
    update();

}

void MainWindow::setPuzzleOnBoard(PuzzleOnBoard * _puzzleOnBoard) {
    puzzleOnBoard = _puzzleOnBoard;
}