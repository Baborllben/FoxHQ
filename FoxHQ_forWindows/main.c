#include "foxhq.h"


int main()
{
	if (isConfigFileExists())
	{

	}
	else
	{
		// 配置文件不存在
		print("a", 0);
		print("b", 1);
		print("c", 2);
		print("d", 3);
	}
	return 0;
}