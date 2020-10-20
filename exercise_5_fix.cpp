#include <iostream>
#include <string.h>
#include <string>
using namespace std;
class Book
{
private:
    char *title;
    char *authors;
    int publishingYear;

public:
    Book()
    {
        /*
         * STUDENT ANSWER
         */
        this->title = NULL;
        this->authors = NULL;
        this->publishingYear = 0;
    }

    Book(const char *title, const char *authors, int publishingYear)
    {
        /*
         * STUDENT ANSWER
         */
        this->title = new char[strlen(title)+1]; //cstring not string
        this->authors = new char[strlen(authors)+1];
        strcpy(this->title, title);
        strcpy(this->authors, authors);
        this->publishingYear = publishingYear;
    }
    
    ~Book()
    {
        /*
         * STUDENT ANSWER
         */
        delete[] title;
        delete[] authors;
        publishingYear = 0;
    }
    
    friend class Printer;
};

class Printer
{
public:
    static void printBook(const Book book)
    {
        /*
         * STUDENT ANSWER
         */ 
        string temp ="";
        cout << book.title << endl;
        for(int i = 0; i < (int)strlen(book.authors)+1; i++){
            if(book.authors[i] != ',' && i!= (int)strlen(book.authors)) temp += book.authors[i];
            else {
                cout << temp << 1 << endl;
                temp = "";
                i++;
            }
        }
        cout << book.publishingYear;        
    }
};
int main() 
{
    Book book1("Giai tich 1", "Nguyen Dinh Huy, Nguyen Thi Xuan Anh", 2000);
    Printer::printBook(book1);
}