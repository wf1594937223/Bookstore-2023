# include "account.h"
# include "account_save.h"
# include "finance.h"
# include "isbntoid.h"
# include "keywordstoisbn.h"
# include "authortoisbn.h"
# include "nametoisbn.h"
# include "useridtoid.h"
# include "book.h"
# include <iomanip>
using std::string;
int gtpla(string s, int x)
{
    int l = s.length();
    for (int i = x; i < l; i++)
    {
        if (s[i] == ' ' && (i + 1 == l || s[i + 1] != ' ')) return i + 1;
    }
    return l;
}
string gtstr(string s, int x)
{
    string s1 = ""; int l = s.length();
    for (int i = x; i < l; i++)
    {
        if (s[i] == ' ') break;
        s1 += s[i];
    }
    return s1;
}
string gtstr2(string s, int x)
{
    string s1 = ""; int l = s.length();
    for (int i = x; i < l; i++)
    {
        if (s[i] == ' ' || s[i] == '"') break;
        s1 += s[i];
    }
    return s1;
}
int strtoint(string s)
{
    int anss = 0, m = s.length(), fl = 1;
    for (int i = 0; i < m; i++)
    {
        if (s[i] == '-') {fl = -1; continue;}
        anss = (anss * 10) + s[i] - '0';
    }
    return anss * fl;
}
double strtodouble(string s)
{
    int i, anss = 0, m = s.length(), fl = 1; double ansn = 0, tmp = 1;
    for (i = 0; i < m; i++)
    {
        if (s[i] == '-') {fl = -1; continue;}
        if (s[i] != '.') anss = (anss * 10) + s[i] - '0'; else break;
    }
    i++;
    for (; i < m; i++)
    {
        tmp /= 10.0;
        ansn += tmp * (s[i] - '0');
    }
    return fl * (anss + ansn);
}
bool checkint(string s)
{
    int i, j, k = s.length(), tot = 0;
    for (i = 0; i < k; i++)
    {
        if (s[i] == '-') {if (i) return 0; tot++; continue;}
        if (s[i] < '0' || s[i] > '9') return 0;
    }
    return (tot < 2);
}
bool checkdouble(string s)
{
    int i, j, k = s.length(), tot = 0, totd = 0;
    for (i = 0; i < k; i++)
    {
        if (s[i] == '-') {if (i) return 0; tot++; continue;}
        if (s[i] == '.') {totd++; continue;}
        if (s[i] < '0' || s[i] > '9') return 0;
    }
    return (tot < 2) && (totd < 2);
}
void output(vector<int> ve)
{
    int i, j = ve.size();
    for (i = 0; i < j; i++)
    {
//        std::cout << ve[i] << std::endl;
        std::cout << book::book_isbn(ve[i]) << '\t';
        std::cout << book::book_bookname(ve[i]) << '\t';
        std::cout << book::book_author(ve[i]) << '\t';
        std::cout << book::book_keywords(ve[i]) << '\t';
        std::cout << std::fixed << std::setprecision(2) << book::book_price(ve[i]) << '\t';
        std::cout << book::book_quantity(ve[i]) << '\n';
    }
    if (!j) std::cout << '\n';
    return;
}
void output2(vector<string> ve)
{
    int i, j = ve.size();
    for (i = 0; i < j; i++)
    {
        int k = iti::find(ve[i])[0];
        std::cout << book::book_isbn(k) << '\t';
        std::cout << book::book_bookname(k) << '\t';
        std::cout << book::book_author(k) << '\t';
        std::cout << book::book_keywords(k) << '\t';
        std::cout << book::book_price(k) << '\t';
        std::cout << book::book_quantity(k) << '\n';
    }
    if (!j) std::cout << '\n';
    return;
}
void inva()
{
    std::cout << "Invalid" << std::endl;
    return;
}
void inva(int x)
{
    std::cout << "Invalid-reason:" << x << std::endl;
    return;
}
void inva(string x)
{
    std::cout << "Invalid-reason:" << x << std::endl;
    return;
}
int main()
{
//    freopen("3.in", "r", stdin);
//    freopen("3.out", "w", stdout);
    account::init();
    finance::init();
    book::init_prog();
    iti::init_prog();
    kti::init_prog();
    nti::init_prog();
    uti::init_prog();
    ati::init_prog();
    account_save::init_prog();
    int i, j, n, m, acc_id, book_id;
    int a1, a2, a3, a4, a5;
    string s, s1, s2, s3, s4, s5;
//        std::cout << "OK!" << std::endl;
//        return 0;
    while(1)
    {
        m = 0;
        std::getline(std::cin, s);
        if (s[0] == 'q' && s[1] == 'u' || s[0] == 'e' && s[1] == 'x') break;
        if (s[0] == 's' && s[1] == 'u')
        {
            m = gtpla(s, m); s1 = gtstr(s, m); //std::cout << s1 << std::endl;
            a1 = account::now_account(); a2 = account_save::account_state(a1);
            if (!uti::find(s1).size()) {inva(); continue;}
            acc_id = uti::find(s1)[0];
            n = account_save::account_state(acc_id); s3 = account_save::account_password(acc_id);
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            m = gtpla(s, m); s2 = gtstr(s, m);
            if (s2 == "" && n <= a2 || s2 != "" && s2 != s3) {inva(); continue;}
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            account::login(acc_id);
            account_save::account_login(acc_id);
            continue;
        }
        if (s[0] == 'l' && s[1] == 'o')
        {
            a1 = account::now_account();
            a2 = account_save::account_type(a1);
            if (a2 < 1) {inva(); continue;}
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            int id = account::now_account();
            account_save::account_logout(id);
            account::logout();
            continue;
        }
        if (s[0] == 'r' && s[1] == 'e')
        {
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s2 = gtstr(s, m);
            m = gtpla(s, m); s3 = gtstr(s, m);
            if (s3 == "") {inva(); continue;}
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            account_save::add(1, s1, s2, s3);
            continue;
        }
        if (s[0] == 'p' && s[1] == 'a')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 1) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s2 = gtstr(s, m);
            m = gtpla(s, m); s3 = gtstr(s, m);
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            if (s2 == "") {inva(); continue;}
            if (!uti::find(s1).size()) {inva(); continue;}
            if (s3 == "")
            {
                s3 = s2;
                a1 = account::now_account(); a2 = account_save::account_type(a1);
                if (a2 != 7) {inva(); continue;}
                a3 = uti::find(s1)[0];
                account_save::modify(a3, s3);
                continue;
            }
            a3 = uti::find(s1)[0];
            s4 = account_save::account_password(a3);
            if (s4 != s2) {inva(); continue;}
            account_save::modify(a3, s3);
            continue;
        }
        if (s[0] == 'u' && s[1] == 's')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
