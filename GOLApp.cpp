// GOLApp.cpp
//
// Placeholder file with main
// replace with your own test code
// do not turn in

#include "BasicGOL.h"
#include "ThreeStateGOL.h"
#include "WrapAroundGOL.h"
#include "RollingHistory.h"
 
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

int main(int argc, char **argv){
   try{
      BasicGOL game1(4, 4, "XOXOXOXXOOXOXOXO");
      RollingHistory history(3);
      history.AddGame(game1.clone());
      game1.NextGen();
      history.AddGame(game1.clone());
      game1.NextGen();
      history.AddGame(game1.clone());
      game1.NextGen();
      history.AddGame(game1.clone());
      game1.NextGen();
      history.AddGame(game1.clone());
      history.PrintHistory();
      game1.NextGen();
      std::cout << "***\n";
      history.AddGame(game1.clone());
      history.PrintHistory();
      game1.NextGen();
      std::cout << "&&&&\n";
      history.AddGame(game1.clone());
      history.PrintHistory();
      history.GetNewest()->PrintGame();
      history.GetOldest()->PrintGame();

      //BasicGOL game2(4, 4, "XXOXOXXOOXOXOOXO", 10);
      // ThreeStateGOL game2(2, 2, "XOXX");
      //WrapAroundGOL game3(5, 5, "XXXXXXXOXXXXXOXXOOOXXXXXX");
      //ThreeStateGOL game4(6, 5, "XXXXXXXDOODXXOXXOXXDOODXXXXXXX");
     // --game1;
     // game1.PrintGame();
      
     // WrapAroundGOL game4(5, 5, "XXXXXOOOXXXXXOOXXXOOXXXXX");
     // game4.PrintGame();
     // --game4;
      
      
      //game1.NextGen();
      // game2.NextGen();
      //game3.NextGen();
      //game3.PrintGame();
      //++game3;
      //game3.PrintGame();
      //++game3;
      //game3.PrintGame();
      //game3.NextNGen(2);
      //game3.PrintGame();
      //game4.PrintGame();
      //game4.NextNGen(2);
      //game4.PrintGame();
      //ThreeStateGOL game5(3, 3, "XOXXOXXOX");
      //game5.NextGen();
      //--game5;
      //game5.PrintGame();
   
      
     /*
      game1.PrintGame();
      game1.NextNGen(0);
      game1.PrintGame();
      game1.ToggleCell(0);
      game1.PrintGame();
      game1+=2;
      game1.PrintGame();
      ++game1;
      game1.PrintGame();
      game1 = game2;
      game1.PrintGame();
      game3.PrintGame();
      */
   }
   catch (std::out_of_range &e){
      std::cerr << "Out of range error: " << e.what() << std::endl;
   }
   catch (std::invalid_argument &e){
      std::cerr << e.what() << std::endl;
   }
   return 0;
}
