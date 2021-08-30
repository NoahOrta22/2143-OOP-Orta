/*
 
  $$$$$$\   $$$$$$\   $$$$$$\                                                         
 $$  __$$\ $$$ __$$\ $$ ___$$\                                                        
 $$ /  $$ |$$$$\ $$ |\_/   $$ |                                                       
 $$$$$$$$ |$$\$$\$$ |  $$$$$ /                                                        
 $$  __$$ |$$ \$$$$ |  \___$$\                                                        
 $$ |  $$ |$$ |\$$$ |$$\   $$ |                                                       
 $$ |  $$ |\$$$$$$  /\$$$$$$  |                                                       
 \__|  \__| \______/  \______/                                                        
                                                                                      
                                                                                      
                                                                                      
  $$$$$$\    $$\ $$\   $$\  $$$$$$\         $$$$$$\   $$$$$$\  $$$$$$$\               
 $$  __$$\ $$$$ |$$ |  $$ |$$ ___$$\       $$  __$$\ $$  __$$\ $$  __$$\              
 \__/  $$ |\_$$ |$$ |  $$ |\_/   $$ |      $$ /  $$ |$$ /  $$ |$$ |  $$ |             
  $$$$$$  |  $$ |$$$$$$$$ |  $$$$$ /       $$ |  $$ |$$ |  $$ |$$$$$$$  |             
 $$  ____/   $$ |\_____$$ |  \___$$\       $$ |  $$ |$$ |  $$ |$$  ____/              
 $$ |        $$ |      $$ |$$\   $$ |      $$ |  $$ |$$ |  $$ |$$ |                   
 $$$$$$$$\ $$$$$$\     $$ |\$$$$$$  |       $$$$$$  | $$$$$$  |$$ |                   
 \________|\______|    \__| \______/        \______/  \______/ \__|                   
                                                                                      
                                                                                      
                                                                                      
 $$\   $$\                     $$\              $$$$$$\             $$\               
 $$$\  $$ |                    $$ |            $$  __$$\            $$ |              
 $$$$\ $$ | $$$$$$\   $$$$$$\  $$$$$$$\        $$ /  $$ | $$$$$$\ $$$$$$\    $$$$$$\  
 $$ $$\$$ |$$  __$$\  \____$$\ $$  __$$\       $$ |  $$ |$$  __$$\\_$$  _|   \____$$\ 
 $$ \$$$$ |$$ /  $$ | $$$$$$$ |$$ |  $$ |      $$ |  $$ |$$ |  \__| $$ |     $$$$$$$ |
 $$ |\$$$ |$$ |  $$ |$$  __$$ |$$ |  $$ |      $$ |  $$ |$$ |       $$ |$$\ $$  __$$ |
 $$ | \$$ |\$$$$$$  |\$$$$$$$ |$$ |  $$ |       $$$$$$  |$$ |       \$$$$  |\$$$$$$$ |
 \__|  \__| \______/  \_______|\__|  \__|       \______/ \__|        \____/  \_______|
                                                                                      
                                                                                      
                                                                                      
 
*/


/*****************************************************************************
*                    
*  Author:           Noah Orta
*  Email:            noahraulscout@gmail.com
*  Label:            A04
*  Title:            Commenting code
*  Course:           CMPS 3013
*  Semester:         Fall 2021
* 
*  Description:
*        This program implements a class that allows a linked list to be used just like 
*        an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
*        array elements, but really it traverses the list to find the specified node using
*        an index value. It also overloads the "+" and "-" signs allowing a user to "add"
*        or "push" items onto the end of the list, as well as "pop" items off the end of our 
*        array. This class is not meant to replace the STL vector library, its simply a project
*        to introduce the beginnings of creating complex / abstract data types. 
*        
*  Usage: 
*       - $ ./main filename
*       - This will read in a file containing whatever values to be read into our list/array. 
*       
*  Files:            
*       main.cpp    : driver program 
*       list.h      : header file with list defintion
*       list.cpp    : list implementation
*****************************************************************************/


#include <iostream>

using namespace std;

/**************************************************************************************
 * CircularArrayQue
 * 
 * Description:
 *      
 * 
 * Public Methods:
 *                          CircularArrayQue()
 *                          CircularArrayQue(int size)
 *                                              
 *      void                Push(int item)
 *      int                 Pop()
 *     
 * 
 * Private Methods:
 *
 *      void                init(int size = 0)
 *      bool                Full()
 *      
 * 
 * Usage: 
 * 
 *      CircularArrayQue C1(5);                 // Create Instance of CircularArrayqQue
 *                                              // with a queue of size 5 
 *      C1.push(6);                             // adds the number '6' to the end of queue
 * 
 *      C1.pop();                               // Takes off the first item of the queue
 *  
 **************************************************************************************/

