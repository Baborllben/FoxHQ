#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>


extern "C" int lookForConfigFile()
{
	FILE* configFile = NULL;
	errno_t err= fopen_s(&configFile, "./config.ini", "r");
	if (err == 0)
	{
		fclose(configFile);
		return 1;
	}
	else
	{
		printf("%d", err);
		return 0;
	}
}



char* readConfigFile()
{
	FILE* configFile = NULL;
	errno_t err = fopen_s(&configFile, "./config.ini", "r");
	char configFileInString_oneLine[256] = { 0 };
	char configFileInString_oneLine_last[256] = { 0 };
	while (1)
	{
		fgets(configFileInString_oneLine, 256, configFile);
		printf("%s", configFileInString_oneLine);
		if (!strcmp(configFileInString_oneLine, configFileInString_oneLine_last))
		{
			break;
		}
		strcpy_s(configFileInString_oneLine_last, 256, configFileInString_oneLine);
	}
}