#include<iostream>
using namespace std;

enum Color
{
    red,
    green,
    blue
};
enum Size
{
    small,
    medium,
    big
};

class Toy
{
protected:
    double price;

public:
    Toy(double price)
    {
        this->price = price;
    }

    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;

public:
    CarToy(double price, Color color) : Toy(price)
    {
        this->color = color;
    }

    void printType()
    {
        cout << "This is a car toy\n";
    }

    friend class ToyBox;
};

class PuzzleToy : public Toy
{
private:
    Size size;

public:
    PuzzleToy(double price, Size size) : Toy(price)
    {
        this->size = size;
    }

    void printType()
    {
        cout << "This is a puzzle toy\n";
    }

    friend class ToyBox;
};

class ToyBox
{
private:
    Toy* toyBox[5];
    int numberOfItems;

public:
    ToyBox()
    {
        /*TODO: set zero numberOfItems and nullptr toyBox*/
        *toyBox = nullptr;
        numberOfItems = 0;
    }
    
    int addItem(const CarToy& carToy)
    {
        /*  function add a new Car toy to the box.
                 If successfully added, the function returns the current number of toys in the box. 
                 If the box is full, return -1.
         */

        Color _color = carToy.color;
        double _price = carToy.price;

        // Adding a new Item 
        if(numberOfItems < 5) {
            toyBox[numberOfItems] = new CarToy(_price, _color);
            numberOfItems++;
        
        // The box is not full
            return numberOfItems;
        }
        else return -1;
    }
    
    int addItem(const PuzzleToy& puzzleToy)
    {
        /*  TODO: function add a new Puzzle toy to the box.
                 If successfully added, the function returns the current number of toys in the box. 
                 If the box is full, return -1.
         */
        Size _size = puzzleToy.size;
        double _price = puzzleToy.price;

        // Adding new item
        if(numberOfItems < 5){
            toyBox[numberOfItems] = new PuzzleToy(_price, _size);
            numberOfItems++;

        // the box not full(<=5)
            return numberOfItems;
        }
        else return -1;

    }
    
    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};

int main(){
CarToy car(20000,red);
PuzzleToy puzzle(30000,small);

ToyBox box;
Toy* toy = new CarToy(30000,red);
toy->printType();
}