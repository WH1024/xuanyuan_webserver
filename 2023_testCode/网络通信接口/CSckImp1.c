#include"CSckImp1.h"

struct Info {
	char data[1024];
	int len;
};

//��ʼ��
void init_CSocketProtocol(void** handle) {

	if (NULL == handle) {
		return;
	}

	struct Info* info = malloc(sizeof(struct Info));
	memset(info, 0, sizeof(struct Info));

	*handle = info;
}

//���ͽӿ�
void send_CSocketProtocol(void* handle, unsigned char* sendData, int sendLen) {
	if (NULL == handle) {
		return;
	}
	if (NULL == sendData) {
		return;
	}
	struct Info* info = (struct Info*)handle;
	
	strcpy(info->data, sendData, sendLen);
	info->len = sendLen;

}

//���սӿ�
void recv_CSocketProtocol(void* handle, unsigned char* recvData, int* recvLen) {
	if (NULL == handle) {
		return;
	}
	if (NULL == recvData) {
		return;
	}
	if (NULL == recvLen) {
		return;
	}

	struct Info* info = (struct Info*)handle;
	strncpy(recvData, info->data, info->len);
	*recvLen = info->len;
}

//�ر�
void close_CSocketProtocol(void* handle) {
	if (NULL == handle) {
		return;
	}
	free(handle);
	handle = NULL;
}