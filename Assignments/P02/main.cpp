
/**
*                    
*  Author:           Noah Orta
*  Email:            noahraulscout@gmail.com  
*  Label:            P02
*  Title:            MyVector 2
*  Course:           CMPS 2143
*  Semester:         Fall 2021
* 
*  Description:
*        A Vector project made out of a linked list with a ton
*        of overloading operators
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
 *      T                   popFront()
 *      T                   popRear()
 *      T                   popAt(int sub)
 *      int                 find(int val)
 *      void                print(ofstream &outfile)   
 *      void                printBack(ofstream &outfile)
 *      T                   &operator[](int sub)
 *      friend ostream      &operator<<(ostream& out, const MyVector& vector)
 *      friend ofstream     &operator<<(ofstream& out, const MyVector& vector)
 *      MyVector            operator+(MyVector& other)
 *      MyVector            operator-(MyVector& other)
 *      MyVector            operator*(MyVector& other)
 *      MyVector            operator/(MyVector& other)
 *      bool                operator==(MyVector& other)
 *      MyVector            &operator=(const MyVector& assigner)
 *     
 * 
 * Private Methods:
 *
 *      
 * 
 * Usage: 
 * 
 *      MyVector V<int>(Arr, 34);           //Makes a vector from an array of size 34
 *
 *      MyVector V2<int>(V);                //Makes a copy of array V
 *
 *      V2.pushAt(4, 78)                    //adds the number 78 at subscript 4
 *                                   
 *      num =  V.popFront()                 //pops the first node and returns the int
 *
 *      MyVector v3 = v1 + v2;              //adds vector v1 and v2, stores it in v3
 *  
 **************************************************************************************/
template <class T>
class MyVector {
  
  private:

    // Node for our linked list
    struct node {
      T data;  // data value (could be a lot more values)

      node* next;       // points to the next node
      node* previous;   // points to the previous node

