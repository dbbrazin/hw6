//HW6 by Dane Brazinski
//SU Net ID: dbbrazin SUID: 533140379
//HW6 Due: March 8, Wednesday, at 11:59PM
#include <iostream>
#include <memory>
using namespace std;
template <typename T> class Node { //Your T has to support either int or float
public:
    shared_ptr<T> pValue; //pValue is a pointer to an object of type T
    shared_ptr<Node<T>> row_next;//Points to the next node in the same row
    shared_ptr<Node<T>> col_next;//Points to the nexe node in the same col
    Node() {}
    Node(T v) { pValue = make_shared<T>(v); }// pValue.reset(new T(v)); will also work,but slower
};

template <typename T> class Ring2D {
public:
    shared_ptr<Node<T>> head;//Points to the node at first row and first column
    Ring2D() {};

    //Implement the following functions:
    Ring2D(const initializer_list<T>& I); //initializer_list
    /*
    the first two number in the initializer_list will be number of rows and number of columns
    followed by values in each row
    For example, for  3 4  1 2 3 4  5 6 7 8  9 10 11 12: 3 rows and 4 columns; first row: to 1 2 3 4;
    second row: 5 6 7 8; third row 9 10 11 12
    */
    ~Ring2D();//destructor; whenever possible, you should do minimum work.



    Ring2D(const Ring2D<T>& R);//copy constructor
    void operator=(const Ring2D<T>& R);//Lvalue operator=; copy assignment
    Ring2D(Ring2D<T>&& R);//move constructor
    void operator=(Ring2D<T>&& R);//Rvalue operator=; move assignment
    Ring2D<T> ThreeTimes();//Return a Ring2D with values being three times of the current Ring2D

    void DeleteRow(int r);//Delete row r of Ring2D
    //If r is out of range, simply do nothing and return.

};

/*
Implement the needed overloaded operater<< such that you can do cout <<Ring2D<T> instance.
For the example described in the above initializer_list, you output should look like:
1 2 3 4
5 6 7 8
9 10 11 12
*/


/*
Print: "Copy Constructor", "Move Constructor", "Copy Assignment", "Move Assignment", "Destructor" when leaving
the corresponding functions --  the same way I did for Lecture on Ring (3/31/2020).


*/

template<typename T> Ring2D<T>::Ring2D(const initializer_list<T> &I) {
    auto start = I.begin();
    int row = *start++; //3
    int col = *start++; //4
    auto p = I.end() - 1;
    shared_ptr<Node<T>> lastInRow, lastRowHead, rowNext, firstOn;
    head = make_shared<Node<T>>(*start);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            shared_ptr<Node<T>> p1 = make_shared<Node<T>>(*p--);
            if (j == 0)
                lastInRow = p1;
            p1->col_next = head;
            p1->row_next = rowNext;
            head = p1;
            if (i != 0)
                for(int x = 0; x < col-1; x++)
                    rowNext = rowNext->col_next;

            if(i == row-1) {
                firstOn->row_next = p1;
                for (int x = 0; x < col - 1; x++)
                    firstOn = firstOn->col_next;
            }
        }
        if(i==0)
            firstOn = lastInRow;
        lastInRow->col_next = head;
        head->row_next = lastRowHead;
        rowNext = lastInRow;
        lastRowHead = head;
    }
}

template <class T> Ring2D<T>::~Ring2D() { //destructor
    if (!head) {
        cout << "Destrutor" << endl;
        return;
    }
    head->col_next.reset();
    head->row_next.reset();
    head.reset();
    cout << "Destrutor" << endl;
}


template <class T> Ring2D<T>::Ring2D(const Ring2D<T>& R) { //copy constructor
    if (!R.head) return;

    int row = 0;
    int col = 0;
    shared_ptr<Node<T>> current = R.head;
    do {
        col++;
        current = current->col_next;
    } while (current != R.head);
    do {
        row++;
        current = current->row_next;
    } while (current != R.head);

    shared_ptr<Node<T>> lastInRow, lastRowHead, rowNext, firstOn;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            shared_ptr<Node<T>> p1 = make_shared<Node<T>>();
            if (j == 0)
                lastInRow = p1;
            p1->col_next = head;
            p1->row_next = rowNext;
            head = p1;
            if (i != 0)
                for(int x = 0; x < col-1; x++)
                    rowNext = rowNext->col_next;

            if(i == row-1) {
                firstOn->row_next = p1;
                for (int x = 0; x < col - 1; x++)
                    firstOn = firstOn->col_next;
            }
        }
        if(i==0)
            firstOn = lastInRow;
        lastInRow->col_next = head;
        head->row_next = lastRowHead;
        rowNext = lastInRow;
        lastRowHead = head;
    }

    shared_ptr<Node<T>> p = head, rowHead = R.head; current = R.head;
    do {
        do {
            p->pValue = make_shared<T>(*current->pValue);
            current = current->col_next;
            p = p->col_next;
        } while (current != rowHead);
        current = current->row_next;
        p = p->row_next;
        rowHead = rowHead->row_next;
    } while (current != R.head);

    cout << "Copy Constructor" << endl;
}

