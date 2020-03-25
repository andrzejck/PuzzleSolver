//
// Created by ar on 11.01.20.
//

#include "PuzzleList.h"

bool comparePuzzle(Puzzle * l1, const Puzzle * l2){
    return l1->getArea() > l2->getArea();
}

/*PuzzleList::PuzzleList(){
  puzzleList = std::vector<std::shared_ptr<Puzzle>>();
}*/



//void PuzzleList::generateSimplified2() {
//
//    Puzzle t("");
//
//    //t = Puzzle("0");
//    /*t = Puzzle("0");
//      t.addPoint(Point(0,0));
//      t.addPoint(Point(363,0));
//      t.addPoint(Point(0,363));
//      t.setSidesIterable(3);
//      t.calculate();
//      puzzleList.push_back(t);
//      puzzleIds[t.getId()]++;*/
//
//    t = Puzzle("0|1");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(510,0));
//    t.addPoint(Point(255,255));
//    t.setSidesIterable(3);
//    t.setMinSpan(250);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t =  Puzzle("0|1");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(510,0));
//    t.addPoint(Point(255,255));
//    t.setSidesIterable(3);
//    t.setMinSpan(250);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("13+11");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(365,0));
//    t.addPoint(Point(365,365));
//    t.addPoint(Point(0,365));
//    t.setSidesIterable(1);
//    t.setMinSpan(350);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    //=============================
//
//    t = Puzzle("16");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(144,0));
//    t.addPoint(Point(0,144));
//    t.setSidesIterable(3);
//    t.setMinSpan(95);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("18");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(145,0));
//    t.addPoint(Point(145,145));
//    t.addPoint(Point(0,145));
//    t.setSidesIterable(1);
//    t.setMinSpan(140);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("17");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(290,150));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(2);
//    t.setMinSpan(145);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//
//    t = Puzzle("2|3");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(0,290));
//    t.setSidesIterable(3);
//    t.setMinSpan(200);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("2|3");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(0,290));
//    t.setSidesIterable(3);
//    t.setMinSpan(200);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("4");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(435,0));
//    t.addPoint(Point(150,292));
//    t.addPoint(Point(0,292));
//    t.setSidesIterable(4);
//    t.setMinSpan(285);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//    t = Puzzle("6|7");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(555,0));
//    t.addPoint(Point(160,160));
//    t.setSidesIterable(3);
//    t.setMinSpan(150);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("6|7");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(555,0));
//    t.addPoint(Point(160,160));
//    t.setSidesIterable(3);
//    t.setMinSpan(150);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//    t = Puzzle("9");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(170,0));
//    t.addPoint(Point(210,360));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(4);
//    t.setMinSpan(180);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//    t = Puzzle("15");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(440,0));
//    t.addPoint(Point(360,160));
//    t.addPoint(Point(230,220));
//    t.setSidesIterable(4);
//    t.setMinSpan(210);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("10");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(405,0));
//    t.addPoint(Point(100,300));
//    t.setSidesIterable(3);
//    t.setMinSpan(300);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("5");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(363,0));
//    t.addPoint(Point(50,404));
//    t.setSidesIterable(3);
//    t.setMinSpan(290);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//    t = Puzzle("12");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(440,0));
//    t.addPoint(Point(340,270));
//    t.addPoint(Point(210,220));
//    t.addPoint(Point(155,350));
//    t.setSidesIterable(5);
//    t.setMinSpan(350);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//
////
////    t = Puzzle("14+8");
////    t.addPoint(Point(0,0));
////    t.addPoint(Point(570,0));
////    t.addPoint(Point(220,360));
////    t.addPoint(Point(0,150));
////    t.setSidesIterable(4);
////    t.setMinSpan(350);
////    t.setTwoSided(true);
////    t.calculate();
////    puzzleList.push_back(t);
////    puzzleIds[t.getId()]++;
//
//
//    t = Puzzle("14");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(570,0));
//    t.addPoint(Point(430,160));
//    t.addPoint(Point(220,160));
//    t.addPoint(Point(220,360));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(6);
//    t.setTwoSided(true);
//    t.setMinSpan(350);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("8");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(200,0));
//    t.addPoint(Point(0,200));
//    t.setSidesIterable(3);
//    t.setMinSpan(150);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//    /*t = Puzzle("12+16");
//     t.addPoint(Point(0,0));
//     t.addPoint(Point(440,0));
//     t.addPoint(Point(340,270));
//
//     t.addPoint(Point(155,350));
//     t.setSidesIterable(4);
//     t.setTwoSided(true);
//     t.calculate();
//
//     puzzleList.push_back(t);
//     puzzleIds[t.getId()]++;*/
//
//    calculateMins();
//    //std::cout << "************** genrated ************" << this->size() << std::endl;
//}

