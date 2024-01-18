#ifndef ACCOUNT
#define ACCOUNT
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
namespace account //开头记录一个sum，每个账号记录new_id，哪本书
{
int sum;
int getpla_acc(int x)
{
    return (x - 1) * 2 * sizeof(int) + sizeof(int);
}
void init()
{
    fstream file;
    file.open("0.acc", std::ios::binary | std::ios::in | std::ios::out);
    if (!file.good())
    {
        sum = 0;
        file.close();
        file.open("0.acc", std::ios::binary | std::ios::out);
        file.write(reinterpret_cast <char *> (&sum), sizeof(int));
    }
    else
    {
        file.seekg(0);
        file.read(reinterpret_cast <char *> (&sum), sizeof(int));
    }
    return;
}
void login(int account_id)
{
    sum++;
    fstream file;
    file.open("0.acc", std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(getpla_acc(sum));
    file.write(reinterpret_cast <char *> (&account_id), sizeof(int));
    int x = 0;
    file.write(reinterpret_cast <char *> (&x), sizeof(int));
    return;
}
void select(int book_id)
{
    fstream file;
    file.open("0.acc", std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(getpla_acc(sum) + sizeof(int));
    file.write(reinterpret_cast <char *> (&book_id), sizeof(int));
    return;
}
void logout()
{
    int x = 0;
    fstream file;
    if (!sum) return;
    file.open("0.acc", std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(getpla_acc(sum));
    file.write(reinterpret_cast <char *> (&x), sizeof(int));
    file.write(reinterpret_cast <char *> (&x), sizeof(int));
    sum--;
    return; 
}
int now_account()
{
    fstream file; int x;
    if (!sum) return 0;
    file.open("0.acc", std::ios::binary | std::ios::in | std::ios::out);
    file.seekg(getpla_acc(sum));
    file.read(reinterpret_cast <char *> (&x), sizeof(int));
    return x;
}
int now_select()
{
    fstream file; int x;
    file.open("0.acc", std::ios::binary | std::ios::in | std::ios::out);
    file.seekg(getpla_acc(sum) + sizeof(int));
    file.read(reinterpret_cast <char *> (&x), sizeof(int));
    return x;
}
void end()
{
    fstream file;
    file.open("0.acc", std::ios::binary | std::ios::in | std::ios::out);
    file.seekp(0);
    file.write(reinterpret_cast <char *> (&sum), sizeof(double));
}
}
#endif