class CircularArrayQue {
private:
    int *Container;           // Points to the queue array
    int Front;                // Keeps track of the front of the queue
    int Rear;                 // Keeps track of the back of the queue
    int QueSize;              // items in the queue
    int CurrentSize;          // Current amount of items in the queue



    /****************************************************************
     * Private : init
     * 
     * Description:
     *      Initializes the size of the queue and sets Front, Rear, 
     *      and the CurrentSize equal to zero
     * 
     * Params:
     *      int    :  the size of the queue
     * 
     * Returns:
     *      void
     */
    void init(int size = 0) {
        Front = Rear = CurrentSize = 0;
        QueSize = size;
    }

     /****************************************************************
     * Private : Full
     * 
     * Description:
     *      Checks to see if the queue is full
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      bool     :   Returns true if full and false if not full
     */
    bool Full() {
        return CurrentSize == QueSize;
    }

public:

     /****************************************************************
     * Public : CircularArrayQue
     * 
     * Description:
     *      Assigns the pointer variable "Container" to a new queue array of
     *      size 10, Then passes 10 to the function "init(int)"
     *      
     * Params:
     *      None
     * 
     */
    CircularArrayQue() {
        Container = new int[10]; //Makes a new array of size 10
        init(10);
    }
     /****************************************************************
     * Public : CircularArrayQue
     * 
     * Description:
     *      Assigns the pointer variable "Container" to a new queue array of
     *      whatever size is passed in, Then passes that size onto the 
     *      function "init(int)"
     *      
     * Params:
     *      int   :     The size of the queue
     * 
     */

    CircularArrayQue(int size) {
        Container = new int[size];  //Makes a new array of size "size"
        init(size);
    }

    /****************************************************************
     * Public : Push
     * 
     * Description:
     *      If the array is not full then the integer being passed in will
     *      be placed at the end of the queue, the rear will be pushed 
     *      back one, and Current size will incrument by one. If the array
     *      is full the "FULL!!!!!" will be printed out to the console
     *      
     * Params:
     *      int   :     the integer being added to the queue
     * 
     * Returns:
     *      Void
     *
     */
    void Push(int item) {
        if (!Full()) {                    // if the array is not full
            Container[Rear] = item;       // add the item to the end of queue
            Rear = (Rear + 1) % QueSize;  // push the rear back
            CurrentSize++;                // add "1" to the current size
        } else {                          // if the array is full, print "FULL"
            cout << "FULL!!!!" << endl;
        }
    }

    /****************************************************************
     * Public : Pop
     * 
     * Description:
     *      Moves "front" down one and creates a temp variable to keep
     *      track of number being removed, to be returned. By moving "front"
     *      down one, the integer stored in the queue is essentially 
     *      being removed from the queue
     *      
     * Params:
     *      None
     * 
     * Returns:
     *      int   :     returns the number being removed
     *
     */
    int Pop() {
        int temp = Container[Front];    // Assigns temp to the front number
        Front = (Front + 1) % QueSize;  // Moves front down one, removing 
                                        // the first number of queue
        CurrentSize--;                  // subtract "1" from the current size
        return temp;                    // return the number that was 
                                        // being removed
    }
    // friending ostream so it can access this classes private data members
    friend ostream &operator<<(ostream &os, const CircularArrayQue &other);
};

// Overloading ostream so this array can be printed to stdout (or files)
// simply by using something similar to : cout << ClassInstance << endl;
ostream &operator<<(ostream &os, const CircularArrayQue &other) {

    for (int i = other.Front; i < other.CurrentSize; i = (i + 1) % other.QueSize) {
        os << other.Container[i] << " ";
    }
    os << endl;
    return os;
}

/**
 * Main Driver
 * 
 * For this program, the main driver was used to test the CircularArrayQue class
 * 
 */
int main() {
    CircularArrayQue C1(5);     //Creates a queue of size 5

    // C1.Push(34);
    // C1.Push(38);
    // C1.Push(44);
    // C1.Push(22);
    // C1.Push(99);
    // C1.Push(100);

    C1.Push(1);                 //Adds the number "1" to the queue
    C1.Push(2);                 //Adds the number "2" to the queue
    C1.Push(3);                 //Adds the number "3" to the queue
    // C1.Push(6);
    // C1.Push(7);
    cout << C1 << endl;         //Prints out the queue

    // C1.Push(1);
    // C1.Push(2);
    // C1.Push(3);

    cout << C1 << endl;         //Prints out the queue
}
