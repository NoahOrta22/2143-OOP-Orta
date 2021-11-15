#ifndef ATTACK
#define ATTACK

#include <iostream>
#include "DieRoll.hpp"

using namespace std;

static int seedNum = time(0); //so the see will always be different


/**************************************************************************************
 * Attack
 * 
 * Description:
 *      A class where characters get there specific attack types with random attack
 *      strengths. An attack method is also called when the players are trying
 *      to attack.
 *      
 * 
 * Public Methods:
 *                          Attack()
 *
 *      void                setWeapon()
 *      int                 attack()     
 *      friend ostream& operator<<(ostream, const Attack)                                   
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      Abstract class
 *
 *  
 **************************************************************************************/
class Attack {
  private:
    vector<DieRoll> dice;   // holds the die or dice the character uses

    DieRoll die;            // rolls to see what the attack strength will be

    DieRoll die1;           //  The first attack die that the character holds
    DieRoll die2;           //  IF the character needs a second die
    
    int randAttackStrength; // then puts it into this variable

    vector<int> numRolls = {0, 0};       // number of rolls the weapon gets

    bool best = false;
    bool add = false;
    bool avg = false;


  public:

    Attack() {
      DieRoll die(seedNum);
      seedNum++;             //so the see will always be different

      //DieRoll die1(SeedNum);
    }

    //  
    //  sets a random weapon strength for a specific type of character
    //  params: string - the weapon type
    //  
    void setWeapon(string type) {

      // If it's a warrior or elf weapon (sword)
      if(type == "Warrior" || type == "Elf") {
        die.setDie(3);   //makes the die 2 sided (2 strength types)
        randAttackStrength = die.addRolls(1); //rolls the die one time getting 1 or 2

        add = true;
        //1.d.12
        if(randAttackStrength == 1) {
          // cout << "war: strength 1\n";   //  for debugging

          die1.setDie(12);   //make a 4 sided die

          numRolls[0] = 1;     //weapon strength gets 1 roll

          dice.push_back(die1); //add to the vector
        }
        //2.d.6
        else if(randAttackStrength == 2) {
          // cout << "war: strength 2\n";   //  for debugging

          die1.setDie(6);   //make a 6 sided die

          numRolls[0] = 2;     //weapon strength gets sum of 2 rolls

          dice.push_back(die1); //add to the vector
        }
        //3.d.4
        else if(randAttackStrength == 3) {
          // cout << "war: strength 3\n";   //  for debugging

          die1.setDie(4);   //make a 6 sided die

          numRolls[0] = 3;     //weapon strength gets sum of 3 rolls

          dice.push_back(die1); //add to the vector
        }

      }

      // If it's a Wizard weapon (Magic weapon)
      else if(type == "Wizard") {
        die.setDie(4);   //makes the die 4 sided (4 strength types)
        randAttackStrength = die.addRolls(1); //rolls the die one time to pick stregth of attack

        add = true;

        //1.d.20
        if(randAttackStrength == 1) {
          // cout << "wiz: strength 1\n";   //  for debugging

          die1.setDie(20);   //make a 20 sided die

          numRolls[0] = 1;     //weapon strength gets 1 roll

          dice.push_back(die1); //add to the vector
        }
        //2.d.10
        else if(randAttackStrength == 2) {
          // cout << "wiz: strength 2\n";   //  for debugging

          die1.setDie(10);   //make a 10 sided die

          numRolls[0] = 2;     //weapon strength gets 2 roll

          dice.push_back(die1); //add to the vector
        }
        //3.d.8
        else if(randAttackStrength == 3) {
          // cout << "wiz: strength 3\n";   //  for debugging

          die1.setDie(8);   //make a 8 sided die

          numRolls[0] = 3;     //weapon strength gets 3 roll

          dice.push_back(die1); //add to the vector
        }
        //5.d.4
        else if(randAttackStrength == 4) {
          // cout << "wiz: strength 4\n";   //  for debugging

          die1.setDie(4);   //make a 4 sided die

          numRolls[0] = 5;     //weapon strength gets 5 roll

          dice.push_back(die1); //add to the vector
        }

      }

      //If it's a Archer Weapon (Bow weapon)
      else if(type == "Archer") {
        die.setDie(3);   //makes the die 3 sided (3 strength types)
        randAttackStrength = die.addRolls(1); //rolls the die one time to pick stregth of attack

        add = true;

        //1.d.12
        if(randAttackStrength == 1) {
          // cout << "Arch: strength 1\n";

          die1.setDie(8);

          numRolls[0] = 1;

          dice.push_back(die1);

        }
        //2.d.4
        else if(randAttackStrength == 2) {
          // cout << "Arch: strength 2\n";

          die1.setDie(4);

          numRolls[0] = 2;

          dice.push_back(die1);
        }
        //1.d.10
        else if(randAttackStrength == 3) {
          // cout << "Arch: strength 3\n";

          die1.setDie(10);

          numRolls[0] = 1;

          dice.push_back(die1);
        }
      }
      
      // for the DragonBorn attack (fire weapon)
      else if(type == "DragonBorn") {
        die.setDie(2);   //makes the die 3 sided (3 strength types)
        randAttackStrength = die.addRolls(1); //rolls the die one time to pick stregth of attack

        add = true;

        //1.d.6
        if(randAttackStrength == 1) {
          // cout << "Fire: strength 1\n";
          die1.setDie(6);

          numRolls[0] = 1;

          dice.push_back(die1);
        }
        //1.d.8
        else if(randAttackStrength == 2) {
          // cout << "Fire: strength 2\n";
          die1.setDie(8);

          numRolls[0] = 1;

          dice.push_back(die1);
        }

      }

      //  for the elf (magic for second die)
      if(type == "Elf" || type == "DragonBorn") {
        die.setDie(4);   //makes the die 4 sided (4 strength types)
        randAttackStrength = die.addRolls(1); //rolls the die one time to pick stregth of attack

        add = true;

        //1.d.20
        if(randAttackStrength == 1) {
          // cout << "magic: strength 1\n";   //  for debugging

          die2.setDie(20);   //make a 20 sided die

          numRolls[1] = 1;     //weapon strength gets 1 roll

          dice.push_back(die2); //add to the vector
        }
        //2.d.10
        else if(randAttackStrength == 2) {
          // cout << "magic: strength 2\n";   //  for debugging

          die2.setDie(10);   //make a 10 sided die

          numRolls[1] = 2;     //weapon strength gets 2 roll

          dice.push_back(die2); //add to the vector
        }
        //3.d.8
        else if(randAttackStrength == 3) {
          // cout << "magic: strength 3\n";   //  for debugging

          die2.setDie(8);   //make a 8 sided die

          numRolls[1] = 3;     //weapon strength gets 3 roll

          dice.push_back(die2); //add to the vector
        }
        //5.d.4
        else if(randAttackStrength == 4) {
          // cout << "magic: strength 4\n";   //  for debugging

          die2.setDie(4);   //make a 4 sided die

          numRolls[1] = 5;     //weapon strength gets 5 roll

          dice.push_back(die2); //add to the vector
        }

      }
    }

