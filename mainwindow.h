#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include "PuzzleList.h"



#include "PuzzleOnBoard.h"
#include "Layout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

    void setPuzzleOnBoard(PuzzleOnBoard * _puzzleOnBoard);
    void setPuzzlesOnBoard(std::vector<PuzzleOnBoard> & _puzzlesOnBoard){
        puzzlesOnBoard = _puzzlesOnBoard;
    }
    void addPolygon(Polygon * polygon){
        polygons.push_back(polygon);
    }

    void setLayout(Layout * _layout){
        layout = _layout;
    }

    void clearPolygons(){
        polygons.clear();
    }
    /*void setPuzzleOnBoard(const PuzzleOnBoard &_puzzleOnBoard){
        puzzleOnBoard=_puzzleOnBoard;
    }*/
signals:
    void pPaintPuzzle();



private:
    Ui::MainWindow *ui;

    PuzzleOnBoard * puzzleOnBoard;
    std::vector<PuzzleOnBoard> puzzlesOnBoard;
    std::vector<Polygon*> polygons;
    Layout * layout;
private slots:
    void sPaintPuzzle();
};


#endif // MAINWINDOW_H
