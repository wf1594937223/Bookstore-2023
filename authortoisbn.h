#ifndef ATI
#define ATI
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
using std::string;
using std::vector;
namespace ati
{
string tostr(int x);
void init_total();
int getpla_blo(int x);
int getpla_txt(int x);
void depart_txt(int x);
void insert(string index, string value);
void del(string index, string value);
vector <string> find(string index);
}
#endif 