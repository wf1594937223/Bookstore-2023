#ifndef BOOK
#define BOOK
# include <stdio.h>
# include <iostream>
# include <fstream>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
namespace book
{
    int getpla_book(int x)
    {
        return (x - 1) * (200 + 2 * sizeof(int) + 2 * sizeof(double));
    }
    int i, j, n, m;
    void add(int id, string isbn, string bookname = "", string author = "", int quantity = 0, double price = 0, double total_cost = 0, string keywords = "")
    {
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
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
    void modify(int id, string isbn, string bookname, string author, string keywords, double price)
    {
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id));
        file.write(reinterpret_cast<char *>(&id), sizeof(int));
        file.write(isbn.c_str(), 20);
        file.write(bookname.c_str(), 60);
        file.write(author.c_str(), 60);
        file.seekp(getpla_book(id) + 140 + sizeof(int));
        file.write(reinterpret_cast<char *>(&price), sizeof(double));
        file.seekp(getpla_book(id) + 140 + sizeof(int) + 2 * sizeof(double));
        file.write(keywords.c_str(), 60);
    }
    string book_isbn(int id)
    {
        string s; char c[64];
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + sizeof(int));
        file.read(c, 20); s = c;
        return s;
    }
    string book_bookname(int id)
    {
        string s; char c[64];
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 20 + sizeof(int));
        file.read(c, 60); s = c;
        return s;
    }
    string book_bookname(int id)
    {
        string s; char c[64];
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 20 + sizeof(int));
        file.read(c, 60); s = c;
        return s;
    }
    string book_author(int id)
    {
        string s; char c[64];
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 80 + sizeof(int));
        file.read(c, 60); s = c;
        return s;
    }
    int book_quantity(int id)
    {
        string s; char c[64]; int x;
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 140 + sizeof(int));
        file.read(reinterpret_cast<char *>(&x), sizeof(int));
        return x;
    }
    double book_price(int id)
    {
        string s; char c[64]; double x;
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 140 + sizeof(int) + sizeof(int));
        file.read(reinterpret_cast<char *>(&x), sizeof(double));
        return x;
    }
    double book_total_cost(int id)
    {
        string s; char c[64]; double x;
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 140 + sizeof(int) + sizeof(double) + sizeof(int));
        file.read(reinterpret_cast<char *>(&x), sizeof(double));
        return x;
    }
    string book_keywords(int id)
    {
        string s; char c[64];
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 140 + sizeof(int) + 2 * sizeof(double) + sizeof(int));
        file.read(c, 60); s = c;
        return s;
    }
    void buy(int id, int quantity)
    {
        int x = book_quantity(id); x -= quantity;
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + 140 + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
        return;
    }
    void import(int id, int quantity)
    {
        int x = book_quantity(id); x += quantity;
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + 140 + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
        return;
    }
}
#endif