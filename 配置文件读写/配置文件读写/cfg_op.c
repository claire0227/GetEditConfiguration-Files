#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cfg_op.h"

# define MaxLine 2048

int GetCfgItem(char *pFileName/*in*/,char *pKey/*in*/,char *pValue/*in out*/)
{
	int ret = 0;
	FILE *fp = NULL;
	char *pTemp = NULL;

	char *pBegin = NULL;
	char *pEnd = NULL;

	char lineBuf[MaxLine];
	
	fp = fopen(pFileName,"r");
	if(fp == NULL)
	{
		ret = -1;
		return ret;
	}
	while(!feof(fp))
	{
		//fgets(_Out_z_cap_(_MaxCount) char * _Buf, _In_ int _MaxCount, _Inout_ FILE * _File)
		fgets(lineBuf,MaxLine,fp);
		//printf("lineBuf%s",lineBuf);
		pTemp = strchr(lineBuf,'=');
		if(pTemp == NULL)
		{
			continue;
		}
		pTemp = strstr(lineBuf,pKey);
		if(pTemp == NULL)
		{
			continue;
		}
		pTemp = pTemp + strlen(pKey);
		pTemp  = strchr(pTemp,'=');
		if(pTemp == NULL)
		{
			continue;
		}
		pTemp = pTemp+1;
		printf("%s",pTemp);
		//去除字符串前后空格的函数
		while(1)
		{
			if(*pTemp==' ')
				pTemp++;
			else
			{
				pBegin = pTemp;
				if(*pBegin =='\n')
				{
					printf("配置项:%s没有配置\n",pKey);
					goto End;
				}
				break;
			}	
		}
		//获取结束点
		while(1)
		{
           if((*pTemp==' '||*pTemp=='\n')) 
		   {
			   break;
		   }
		   else
			   pTemp++;
		}
		pEnd = pTemp;
        memcpy(pValue,pBegin,pEnd-pBegin);
	}
End:
	if(fp== NULL)
		fclose(fp);
	return ret;
}



//写配置文件
//实现流程
//循环读每一行，检查key配置项是否存在，存在修改相应的value值
//若不存在，则在文件末尾添加“key = value”
//难点，如何修改文件流中的值,先把文件的内容缓存起来，修改之后再次放入文件中
int WriteCfgItem(char *pFileName/*in*/,char *pItemName/*in*/,char *pItemValue/*in out*/)
{

	int itag = 0;//标记值，标记是否为被修改的数据块
	int ret = 0;
	int length = 0;//代表文件的长度
	FILE	* fp = NULL;
	char lineBuf[MaxLine];
	char *pTemp = NULL,*pBegin = NULL,*pEnd=NULL;
	char filebuf[1024*8] = {0};//文件缓冲区


	if(pFileName==NULL ||pItemName==NULL ||pItemValue==NULL)
	{
		ret=-1;
		printf("WriteCfgItem error\n");
		goto End;
	}
	fp = fopen(pFileName,"r+");
	if(fp == NULL)
	{
		ret = -2;
		printf("fopen() err.\n");
	}
	if(fp == NULL)//提高容错力，当文件不存在的时候，新建文件
	{
		fp = fopen(pFileName,"w+t");
		if(fp == NULL)
		{
			ret = -3;
			printf("fopen() err.\n");
			goto End;
		}
	}

	fseek(fp,0L,SEEK_END);//把文件指针从0位置开始，移动到文件末尾
	length = ftell(fp);//获取文件的长度
	fseek(fp,0L,SEEK_SET);//重新移动到开头位置

	if(length > 1024*8)
	{
		ret = -3;
		printf("文件长度超标，不支持\n");
		goto End;
	}

	//读取数据
	while(!feof(fp))//读到文件尾
	{
		memset(lineBuf,0,sizeof(lineBuf));
		pTemp = fgets(lineBuf,MaxLine,fp);
		if(pTemp == NULL)
			break;
		//key关键字是否在本行
		pTemp = strstr(lineBuf,pItemName);
		if(pTemp == NULL)
		{
			strcat(filebuf,lineBuf);
			continue;
		}
		else
		{
			sprintf(lineBuf,"%s=%s\n",pItemName,pItemValue);
			strcat(filebuf,lineBuf);
			itag =1;
		}

	}
	//不存在则追加
	if(itag == 0)
	{
		fprintf(fp,"%s=%s\n",pItemName,pItemValue);
	}
	else//若key关键字存在，需要重新建立文件
	{

		if(fp != NULL)
		{
			fclose(fp);
		}
		fp = fopen(pFileName,"w+t");
		if(fp == NULL)
		{
			ret = -4;
			printf("fopen() err.\n");
			goto End;
		}
		fputs(filebuf,fp);//缓存区内容写入文件

	}
End:
	if(fp != NULL)
	{
		fclose(fp);
	}
	return ret;
}
