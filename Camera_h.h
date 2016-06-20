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

int CameraInit ( unsigned int* SerialNumber );//USB3.0����豸��ʼ������
/*
 * ���ܣ�USB3.0����豸��ʼ������
 * ����:
 * SerialNumber - ���ڷ�����������к�
 * ����ֵ�� 
 *	-1 û���ҵ�����豸����ʼ��ʧ��
 *	0  ��ʼ���ɹ�
 *	1  �ҵ�����������δ�ܱ�ϵͳʶ��ΪUSB3.0�豸�������޷���������
 */



bool Capture ( unsigned int IntegrationTime );//ͼ�����㺯��
/*
 * ���ܣ�ͼ�����㺯��
 * ����:
 * IntegrationTime - ����ʱ�䣬��ΧΪ5ms ~ 10000ms
 * ����ֵ�� 
 *	true  ����ɹ�
 *    false ����ʧ��
 */



bool SaveImage ( char* Path, char* Name ); 
/*
 * ���ܣ�ͼ��洢����
 * ����:
 * Path - �洢ͼ���·��
 * Name - �洢ͼ�������
 * ����ֵ�� 
 *	true  �洢ͼ��ɹ�
  *	false �洢ͼ��ʧ��
 */


bool LEDOpen ( bool open ); //LED�ƿ��غ���
/*
 * ���ܣ�LED�ƿ��غ���
 * ����:
 * open - LED�ƿ��ؿ��ƣ�trueΪ���ƣ�falseΪ�ص�
 * ����ֵ�� 
 *	true  ����LED�ƿ��سɹ�
  *	false ����LED�ƿ���ʧ��
 */

#endif /* DEVICE_MODULE_H */
