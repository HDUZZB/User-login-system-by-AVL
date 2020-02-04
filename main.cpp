
#include "Landing.cpp"
#include <time.h>
#include <string>
#include <stdlib.h>

int main()
{
	system("color 70"); // 设置控制台背景颜色
	Landing land;
	int fst = 0;
	while(!land.welcome(fst++));
	return 0;
}