//            std::cout << a2 << std::endl;
            if (a2 < 3) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s2 = gtstr(s, m);
            m = gtpla(s, m); s3 = gtstr(s, m); a1 = strtoint(s3);
//            std::cout << s3 << ' ' << a2 << ' ' <<  a1 << std::endl;
            m = gtpla(s, m); s3 = gtstr(s, m);
            if (a2 <= a1) {inva(); continue;}
            if (uti::find(s1).size()) {inva(); continue;}
            if (s3 == "") {inva(); continue;}
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            account_save::add(a1, s1, s2, s3);
            continue;
        }
        if (s[0] == 'd' && s[1] == 'e')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 7) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            if (!uti::find(s1).size()) {inva(); continue;}
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            int id = uti::find(s1)[0];
            if (account_save::account_state(id) != 1) {inva(); continue;}
            account_save::del(id);
            continue;
        }
        if (s[0] == 's' && s[1] == 'h' && (s.length() == 4 || s[5] == '-'))
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 1) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            if (s1 == "")
            {
                output(iti::all());
                continue;
            }
            if (s1[1] == 'I')
            {
                m += 6; s2 = gtstr(s, m);
                if (s2 == "") {inva(); continue;}
                m = gtpla(s, m); s4 = gtstr(s, m);
                if (s4 != "") {inva(); continue;}
                output(iti::find(s2));
                continue;
            }
            if (s1[1] == 'n')
            {
                m += 7; s2 = gtstr2(s, m);
                if (s2 == "") {inva(); continue;}
                m = gtpla(s, m); s4 = gtstr(s, m);
                if (s4 != "") {inva(); continue;}
                output2(nti::find(s2));
                continue;
            }
            if (s1[1] == 'a')
            {
                m += 9; s2 = gtstr2(s, m);
                if (s2 == "") {inva(); continue;}
                m = gtpla(s, m); s4 = gtstr(s, m);
                if (s4 != "") {inva(); continue;}
                output2(ati::find(s2));
                continue;
            }
            if (s1[1] == 'k')
            {
                m += 10; s2 = gtstr2(s, m);
                if (s2 == "") {inva(); continue;}
                m = gtpla(s, m); s4 = gtstr(s, m);
                if (s4 != "") {inva(); continue;}
                int fl = 1, l = s2.length();
                for (i = 0; i < l; i++)
                    if (s2[i] == '|') {fl = 0; break;}
                if (!fl) {inva(); continue;}
                output2(kti::find(s2));
                continue;
            }
            continue;
        }
        if (s[0] == 'b' && s[1] == 'u')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 1) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s2 = gtstr(s, m);
            if (!iti::find(s1).size()) continue;
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            a1 = iti::find(s1)[0];
            if (!checkint(s2)) {inva(); continue;}
            a2 = strtoint(s2); if (a2 <= 0) {inva(); continue;}
            book::buy(a1, a2);
            continue;
        }
        if (s[0] == 's' && s[1] == 'e')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 3) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            if (!iti::find(s1).size())
            {
                book::add(s1);
                a1 = iti::find(s1)[0];
//            std::cout << a1 << std::endl;
                account::select(a1);
                continue;
            }
            a1 = iti::find(s1)[0];
            account::select(a1);
            continue;
        }
        if (s[0] == 'm' && s[1] == 'o')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 3) {inva(); continue;}
            int id = account::now_select();
            if (!id) {inva(); continue;}
            a1 = 0; a2 = 0; a3 = 0; a4 = 0; a5 = 0;
            while(1)
            {
                m = gtpla(s, m); s1 = gtstr(s, m);
                if (s1 == "") break;
                if (s1[1] == 'I') a1++;
                if (s1[1] == 'n') a2++;
                if (s1[1] == 'a') a3++;
                if (s1[1] == 'k') a4++;
                if (s1[1] == 'p') a5++;
            }
            if (a1 > 1 || a2 > 1 || a3 > 1 || a4 > 1 || a5 > 1) {inva(); continue;}
            m = 0;
            while(1)
            {
                m = gtpla(s, m); s1 = gtstr(s, m);
                if (s1 == "") break;
                if (s1[1] == 'I')
                {
                    m += 6; s2 = gtstr(s, m);
                    if (s2 == "") {inva(); continue;}
                    m = gtpla(s, m); s4 = gtstr(s, m);
                    if (s4 != "") {inva(); continue;}
                    book::modify_isbn(id, s2);
                    continue;
                }
                if (s1[1] == 'n')
                {
                    m += 7; s2 = gtstr2(s, m);
                    if (s2 == "") {inva(); continue;}
                    m = gtpla(s, m); s4 = gtstr(s, m);
                    if (s4 != "") {inva(); continue;}
                    book::modify_bookname(id, s2);
                    continue;
                }
                if (s1[1] == 'a')
                {
                    m += 9; s2 = gtstr2(s, m);
                    if (s2 == "") {inva(); continue;}
                    m = gtpla(s, m); s4 = gtstr(s, m);
                    if (s4 != "") {inva(); continue;}
                    book::modify_author(id, s2);
                    continue;
                }
                if (s1[1] == 'k')
                {
                    m += 10; s2 = gtstr2(s, m);
                    if (s2 == "") {inva(); continue;}
                    m = gtpla(s, m); s4 = gtstr(s, m);
                    if (s4 != "") {inva(); continue;}
                    book::modify_keywords(id, s2);
                    continue;
                }
                if (s1[1] == 'p')
                {
                    m += 7; s2 = gtstr2(s, m);
                    if (s2 == "") {inva(); continue;}
                    m = gtpla(s, m); s4 = gtstr(s, m);
                    if (s4 != "") {inva(); continue;}
                    book::modify_price(id, strtodouble(s2));
                    continue;
                }
            }
            continue;
        }
        if (s[0] == 'i' && s[1] == 'm')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 3) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s2 = gtstr(s, m);
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            a2 = account::now_select();
            if (!a2) {inva(); continue;}
            if (!checkint(s1)) {inva(); continue;}
            a1 = strtoint(s1); if (a1 <= 0) {inva(); continue;}
            if (!checkdouble(s2)) {inva(); continue;}
            double d1 = strtodouble(s1); if (d1 <= 0) {inva(); continue;}
            book::import(a2, a1, d1);
            continue;
        }
        if (s[0] == 's' && s[1] == 'h' && s[5] == 'f')
        {
            a1 = account::now_account(); a2 = account_save::account_type(a1);
            if (a2 < 7) {inva(); continue;}
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s4 = gtstr(s, m);
            if (s4 != "") {inva(); continue;}
            if (s1 == "")
            {
                std::cout << "+ " << finance::que_earn_all() << " - " << finance::que_pay_all() << '\n';
                continue;
            }
            a1 = strtoint(s1);
            std::cout << "+ " << finance::que_earn(a1) << " - " << finance::que_pay(a1) << '\n';
            continue;
        }
        int fl = 0;
        for (i = s.size() - 1; i >= 0; i--)
        {
            if (s[i] != ' ')
            {
                fl = 1;
                break;
            }
        }
        if (fl) inva();
    }

    account::end();
    finance::end();
    account_save::end_prog();
    book::end_prog();
    iti::end_prog();
    kti::end_prog();
    nti::end_prog();
    uti::end_prog();
    ati::end_prog();
    return 0;
}
//g++ bookstore.cpp nametoisbn.cpp authortoisbn.cpp keywordstoisbn.cpp useridtoid.cpp isbntoid.cpp -o code