    // vector getWeapon() {
    //   return dice;
    // }

    // using the character specific attack to roll the dice and return the damage
    int attack() {
      int damage = 0;

      //if we're adding the rolls
      if(add) {
        //rolls the first die numRolls times
        for(int i = 0; i < dice.size(); i++) {
          // cout << "Die size: " << dice[i].getSides() << endl;
          // cout << "numRolls: " << numRolls[i] << endl;
          damage += dice[i].addRolls(numRolls[i]);
          // cout << "damage: " << damage << endl;
        }
        
      }

      //if we're getting the best of n rolls
      else if(best){
        for(int i = 0; i < dice.size(); i++) {
          damage += dice[i].addRolls(numRolls[i]);
        }
      }

      //if we're getting the average of n rolls
      else if(avg) {
        for(int i = 0; i < dice.size(); i++) {
          damage += dice[i].addRolls(numRolls[i]);
        }
      }
      return damage;
    }

    friend ostream& operator<<(ostream &os, const Attack &a){
      os << "Dice Size: ";
      for(int i=0;i<a.dice.size();i++){
        os << a.dice[i];
      }
      os << "\nNum Rolls: ";
      for(int i=0;i<a.numRolls.size();i++){
        if(a.numRolls[i] != 0)
          os << "[" << a.numRolls[i] << "]";
      }
      //os << "AttackType"<<a.dice.size()<<a.dice[0];
      return os;
    }
    
};


#endif
