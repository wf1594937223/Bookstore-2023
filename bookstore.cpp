# include "account.h"
# include "account_save.h"
# include "finance.h"
# include "isbntoid.h"
# include "keywordstoisbn.h"
# include "nametoisbn.h"
# include "useridtoid.h"
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
int strtoint(string s)
{
    int anss = 0, m = s.length();
    for (int i = 0; i < m; i++) anss = (anss * 10) + s[i];
    return n;
}
int strtodouble(string s)
{
    int anss = 0, m = s.length(); double ansn = 0, tmp = 1;
    for (int i = 0; i < m; i++)
        if (s[i] != '.') anss = (anss * 10) + s[i] - '0'; else break;
    i++;
    for (; i < m; i++)
    {
        tmp /= 10;
        ansn += tmp * (s[i] - '0');
    }
    return anss + ansn;
}
int main()
{
    account::init();
    finance::init();
    iti::init_prog();
    kti::init_prog();
    nti::init_prog();
    uti::init_prog();
    int i, j, n, m, acc_id, book_id;
    int a1, a2, a3, a4;
    string s, s1, s2, s3;
    while(1)
    {
        m = 0;
        std::getline(std::cin, s);
        if (s[0] == 'q' && s[1] == 'u' || s[0] == 'e' && s[1] == 'x') break;
        if (s[0] == 's' && s[1] == 'u')
        {
            m = gtpla(s, m); s1 = gtstr(s, m);
            acc_id = uti::find(s1)[0];
            n = account_save::account_state(acc_id); s3 = account_save::account_password(acc_id);
            a1 = account::now_account(); a2 = account_save::account_state(a1);
            m = gtpla(s, m); s2 = gtstr(s, m);
            if (s2 == "" && n <= a2 || s2 != "" && s2 != s3) continue;
            login(acc_id);
            continue;
        }
        if (s[0] == 'l' && s[1] == 'o')
        {
            account::logout();
            continue;
        }
        if (s[0] == 'r' && s[1] == 'e')
        {
            m = gtpla(s, m); s1 = gtstr(s, m);
            m = gtpla(s, m); s2 = gtstr(s, m);
            m = gtpla(s, m); s3 = gtstr(s, m); a1 = strtoint(s3);
            m = gtpla(s, m); s3 = gtstr(s, m);
            account_save::add(a1, s1, s2, s3);
        }
    }

    account::end();
    finance::end();
    iti::end_prog();
    kti::end_prog();
    nti::end_prog();
    uti::end_prog();
    return 0;
}