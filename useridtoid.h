#ifndef UTI
#define UTI
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
using std::string;
using std::vector;
namespace uti
{
string tostr(int x);
void init_total();
int getpla_blo(int x);
int getpla_txt(int x);
void depart_txt(int x);
void insert(string index, int value);
void del(string index, int value);
vector <int> find(string index);
}
#endif 