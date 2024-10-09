#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#endif // DATASTRUCT_H


#define S_TEXT_LEN 128
#define S_NAME_LEN 128
#define S_PROFILE_LEN 256
struct AbstractData
{
    int s_sort;//派生类的类别
    char s_text[S_TEXT_LEN];//注释，用于数据传输时的解释
};

struct Project : AbstractData
{
    char s_name[S_NAME_LEN];
    char s_profile[S_PROFILE_LEN];
};
