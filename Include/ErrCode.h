/*
* Copyright (c) 2005, 北京金橙子科技有限公司
* All rights reserved.
*
* 文件名称： Errcode.h
* 文件标识：
* 摘要：
*
* 版本：3.0
* 作    者：qy
* 完成日期：2010年3月
* 版本纪录: 创建文件
*/
#pragma once

#define ERR_SUCCESS       0   //成功 

#define ERR_SERIAL_READ    1   //读文件错误
#define ERR_SERIAL_WRITE   2   //写文件错误
#define ERR_SERIAL_HANDLE  3   //空文件句柄
#define ERR_SERIAL_UNKNOW  4   //未知文件
#define ERR_SERIAL_FORMAT  5   //文件格式错误
#define ERR_SERIAL_VERSION 6   //文件版本错误
#define ERR_SERIAL_CRC     7
#define ERR_SERIAL_CLIENTID     8//客户ID错误

//错误码定义

#define ERR_PLUG_NORMAL           11    //一般错误
#define ERR_PLUG_SKIP             12    //忽略错误
#define ERR_PLUG_MEMORY           13    //内存错误

#define ERR_PLUG_FILE_OPEN        14    //文件打开错误
#define ERR_PLUG_FILE_CREATE      15    //文件创建错误
#define ERR_PLUG_FILE_READ        16    //文件读错误
#define ERR_PLUG_FILE_WRITE       17    //文件写错误
#define ERR_PLUG_FILE_FORMAT      18    //文件格式错误
#define ERR_PLUG_FILE_VERSION     19    //不支持的文件版本

#define ERR_CFG_OPENFILE   51
#define ERR_CFG_READ       52
#define ERR_CFG_WRITE      53
#define ERR_CFG_IDENTIFY   54
#define ERR_CFG_VER        55
#define ERR_CFG_SIZE       56


#define ERR_UNKNOWN        100    //未知错误