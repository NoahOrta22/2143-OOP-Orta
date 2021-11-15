#ifndef GAME
#define GAME

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include "Characters.hpp"
#include "DieRoll.hpp" 


using namespace std;

class Defenders;
class Attackers;

static int amtOfAttackers = 0; //will be used by multiple classes (the amount of attackers)
static int amtOfDefenders = 0;  //amount of defenders

/**************************************************************************************
 * Defenders
 * 
 * Description:
 *      The defenders are the good guys. For every 100 attackers there are 5 defenders, 
 *      one of each type
 *      
 * 
 * Public Methods:
 *
 *      void                add(string type)
 *      void                setUp(int numAttackers)  
 *      void                printQueues()                  
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      Defenders defenders;           //Makes a Defenders objects
 *      defenders.setUp(2390);         //sets up the amount of defenders we need for 
 *                                     //2390 attackers                                     
 *
 *  
 **************************************************************************************/
class Defenders {
  private:

    friend class Game;    //Makes it easier to go through the defenders

    //  Pretty sure I wont need this
    //
    // vector<Warrior> warriorsQ;    //
    // vector<Wizard> wizardQ;       //  Queues (circular arrays) to hold the defenders
    // vector<Archer> archerQ;       //  
    // vector<Elf> elfQ;             //  eventually make a map to each
    // vector<DragonBorn> dragonQ;   //


    //  A map to hold the defenders.
    //
    //  The key is the name of the type, and each type name has a corresponding vector
    //  that holds objects of that type. That vector will be the defenders queue 
    //  for that type.
    //
    //  Ex: defenders["Warrior"] <- holds a vector of warrior objects
    map <string, vector<Character*>> defenders = {
      {"Warrior", {}},  
      {"Wizard", {}},  
      {"Archer", {}},
      {"Elf", {}}, 
      {"DragonBorn", {}}
    };

    //  helped with understanding
    //
    // map <string, vector<int>> stuff = {
    //   {"one", {1, 2, 3}},
    //   {"two", {2, 3, 4, 5}}
    // };



