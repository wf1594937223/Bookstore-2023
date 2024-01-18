# include <stdio.h>
# include "nametoisbn.h"
# include "authortoisbn.h"
int main()
{
    freopen("5.in", "r", stdin);
    freopen("5.ans", "w", stdout);
    ati::init_prog();
    int i, j, n, m;
    string s1, s2, s3;
    std::cin >> n;
    for (i = 1; i <= n; i++)
    {
        std::cin >> s1;
        if (s1 == "insert")
        {
            std::cin >> s2 >> s3;
            ati::insert(s2, s3);
        }
        if (s1 == "delete")
        {
            std::cin >> s2 >> s3;
            ati::del(s2, s3);
        }
        if (s1 == "find")
        {
            std::cin >> s2;
            vector < string > ve = ati::find(s2);
            if (!ve.size())
            {
                std::cout << "null" << std::endl;
                continue;
            }
            for (j = 0; j < ve.size(); j++)
                std::cout << ve[j] << " ";
            std::cout << std::endl;
        }
    }
    ati::end_prog();
}