#ifndef BOOK
#define BOOK
# include <stdio.h>
# include <iostream>
# include <fstream>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
int getpla_book(int x)
{
    return (x - 1) * (200 + 2 * sizeof(int) + 2 * sizeof(double));
}
namespace book
{
    int i, j, n, m;
    void modify(int id, string isbn, string bookname = "", string author = "", int quantity = 0, double price = 0, double total_cost = 0, string keywords = "")
    {
        fstream file;
        file.open("book.txt");
        file.seekp(getpla_book(id));
        file.write(reinterpret_cast<char *>(&id), sizeof(int));
        file.write(isbn.c_str(), 20);
        file.write(bookname.c_str(), 60);
        file.write(author.c_str(), 60);
        file.write(reinterpret_cast<char *>(&quantity), sizeof(int));
        file.write(reinterpret_cast<char *>(&price), sizeof(double));
        file.write(reinterpret_cast<char *>(&total_cost), sizeof(double));
        file.write(keywords.c_str(), 60);
    }//sizeof(int), 20, 60, 60, sizeof(int), sizeof(double), sizeof(double), 60
}
#endif