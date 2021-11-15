#ifndef DIE_ROLL
#define DIE_ROLL

#include <iostream>
#include <math.h>

using namespace std;

/**
 * RandRoll
 * @description: A class to implement roll playing dice rolls.
 * @methods:
 * private:
 *      int Random(Max) : returns a value between 0 and max.
 *      int Random(Min , Max) : returns a value between min and max
 *      void init(int , int)  : initialize class
 * public:
 *      DieRoll()
 *      DieRoll(int)
 *      DieRoll(int,int)
 *      void setDie(int)    : set sides
 *      int addRolls(int)   
 *      int bestRoll(int)
 *      int averageRoll(int)
 */
class DieRoll {
    int sides;

    int Random(int max) {
      return 1 + (rand() % max);
    }

    // min = 40 max = 100
    int Random(int min, int max) {
      return 1 + min + (rand() % (max - min));
    }
    void init(int _seed, int _sides) {
      sides = _sides;
      srand(_seed);
    }
  public:
    DieRoll() {
      //cout << "default base" << endl;
      init(time(0), 6);
    }
    DieRoll(int _seed) {
      //cout << "overloaded const" << endl;
      init(_seed, 6);
    }


    DieRoll(int _seed, int _sides) {
      //cout << "overloaded const" << endl;
      init(_seed, _sides);
      // seed = _seed;
      // sides = _sides;
    }

    // setting the sides of the die
    void setDie(int _sides) {
      sides = _sides;
    }

    int getSides() {
      return sides;
    }

    // Rolls a certain number of times and adds the values together
    int addRolls(int times) {
      int sum = 0;
      while (times--) {
        int rolll = Random(sides);
        sum+= rolll;
        //cout << "roll: " << rolll << endl;

        //sum += Random(sides);
      }
      return sum;
    }

    // Rolls a certain number of times and finds the best roll
    int bestRoll(int times) {
      int best = 0;
      int roll = 0;
      while(times--) {
        roll = Random(sides); //roll the dice
        if(roll > best) {     //assign to best if better than best
          best = roll;
        }
      }
      return best;
    }

    //  
    int averageRoll(int times) {
      float total = addRolls(times);      //finds the sum
      int average = round(total/times);   //finds the average
      return average;
    }
    
    friend ostream& operator<<(ostream &os, const DieRoll &d){
      return os << "["<<d.sides<<"]";
    }
};

#endif
