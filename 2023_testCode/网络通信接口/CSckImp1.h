#pragma once

#include<stdlib.h>

//��ʼ��
void init_CSckImp1(void** handle);
//���ͽӿ�
void send_CSckImp1(void* handle, unsigned char* sendData, int sendLen);
//���սӿ�
void recv_CSckImp1(void* handle, unsigned char* recvData, int* recvLen);
//�ر�
void close_CSckImp1(void* handle);

