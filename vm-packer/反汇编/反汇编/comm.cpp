/*-----------------------------------------------------------------------
第20章  虚拟机的设计
《加密与解密（第四版）》
(c)  看雪学院 www.kanxue.com 2000-2018
-----------------------------------------------------------------------*/

#include "stdafx.h"
#include "comm.h"
//MessageBox
void MsgBox( char* content, UINT nType )
{
	if( !content )
		return;
	MessageBoxA(NULL,content,VMPACKERTITLE,nType);
}
//去掉换行符和空格
//返回值,当没有内容时返回NULL;
BOOL Trim( char* pstr,char* str )
{
	int i,j = 0;

	if( !pstr || !str )
		return FALSE;

	strcpy(str,pstr);

	j = strlen(str);
	i = 0;
	for(i = 0; i < j; i ++)//去除换行符
	{
		if((str[i] == 0x0a) || (str[i] == 0x0d))
		{
			str[i] = 0;
		}
	}
	j = strlen(str);
	i = 0;
	while(str[i] == ' ')i++;//去掉头步空格
	if(i >= j) //全部空格，不处理
	{
		return FALSE;
	}
	memmove(str,str+i,j-i+1);
	j = strlen(str);
	i = 0;
	while(str[i] == ' ')i--;//去掉尾部空格
	if( i ) str[i] = '\0';
	if(i >= j) //全部空格，不处理
	{
		return FALSE;
	}
	return TRUE;
}
//字符串转16进制数
DWORD StringToHex(char* strSource)
{ 
	DWORD nTemp=0;
	char strTemp[64];

	if( strSource == NULL )
		return -1;
	strcpy(strTemp,strSource);

	for(char cc='G',dd='g';cc<='Z',dd<='z';  cc++,dd++)    //判断输入的字符串是否合法
	{
		if( strchr(strTemp,cc) != NULL || strchr(strTemp,dd) != NULL )
		{
			//::MessageBox(NULL,"请输入正确的16进制字符串!","输入错误",MB_ICONEXCLAMATION);
			return -1;
		}
	}

	for(int i = 0;  i<(int)::strlen(strSource);  i++)
	{
		int nDecNum;
		switch(strSource[i])
		{
		case 'a':
		case 'A':
			nDecNum = 10;
			break;
		case 'b':
		case 'B':
			nDecNum = 11;
			break;
		case 'c':
		case 'C':
			nDecNum = 12;
			break;
		case 'd':
		case 'D':
			nDecNum = 13;
			break;
		case 'e':
		case 'E':
			nDecNum = 14;
			break;
		case 'f':
		case 'F':
			nDecNum = 15;
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			nDecNum = strSource[i] - '0';
			break;
		default:
			return 0;   
		}
		nTemp += (DWORD)nDecNum * (long double)pow((long double)16,(int)(strlen(strSource)-i-1));
	}
	return nTemp;
}
void OutPutStr(char *str, ...)
{
	//#if _DEBUG
	char strbuf[1024]; 

	va_list	vl;
	va_start( vl, str );
	vsprintf( strbuf, str, vl );
	va_end( vl);

	OutputDebugString(strbuf);
	//#endif
}  