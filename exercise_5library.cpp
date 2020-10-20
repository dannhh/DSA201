#include<iostream>
#include<cstring>
#include<cmath>
#include <fstream>

using namespace std;
class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;

public:
    Book()
    {
        this->title = NULL;
        this->authors = NULL;
        this->publishingYear = 0;
    }   
    Book(const char* title, const char* authors, int publishingYear)
    {
        this->title = new char[strlen(title)+1]; //cstring not string
        this->authors = new char[strlen(authors)+1];
        strcpy(this->title, title);
        strcpy(this->authors, authors);
        this->publishingYear = publishingYear;

    }

    Book(const Book &book)
    {
        this->title = new char[strlen(title)+1]; //cstring not string
        this->authors = new char[strlen(authors)+1];
        strcpy(this->title, book.title);
        strcpy(this->authors, book.authors);
        this->publishingYear = book.publishingYear;
    }
    
    void setTitle(const char* title)
    {
        this->title = new char[strlen(title)+1]; //cstring not string
        strcpy(this->title, title);
    }

    void setAuthors(const char* authors)
    {
        this->authors = new char[strlen(authors)+1]; //cstring not string
        strcpy(this->authors, authors);
    }

    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
    }

    char* getTitle() const
    {
        return this->title;
    }

    char* getAuthors() const
    {
        return this->authors;
    }

    int getPublishingYear() const
    {
        return this->publishingYear;
    }

    ~Book()
    {
        delete[] title;
        delete[] authors;
        publishingYear = 0;
    }

    int timkiemchuoi(const char* chuoi){
        return 1;
    }
    friend bool checkAuthor(Book book, const char* author)
    {
        /*
         * STUDENT ANSWER
         * TODO: returns true if the author is on the book's authors list, otherwise it returns false
         */
        string temp;
        bool x = false;
        for (int i = 0; i < (int)strlen(book.authors); i++) {
            if (book.authors[i - 1] == ',' && book.authors[i] == ' ') continue;
            if (book.authors[i] != ',') {
                temp += book.authors[i];
            }
            if (book.authors[i] == ',' || i == (int)strlen(book.authors) - 1) {
                for (int j = 0; j < (int)(temp.length()); j++) {
                    if (*(author + j) != temp[j]) {
                        x = true;
                        break;
                    }
                }
                if (!x) {
                    return true;
                }
                else {
                    x = false;
                    temp = "";
                }
            }
        }
        return false;
    }


    void printBook(){
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
};

int main(){
Book book1("Giai tich 1","Nguyen Thi Xuan Anh,Nguyen Dinh Huy, Nguyen Kim Chung",2000);
cout << checkAuthor(book1,"Nguyen Dinh Huy");
}
