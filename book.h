#ifndef BOOK
#define BOOK
# include <stdio.h>
# include <iostream>
# include <fstream>
# include "isbntoid.h"
# include "finance.h"
# include "nametoisbn.h"
# include "authortoisbn.h"
# include "keywordstoisbn.h"
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
namespace book
{
    vector<string> keywords_split (string keywords)
    {
        vector<string> ve;
        int i, j, n = keywords.length(); string s;
        for (i = 0; i < n; i++)
        {
            if (keywords[i] != '|') s += keywords[i];
            else
            {
                ve.push_back(s);
                s.clear();
            }
        }
        ve.push_back(s);
        s.clear();
        return ve;
    }
    int getpla_book(int x)
    {
        return (x - 1) * (200 + 2 * sizeof(int) + 2 * sizeof(double)) + sizeof(int);
    }
    int i, j, n, m, sum = 0;
    void init_prog()
    {
        fstream file;
	    file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
	    if(!file.good())
        {
            file.close();
            file.open("book.txt", std::ios::binary | std::ios::out);
	    	file.write(reinterpret_cast<char *> (&sum), sizeof(int));
        }
        else
	    	file.read(reinterpret_cast<char *> (&sum), sizeof(int));
	    file.close();
        return;
    }
    void end_prog()
    {
        fstream file;
	    file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
    	file.write(reinterpret_cast<char *> (&sum), sizeof(int));
    	file.close();
        return;
    }
    void add(string isbn, string bookname = "", string author = "", int quantity = 0, double price = 0, double total_cost = 0, string keywords = "")
    {
        fstream file; sum++; int id = sum;// std::cout << "!" << id;
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
        iti::insert(isbn, id);
    }//sizeof(int), 20, 60, 60, sizeof(int), sizeof(double), sizeof(double), 60
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
    void modify(int id, string isbn, string bookname, string author, string keywords, double price)
    {
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id));
        file.write(reinterpret_cast<char *>(&id), sizeof(int));
        file.write(isbn.c_str(), 20);
        file.write(bookname.c_str(), 60);
        file.write(author.c_str(), 60);
        file.seekp(getpla_book(id) + 140 + 2 * sizeof(int));
        file.write(reinterpret_cast<char *>(&price), sizeof(double));
        file.seekp(getpla_book(id) + 140 + 2 * sizeof(int) + 2 * sizeof(double));
        file.write(keywords.c_str(), 60);
    }//sizeof(int), 20, 60, 60, sizeof(int), sizeof(double), sizeof(double), 60
    void modify_price(int id, double price)
    {
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + 2 * sizeof(int) + 140);
        file.write(reinterpret_cast<char *>(&price), sizeof(double));
    }
    void modify_bookname(int id, string bookname)
    {
        string s1 = book_isbn(id), s2 = book_bookname(id);
        nti::del(s2, s1);
        if (bookname == "") return;
        nti::insert(bookname, s1);
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + sizeof(int) + 20);
        file.write(bookname.c_str(), 60);
    }
    void modify_author(int id, string author)
    {
        string s1 = book_isbn(id), s2 = book_author(id);
        ati::del(s2, s1);
        if (author == "") return;
        ati::insert(author, s1);
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + sizeof(int) + 80);
        file.write(author.c_str(), 60);
    }
    void modify_keywords(int id, string keywords)
    {
        string s1 = book_isbn(id), s2 = book_keywords(id);
        vector<string> ve = keywords_split(s2); int i, j = ve.size();
        for (i = 0; i < j; i++)
            kti::del(ve[i], s1);
        if (keywords == "") return;
        ve.clear();
        ve = keywords_split(keywords); j = ve.size();
        for (i = 0; i < j; i++)
            kti::insert(ve[i], s1);
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + 2 * sizeof(int) + 2 * sizeof(double) + 140);
        file.write(keywords.c_str(), 60);
    }
    void modify_isbn(int id, string isbn)
    {
        if (iti::find(isbn).size()) return;
        modify_bookname(id, "");
        modify_author(id, "");
        modify_keywords(id, "");
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + sizeof(int));
        file.write(isbn.c_str(), 20);
        string s1 = book_bookname(id), s2 = book_author(id), s3 = book_keywords(id), s4 = book_isbn(id);
        iti::del(s4, id);
        modify_bookname(id, s1);
        modify_author(id, s2);
        modify_keywords(id, s3);
        iti::insert(isbn, id);
    }
    void buy(int id, int quantity)
    {
        int x = book_quantity(id); x -= quantity;
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + 140 + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
        finance::add_earn(book_price(id) * quantity);
        return;
    }
    void import(int id, int quantity, double total_cost)
    {
        int x = book_quantity(id); x += quantity;
        fstream file;
        file.open("book.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + 140 + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
        finance::add_pay(total_cost);
        return;
    }
}
#endif