/**************************************************************************************
*                    
*  Author:           Noah Orta
*  Email:            noahraulscout@gmail.com  
*  Label:            P03A
*  Title:            RPSLS
*  Course:           CMPS 2143
*  Semester:         Fall 2021
 * 
 * Description:
 *      This program provides players with either rock, paper, scissors, lizard, or
 *      spock; then has them battle eachother. The winner is outputted to the 
 *      terminal and each players weapon is also displayed
 *
 * Files: 
 *      main.cpp
 *      
 **************************************************************************************/

#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

#define ROCK2 u8"\U0001F5FB"
#define PAPER2 u8"\U0001F4C3"
#define SCISSORS2 u8"\U0001F52A"
#define LIZARD2 u8"\U0001F438"
#define SPOCK2 u8"\U0001F596"


struct Hands {
  const string rock = ROCK2;
  const string paper = PAPER2;
  const string scissors = SCISSORS2;
  const string lizard = LIZARD2;
  const string spock = SPOCK2;

  int aNum = 10; 

  static map< string, string > Emojis;  // stl map
  //         name  , emoji

  static map< string, string > Names;  // stl map
  //         emoji  , name

  static map< string, int > subs;      // stl map
  //         emoji  , subscripts

  static map< int, string > subsToE;   //stl map
  //         sub.   , emoji 

  static string RandHand() {
    auto it = Emojis.begin();  // iterator to front of map

    advance(it, rand() % Emojis.size());       // advance some random amnt
                                                //   of steps

    string random_hand = it->second;  // grab emoji from map

    return random_hand;  // return rand emoji
  }

  static string Rock() {
      return Emojis["rock"];
  }
  static string Paper() {
      return Emojis["paper"];
  }
  static string Scissors() {
      return Emojis["scissors"];
  }
  static string Lizard() {
      return Emojis["lizard"];
  }
  static string Spock() {
      return Emojis["spock"];
  }
};

////////////////////////////////////////////////////////////////////////////////
//
//  Description: Makes a player that is randomly assigned 2 weapons
//
//
struct Player{
    string weapon1;
    string weapon2;
    int battleWeapon; //the weapon used in the battle
    

    /**
     * Constructor guarantees a player has two different "weapons"
     */
    Player(){
        weapon1 = Hands::RandHand();
        weapon2 = Hands::RandHand();

        while(weapon2==weapon1){
            weapon2 = Hands::RandHand();
        }
    }
    // other possible methods

    ///////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Overloading the '>' operator. The left hand side is the 
    //               player1 and the right hand side is the second player2
    //               This function will say which player would win the battle 
    //               based off the weapons they have.
    //
    //  Params:      Player &rhs - the Player to the right of the '>'
    //
    //  returns:     bool        - returns weather the lhs won or not
    //
    bool operator>(Player &rhs) {

      // This is a special matrix that ditermines the winner of the game.
      // The columns go in this order: rock, paper, scissors, lizard, spock.
      // which ever element is on the left side of the > will be the element
      // we use to determine which column we go to. Then the rhs will be the 
      // row that we go to. If there's a zero then lhs loses, if there's a 1 
      // then lhs won, and if there's a 2 then there's a tie
      const int gameWinner[5][5] = {
        {2, 1, 0, 0, 1},                      //rock        sub: 0
        {0, 2, 1, 1, 0},                      //paper       sub: 1
        {1, 0, 2, 0, 1},                      //scissors    sub: 2
        {1, 0, 1, 2, 0},                      //lizard      sub: 3
        {0, 1, 0, 1, 2}                       //spock       sub: 4
      };

      int column = Hands::subs[this->weapon1];   //these will get the corresponding
      int row = Hands::subs[rhs.weapon1];        //number from the substricpt map

      int winner = gameWinner[row][column];   //go to lhs sub and rhs sub

      this->battleWeapon = column;  //Keeps track of the weapon being used in battle 
      rhs.battleWeapon = row;       //and refers back to the subToEmoji map later

      // If there was a tie with weapon1 go to weapon2
      if(winner == 2) {
        column = Hands::subs[this->weapon1];   //these will get the corresponding
        row = Hands::subs[rhs.weapon1];        //number from the substricpt map

        winner = gameWinner[row][column];   //go to lhs sub and rhs sub

        this->battleWeapon = column;  //Keeps track of the weapon being used in battle 
        rhs.battleWeapon = row;       //and refers back to the subToEmoji map later

        // If there was still a tie then return zero so there wont be 
        // a winner for either one
        if(winner == 2) {
          winner = 0;
        }
      }

      return winner;
    }

};


// initialize static data member for
// hands struct (class)
map< string, string > Hands::Emojis = {
    {"rock", ROCK2},
    {"paper", PAPER2},
    {"scissors", SCISSORS2},
    {"lizard", LIZARD2},
    {"spock", SPOCK2}
};

// initialize static data member for
// hands struct (class)
map< string, string > Hands::Names = {
    {ROCK2, "rock"},
    {PAPER2, "paper"},
    {SCISSORS2, "scissors"},
    {LIZARD2, "lizard"},
    {SPOCK2, "spock"}
};

//  Finds a substript for the 2d array we're using to find the winner
map< string, int > Hands::subs = {
    {ROCK2, 0},
    {PAPER2, 1},
    {SCISSORS2, 2},
    {LIZARD2, 3},
    {SPOCK2, 4}
};

// This map goes from the subscripts to the emojis
map< int, string > Hands::subsToE = {
    {0, ROCK2},
    {1, PAPER2},
    {2, SCISSORS2},
    {3, LIZARD2},
    {4, SPOCK2}
};


///////////////////////////////////////////////////////////////////////////////
//
//  Description: Prints out the winner of the battle
//
//  Params: Player &P1 - the left hand side player 
//          Player &P2 - the right hand side player
//
void whoWon(Player &P1, Player &P2, ofstream &outfile) {
  if(P1 > P2) {
    outfile << "Player one's " << Hands::subsToE[P1.battleWeapon] 
         << " beats Player two's " << Hands::subsToE[P2.battleWeapon] << "!\n";
  }
  else if(P2 > P1) {
    outfile << "Player two's " << Hands::subsToE[P2.battleWeapon] 
         << " beats Player one's " << Hands::subsToE[P1.battleWeapon]  << "!\n";
  }
  else {
    outfile << "There is a tie!\n";
  }
}


int main() {

  ofstream outfile;
  outfile.open("output.txt");

  int numPlayers = 50;

  Player *lottaPlayas[numPlayers];       //makes a lot of player objects
  for(int i = 0; i < numPlayers; i++) {
    lottaPlayas[i] = new Player;
  }

  for(int i = 0; i < numPlayers; i+=2) {    //makes the player objects battle
    whoWon(*lottaPlayas[i], *lottaPlayas[i+1], outfile);
  }

  for(int i = 0; i < numPlayers; i++) {    //deletes the objects
    delete lottaPlayas[i];
  }

}