      // constructor to make adding values easy
      node(T x, node* n = nullptr, node* p = nullptr) {  
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
    MyVector(T *A, int size) {
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

    /////////////////////////////////////////////////////////
    //
    //  Description: Deletes all the free memory
    //
    //  param: none
    //
    //  returns: none
    //
    ~MyVector() {
      node* temp = head; 
      node* garbage; 

      while(temp != nullptr) {
        garbage = temp; 
        temp = temp->next; 
        delete garbage;

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
    void pushFront(T num) {
      
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
    //  Description: adds data to the back of the vector
    //
    //  param: int num - the num being placed at the end
    //
    //  return: void
    //
    void pushRear(T num) {
      
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
    //  Description: adds data from an array to the back of the vector
    //
    //  param: T arr      - the array containing the data
    //  int:   int index  - the index of the array
    //
    //  return: void
    //
    void push_rear(T arr, int index) {
      for(int i = 0; i < index; i++) {
        pushBack(arr[i]);
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
    //  param: T num - the data that is being placed
    //
    //  returns: bool - if the num can be added or not
    //
    bool pushAt(int sub, T num) {
      
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
    void inOrderPush(T num) {

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
    //  return: T - the data being removed
    //
    T popFront() {
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
    //  Description: Removes data from the back of the list
    //
    //  params: none
    //
    //  return: T - the data being removed
    //
    T popRear() {
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
    //  return: T - the data being removed
    //
    T popAt(int sub) {
      T num;    //variable to hold the data being removed

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
    //  params:      T val - the data we're looking for
    //
    //  return:      int - the subscript of where the integer is 
    //
    int find(T val) {
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

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: so that MyVector can be treated as an array
    //
    //  params: int sub - the subscript of where you want to go
    //
    //  returns: the data at the subscripted spot
    //
    T &operator[](int sub) {
      node* temp = this->head;
      
      //  not in bounds
      if(sub >=this->currentSize || sub < 0) {
        cout << "subscript is out of bounds\n";
        exit(0);
      }
      //  traverse list to find subscripted spot
      else {  
        for(int i = 0; i < sub; i++) {
          temp = temp->next;
        }
      }
      return temp->data;        //  return whats there
      
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: prints out a vector
    //
    //  params: ostream& out          - the output we are returning
    //  params: const MyVector vector - the vector we are printing
    //
    //  returns: the data at the subscripted spot
    //
    friend ostream &operator<<(ostream& out, const MyVector& vector) {

      node* temp = vector.head; //  pointer to traverse the list

      //  Printing out to the terminal
      out << "[";
      while(temp->next != nullptr) {
        out << temp->data << ", ";
        temp = temp->next;
      }
      out << temp->data << "]";

      return out;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: prints out a vector
    //
    //  params: ostream& out          - the output we are returning
    //  params: const MyVector vector - the vector we are printing
    //
    //  returns: the data at the subscripted spot
    //
    friend ofstream &operator<<(ofstream& out, const MyVector& vector) {

      node* temp = vector.head; //  pointer to traverse the list

      //  Printing out to the terminal
      out << "[";
      while(temp->next != nullptr) {
        out << temp->data << ", ";
        temp = temp->next;
      }
      out << temp->data << "]";

      return out;
    }

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds two vectors together
    //
    //  params: MyVectors& - the vector left of the '+' being added
    //
    //  returns: a new vector
    //
    MyVector operator+(MyVector& other) {
      MyVector assigned;        //  new Vector combination
      node* temp = this->head;
      node* temp2 = other.head;

      int min;    // index of the smallest Vector

      bool otherMax = false; //if "other" is bigger

      if(this->currentSize >= other.currentSize) {
        min = other.currentSize;      //  "this" is bigger
      }
      else {
        min = this->currentSize;      //  "other" is bigger
        otherMax = true;
      }

      //  adds the values
      for(int i = 0; i < min; i++) {
        //assigned.pushRear(this[i] + other[i]); //ask about this ***
        assigned.pushRear(temp->data + temp2->data);
        temp = temp->next;    //
        temp2 = temp2->next;  //  moves to next spot
      }

      // add on the rest of the "other" MyVector object
      if(otherMax) {
        for(int i = min; i < other.currentSize; i++) {
          assigned.pushRear(other[i]);
          
        }
      }
      else {
        //  add on the rest of the "this" MyVector object
        for(int i = min; i < this->currentSize; i++) {
          // assigned.pushRear(this[i]);
          assigned.pushRear(temp->data);
          if(temp->next != nullptr)
            temp = temp->next;
        }
      }

      return assigned;
    }    


    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: adds two vectors together
    //
    //  params: MyVectors& - the vector left of the '+' being added
    //
    //  returns: a new vector
    //
    MyVector operator-(MyVector& other) {
      MyVector assigned;        //  new Vector combination
      node* temp = this->head;
      node* temp2 = other.head;

      int min;    // index of the smallest Vector

      bool otherMax = false; //if "other" is bigger

      if(this->currentSize >= other.currentSize) {
        min = other.currentSize;      //  "this" is bigger
      }
      else {
        min = this->currentSize;      //  "other" is bigger
        otherMax = true;
      }

      //  adds the values
      for(int i = 0; i < min; i++) {

        //assigned.pushRear(this[i] + other[i]); //ask about this ***
        assigned.pushRear(temp->data - temp2->data);
        temp = temp->next;
        temp2 = temp2->next;
      }

      // add on the rest of the "other" MyVector object
      if(otherMax) {
        for(int i = min; i < other.currentSize; i++) {
          assigned.pushRear(other[i]);
        }
      }
      // add on the rest of the "this" MyVector object
      else {
        for(int i = min; i < this->currentSize; i++) {
          
          assigned.pushRear(temp->data);
          if(temp->next != nullptr)
            temp = temp->next;
        }
      }

      return assigned;
    }    


    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: multiplies two vectors together
    //
    //  params: MyVectors& - the vector left of the '*' being added
    //
    //  returns: a new vector
    //
    MyVector operator*(MyVector& other) {
      MyVector assigned;        //  new Vector combination
      node* temp = this->head;
      node* temp2 = other.head;

      int min;    // index of the smallest Vector

      bool otherMax = false; //if "other" is bigger

      if(this->currentSize >= other.currentSize) {
        min = other.currentSize;      //  "this" is bigger
      }
      else {
        min = this->currentSize;      //  "other" is bigger
        otherMax = true;
      }

      //  adds the values
      for(int i = 0; i < min; i++) {

        //assigned.pushRear(this[i] + other[i]); //ask about this ***
        assigned.pushRear(temp->data * temp2->data);
        temp = temp->next;
        temp2 = temp2->next;
      }

      // add on the rest of the "other" MyVector object
      if(otherMax) {
        for(int i = min; i < other.currentSize; i++) {
          assigned.pushRear(other[i]);
        }
      }
      // add on the rest of the "this" MyVector object
      else {
        for(int i = min; i < this->currentSize; i++) {
          
          assigned.pushRear(temp->data);
          if(temp->next != nullptr)
            temp = temp->next;
        }
      }

      return assigned;
    } 


    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: multiplies two vectors together
    //
    //  params: MyVectors& - the vector left of the '*' being added
    //
    //  returns: a new vector
    //
    MyVector operator/(MyVector& other) {
      MyVector assigned;        //  new Vector combination
      node* temp = this->head;
      node* temp2 = other.head;

      int min;    // index of the smallest Vector

      bool otherMax = false; //if "other" is bigger

      if(this->currentSize >= other.currentSize) {
        min = other.currentSize;      //  "this" is bigger
      }
      else {
        min = this->currentSize;      //  "other" is bigger
        otherMax = true;
      }

      //  adds the values
      for(int i = 0; i < min; i++) {

        // Checking to see if we're dividing by zero
        if(temp2->data == 0){
          cout<<"divide by zero error!"<<endl;
          exit(0);
        } 
        assigned.pushRear(temp->data / temp2->data);
        temp = temp->next;
        temp2 = temp2->next;
      }

      // add on the rest of the "other" MyVector object
      if(otherMax) {
        for(int i = min; i < other.currentSize; i++) {
          assigned.pushRear(other[i]);
        }
      }
      // add on the rest of the "this" MyVector object
      else {
        for(int i = min; i < this->currentSize; i++) {
          
          assigned.pushRear(temp->data);
          if(temp->next != nullptr)
            temp = temp->next;
        }
      }

      return assigned;
    } 

    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Checks to see if two vectors are equal
    //
    //  params: MyVectors& - the vector to the right of "=="
    //
    //  returns: if the vectors are equal or not
    //
    bool operator==(MyVector& other) {

      node* temp = this->head;
      node* temp2 = other.head;

      //  Check if theyre the same size
      if(this->currentSize != other.currentSize) {
        return false;
      }
      else {
        // Traverse the list
        while(temp) {
          //  making sure values are equal
          if(temp->data != temp2->data) {
            return false;
          }
          temp = temp->next;
          temp2 = temp2->next;
        }
      }
      return true;
    }


    ////////////////////////////////////////////////////////////////////////////
    //
    //  Description: Essentially a copy constructor
    //
    //  params: the MyVector object being copied
    //
    //  returns: the new MyVector object being passed in
    //
    MyVector &operator=(const MyVector& assigner) {

      
      // Emptying the list
      node* temp = head; 
      node* garbage; 
      while(temp != nullptr) {
        garbage = temp; 
        temp = temp->next; 
        delete garbage;
      }
      head = tail = nullptr;

      node* currentTemp = assigner.head;
    
      //  traverse other list and assign values to new list
      for (int i = 0; i < assigner.currentSize; i++) {
        pushRear(currentTemp->data);
        currentTemp = currentTemp->next;
      }

      // moving the index over
      this->currentSize = assigner.currentSize;

      return *this;
    }



};



int main() {

  ofstream outfile;
  outfile.open("test.out");

  outfile << "Noah Orta\n9/24/2021\nFall 2143\n\n";

  int a1[] = { 1, 2, 3, 4, 5 };
  int a2[] = { 10, 20, 30 };

  MyVector<int> v1(a1, 5);
  MyVector<int> v2(a2, 3);

  cout << v1[2] << endl;
  // writes out 3

  v1[4] = 9;
  // v1 now = [1,2,3,4,9]

  cout << v1 << endl;
  // writes out [1,2,3,4,9]` to console.

  outfile << v1 << endl;
  // writes out [1,2,3,4,9]` to your output file.

  MyVector v3 = v1 + v2;
  cout << v3 << endl;
  // writes out [11,22,33,4,9]` to console.

  v3 = v1 - v2;
  cout << v3 << endl;
  // writes out [-9,-18,-27,4,9]` to console.

  v3 = v2 - v1;
  cout << v3 << endl;
  // writes out [9,18,27,4,9]` to console.

  v3 = v2 * v1;
  cout << v3 << endl;
  // writes out [10,40,90,4,9]` to console.

  v3 = v1 * v2;
  cout << v3 << endl;
  // writes out [10,40,90,4,9]` to console.

  v3 = v1 / v2;
  cout << v3 << endl;
  // writes out [0,0,0,4,9]` to console.

  v3 = v2 / v1;
  cout << v3 << endl;
  // writes out [10,10,10,4,9]` to console.

  cout << (v2 == v1) << endl;
  // writes 0 to console (false) 

  MyVector<int> v4 = v1;
  cout << (v4 == v1) << endl;
  // writes 1 to console (true) 

}
