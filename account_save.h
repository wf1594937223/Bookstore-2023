#ifndef ACCOUNT_SAVE
#define ACCOUNT_SAVE
# include <stdio.h>
# include <iostream>
# include <fstream>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
namespace account_save//id, state, type(1,3,7), userid, password, username 
{
    int getpla_book(int x)
    {
        return (x - 1) * (64 * 3 + 3 * sizeof(int));
    }
    int i, j, n, m;
    void add(int id, int type, string userid, string password, string username)
    {
        fstream file; int state = 1;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id));
        file.write(reinterpret_cast<char *>(&id), sizeof(int));
        file.write(reinterpret_cast<char *>(&state), sizeof(int));
        file.write(reinterpret_cast<char *>(&type), sizeof(int));
        file.write(userid.c_str(), 60);
        file.write(password.c_str(), 60);
        file.write(username.c_str(), 60);
    }//sizeof(int), 20, 60, 60, sizeof(int), sizeof(double), sizeof(double), 60
    void modify(int id, string password)
    {
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + 64 + 3 * sizeof(int));
        file.write(password.c_str(), 60);
    }
    void del(int id)
    {
        fstream file; int x = 0;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_book(id) + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
    }
    int account_state(int id)
    {
        string s; char c[65]; int x;
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + sizeof(int));
        file.read(reinterpret_cast<char *>(&x), sizeof(int));
        return x;
    }
    int account_type(int id)
    {
        string s; char c[65]; int x;
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 2 * sizeof(int));
        file.read(reinterpret_cast<char *>(&x), sizeof(int));
        return x;
    }
    string account_userid(int id)
    {
        string s; char c[65];
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 3 * sizeof(int));
        file.read(c, 64); s = c;
        return s;
    }
    string account_password(int id)
    {
        string s; char c[65];
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 3 * sizeof(int) + 64);
        file.read(c, 64); s = c;
        return s;
    }
    string account_username(int id)
    {
        string s; char c[65];
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_book(id) + 3 * sizeof(int) + 2 * 64);
        file.read(c, 64); s = c;
        return s;
    }
}
#endif