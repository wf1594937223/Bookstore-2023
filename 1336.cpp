#include <fstream>
#include "1336.h"

MemoryRiver<long long> m;

int main() {
	m.initialise("try.txt");
	long long x = 23, y;
	int p = m.write(x);
	printf("%d\n", p);
	m.read(y, p);
	printf("%lld", y);
	return 0;
}
