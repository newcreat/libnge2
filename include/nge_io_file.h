﻿#ifndef IO_FILE_H_
#define IO_FILE_H_

#include "nge_common.h"

/* PSP与win32文件读写统一接口 */
#ifdef _PSP
#include <pspiofilemgr.h>
#define IO_RDONLY PSP_O_RDONLY
#define IO_WRONLY PSP_O_RDWR
#define IO_APPEND PSP_O_APPEND

#define IO_SEEK_CUR PSP_SEEK_CUR
#define IO_SEEK_END PSP_SEEK_END
#define IO_SEEK_SET PSP_SEEK_SET
#else
#define IO_RDONLY 0
#define IO_WRONLY 1
#define IO_APPEND 2

#define IO_SEEK_CUR SEEK_CUR
#define IO_SEEK_END SEEK_END
#define IO_SEEK_SET SEEK_SET
#endif

#ifdef __cplusplus
extern "C"{
#endif

/**
 *载入打包文件
 *@param const char*,文件名
 *@param int, 一些选项（可选）
 *@return int, 返回包文件句柄，为0时为失败
 */
int io_load_package(const char* fname, int option);

/**
 *切换io打开的模式，使用io_load_package得到的包句柄来切换io_fopen等其他api操作的对象，
  用0作为参数时切换回正常的文件系统。
 *@param int, 包句柄
 *@return int, 为0时为失败
 */
int io_change_package(int pack_handle);

/**
 *打开文件
 *@param const char*,文件名
 *@param int,打开标志(IO_RDONLY,IO_WRONLY,IO_APPEND的一种)
 *@return int,文件句柄,读写均用此文件句柄进行操作
 */
int io_fopen(const char* fname,int flag);

/**
 *读文件,与fread类似
 *@param void*,保存读取数据的缓存
 *@param int,读取个数
 *@param int,读取大小
 *@param int,文件句柄
 *@return,实际读取数量
 */
int io_fread(void* buffer,int count,int size,int handle);

/**
 *写文件,与fwrite类似
 *@param void*,待写数据的缓存
 *@param int,待写块个数
 *@param int,待写块大小
 *@param int,文件句柄
 *@return,实际写入数量
 */
int io_fwrite(void* buffer,int count,int size,int handle);

/**
 *文件指针偏移设置,与fseek类似
 *@param int,文件句柄
 *@param int offset,偏移量
 *@param int flag,seek标志,IO_SEEK_CUR,IO_SEEK_END,IO_SEEK_SET
 *@return int,返回0成功,-1失败
 */
int io_fseek(int handle,int offset,int flag);

/**
 *获得当前文件偏移值
 *@param int handle,文件句柄
 *@return int,文件偏移值
 */
int io_ftell(int handle);

/**
 *关闭文件
 *@param int handle,文件句柄
 *@return int,-1失败
 */
int io_fclose(int handle);

/**
 *文件大小
 *@param int handle,文件句柄
 *@return int,文件大小
 */
int io_fsize(int handle);

#ifdef __cplusplus
}
#endif

#endif
