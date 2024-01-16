#ifndef ACCOUNT_SAVE
#define ACCOUNT_SAVE
# include <stdio.h>
# include <iostream>
# include <fstream>
# include "useridtoid.h"
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
namespace account_save//id, state, type(1,3,7), userid, password, username 
{
    int getpla_user(int x)
    {
        return (x - 1) * (64 * 3 + 3 * sizeof(int)) + sizeof(int);
    }
    int i, j, n, m, sum = 0;
    void init_prog()
    {
        fstream file;
	    file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
	    if(!file.good())
	    	file.write(reinterpret_cast<char *> (&sum), sizeof(int));
	    else
	    	file.read(reinterpret_cast<char *> (&sum), sizeof(int));
	    file.close();
        return;
    }
    void end_prog()
    {
        fstream file;
	    file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
    	file.write(reinterpret_cast<char *> (&sum), sizeof(int));
    	file.close();
        return;
    }
    void add(int type, string userid, string password, string username)
    {
        if (uti::find(userid).size()) return;
        fstream file; int state = 1; sum++; int id = sum;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_user(id));
        file.write(reinterpret_cast<char *>(&id), sizeof(int));
        file.write(reinterpret_cast<char *>(&state), sizeof(int));
        file.write(reinterpret_cast<char *>(&type), sizeof(int));
        file.write(userid.c_str(), 60);
        file.write(password.c_str(), 60);
        file.write(username.c_str(), 60);
        uti::insert(userid, id);
    }//sizeof(int), 20, 60, 60, sizeof(int), sizeof(double), sizeof(double), 60
    int account_state(int id)
    {
        string s; char c[65]; int x;
        if (!id) return 0;
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_user(id) + sizeof(int));
        file.read(reinterpret_cast<char *>(&x), sizeof(int));
        return x;
    }
    int account_type(int id)
    {
        string s; char c[65]; int x;
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_user(id) + 2 * sizeof(int));
        file.read(reinterpret_cast<char *>(&x), sizeof(int));
        return x;
    }
    string account_userid(int id)
    {
        string s; char c[65];
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_user(id) + 3 * sizeof(int));
        file.read(c, 64); s = c;
        return s;
    }
    string account_password(int id)
    {
        string s; char c[65];
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_user(id) + 3 * sizeof(int) + 64);
        file.read(c, 64); s = c;
        return s;
    }
    string account_username(int id)
    {
        string s; char c[65];
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekg(getpla_user(id) + 3 * sizeof(int) + 2 * 64);
        file.read(c, 64); s = c;
        return s;
    }
    void modify(int id, string password)
    {
        fstream file;
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_user(id) + 64 + 3 * sizeof(int));
        file.write(password.c_str(), 60);
    }
    void del(int id)
    {
        fstream file; int x = 0; string userid = account_userid(id);
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_user(id) + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
        uti::del(userid, id);
    }
    void account_login(int id)
    {
        fstream file; int x = 2; string userid = account_userid(id);
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_user(id) + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
    }
    void account_logout(int id)
    {
        fstream file; int x = 1; string userid = account_userid(id);
        file.open("account_save.txt", std::ios::binary | std::ios::in | std::ios::out);
        file.seekp(getpla_user(id) + sizeof(int));
        file.write(reinterpret_cast<char *>(&x), sizeof(int));
    }
}
#endif