void PuzzleList::generateSimplified() {

   Puzzle * t;

  //t = Puzzle("0");
  /*t = Puzzle("0");
    t.addPoint(Point(0,0));
    t.addPoint(Point(363,0));
    t.addPoint(Point(0,363));
    t.setSidesIterable(3);
    t.calculate();
    puzzleList.push_back(t);
    puzzleIds[t.getId()]++;*/

    t = new Puzzle("0|1");
    t->addPoint(Point(0,0));
    t->addPoint(Point(510,0));
    t->addPoint(Point(255,255));
    t->setSidesIterable(3);
    t->setMinSpan(250);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

    t = new Puzzle("0|1");
    t->addPoint(Point(0,0));
    t->addPoint(Point(510,0));
    t->addPoint(Point(255,255));
    t->setSidesIterable(3);
    t->setMinSpan(250);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

    t = new Puzzle("13+11");
    t->addPoint(Point(0,0));
    t->addPoint(Point(365,0));
    t->addPoint(Point(365,365));
    t->addPoint(Point(0,365));
    t->setSidesIterable(1);
    t->setMinSpan(350);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

    //=============================

    t = new Puzzle("16");
    t->addPoint(Point(0,0));
    t->addPoint(Point(144,0));
    t->addPoint(Point(0,144));
    t->setSidesIterable(3);
    t->setMinSpan(95);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

    t = new Puzzle("18");
    t->addPoint(Point(0,0));
    t->addPoint(Point(145,0));
    t->addPoint(Point(145,145));
    t->addPoint(Point(0,145));
    t->setSidesIterable(1);
    t->setMinSpan(140);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

    t = new Puzzle("17");
    t->addPoint(Point(0,0));
    t->addPoint(Point(290,0));
    t->addPoint(Point(290,150));
    t->addPoint(Point(0,150));
    t->setSidesIterable(2);
    t->setMinSpan(145);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;




    t = new Puzzle("2|3");
    t->addPoint(Point(0,0));
    t->addPoint(Point(290,0));
    t->addPoint(Point(0,290));
    t->setSidesIterable(3);
    t->setMinSpan(200);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

   t = new Puzzle("2|3");
   t->addPoint(Point(0,0));
   t->addPoint(Point(290,0));
   t->addPoint(Point(0,290));
   t->setSidesIterable(3);
   t->setMinSpan(200);
   t->calculate();
   puzzleList.push_back(t);
   puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

  t = new Puzzle("4");
  t->addPoint(Point(0,0));
  t->addPoint(Point(435,0));
  t->addPoint(Point(150,292));
  t->addPoint(Point(0,292));
  t->setSidesIterable(4);
  t->setMinSpan(285);
  t->setTwoSided(true);
  t->calculate();
  puzzleList.push_back(t);
  puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;



  t = new Puzzle("6|7");
  t->addPoint(Point(0,0));
  t->addPoint(Point(555,0));
  t->addPoint(Point(160,160));
  t->setSidesIterable(3);
  t->setMinSpan(150);
  t->setTwoSided(true);
  t->calculate();
  puzzleList.push_back(t);
  puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

  t = new Puzzle("6|7");
  t->addPoint(Point(0,0));
  t->addPoint(Point(555,0));
  t->addPoint(Point(160,160));
  t->setSidesIterable(3);
  t->setMinSpan(150);
  t->setTwoSided(true);
  t->calculate();
  puzzleList.push_back(t);
  puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;


  t = new Puzzle("9");
  t->addPoint(Point(0,0));
  t->addPoint(Point(170,0));
  t->addPoint(Point(210,360));
  t->addPoint(Point(0,150));
  t->setSidesIterable(4);
  t->setMinSpan(180);
  t->setTwoSided(true);
  t->calculate();
  puzzleList.push_back(t);
  puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;



    t = new Puzzle("15");
    t->addPoint(Point(0,0));
    t->addPoint(Point(440,0));
    t->addPoint(Point(360,160));
    t->addPoint(Point(230,220));
    t->setSidesIterable(4);
    t->setMinSpan(210);
    t->setTwoSided(true);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

    t = new Puzzle("10");
    t->addPoint(Point(0,0));
    t->addPoint(Point(405,0));
    t->addPoint(Point(100,300));
    t->setSidesIterable(3);
    t->setMinSpan(300);
    t->setTwoSided(true);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;

    t = new Puzzle("5");
    t->addPoint(Point(0,0));
    t->addPoint(Point(363,0));
    t->addPoint(Point(50,404));
    t->setSidesIterable(3);
    t->setMinSpan(290);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;


    t = new Puzzle("12");
    t->addPoint(Point(0,0));
    t->addPoint(Point(440,0));
    t->addPoint(Point(340,270));
    t->addPoint(Point(210,220));
    t->addPoint(Point(155,350));
    t->setSidesIterable(5);
    t->setMinSpan(350);
    t->setTwoSided(true);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;





    t = new Puzzle("14+8");
    t->addPoint(Point(0,0));
    t->addPoint(Point(570,0));
    t->addPoint(Point(220,360));
    t->addPoint(Point(0,150));
    t->setSidesIterable(4);
    t->setMinSpan(350);
    t->setTwoSided(true);
    t->calculate();
    puzzleList.push_back(t);
    puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;


    /*t = new Puzzle("12+16");
     t->addPoint(Point(0,0));
     t->addPoint(Point(440,0));
     t->addPoint(Point(340,270));

     t->addPoint(Point(155,350));
     t->setSidesIterable(4);
     t->setTwoSided(true);
     t->calculate();

     puzzleList.push_back(t);
     puzzleIds[t->getId()]++; puzzleIdsMap[t->getId()]=t;*/

    calculateMins();
 //std::cout << "************** genrated ************" << this->size() << std::endl;
}

