#include <stdio.h>
#include <string.h>
#include <math.h>

int str_to_lower(char * str, int len)
{
    int i;
    for(i=0;i<len;i++)//遍历
    {
        if(str[i]>='A'&&str[i]<='Z')
        {
            str[i]+=32;
        }
    }
    return 0;
}

int str_to_upper(char * str, int len)
{
    int i;
    for(i=0;i<len;i++)//遍历
    {
        if(str[i]>='a'&&str[i]<='z')
        {
            str[i]-=32;
        }
    }
    return 0;
}

/***********************************************
 *  * str_replace  字符串替换
 *  *
 *  * pszInput    要转变的字符串
 *  * pszOld      要替换的子串
 *  * pszNew      被替换成的子串
 *  * pszOutput   输出的缓冲区
 *  * nOutputlen  输出缓冲区的长度
 */
void str_replace(char * pszInput, char * pszOld, char * pszNew,char * pszOutput,int nOutputlen)
{
    char temp[128];
    int nLen=0;
    char *s, *p;
    s = pszInput;
    while (s != NULL)
    {
        p = strstr(s, pszOld);

        if (p == NULL )
        {
            memcpy(pszOutput+nLen,s,strlen(s)+nLen>nOutputlen?nOutputlen-nLen:strlen(s));
            return ;
        }
        memcpy(pszOutput+nLen,s,p-s+nLen>nOutputlen?nOutputlen-nLen:p-s);
        nLen+=p-s+nLen>nOutputlen?nOutputlen-nLen:p-s;
        if(nLen>=nOutputlen)
        {
            return;
        }
        memcpy(pszOutput+nLen,pszNew,strlen(pszNew)+nLen>nOutputlen?nOutputlen-nLen:strlen(pszNew));
        nLen+=strlen(pszNew)+nLen>nOutputlen?nOutputlen-nLen:strlen(pszNew);
        if(nLen>=nOutputlen)
        {
            return;
        }
        s+=strlen(pszOld)+p-s;
    }
    return ;
}
