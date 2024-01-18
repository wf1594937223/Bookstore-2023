# include <stdio.h>
# include "node.h"
using namespace node;
int main()
{
	int x = 2, y = 1;
	printf("%d", node::add(x, y));
	return 0;
}
