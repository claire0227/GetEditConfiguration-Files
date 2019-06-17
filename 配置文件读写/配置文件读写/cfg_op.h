#ifndef __CFG_OP_H__
#define __CFG_OP_H__

#ifdef  __cplusplus
extern "C" 
#endif
//获取配置项
int GetCfgItem(char *pFileName/*in*/,char *pKey/*in*/,char *pValue/*in out*/);
//写配置项
int WriteCfgItem(char *pFileName/*in*/,char *pItemName/*in*/,char *pItemValue/*in out*/);

#ifdef  __cplusplus

#endif

#endif