  public:

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds a specific character to the back of the list
    //
    //  params: string - type: the characters type
    //
    void add(string type) {

      if(type == "Warrior")
        defenders[type].push_back(new Warrior);

      else if(type == "Wizard")
        defenders[type].push_back(new Wizard);

      else if(type == "Archer") 
        defenders[type].push_back(new Archer);

      else if(type == "Elf")
        defenders[type].push_back(new Elf);

      else if(type == "DragonBorn")
        defenders[type].push_back(new DragonBorn);
      
      else{
        cout << "Error: Adding invalid type\n";
        exit(0);
      }

      cout << endl;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Sets up the defenders based on the number of attackers
    //
    //  params: int - numAttackers:   the number of attackers
    //
    void setUp(int numAttackers) {
      //for every 100 attackers we need 5 defenders
      int num = numAttackers * .01;

      if(num == 0) {num = 1;} //if there are less than 100 attackers

      amtOfDefenders = num * 5;

      for(int i = 0; i < num; i++) {
        defenders["Warrior"].push_back(new Warrior);
        defenders["Wizard"].push_back(new Wizard);
        defenders["Archer"].push_back(new Archer);
        defenders["Elf"].push_back(new Elf);
        defenders["DragonBorn"].push_back(new DragonBorn);

        //  Sets the type of fighter it is since the constructor didn't work
        defenders["Warrior"][i]->setFighterType("Defender");
        defenders["Wizard"][i]->setFighterType("Defender");
        defenders["Archer"][i]->setFighterType("Defender");
        defenders["Elf"][i]->setFighterType("Defender");
        defenders["DragonBorn"][i]->setFighterType("Defender");

        defenders["Warrior"][i]->setHp();
        defenders["Wizard"][i]->setHp();
        defenders["Archer"][i]->setHp();
        defenders["Elf"][i]->setHp();
        defenders["DragonBorn"][i]->setHp();
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: removes a defender
    //
    //  Params: string - type       (Type of character)
    //          int    - sub        (subscript of where it is)
    //  
    //
    void remove(string type, int sub) {
      amtOfDefenders--;
      vector<Character*>::iterator it;

      it = defenders[type].begin() + sub;

      delete defenders[type][sub];
      defenders[type].erase(it);
      
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Prints out all the defenders
    //
    void printQueues() {

      //prints out all of the warriors
      for(int i = 0; i < defenders["Warrior"].size(); i++) {
        defenders["Warrior"][i]->printType();
      }
      //prints out all of the wizards
      for(int i = 0; i < defenders["Wizard"].size(); i++) {
        defenders["Wizard"][i]->printType();
      }
      //prints out all of the archers
      for(int i = 0; i < defenders["Archer"].size(); i++) {
        defenders["Archer"][i]->printType();
      }
      //prints out all of the elfs
      for(int i = 0; i < defenders["Elf"].size(); i++) {
        defenders["Elf"][i]->printType();
      }
      //prints out all of the DragonBorn
      for(int i = 0; i < defenders["DragonBorn"].size(); i++) {
        defenders["DragonBorn"][i]->printType();
      }
      
    }
    
};

/**************************************************************************************
 * Attackers
 * 
 * Description:
 *      The attackers are the bad guys. There can be any number amount of them.
 *      
 *      
 * 
 * Public Methods:
 *                          
 *
 *      void                add(string type)
 *      void                setUp(int numAttackers)  
 *      void                remove()
 *      void                printQueues()                  
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      Defenders defenders;           //Makes a Defenders objects
 *      defenders.setUp(2390);         //sets up the amount of defenders we need for 
 *                                     //2390 attackers                                     
 *
 *
 **************************************************************************************/
class Attackers {
  private:

    friend class Game;
    //int amtOfAttackers = 0; //possibly make class Defenders a friend of this one variable
    
    //had to make it a vector of character pointers
    vector<Character*> attackers; // a queue that holds all the attacks in order


  public:

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds a specific character to the back of the list
    //
    void add(string type) {

      if(type == "Warrior")
        attackers.push_back(new Warrior);

      else if(type == "Wizard")
        attackers.push_back(new Wizard);

      else if(type == "Archer") 
        attackers.push_back(new Archer);

      else if(type == "Elf")
        attackers.push_back(new Elf);

      else if(type == "DragonBorn")
        attackers.push_back(new DragonBorn);
      
      else{
        cout << "Error: Adding invalid type\n";
        exit(0);
      }
      attackers.back()->setFighterType("Attacker");
      attackers.back()->setHp();
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: sets up all the attackers
    //
    void setUp() {
      ifstream infile;
      infile.open("input1.txt");

      string attacker;  //the attacker that we're currently reading in

      while(!infile.eof()) {
        infile >> attacker;
        add(attacker);        // adds the attacker we just read in to the queue
        amtOfAttackers += 1;
      }
    }

    // Attackers getAttacker() {
    //   return *attackers[0];
    // }

    //  removes the first element of the list
    void remove() {

      delete attackers[0];
      attackers.erase(attackers.begin());
      
    }

    void printQueue() {
      for(int i = 0; i < attackers.size(); i++) {
        attackers[i]->printType();
      }
    }
 };

 /**************************************************************************************
 * Game
 * 
 * Description:
 *      Game class where the defenders will fight the attackers.
 *      
 * 
 * Public Methods:
 *                          Game()
 *
 *      void                //setUpGame()  
 *      void                plusDefHp(int) 
 *      void                plusAtkHp(int)
 *      void                printCurrentFighters()
 *      void                killAttacker()
 *      void                killDefender()
 *      bool                lastDefOfType(string)
 *      void                switchDefender()
 *      void                FIGHT()
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      Game game;           //Makes a Game object
 *                                      
 *
 **************************************************************************************/
class Game{
  public:

    Attackers attacker;            // Holds all the attacker objects
    Defenders defender;            // Holds all the defender objects

    int numRounds = 0;             // number of rounds fought

    Character* currentDef;         // A character pointer to the current Defender fighting

    Character* currentAtk;         // A character pointer to the current Attacker fighting

    string currentDType = "";      // the type of the current defender

    map <string, int> currentD = { // Keeps track of the current defender's subscripts
      {"Warrior", 0}, 
      {"Wizard", 0 }, 
      {"Archer", 0},
      {"Elf", 0},
      {"DragonBorn", 0}
    };

    map<string, string> nextBest = {
      {"DragonBorn", "Elf"}, 
      {"Elf", "Wizard"},
      {"Wizard", "Warrior"}, 
      {"Warrior", "Archer"},
      {"Archer", "DragonBorn"}
    };

    //  Types of defenders that are still alive
    vector<string> type = {"Archer", "Warrior", "Wizard", "Elf", "DragonBorn"};
    
  public:

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Sets up the attackers and the Defenders
    //
    Game() {                 
      //  reads in all the attackers and sets up the defenders           
      attacker.setUp();      
      defender.setUp(amtOfAttackers); 

      // the type of the current defender will be the same as the first 
      // attacker in the queue
      currentDType = attacker.attackers[0]->getType();

      //the first fighting defender, based on the first attacker's type
      currentDef = defender.defenders[currentDType][0]; 

      currentAtk = attacker.attackers[0]; //assigns to the first attacker in the queue

    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds hp to every defender not currently fighting
    //
    void plusDefHp(int amt = 1) {

      // this for loop goes to every defender and adds one HP point
      for(int i = 0; i < type.size(); i++) {
        for(int c = 0; c < defender.defenders[type[i]].size(); c++) {
          if(defender.defenders[type[i]][c]->getHp() <= defender.defenders[type[i]][c]->getMaximumHp())
            defender.defenders[type[i]][c]->addHp(amt);
        }
      }
      //makes it so that the defender currently fighting gets no hp
      currentDef->minusHp(); 
    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: The only attacker that is gaining hp is the one currently 
    //  fighting, and since the attackers are in the queue, the one fighting 
    //  will always be the at the first subscript
    //
    //  params: int - amt : amount of hp you want to add
    //
    void plusAtkHp(int amt = 1) {
      attacker.attackers[0]->addHp(amt);
    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: prints the current attacker and defender in the fight
    //
    void printCurrentFighters() {
      cout << *currentDef << endl;
      cout << *currentAtk << endl;
      cout << "Current Def subscript: " << currentD[currentDType] << endl;
      cout << "----------------------------------\n";
    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Killers the fighting attacker and sets the current attacker
    //               to the next attacker in the queue
    //
    void killAttacker() {
      attacker.remove();                  //kill the first attacker in queue
      amtOfAttackers--;

      if(amtOfAttackers != 0) {                             //if there is another attacker
        currentAtk = attacker.attackers[0];                 //assigns to the first attacker in the queue
        currentDType = attacker.attackers[0]->getType();    //find out what the new type of the attacker is
        if(!lastDefOfType(currentDType)) {                  //if there is also a defender of that type alive
          currentDef = defender.defenders[currentDType][0]; //change the current defender to the first one
          currentD[currentDType] = 0;                       //in that vector
        }
        else {                                              //else switch to a defender of a different type
          //switch to the next defender queue type that has a defender in it
          while(lastDefOfType(currentDType)) {
            currentDType = nextBest[currentDType];          // change the type of defender to the next nextBest
            currentDef = defender.defenders[currentDType][0]; //change the current defender to the first one
            currentD[currentDType] = 0;                       //in that vector
            //cout << "next best type: " << currentDType << endl;
          }
          switchDefender();
        }
      }
      else {
        cout << "ALL ATTACKERS DEAD, DEFENDERS WIN!!!\n";
        cout << "Number of Rounds Fought: " << numRounds << endl;
        cout << "Amount of Attackers left: " << amtOfAttackers << endl;
        exit(0);
      }

    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Killers the fighting defender and sets the current defender
    //               
    //
    void killDefender() { 
      //currentDef->minusHp(800);  //  ***FOR TESTING***

      string garbageType = currentDType;          // the type of defender that's dead
      int garbageSub = currentD[currentDType];    // subscript of defender that's dead

      //printCurrentFighters(); //  ***FOR TESTING***

      // if we're killing the last defender of that type, take it outta the type vector
      if(defender.defenders[currentDType].size() == 1) {
        garbageSub = 0;
        for(int i = 0; i < type.size(); i++) {
          if(type[i] == currentDType) {

            vector<string>::iterator it;
            it = type.begin() + i;
            type.erase(it);
          }
        }
      }

      switchDefender();                           // switch the defender out

      //  fixes the subscript issue when the dying defenders subscript is out
      //  of the the vector range 
      if(currentD[currentDType] > garbageSub) {
        currentD[currentDType]--;
      }

      // cout << "finished the switch*****************************\n";
      // cout << "Garbage Type: " << garbageType << endl;
      // cout << "Garbage Sub: " << garbageSub << endl;

      defender.remove(garbageType, garbageSub);   //kill the old defender

      //cout << "Current Def subscript: " << currentD[currentDType] << endl;

    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: says whether we are killing the last of that defender
    //               type or not.
    //
    //  Returns:     bool - if it is the last type of that defender or if all
    //                      defenders of that type are dead it returns true
    //
    bool lastDefOfType(string dType) {
      for(int i = 0; i < type.size(); i++) {
        if(type[i] == dType) {
          return false;
        }
      }
      return true;
    }

    /////////////////////////////////////////////////////////////////////////////
    //
    //  Description: If the defender is low on hp then it can switch out with 
    //               another defender of the same type (the one with the most hp)
    //               
    //
    void switchDefender() {

      int tempHp;   // the hp reading of the potential next fighter that we're looking at

      // give the defenders a starting max hp then find a higher one
      int maxHp = currentDef->getHp();

      // if there are still defenders that are alive in that type
      if(!lastDefOfType(currentDType)) {

        //  if there's only one of that type of defender
        if(defender.defenders[currentDType].size() == 1) {
          //  ***THEN IT SHOULD JUST STAY THE SAME DEFENDER
          
        }
        // if theres more than one of that type of defender
        else if(defender.defenders[currentDType].size() > 1) {
          //look for the defender of that type with the most hp
          for(int i = 0; i < defender.defenders[currentDType].size(); i++) {
            tempHp = defender.defenders[currentDType][i]->getHp();
            
            if(tempHp > maxHp) { //if that defenders hp is greater than the one currently fighting
                                //then make that defender the current fighting defender

              maxHp = tempHp;    // reset the max hp

              currentDef = defender.defenders[currentDType][i];

              currentD[currentDType] = i; //change the subscript of that type to make
            }                             //it the current subscript
          }
        }
        
      }
      else {   //  else if the last defender of that type is already dead

        if(type.size() == 0 & maxHp < 1) {    //if all of the character types are dead
          cout << "\nALL DEFENDERS ARE DEAD, ATTACKERS WIN!!!\n";
          cout << "Number of Rounds Fought: " << numRounds << endl;
          cout << "Amount of Attackers left: " << amtOfAttackers << endl;
          exit(0);
        }

        //if all the defenders of a certain type are dead
        else if(maxHp < 1 || defender.defenders[currentDType].size() == 1) {   

          //  map to see how the defenders pick there next type
          //
          // map<string, string> nextBest = {
          //   {"DragonBorn", "Elf"}, 
          //   {"Elf", "Wizard"},
          //   {"Wizard", "Warrior"}, 
          //   {"Warrior", "Archer"},
          //   {"Archer", "DragonBorn"}
          // };

          string tempType = currentDType;

          //switch to the next defender queue type that has a defender in it
          while(lastDefOfType(currentDType)) {
            currentDType = nextBest[currentDType]; // change the type of defender to the next nextBest
            //cout << "next best type: " << currentDType << endl;
          }

          currentDef = defender.defenders[currentDType][0]; //change the current defender to the first 
                                                            //defender of that new type
          currentD[currentDType] = 0; //change the subscript of that type to make it zero

          //cout << "Types left: ";
          for(int i = 0; i < type.size(); i++) {
            cout << type[i] << ", ";
          }
          //cout << "\n";
          
          switchDefender();               //then call the function again with that different type
          //cout << "made it\n";
        }
      }
      
    }

    void defendersTurn() {
      printUpdate();
      //  defender attacks attacker -------------
      int defDamage = currentDef->attack();   //amount of damage the defender caused 
      currentAtk->minusHp(defDamage);         //issue the damage to current attacker
      //cout << "defDamage: " << defDamage << "\n\n";

      if(currentAtk->getHp() < 1) {           //if the defender's attack killed the attacker
        killAttacker();                       //then kill the attacker and replace it
        defendersTurn();
      }
    }

    void attackersTurn() {
      printUpdate();
      //  attacker attacks defender -------------
      int atkDamage = currentAtk->attack();   //amount of damage the attacker caused
      currentDef->minusHp(atkDamage);         //issue the damage to current defender
      //cout << "atkDamage: " << atkDamage << "\n\n";


      if(currentDef->getHp() < 1) {           //if the attacker's attack killed the defender  
        //cout << "Killing def\n"; 
        killDefender();                       //then kill the defender and replace it
      }
      else if(currentDef->lowHp()) {          //else if the defender's hp is low
        switchDefender();                     //switch the defender out with another one
      }
    }

    void printUpdate() {
      cout << "NUMBER OF ATTACKERS: " << amtOfAttackers << endl;
      cout << "NUMBER OF DEFENDERS: " << amtOfDefenders << endl;
      system("clear");
    }


    void FIGHT() {
      //cout << "************START***************\n";
      //printCurrentFighters();
      numRounds++;

      defendersTurn();

      // plusDefHp();
      // plusAtkHp(3);

      attackersTurn();

      plusDefHp();
      plusAtkHp();
      
      //cout << "-------------------------------\n";

    }


};


#endif