template <class T> void Ring2D<T>::operator=(const Ring2D<T>& R) { //Lvalue assignment, i.e., copy assignment
    if (head) {
        head->col_next.reset();
        head->row_next.reset();
        head.reset();//wihtout this, the first node will not be deleted.
    }

    int row = 0;
    int col = 0;
    shared_ptr<Node<T>> current = R.head, rowHead = R.head;
    do {
        col++;
        current = current->col_next;
    } while (current != R.head);
    do {
        row++;
        current = current->row_next;
    } while (current != R.head);

    shared_ptr<Node<T>> lastInRow, lastRowHead, rowNext, firstOn;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            shared_ptr<Node<T>> p1 = make_shared<Node<T>>();
            if (j == 0)
                lastInRow = p1;
            p1->col_next = head;
            p1->row_next = rowNext;
            head = p1;
            if (i != 0)
                for(int x = 0; x < col-1; x++)
                    rowNext = rowNext->col_next;

            if(i == row-1) {
                firstOn->row_next = p1;
                for (int x = 0; x < col - 1; x++)
                    firstOn = firstOn->col_next;
            }
        }
        if(i==0)
            firstOn = lastInRow;
        lastInRow->col_next = head;
        head->row_next = lastRowHead;
        rowNext = lastInRow;
        lastRowHead = head;
    }

    shared_ptr<Node<T>> p = head; current = R.head, rowHead = R.head;
    do {
        do {
            p->pValue = make_shared<T>(*current->pValue);
            current = current->col_next;
            p = p->col_next;
        } while (current != rowHead);
        current = current->row_next;
        p = p->row_next;
        rowHead = rowHead->row_next;
    } while (current != R.head);
    cout << "Copy Assignment" << endl;
}



template<class T> Ring2D<T>::Ring2D(Ring2D<T>&& R) { //Move constructor
    head = R.head;
    R.head.reset();
    cout << "Move Constructor" << endl;
}

template<class T> void Ring2D<T>::operator=(Ring2D<T>&& R) {//Rvalue assignment; move assignment
    if (head) {
        head->col_next.reset();
        head->row_next.reset();
        head.reset();
    }
    head = R.head;
    R.head.reset();
    cout << "Move Assignment" << endl;
}

template<class T> Ring2D<T> Ring2D<T>::ThreeTimes() {
    Ring2D<T> temp = *this;
    if (!head) return temp;
    shared_ptr<Node<T>> current = temp.head, rowHead = temp.head;
    do {
        do {
            current->pValue = make_shared<T>((*current->pValue)*3);
            current = current->col_next;
        } while (current != rowHead);
        current = current->row_next;
        rowHead = rowHead->row_next;
    } while (current != temp.head);
    return temp;
}

template <class T> void Ring2D<T>::DeleteRow(int r) {
    if (!head) return;
    int row = 0;
    shared_ptr<Node<T>> current = head, rowHead, rowBefore = head;
    do {
        row++;
        if (r == row)
            rowHead = current;
        current = current->row_next;
    } while (current != head);
    if (r > row) return;
    if (rowHead == head) head = head->row_next;
    while(rowBefore->row_next != rowHead)
        rowBefore = rowBefore->row_next;
    while(row){
        rowBefore->row_next = rowHead->row_next;
        rowBefore = rowBefore->col_next;
        rowHead = rowHead->col_next;
        row--;
    }
    //rowHead->col_next.reset()
    rowHead.reset();
}

template <class T> ostream& operator<<(ostream &str, const Ring2D<T> &R) {
    if(!R.head) return str;
    shared_ptr<Node<T>> current = R.head, rowHead = R.head;
    do {
        do {
            str << *(current->pValue) << " ";
            current = current->col_next;
        } while (current != rowHead);
        str << endl;
        current = current->row_next;
        rowHead = rowHead->row_next;
    } while (current != R.head);
    return str;
}

int main() {

    Ring2D<int> R1{ 3, 4,  1, 2, 3, 4,  5, 6, 7, 8,  9, 10, 11, 12};//initializer_list
    cout << R1 << endl<<endl;


    Ring2D<int> R2{ R1 };//copy constructor
    cout << R2 << endl<<endl;

    Ring2D<int> R3;
    R3 = R1;//copy assignment
    cout << R3 << endl << endl;

    Ring2D<int> R4;
    R4 = R1.ThreeTimes();//this is pointing to object R1
    //Compiler will convert it to R4.operator=(R1.ThreeTimes());
    //copy constructor -- declare temp and initialize it to R1
    //move constructor -- create hidden (temporary) copy
    //destructor-- delete temp becuase it goes out of scope
    //move assignment -- Assign value from hidden copy to R4
    //destructor-- delete hedden copy because it goes out of scope
    cout << R4 << endl<<endl;


    R4.DeleteRow(2);
    cout << R4 << endl << endl;
    R4.DeleteRow(2);
    cout << R4 << endl << endl;
    R4.DeleteRow(1);
    cout << R4 << endl << endl;

    return 0;
}