//void PuzzleList::generateSimplified1() {
//
//    Puzzle t("");
//
//    //t = Puzzle("0");
//    /*t = Puzzle("0");
//      t.addPoint(Point(0,0));
//      t.addPoint(Point(363,0));
//      t.addPoint(Point(0,363));
//      t.setSidesIterable(3);
//      t.calculate();
//      puzzleList.push_back(t);
//      puzzleIds[t.getId()]++;*/
//
//    t = Puzzle("0|1");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(510,0));
//    t.addPoint(Point(255,255));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t =  Puzzle("0|1");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(510,0));
//    t.addPoint(Point(255,255));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("13+11");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(365,0));
//    t.addPoint(Point(365,365));
//    t.addPoint(Point(0,365));
//    t.setSidesIterable(1);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    //=============================
//
//    t = Puzzle("16");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(144,0));
//    t.addPoint(Point(0,144));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    /*t = Puzzle("18");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(145,0));
//    t.addPoint(Point(145,145));
//    t.addPoint(Point(0,145));
//    t.setSidesIterable(1);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;*/
//
//    t = Puzzle("17");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(290,150));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(2);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//
//    t = Puzzle("2");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(0,290));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("3");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(0,290));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("4");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(435,0));
//    t.addPoint(Point(150,292));
//    t.addPoint(Point(0,292));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//    t = Puzzle("6+7");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(160,0));
//    t.addPoint(Point(555,160));
//    t.addPoint(Point(160,320));
//    t.setSidesIterable(4);
//    t.setTwoSided(false);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
////    t = Puzzle("6|7");
////    t.addPoint(Point(0,0));
////    t.addPoint(Point(555,0));
////    t.addPoint(Point(160,160));
////    t.setSidesIterable(3);
////    t.setTwoSided(true);
////    t.calculate();
////    puzzleList.push_back(t);
////    puzzleIds[t.getId()]++;
//
//
//    t = Puzzle("9");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(170,0));
//    t.addPoint(Point(210,360));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//    t = Puzzle("15");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(440,0));
//    t.addPoint(Point(360,160));
//    t.addPoint(Point(230,220));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("10");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(405,0));
//    t.addPoint(Point(100,300));
//    t.setSidesIterable(3);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("5");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(363,0));
//    t.addPoint(Point(50,404));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//    t = Puzzle("12");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(440,0));
//    t.addPoint(Point(340,270));
//    t.addPoint(Point(210,220));
//    t.addPoint(Point(155,350));
//    t.setSidesIterable(5);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//
//
//    t = Puzzle("14+8");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(570,0));
//    t.addPoint(Point(220,360));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//    /*t = Puzzle("12+16");
//     t.addPoint(Point(0,0));
//     t.addPoint(Point(440,0));
//     t.addPoint(Point(340,270));
//
//     t.addPoint(Point(155,350));
//     t.setSidesIterable(4);
//     t.setTwoSided(true);
//     t.calculate();
//
//     puzzleList.push_back(t);
//     puzzleIds[t.getId()]++;*/
//
//
//    //std::cout << "************** genrated ************" << this->size() << std::endl;
//}
//
//
//void PuzzleList::generate() {
//
//    Puzzle t("");
//
//    //t = Puzzle("0");
//    /*t = Puzzle("0");
//      t.addPoint(Point(0,0));
//      t.addPoint(Point(363,0));
//      t.addPoint(Point(0,363));
//      t.setSidesIterable(3);
//      t.calculate();
//      puzzleList.push_back(t);
//      puzzleIds[t.getId()]++;*/
//
//    t = Puzzle("0|1");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(510,0));
//    t.addPoint(Point(255,255));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t =  Puzzle("0|1");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(510,0));
//    t.addPoint(Point(255,255));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("13+11");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(365,0));
//    t.addPoint(Point(365,365));
//    t.addPoint(Point(0,365));
//    t.setSidesIterable(1);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    //=============================
//
//    t = Puzzle("16");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(144,0));
//    t.addPoint(Point(0,144));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("18");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(145,0));
//    t.addPoint(Point(145,145));
//    t.addPoint(Point(0,145));
//    t.setSidesIterable(1);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("17");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(290,150));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(2);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//
//    t = Puzzle("2");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(0,290));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("3");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(290,0));
//    t.addPoint(Point(0,290));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("4");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(435,0));
//    t.addPoint(Point(150,292));
//    t.addPoint(Point(0,292));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//    t = Puzzle("6|7");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(555,0));
//    t.addPoint(Point(160,160));
//    t.setSidesIterable(3);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("6|7");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(555,0));
//    t.addPoint(Point(160,160));
//    t.setSidesIterable(3);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//    t = Puzzle("9");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(170,0));
//    t.addPoint(Point(210,360));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//    t = Puzzle("15");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(440,0));
//    t.addPoint(Point(360,160));
//    t.addPoint(Point(230,220));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("10");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(405,0));
//    t.addPoint(Point(100,300));
//    t.setSidesIterable(3);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("5");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(363,0));
//    t.addPoint(Point(50,404));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//    t = Puzzle("12");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(440,0));
//    t.addPoint(Point(340,270));
//    t.addPoint(Point(210,220));
//    t.addPoint(Point(155,350));
//    t.setSidesIterable(5);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//
//
//
//
///*    t = Puzzle("14+8");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(570,0));
//    t.addPoint(Point(220,360));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(4);
//    t.setTwoSided(true);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;*/
//
//    t = Puzzle("14");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(570,0));
//    t.addPoint(Point(430,160));
//    t.addPoint(Point(220,160));
//    t.addPoint(Point(220,360));
//    t.addPoint(Point(0,150));
//    t.setSidesIterable(6);
//    t.setTwoSided(true);
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    t = Puzzle("8");
//    t.addPoint(Point(0,0));
//    t.addPoint(Point(200,0));
//    t.addPoint(Point(0,200));
//    t.setSidesIterable(3);
//    t.calculate();
//    puzzleList.push_back(t);
//    puzzleIds[t.getId()]++;
//
//    /*t = Puzzle("12+16");
//     t.addPoint(Point(0,0));
//     t.addPoint(Point(440,0));
//     t.addPoint(Point(340,270));
//
//     t.addPoint(Point(155,350));
//     t.setSidesIterable(4);
//     t.setTwoSided(true);
//     t.calculate();
//
//     puzzleList.push_back(t);
//     puzzleIds[t.getId()]++;*/
//
//
//    //std::cout << "************** genrated ************" << this->size() << std::endl;
//}

bool PuzzleList::operator==(const PuzzleList &rhs) const {
    return puzzleIds == rhs.puzzleIds;
}

bool PuzzleList::operator!=(const PuzzleList &rhs) const {
    return !(rhs == *this);
}

float PuzzleList::getMinAngle() const {
    return minAngle;
}

float PuzzleList::getMinSpan() const {
    return minSpan;
}
