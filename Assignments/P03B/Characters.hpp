#ifndef CHARACTERS
#define CHARACTERS

#include <iostream>
#include <fstream>
#include "Attack.hpp"
#include "DieRoll.hpp"

using namespace std;



/**************************************************************************************
 * Character
 * 
 * Description:
 *      Base class for all game characters
 *      
 * 
 * Public Methods:
 *                          Character()
 *
 *      void                printType()
 *      string              getType()
 *      string              getFighterType()
 *      void                setFighterType(string)
 *      int                 getMaximumHp()
 *      int                 getHp()   
 *      void                setHp()    
 *      void                addHp()
 *      void                minusHp()
 *      virtual bool        lowHp()
 *      int                 attack()                                 
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
class Character {
  protected:

    DieRoll D2;     //  ***FOR TESTING***
   
    string type;    //the type of character it is (Ex: "Warriror")

    int hp;               // character health
    int maximumHp;        // maximum hp health

    int recoverySpeed;    // amount of health the attackers get per round

    string fighterType;

    string characters[5] = {"Warrior", "Wizard", "Archer", "Elf", "DragonBorn"};

  public: 

    Attack weapon;   //The weapon the character has //eventually will put this in private and make game a friend

    Character(string fType = "N/A") {
      type = "";
      fighterType = fType;
    }

    virtual ~Character() {
      
    }
    
    //prints the type of the character
    void printType() {
      cout << type << endl;
    }

    // returns the type of character as a string
    string getType() {
      return type;
    }

    // return whether its a attacker or defender
    string getFighterType() {
      return fighterType;
    }

    // Set whether the fighter is an attacker or defender
    void setFighterType(string type) {
      fighterType = type;
    }

    //  returns the maximum hp a character can have
    int getMaximumHp() {
      return maximumHp;
    }

    //  returns the hp of the character
    int getHp() {
      return hp;
    }

    //  set the hp of the character
    void setHp() {
      if(fighterType == "Defender") {
        hp = weapon.attack() * 3;   //sets a random hp for the character
      }
      else if(fighterType == "Attacker") {
        hp = weapon.attack() * 30;
      }
      
      maximumHp = 3000;//hp + 200;       //maximum hp the defender can regen to
    }

    // add hp to a character
    void addHp(int amount = 1) {
      hp += amount;
    }

    //  subtract hp from a character
    void minusHp(int amount = 1) {
      hp -= amount;
    }

    //  Checking to see if the fighters hp is low (WILL BE USED FOR DEFENDERS) 
    virtual bool lowHp() = 0;

    // using the character specific attack to roll the dice and return the damage
    int attack() {
      return weapon.attack();
    }

    friend ostream& operator<<(ostream& out, const Character& c) {
      out << "Fighter: " << c.fighterType << endl;
      out << "Type: " << c.type << endl;
      out << c.weapon <<endl;
      out << "HP: " << c.hp << endl;
      
      return out;
    }
    
};


/**************************************************************************************
 * Warrior
 * 
 * Description:
 *      A derived class from Character.
 *
 *      - has an attack of a sword type
 *      - sword: 1.d.12 or 2.d.6 or 3.d.4
 * 
 * Public Methods:
 *                          Warrior()
 *                         ~Warrior()
 *
 *      void                getInput()  
 *      bool                lowHp()                                     
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      Warrior soldier;           //Makes a warrior object
 *
 *  
 **************************************************************************************/
class Warrior : public Character {
  private: 


  public: 

    // no param constructor
    Warrior() {

      // D2.setDie(5);     // for testing purposes to get an input file

      weapon.setWeapon("Warrior");    //gets a sword from the attack class

      setHp();                      //sets a random hp for the character

      type = "Warrior";           //the type of character

    }

    ~Warrior() {

    }

    // for testing purposes to get an input file
    void getInput() {
      ofstream outfile;
      outfile.open("input1.txt");

      D2.setDie(5);

      for(int i = 0; i < 10000; i++) {
        outfile << characters[D2.addRolls(1)-1] << endl;
      }
    }

