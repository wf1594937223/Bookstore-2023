//一个文件存块开始 另一个存具体内容
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::vector;
namespace nti
{
struct NODE
{
    int id, l, r;
};
const int lim_txt = 4;
const int half_siz = lim_txt / 2;
int tot_txt, tot_str, beg;
string tostr(int x)
{
    if (!x) return "";
    char c = ((x % 10) & 15) + '0';
    return tostr(x / 10) + c;
}
void init_total()
{
    string s = "0.nti";
    fstream file;
    file.open(s, std::ios::binary | std::ios::out);
    int tmp = 1;
    file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
	file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    tot_txt = 1;
	beg = 1;
	tmp = 0; s = "";
	file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
	file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
	file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
	file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
	file.write(s.c_str(), 64);
	file.write(s.c_str(), 64);
	file.write(reinterpret_cast<char *>(&tmp), sizeof(int));
    file.close();
	s = "1.nti";
	file.open(s, std::ios::binary | std::ios::out);
	file.close();
    return;
}
int getpla_blo(int x)
{
    return ((x - 1) * 5 + 2) * sizeof(int) + (x - 1) * 128;
}
int getpla_txt(int x)
{
    return ((x - 1) * 2) * sizeof(int) + (x - 1) * 128;
}//目前考虑的是开始记录该块大小，上一个，下一个，最大串，最大串对应最大存储，初始串位置
//每个串记录串、值、上一个、下一个
//注意值是64bite字符串
void depart_txt(int x)
{
//	std::cout << x << std::endl;
	fstream file0, file1;
    string s1, s2, s3;
	file0.open("0.nti", std::ios::binary | std::ios::in | std::ios::out);
	file1.open("1.nti", std::ios::binary | std::ios::in | std::ios::out);
    int i, j;
    int a1, a2, a3, a4, a5, w;
    char cstr[65];
    tot_txt++;
    a1 = half_siz;
	file0.seekp(getpla_blo(x));
//	file0.seekp(12);
//	std::cout << file0.tellp() << sizeof(int) << std::endl;
    file0.write(reinterpret_cast<char *> (&a1), sizeof(int));
    file0.seekg(getpla_blo(x) + sizeof(int));
    file0.read(reinterpret_cast<char *> (&a3), sizeof(int));
    file0.read(reinterpret_cast<char *> (&a5), sizeof(int));
//	std::cout << a3 << a5 << std::endl;
	file0.seekg(getpla_blo(x) + 3 * sizeof(int) + 128);
    file0.read(reinterpret_cast<char *> (&j), sizeof(int));
//	std::cout << file0.tellp() << file0.tellg() << std::endl;
	file0.seekp(getpla_blo(x) + sizeof(int));
    file0.write(reinterpret_cast<char *> (&a3), sizeof(int));
//	std::cout << file0.tellp() << sizeof(int) << std::endl;
    file0.write(reinterpret_cast<char *> (&tot_txt), sizeof(int));
//	std::cout << tot_txt << std::endl;
    for (i = 1; i <= half_siz; i++)
    {
		file1.seekg(getpla_txt(j));
        file1.read(cstr, 64); s1 = cstr;
        file1.read(cstr, 64); s3 = cstr;
        file1.read(reinterpret_cast<char *> (&a2), sizeof(int));
        a3 = j;
        file1.read(reinterpret_cast<char *> (&j), sizeof(int));
    }
    a4 = 0;
    file1.seekp(getpla_txt(a3) + 128 + sizeof(int));
    file1.write(reinterpret_cast<char *> (&a4), sizeof(int));
    file1.seekp(getpla_txt(j) + 128);
    file1.write(reinterpret_cast<char *> (&a4), sizeof(int));
	file0.seekp(getpla_blo(x) + 3 * sizeof(int));
    file0.write(s1.c_str(), 64);
    file0.write(s3.c_str(), 64);
//    file0.write(reinterpret_cast<char *> (&a1), sizeof(int));
	w = j;
    a1 = half_siz;
    file0.seekp(getpla_blo(tot_txt));
    file0.write(reinterpret_cast<char *> (&a1), sizeof(int));
    file0.write(reinterpret_cast<char *> (&x), sizeof(int));
    file0.write(reinterpret_cast<char *> (&a5), sizeof(int));
    for (i = 1; i <= half_siz; i++)
    {
//		if (!j) cer();
		file1.seekg(getpla_txt(j));
        file1.read(cstr, 64); s1 = cstr;
        file1.read(cstr, 64); s3 = cstr;
        file1.read(reinterpret_cast<char *> (&a2), sizeof(int));
        file1.read(reinterpret_cast<char *> (&j), sizeof(int));
    }
	file0.seekp(getpla_blo(tot_txt) + 3 * sizeof(int));
    file0.write(s1.c_str(), 64);
    file0.write(s3.c_str(), 64);
//    file0.write(reinterpret_cast<char *> (&a1), sizeof(int));
    file0.write(reinterpret_cast<char *> (&w), sizeof(int));
	file0.close();
	file1.close();
    return;
}
void insert(string index, string value)
{
	fstream file0, file1;
	file0.open("0.nti", std::ios::binary | std::ios::in | std::ios::out);
	file1.open("1.nti", std::ios::binary | std::ios::in | std::ios::out);
    int i = beg, j;
    char cstr[65];
    while(i)
    {
        file0.seekg(getpla_blo(i));
        int siz, x, y, z; string s1, s2, s3, val;
        file0.read(reinterpret_cast<char *> (&siz), sizeof(int));
        file0.read(reinterpret_cast<char *> (&x), sizeof(int));//previous block id
        file0.read(reinterpret_cast<char *> (&y), sizeof(int));//next block id
        file0.read(cstr, 64); s1 = s2 = cstr;//maxinum str
        file0.read(cstr, 64); val = cstr;//maxinum value
        file0.read(reinterpret_cast<char *> (&z), sizeof(int));//first store id
//		std::cout << siz << ' ' << val << ' ' << z << std::endl;
        if (y && (index > s1 || index == s1 && value > val))
        {
            i = y;
            continue;
        }
//		printf("!!!");
//		cer();
        tot_str++;
        siz++;
		if (!z)
		{
//			cer();
			file0.seekp(getpla_blo(i)); siz = 1;
			file0.write(reinterpret_cast<char *> (&siz), sizeof(int));
			file0.seekp(getpla_blo(i) + 3 * sizeof(int));
			file0.write(index.c_str(), 64);
			file0.write(value.c_str(), 64);
			j = tot_str;
			file0.write(reinterpret_cast<char *> (&j), sizeof(int));
            file1.seekp(getpla_txt(tot_str));
			file1.write(index.c_str(), 64);
            file1.write(value.c_str(), 64);
//			file1.write(reinterpret_cast<char *> (&value), sizeof(int));
			j = 0;
			file1.write(reinterpret_cast<char *> (&j), sizeof(int));
			file1.write(reinterpret_cast<char *> (&j), sizeof(int));
			return;
		}
        j = z;
        for(;;)
        {
            file1.seekg(getpla_txt(j));
            file1.read(cstr, 64); s1 = cstr;
            file1.read(cstr, 64); s3 = cstr;
            int u, v, w;
            file1.read(reinterpret_cast<char *> (&v), sizeof(int));
            file1.read(reinterpret_cast<char *> (&w), sizeof(int));
            if (s1 < index || s1 == index && s3 < value)
            {
                if (!w) break;
                j = w;
                continue;
            }
            break;
        }//j : first store id whose storage is larger than this
        int a1, a2, a3, a4;
        file1.seekg(getpla_txt(j));
        file1.read(cstr, 64); s1 = cstr;
        file1.read(cstr, 64); s3 = cstr;
        file1.read(reinterpret_cast<char *> (&a2), sizeof(int));
        file1.read(reinterpret_cast<char *> (&a3), sizeof(int));
        if (index == s1 && s3 == value) {tot_str--; siz--; return;}
        file1.seekp(getpla_txt(tot_str));
        file1.write(index.c_str(), 64);
        file1.write(value.c_str(), 64);
        file1.write(reinterpret_cast<char *> (&a2), sizeof(int));
        file1.write(reinterpret_cast<char *> (&j), sizeof(int));
        if (index > s1 || index == s1 && value > s3)
        {
            file0.seekp(getpla_blo(i) + 3 * sizeof(int));
            file0.write(index.c_str(), 64);
            file0.write(value.c_str(), 64);
            file1.seekp(getpla_txt(j) + 128 + sizeof(int));
            file1.write(reinterpret_cast<char *> (&tot_str), sizeof(int));
            file1.seekp(getpla_txt(tot_str) + 128);
            file1.write(reinterpret_cast<char *> (&j), sizeof(int));
            a4 = 0;
            file1.write(reinterpret_cast<char *> (&a4), sizeof(int));
        }
        else
        {
            if (a2)
            {
                file1.seekp(getpla_txt(a2) + 128 + sizeof(int));
                file1.write(reinterpret_cast<char *> (&tot_str), sizeof(int));
            }
            file1.seekp(getpla_txt(j) + 128);
            file1.write(reinterpret_cast<char *> (&tot_str), sizeof(int));
	        if (!a2)
            {
                file0.seekp(getpla_blo(i) + 3 * sizeof(int) + 128);
                file0.write(reinterpret_cast<char *> (&tot_str), sizeof(int));
            }
        }
        file0.seekp(getpla_blo(i));
        file0.write(reinterpret_cast<char *> (&siz), sizeof(int));
		file0.close();
		file1.close();
//		if (index == "19824553971700740052129610100715568069141470348418") std::cout << "ok" << siz << a2 << j << value << std::endl;
//		std::cout << "!ok" << i << value << std::endl;
        if (siz >= lim_txt) depart_txt(i);
        return;
    }
}
void del(string index, string value)
{
	fstream file0, file1;
	file0.open("0.nti", std::ios::binary | std::ios::in | std::ios::out);
	file1.open("1.nti", std::ios::binary | std::ios::in | std::ios::out);
    int i = beg, j;
    char cstr[65];
    while(i)
    {
        file0.seekg(getpla_blo(i));
        int siz, x, y, z; string s1, s2, s3, val;
        file0.read(reinterpret_cast<char *> (&siz), sizeof(int));
        file0.read(reinterpret_cast<char *> (&x), sizeof(int));//previous block id
        file0.read(reinterpret_cast<char *> (&y), sizeof(int));//next block id
        file0.read(cstr, 64); s1 = s2 = cstr;//maxinum str
        file0.read(cstr, 64); val = cstr;//maxinum value
        file0.read(reinterpret_cast<char *> (&z), sizeof(int));//first store id
        if (y && (index > s1 || index == s1 && value > val))
        {
            i = y;
            continue;
        }
        j = z;
		if (!z) return;
        for(;;)
        {
            file1.seekg(getpla_txt(j));
            file1.read(cstr, 64); s1 = cstr;
            file1.read(cstr, 64); s3 = cstr;
            int u, v, w;
            file1.read(reinterpret_cast<char *> (&v), sizeof(int));
            file1.read(reinterpret_cast<char *> (&w), sizeof(int));
            if (s1 < index || s1 == index && s3 < value)
            {
                if (!w) break;
                j = w;
                continue;
            }
            break;
        }//j : first store id whose storage is larger than this
        int a1, a2, a3, a4;
        file1.seekg(getpla_txt(j));
        file1.read(cstr, 64); s1 = cstr;
        file1.read(cstr, 64); s3 = cstr;
        file1.read(reinterpret_cast<char *> (&a2), sizeof(int));
        file1.read(reinterpret_cast<char *> (&a3), sizeof(int));
        if (s1 != index || s3 != value) return;
        file0.seekp(getpla_blo(i)); siz--;
        file0.write(reinterpret_cast<char *> (&siz), sizeof(int));
		if ((!a2) && (!a3))
		{
			file0.seekp(getpla_blo(i));
			a4 = 0; s1 = "";
			file0.write(reinterpret_cast<char *>(&a4), sizeof(int));
			file0.write(reinterpret_cast<char *>(&a4), sizeof(int));
			file0.write(reinterpret_cast<char *>(&a4), sizeof(int));
			file0.write(s1.c_str(), 64);
			file0.write(s1.c_str(), 64);
			file0.write(reinterpret_cast<char *>(&a4), sizeof(int));
			if(x)
			{
				file0.seekp(getpla_blo(x) + 2 * sizeof(int));
				file0.write(reinterpret_cast<char *> (&y), sizeof(int));
			}
			else if(y)
				beg = y;
			if(y)
			{
				file0.seekp(getpla_blo(y) + sizeof(int));
				file0.write(reinterpret_cast<char *> (&x), sizeof(int));
			}
//			file.seekp(sizeof(int));
//			file.write(reinterpret_cast<char *> (&x), sizeof(int));
//			file.write(reinterpret_cast<char *> (&y), sizeof(int));
			return;
		}
        if (a2)
        {
            file1.seekp(getpla_txt(a2) + 128 + sizeof(int));
            file1.write(reinterpret_cast<char *> (&a3), sizeof(int));
        }
		else
		{
			file0.seekp(getpla_blo(i) + 3 * sizeof(int) + 128);
			file0.write(reinterpret_cast<char *> (&a3), sizeof(int));
		}
        if (a3)
        {
            file1.seekp(getpla_txt(a3) + 128);
            file1.write(reinterpret_cast<char *> (&a2), sizeof(int));
        }
		else
		{
			file1.seekg(getpla_txt(a2));
			file1.read(cstr, 64); s1 = cstr;
	        file1.read(cstr, 64); s3 = cstr;
			file0.seekp(getpla_blo(i) + 3 * sizeof(int));
			file0.write(s1.c_str(), 64);
			file0.write(s3.c_str(), 64);
//			file.seekp(getpla(a2) + 64 + 2 * sizeof(int));
//			file.write(reinterpret_cast<char *> (&a4), sizeof(int));
		}
		file0.close();
		file1.close();
//		if (index == "19824553971700740052129610100715568069141470348418") std::cout << "okd" << siz << a2 << a3 << value << std::endl;
        return;
    }
}
vector <string> find(string index)
{
	fstream file0, file1; vector <string> ve;
	file0.open("0.nti", std::ios::binary | std::ios::in | std::ios::out);
	file1.open("1.nti", std::ios::binary | std::ios::in | std::ios::out);
    int i = beg, j, tott = 0;
    char cstr[65];
    while(i)
    {
        if (!i) break;
        file0.seekg(getpla_blo(i));
        int siz, x, y, z; string s1, s2, s3, val;
        file0.read(reinterpret_cast<char *> (&siz), sizeof(int));
        file0.read(reinterpret_cast<char *> (&x), sizeof(int));//previous block id
        file0.read(reinterpret_cast<char *> (&y), sizeof(int));//next block id
        file0.read(cstr, 64); s1 = s2 = cstr;//maxinum str
        file0.read(cstr, 64); val = cstr;//maxinum value
        file0.read(reinterpret_cast<char *> (&z), sizeof(int));//first store id
        if (index > s1)
        {
            i = y;
            continue;
        }
        j = z;
//		std::cout << "!" << i << std::endl;
        for(;;)
        {
            if (!j) break;
//			std::cout << "! " << j << std::endl;
//			std::cout << "!!!";
            file1.seekg(getpla_txt(j));
            file1.read(cstr, 64); s1 = cstr;
            file1.read(cstr, 64); s3 = cstr;
            int u, v, w;
            file1.read(reinterpret_cast<char *> (&v), sizeof(int));
            file1.read(reinterpret_cast<char *> (&w), sizeof(int));
//			std::cout << "! " << w << std::endl;
//			if (j == w)
//			{
//				std::cout << "Huge warning!" << std::endl;
//				exit(0);
//			}
			j = w;
            if (s1 > index)
            {
				file0.close();
				file1.close();
                return ve;
            }
            if (s1 < index) continue;
            ve.push_back(s3);
			tott++;
        }
        i = y;
    }
    return ve;
}
void init_prog()
{
    fstream file;
	file.open("0.nti", std::ios::binary | std::ios::in | std::ios::out);
	if(!file.good())
		init_total();
	else
	{
		file.read(reinterpret_cast<char *> (&tot_txt), sizeof(int));
		file.read(reinterpret_cast<char *> (&beg), sizeof(int));
		file.read(reinterpret_cast<char *> (&tot_str), sizeof(int));
//		std::cout << tot_txt << beg << std::endl;
//		return 0;
	}
	file.close();
    return;
}
void end_prog()
{
    fstream file;
    file.open("0.nti", std::ios::binary | std::ios::in | std::ios::out);
	file.write(reinterpret_cast<char *> (&tot_txt), sizeof(int));
	file.write(reinterpret_cast<char *> (&beg), sizeof(int));
	file.write(reinterpret_cast<char *> (&tot_str), sizeof(int));
	file.close();
}
}
