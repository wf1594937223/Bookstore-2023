#ifndef STOREI
#define STOREI
# include <iostream>
# include <fstream>
# include <string>
using std::string;
string tostr(int x);
void init_total();
int getpla_blo(int x);
int getpla_txt(int x);
void depart_txt(int x);
void insert(string index, int value);
void del(string index, int value);
void find(string index);
#endif