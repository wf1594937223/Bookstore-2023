#ifndef FINANCE
#define FINANCE
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
namespace finance//开局记录sum，每个记录id,前缀收入和，前缀支出和
{
int sum;
int getpla_fin(int x)
{
    return (x - 1) * 2 * sizeof(double) + x * sizeof(int);
}
void init()
{
    fstream file;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    if (!file.good())
    {
        sum = 0;
        file.close();
        file.open("0.fin", std::ios::binary | std::ios::out);
        file.write(reinterpret_cast <char *> (&sum), sizeof(int));
    }
    else
    {
        file.seekg(0);
        file.read(reinterpret_cast <char *> (&sum), sizeof(int));
    }
    return;
}
double que_earn(int count)
{
    fstream file; double x = 0, y = 0;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    if (sum == 0 || count == 0) return 0;
    file.seekg(getpla_fin(sum - count) + sizeof(int));
    file.read(reinterpret_cast <char *> (&x), sizeof(double));
    if (sum == count) x = 0;
    file.seekg(getpla_fin(sum) + sizeof(int));
    file.read(reinterpret_cast <char *> (&y), sizeof(double));
    return y - x;
}
double que_earn_all()
{
    fstream file; double x, y; int count = sum;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    if (sum == 0 || count == 0) return 0;
    file.seekg(getpla_fin(sum - count) + sizeof(int));
    file.read(reinterpret_cast <char *> (&x), sizeof(double));
    if (sum == count) x = 0;
    file.seekg(getpla_fin(sum) + sizeof(int));
    file.read(reinterpret_cast <char *> (&y), sizeof(double));
    return y - x;
}
double que_pay(int count)
{
    fstream file; double x, y;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    if (sum == 0 || count == 0) return 0;
    file.seekg(getpla_fin(sum - count) + sizeof(int) + sizeof(double));
    file.read(reinterpret_cast <char *> (&x), sizeof(double));
    if (sum == count) x = 0;
    file.seekg(getpla_fin(sum) + sizeof(int) + sizeof(double));
    file.read(reinterpret_cast <char *> (&y), sizeof(double));
    return y - x;
}
double que_pay_all()
{
    fstream file; double x, y; int count = sum;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    if (sum == 0 || count == 0) return 0;
    file.seekg(getpla_fin(sum - count) + sizeof(int) + sizeof(double));
    file.read(reinterpret_cast <char *> (&x), sizeof(double));
    if (sum == count) x = 0;
    file.seekg(getpla_fin(sum) + sizeof(int) + sizeof(double));
    file.read(reinterpret_cast <char *> (&y), sizeof(double));
    return y - x;
}
void add_earn(double x)
{
    fstream file; double u, v;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    file.seekg(getpla_fin(sum) + sizeof(int));
    file.read(reinterpret_cast <char *> (&u), sizeof(double));
    file.read(reinterpret_cast <char *> (&v), sizeof(double));
    u += x;
    sum++;
    file.seekp(getpla_fin(sum));
    file.write(reinterpret_cast <char *> (&sum), sizeof(int));
    file.write(reinterpret_cast <char *> (&u), sizeof(double));
    file.write(reinterpret_cast <char *> (&v), sizeof(double));
}
void add_pay(double x)
{
    fstream file; double u, v;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    file.seekg(getpla_fin(sum) + sizeof(int));
    file.read(reinterpret_cast <char *> (&u), sizeof(double));
    file.read(reinterpret_cast <char *> (&v), sizeof(double));
    v += x;
    sum++;
    file.seekp(getpla_fin(sum));
    file.write(reinterpret_cast <char *> (&sum), sizeof(int));
    file.write(reinterpret_cast <char *> (&u), sizeof(double));
    file.write(reinterpret_cast <char *> (&v), sizeof(double));
}
void end()
{
    fstream file;
    file.open("0.fin", std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(0);
    file.write(reinterpret_cast <char *> (&sum), sizeof(double));
}
}
#endif