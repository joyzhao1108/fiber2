/***********************************************************
 * YOU SHOULD NOT TOUCH THIS FILE. IF YOU HAVE TO DO THAT, *
 * PLEASE LET ME KNOW.                                     *
 *                                           - LY          *
 * Copyright (C) 2015-2016 Li Yong                         *
 * All rights reserved.                                    *
 *                                                         *
 **********************************************************/

#ifndef DEVICE_MODULE_H
#define DEVICE_MODULE_H

int CameraInit ( unsigned int* SerialNumber );//USB3.0相机设备初始化函数
/*
 * 功能：USB3.0相机设备初始化函数
 * 参数:
 * SerialNumber - 用于返回相机的序列号
 * 返回值： 
 *	-1 没有找到相机设备，初始化失败
 *	0  初始化成功
 *	1  找到相机，但相机未能被系统识别为USB3.0设备，可能无法正常工作
 */



bool Capture ( unsigned int IntegrationTime );//图像拍摄函数
/*
 * 功能：图像拍摄函数
 * 参数:
 * IntegrationTime - 积分时间，范围为5ms ~ 10000ms
 * 返回值： 
 *	true  拍摄成功
 *    false 拍摄失败
 */



bool SaveImage ( char* Path, char* Name ); 
/*
 * 功能：图像存储函数
 * 参数:
 * Path - 存储图像的路径
 * Name - 存储图像的名称
 * 返回值： 
 *	true  存储图像成功
  *	false 存储图像失败
 */


bool LEDOpen ( bool open ); //LED灯开关函数
/*
 * 功能：LED灯开关函数
 * 参数:
 * open - LED灯开关控制，true为开灯，false为关灯
 * 返回值： 
 *	true  操作LED灯开关成功
  *	false 操作LED灯开关失败
 */

#endif /* DEVICE_MODULE_H */
