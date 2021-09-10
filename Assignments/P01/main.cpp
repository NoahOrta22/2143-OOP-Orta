
/**
*                    
*  Author:           Noah Orta
*  Email:            noahraulscout@gmail.com  
*  Label:            P01
*  Title:            MyVector
*  Course:           CMPS 2143
*  Semester:         Fall 2021
* 
*  Description:
*        A Vector project made out of a linked list
*
*  Files:
*     main.cpp     : driver program
*
* 
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**************************************************************************************
 * MyVector
 * 
 * Description:
 *      A vector class made out of link list nodes.
 *      
 * 
 * Public Methods:
 *                          MyVector()
 *                          MyVector(int *A, int size)
 *                          MyVector(string FileName) 
 *                          MyVector(const MyVector &V1)
 *
 *      void                printSize()
 *      void                pushFront(int num)                                        
 *      void                pushFront(MyVector &vector)
 *      void                pushRear(int num)
 *      void                pushRear(MyVector &vector)
 *      bool                pushAt(int sub, int num)
 *      void                inOrderPush(int num)
 *      int                 popFront()
 *      int                 popRear()
 *      int                 popAt(int sub)
 *      int                 find(int val)
 *      void                print(ofstream &outfile)   
 *      void                printBack(ofstream &outfile)
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      MyVector V(Arr, 34);                //Makes a vector from an array of size 34
 *
 *      MyVector V2(V);                     //Makes a copy of array V
 *
 *      V2.pushAt(4, 78)                    //adds the number 78 at subscript 4
 *                                   
 *      num =  V.popFront()                 //pops the first node and returns the int
 *                               
 *  
 **************************************************************************************/

class MyVector {
  
  private:

    // Node for our linked list
    struct node {
      int data;  // data value (could be a lot more values)

      node* next;       // points to the next node
      node* previous;   // points to the previous node

      // constructor to make adding values easy
      node(int x, node* n = nullptr, node* p = nullptr) {  
          data = x;
          next = n;
          previous = p;
      }
    };

    node* head;    // the head of the vector/linked list
    node* tail;    // the tail of the vector/linked list

    int currentSize; //the current size of the vector


  public:

    /////////////////////////////////////////////////////////
    //
    //  Description: initializes a MyVector object
    //
    //  param: none
    //
    //  returns: none
    //
    MyVector() {
      head = nullptr;    // the head of the vector/linked list
      tail = nullptr;    // the tail of the vector/linked list

      currentSize = 0; //the current size of the vector
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: initializes a MyVector object with an array 
    //
    //  param: int *A    -   the array
    //  param: int size  -   the size of the array
    //
    //  returns: none
    //
    MyVector(int *A, int size) {
      head = nullptr;    // the head of the vector/linked list
      tail = nullptr;    // the tail of the vector/linked list

      currentSize = 0;   //the current size of the vector

      for(int i = 0; i < size; i++) {
        pushRear(A[i]);
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: initializes a MyVector object and places items from a 
    //               file into it 
    //
    //  param: string FileName - the file of integers that will be read
    //
    //  returns: none
    //
    MyVector(string FileName) {
      head = nullptr;    // the head of the vector/linked list
      tail = nullptr;    // the tail of the vector/linked list

      currentSize = 0;   //the current size of the vector

      ifstream fin;
      fin.open(FileName);

      int temp;
      while(!fin.eof()) {
        fin >> temp;
        pushRear(temp);
      }

    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: initializes a MyVector object and places items from a 
    //               different MyVector object into it 
    //
    //  param: MyVector &V1 - the MyVector object that will be copied
    //
    //  returns: none
    //
    MyVector(const MyVector &V1) {
      head = nullptr;    // the head of the vector/linked list
      tail = nullptr;    // the tail of the vector/linked list

      currentSize = 0;   //the current size of the vector

      node* temp = V1.head;

      while(temp != nullptr) {
        pushRear(temp->data);
        temp = temp->next;
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Prints out the current size of the array
    //
    //
    void printSize() {
      cout << currentSize << '\n';
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds integers to the front of the Vector
    //
    //  param: int num - the number being added
    //
    //  returns: void
    //
    void pushFront(int num) {
      
      // if there are no values in the vector
      if(head == nullptr) {
        head = new node(num); //make head point to the value
        tail = head;          //head and tail are the same since
                              //theres only one value in vector
        currentSize++;   //increase the current size by one
      }                       
      else {
        head->previous = new node(num, head); //adds a int to the front
        head = head->previous;                //and changes the head's next 
                                              //to the old head
        currentSize++;   //increase the current size by one
      }                              
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds a separate vector to the front of 
    //               the Vector.
    //
    //  param: MyVector vector - the vector being added
    //
    //  returns: void
    //
    void pushFront(MyVector &vector) {
      node* temp = vector.tail; //  temp pointer to traverse the list

      //while loop to add items from the old list to the new one
      while(temp) {
        pushFront(temp->data); //push the data to the end of the list

        temp = temp->previous;    //go to next item

      }
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds integers to the back of the vector
    //
    //  param: int num - the num being placed at the end
    //
    //  return: void
    //
    void pushRear(int num) {
      
      // if there are no values in the vector
      if(head == nullptr) {
        head = new node(num); //make head point to the value
        tail = head;          //head and tail are the same since
                              //theres only one value in vector
        currentSize++;   //increase the current size by one
      }
      else{
        tail->next = new node(num, nullptr, tail);//adds a int to the back
                                                  //and changes the tail's next 
                                                  //to the old tail
        tail = tail->next; //move the tail down one
        currentSize++;   //increase the current size by one
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds a separate vector to the back of 
    //               the Vector.
    //
    //  param: MyVector vector - the vector being added
    //  param: node* front - the head of the other vector
    //
    //  returns: void
    //
    void pushRear(MyVector &vector) {

      node* temp = vector.head; //  temp pointer to traverse the list

      //adds items from the old list to the new one
      while(temp) {
        pushRear(temp->data); //push the data to the end of the list

        temp = temp->next;    //go to next item

      }
      
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds an integer at a specific location
    //
    //  param: int sub - the subscript of where the int will be placed
    //  param: int num - the num that is being placed
    //
    //  returns: bool - if the num can be added or not
    //
    bool pushAt(int sub, int num) {
      
      //  if the subscript is bigger than the index or < 0, return false
      if(sub > currentSize || sub < 0) {
        return false;
      }
      else {
        //  if the subsript equals zero or the currentSize then just 
        //  attach it to the head or tail
        if(sub == 0) {
          pushFront(num);
          // head->previous = new node(num, head);
          // head = head->previous;
        }
        else if (sub == currentSize) {
          pushRear(num);
          // tail->next = new node(num, nullptr, tail);
          // tail = tail->next;                         //making the new tail
        }

        //  else, we have to traverse the list to the int
        else {
          
          node* temp = head; //temp pointer to traverse the list

          //traverse the list to the node where we want to insert
          for(int i = 0; i < sub; i++) {
            temp = temp->next;
          }

          //  This is just connecting everything
          // **************************************************
          //makes a node that points to previous position so we now have
          //the "previous" node we need to be connected to (temp2) and
          //the "next" node we need to connect to (temp)
          node* temp2 = temp->previous; 
          temp->previous = new node(num, temp, temp2);
          temp2->next = temp->previous;             //connecting the previous node 
                                                    //with the new node
          currentSize++;               //increase the current size by one since we
                                       //have to push manually
        }
        
        return true;
      }
      
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: places the node in the correct position so the vector 
    //               stays in either a ascending or descending order
    //
    //  param: int num - the integer being added
    //
    //  return: void
    //
    void inOrderPush(int num) {

      int sub = 0; //location on insertion

      if(head->data < tail->data) {       // if the list is ascending order
        node* temp = head;
        while(temp->data < num) {
          sub++;              // increase the subscript
          if(sub == currentSize) {
            break;
          }
          temp = temp->next;  // move down the list
        }
        pushAt(sub, num);     // Now send to the func to do all the work of inserting
      }
      else if(head > tail) {   // if the list is descending order
        node* temp = head;
        while(temp->data > num) { 
          sub++;              // increase the subscript
          if(sub == currentSize) {
            break;
          }
          temp = temp->next;  // move down the list
        }
        pushAt(sub, num);     // Now send to the func to do all the work of inserting
      }
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Removes an integer from the front of the list
    //
    //  params: none
    //
    //  return: int - the integer being removed
    //
    int popFront() {
      int num = head->data;       // integer being removed

      node* temp = head;          // make a temp pointer to delete
      head = head->next;          // move the head down one
      head->previous = nullptr;   // sets heads previous to nullptr
      delete temp;                //delete the garbage

      currentSize--;              //reduce the current size by one

      return num;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Removes an integer from the back of the list
    //
    //  params: none
    //
    //  return: int - the integer being removed
    //
    int popRear() {
      int num = tail->data;     // integer being removed

      node* temp = tail;        // make a temp pointer to delete
      tail = tail->previous;    // move the head down one
      tail->next = nullptr;   // sets heads previous to nullptr
      delete temp;              //delete the garbage

      currentSize--;            //reduce the current size by one

      return num;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: takes in a subscript and removes the int at that spot
    //
    //  params: int sub - the subscript location of the integer in vector
    //
    //  return: int - the integer being removed
    //
    int popAt(int sub) {
      int num;

      //  if the subscript is bigger than the index, or < 0, return false
      if(sub >= currentSize || sub < 0) {
        return false;
      }
      else {
        //  if the subsript equals zero or the currentSize then just 
        //  use popRear or popFront
        if(sub == 0) {
          num = popFront();
        }
        else if (sub == currentSize-1) {
          num = popRear();
        }

        //  else, we have to traverse the list to the int
        else {
          
          node* temp = head; //temp pointer to traverse the list

          //traverse the list to the node we want to remove
          for(int i = 0; i < sub; i++) {
            temp = temp->next;
          }
          num = temp->data;

          //  This is just deleting the node and reconnecting them all
          //  *************************************************
          node* garbage = temp;          // to keep track of node we're deleting
          node* temp2 = temp->previous;  // node before garbage
          temp = garbage->next;          // node after garbage
          temp2->next = temp;            //connecting the previous node 
          temp->previous = temp2;        //with the next node
          delete garbage;
          
        }
        currentSize--;   //increase the current size by one
        return num;
      }

    }


    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Finds the subscript of the integer in the list the user
    //               is looking, then returns the subscript. If the integer 
    //               is not found then it will return the index
    //
    //  params:      int val - the integers we're looking for
    //
    //  return:      int - the subscript of where the integer is 
    //
    int find(int val) {
      int sub = 0;        // the subscript

      node* temp = head;  // temp pointer to traverse the list
      //  while the val isn't found or we've went through the whole list
      while(temp != nullptr && temp->data != val) {
        temp = temp->next; 
        sub++;

      }
      if(sub == currentSize) {
        sub = -1;
      }
      
      return sub;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: prints the Vector from forward to backwards
    //
    //  params: ofstream &outfile - outfile that we're printing to from main
    //
    //  returns: void
    //
    void print(ofstream &outfile) {
      node* temp = head;

      //  Printing out to the terminal
      cout << "[";
      while(temp->next != nullptr) {
        cout << temp->data << ", ";
        temp = temp->next;
      }
      cout << temp->data << "]\n";

      //  Printing out to the outfile
      temp = head;
      outfile << "[";
      while(temp->next != nullptr) {
        outfile << temp->data << ", ";
        temp = temp->next;
      }
      outfile << temp->data << "]\n";

    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: prints the Vector from backwards to forwards
    //
    //  params: none
    //
    //  returns: void
    //
    void printBack(ofstream &outfile) {
      node* temp = tail;

      //  Printing out to the terminal
      cout << "[";
      while(temp->previous != nullptr) {
        cout << temp->data << ", ";
        temp = temp->previous;
      }
      cout << temp->data << "]\n";

      //  Printing out to the outfile
      temp = tail;
      outfile << "[";
      while(temp->previous != nullptr) {
        outfile << temp->data << ", ";
        temp = temp->previous;
      }
      outfile << temp->data << "]\n";
    }

};

int main() {

  ofstream outfile;
  outfile.open("test.out");

  outfile << "Noah Orta\n9/10/2021\nFall 2143\n\n";

  int x = 0;

  MyVector v1;
  v1.pushFront(18);
  v1.pushFront(20);
  v1.pushFront(25);
  v1.pushRear(18);
  v1.pushRear(20);
  v1.pushRear(25);
  v1.print(outfile);
  // [25, 20, 18, 18, 20, 25]

  int A[] = {11,25,33,47,51};
  MyVector v2(A,5);
  v2.print(outfile);
  // [11, 25, 33, 47, 51]

  v2.pushFront(9);
  v2.inOrderPush(27);
  v2.pushRear(63);
  v2.print(outfile);
  // [9, 11, 25, 27, 33, 47, 51, 63]

  v1.pushRear(v2);
  v1.print(outfile);
  // [25, 20, 18, 18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]

  x = v1.popFront();
  x = v1.popFront();
  x = v1.popFront();
  v1.print(outfile);
  // [18, 20, 25, 9, 11, 25, 27, 33, 47, 51, 63]
  cout<<x<<endl;
  outfile<<x<<endl;
  // 18

  x = v1.popRear();
  x = v1.popRear();
  x = v1.popRear();
  v1.print(outfile);
  // [18, 20, 25, 9, 11, 25, 27, 33]
  cout<<x<<endl;
  outfile<<x<<endl;
  // 47

  x = v2.popAt(3);
  v2.print(outfile);
  // [9, 11, 25, 33, 47, 51, 63]
  cout<<x<<endl;
  outfile<<x<<endl;
  // 27

  x = v2.find(51);
  cout<<x<<endl;
  outfile<<x<<endl;
  // 5

  x = v2.find(99);
  cout<<x<<endl;
  outfile<<x<<endl;
  // -1

  MyVector v3(v1);
  v3.print(outfile);
  // [18, 20, 25, 9, 11, 25, 27, 33]

  v3.pushFront(v2);
  v3.print(outfile);
  //[9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

  MyVector v4("input.dat");
  v4.pushRear(v3);
  v4.print(outfile);
  // [56, 61, 97, 66, 83, 25, 26, 11, 53, 49, 62, 18, 10, 18, 14, 3, 4, 23, 18, 24, 26, 27, 54, 14, 12, 45, 65, 98, 56, 97, 15, 84, 98, 9, 11, 25, 33, 47, 51, 63, 18, 20, 25, 9, 11, 25, 27, 33]

}
