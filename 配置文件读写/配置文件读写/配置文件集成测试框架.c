#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cfg_op.h"

#define CFGNAME "c:/mycfg.ini"

void mymenu()
{
	printf("========================================\n");
	printf("1 测试写配置文件\n");
	printf("2 测试读配置文件\n");
	printf("0 退出\n");
	printf("========================================\n");

}
//int GetCfgItem(char *pFileName/*in*/,char *pKey/*in*/,char *pValue/*in out*/,int *pValueLen/*out*/);
//int WriteCfgItem(char *pFileName/*in*/,char *pItemName/*in*/,char *pItemValue/*in out*/,int *ItemValueLen/*out*/);
//写测试案例
//获取配置文件
int TGetCfg()
{
	int		ret = 0;
	char		Name[1024] = {0};
	char		value[1024] = {0};

	printf("\n请键入key:");
	scanf("%s",Name);
	

	ret = GetCfgItem(CFGNAME,Name,value);
	if(ret !=0)
	{
	printf("func WriteCfgItem err: %d",ret);
	}
	printf("你的输入是：%s = %s\n",Name,value);
	return ret;

}
//写配置文件
int TWriteCfg()
{
	int ret = 0;
	char Name[1024] = {0};
	char value[1024] = {0};

	printf("\n请键入key:");
	scanf("%s",Name);
	
	printf("\n请键入value:");
	scanf("%s",value);

	ret = WriteCfgItem(CFGNAME,Name,value);
	if(ret !=0)
	{
		printf("func WriteCfgItem err: %d",ret);
	}
	return ret;

}
void main()
{
	int choice;
	for(;;)
	{
		//显示一个菜单

		mymenu();
		scanf("%d",&choice);
		switch(choice)
		{
		case 1://写配置项
			TWriteCfg();
			break;
		case 2://读配置项
			TGetCfg();
			break;
		case 0:
			exit(0);
		default:
			exit(0);

		}
	}
	printf("hello...\n");
	system("pause");
	return;
}