    bool lowHp() {
      if(hp < 8) 
        return true;
      else
        return false;
    }


};


/**************************************************************************************
 * Wizard
 * 
 * Description:
 *      A derived class from character
 *
 *      - has an attack of a magic type 
 *      - magic: 1.d.20 or 2.d.10 or 3.d.8 or 5.d.4 
 * 
 * Public Methods:
 *                          Wizard()  
 *                         ~Wizard()
 *
 *      bool                lowHp()                                
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *     Wizard wiz               //Makes a Wizard object
 *
 *
 *  
 **************************************************************************************/
class Wizard : public Character {
  private:

  public:

    Wizard() {

      weapon.setWeapon("Wizard");     //gets a magic weapon from attack class

      setHp();                      //sets a random hp for the character

      type = "Wizard";            //the type of character

    }

    ~Wizard() {

    }

    bool lowHp() {
      if(hp < 20) 
        return true;
      else
        return false;
    }

};


/**************************************************************************************
 * Archer
 * 
 * Description:
 *      A derived class from character
 *
 *      - has an attack of a bow type
 *      - bow: 1.d.8 or 2.d.4 or 1.d.10    
 * 
 * Public Methods:
 *                          Archer()  
 *                         ~Archer()   
 *                             
 *        bool              lowHp()     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *     Archer archer;                   //makes an archer object
 *
 *  
 **************************************************************************************/
class Archer : public Character {
  private: 

  public:

    Archer() {
      
      weapon.setWeapon("Archer");       //gets a bow weapon from attack class

      setHp();                      //sets a random hp for the character

      type = "Archer";              //the type of character
    }

    ~Archer() {

    }

    bool lowHp() {
      if(hp < 6) 
        return true;
      else
        return false;
    }

};


/**************************************************************************************
 * Elf
 * 
 * Description:
 *      A derived class from character
 *
 *      - has an attack of a sword type and a magic type 
 *      - sword: 1.d.12 or 2.d.6 or 3.d.4
 *      - magic: 1.d.20 or 2.d.10 or 3.d.8 or 5.d.4
 * 
 * Public Methods:
 *                          Elf()   
 *                         ~Elf()
 *
 *       bool               lowHp()                         
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      Elf elf;                          // makes an Elf object
 *
 *  
 **************************************************************************************/
class Elf : public Character {
  private:
    

  public:

    Elf() {
    
      weapon.setWeapon("Elf"); //gets a sword weapon and magic weapon from attack class

      setHp();                 //sets a random hp for the character

      type = "Elf";            //the type of character
    }

    ~Elf() {

    }

    bool lowHp() {
      if(hp < 25) 
        return true;
      else
        return false;
    }

};


/**************************************************************************************
 * DragonBorn
 * 
 * Description:
 *      A derived class from character
 *      
 *      - has an attack type of magic and fire
 *      - magic: 1.d.20 or 2.d.10 or 3.d.8 or 5.d.4
 *      - fire: 1.d.6 or 1.d.8
 *      
 * 
 * Public Methods:
 *                          DragonBorn()    
 *                         ~DragonBorn()
 *
 *       bool               lowHp()                              
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      DragonBorn dragon;              //makes a DragonBorn object
 *
 *  
 **************************************************************************************/
class DragonBorn : public Character {
  private: 
    int constDamage = 10;

  public: 

    DragonBorn() {
      // D1.setDie(6);       // for magic attack
      // D2.setDie(6);       // for fire attack

      weapon.setWeapon("DragonBorn"); //gets a fire weapon and a magic weapon from attack class

      setHp();                         //sets a random hp for the character

      type = "DragonBorn";
    }

    ~DragonBorn() {
      
    }

    bool lowHp() {
      if(hp < 25) 
        return true;
      else
        return false;
    }

    //  adds 2 rolls from a 6 sided die, then adds 2 rolls from a 6 another sided die, 
    //  then adds a constant 
    // int attack() {
    //   int damage;
    //   damage = D1.addRolls(2) + D2.addRolls(2) + constDamage;
    //   return damage;
    // }
};




#endif
