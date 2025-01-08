#include "utils/tomlc99/toml.h"
#include <stdio.h>
#include <string.h>

int Get_Config_File_Content(char *buffer)
{
    FILE *file;
    int file_Size;

    // 打开toml
    file = fopen("config.toml", "rb");
    if (!file) return 1;

    // 获取toml大小
    fseek(file, 0, SEEK_END);
    file_Size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // 获取buffer大小
    int buffer_Size = strlen(buffer);

    // 比较buffer与toml的大小
    if (buffer_Size < file_Size) return 2;

    // 读取文件内容
    fread(buffer, file_Size, 1, file);
    buffer[file_Size] = '\0';

    // 关闭toml
    fclose(file);
    
    return 0;
}

toml_table_t* parse_Config_File(char *content, char *errbuf)
{
    return toml_parse(content, errbuf, sizeof(errbuf));
}

char *Get_bindIP(toml_table_t *TABLE_server)
{
    // 127.0.0.1 为缺省设置
    if (!TABLE_server) return "127.0.0.1";
    toml_datum_t bind_ip = toml_string_in(TABLE_server, "bind_ip");
    if (bind_ip.ok) return bind_ip.u.s;
    else return "127.0.0.1";
}

int Get_bindPort(toml_table_t *TABLE_server)
{
    // 25565 为缺省设置
    if (!TABLE_server) return 25565;
    toml_datum_t bind_port = toml_int_in(TABLE_server, "bind_port");
    if (bind_port.ok)
    {
        if (bind_port.u.i > 65535 || bind_port.u.i < 0) return 25565;
        else return bind_port.u.i;
    }
    else return 25565;
}