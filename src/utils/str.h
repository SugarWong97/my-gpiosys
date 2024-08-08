#ifndef __STR_H__
#define __STR_H__

// 全字母转小写
int str_to_lower(char * str, int len);
// 全字母转大写
int str_to_upper(char * str, int len);

/***********************************************
 *  * str_replace  字符串替换
 *  *
 *  * pszInput    要转变的字符串
 *  * pszOld      要替换的子串
 *  * pszNew      被替换成的子串
 *  * pszOutput   输出的缓冲区
 *  * nOutputlen  输出缓冲区的长度
 */
void str_replace(char * pszInput, char * pszOld, char * pszNew,char * pszOutput,int nOutputlen);

#endif/*__STR_H__*/
