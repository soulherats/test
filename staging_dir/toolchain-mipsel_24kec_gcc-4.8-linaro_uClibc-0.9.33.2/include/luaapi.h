#ifndef _LUAAPI_H_
#define _LUAAPI_H_

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <luaconf.h>
#include <dlfcn.h>
#include <pthread.h>
#include <json/json.h>

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#include <asm/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/netlink.h>


/*
* luaapi 的返回值
*/
#define RES_OK		0
#define RES_FAILURE	-1

#define MOD_UNLOAD 0
#define MOD_LOAD 1

typedef enum PRINT_LEVEL_S
{
	ERROR_L = 1,
	INFO_L,	
	MIN_L	
}PRINT_LEVEL_T;

#define lua_isstring(L,n)	(lua_type(L, (n)) == LUA_TSTRING)

#define debugPrint(level,x) if(gDebug>=(level)) printf x;

/*最大的module name长度*/
#define MAX_MODULE_NAME 32

typedef enum EModule_e
{
	DEMON_MODULE				= 1,
	HI_CHANNEL_USER_MODULE		= 2,
	MAX_MODULE					= 100
}EModule_t;

/*lua 注册函数的类型*/
typedef int (*LUAFUN_T)(lua_State *L);
typedef LUAFUN_T* PLUAFUN_T;

typedef void* (*FUN_T)(void*);
typedef FUN_T* PFUN_T;

/*
*  定义模块
*  用于传递给regModule 
*/
typedef struct MODULE_S
{
	EModule_t eModID;
	char cModName[MAX_MODULE_NAME];
	FUN_T pFun;
	int	iLoad;
	void* p;
}MODULE_T;

typedef MODULE_T* PMODULE_T;

extern int newTab(lua_State *L);
extern int setStrToTab (lua_State *L, const char *key, const char* value) ;
extern int setTabToTab (lua_State *L, const char *tabname) ;
extern int setIntToTab (lua_State *L, const char *key, int value);
extern int setBoolToTab (lua_State *L, const char *key, int value);
extern int getStrFromTab (lua_State *L, const char *key, char* pValue, int len);
extern int getIntFromTab (lua_State *L, const char *key, int* pValue);
extern int getTabFromTab (lua_State *L, const char *tabname);
extern int getTabStrFromTab (lua_State *L, const char *tabname, const char *key, char* pValue, int len);
extern int getIntByIndex(lua_State *L, int* pValue, int index);
extern int newTabRes(lua_State *L, int value);
extern int loadModule(const char* cModName);
extern int regModule(PMODULE_T pMod);
extern int getModMethodById(EModule_t eModID, PFUN_T ppFun);
extern int getModMethodByName(const char* cModName, PFUN_T ppFun);
extern int gDebug;

#endif
