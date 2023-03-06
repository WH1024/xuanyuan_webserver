#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // 1.创建socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1) {
        perror("socket");
        exit(-1);
    }
    // 2.绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;  // 0.0.0.0
    saddr.sin_port = htons(9999);
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1) {
        perror("bind");
        exit(-1);
    }
    // 3.监听
    ret = listen(lfd, 8);
    if(ret == -1) {
        perror("listen");
        exit(-1);
    }
    // 4.接收客户端连接
    struct sockaddr_in clientaddr;
    int len = sizeof(clientaddr);
    int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &len);
    if(cfd == -1) {
        perror("accept");
        exit(-1);
    }
    // 输出客户端的信息
    int filesize;
    char clientIP[16];
    char buf[4096];
    char *p, *str;
    char *name = "./index.html";
    FILE *fp;
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);
    printf("client ip is %s, port is %d\n", clientIP, clientPort);
    // 5.通信
    char recvBuf[1024] = {0};
    while(1) {
        // 获取客户端的数据
        int num = read(cfd, recvBuf, sizeof(recvBuf));
        if(num == -1) {
            perror("read");
            exit(-1);
        } else if(num > 0) {
            printf("recv client data : %s\n", recvBuf);
        } else if(num == 0) {
            // 表示客户端断开连接
            printf("clinet closed...");
            break;
        }
        
        if((fp = fopen(name, "r")) == NULL){
            return 0;
        }
        fseek(fp, 0, SEEK_END);
        filesize = ftell(fp);
        str = (char *)malloc(filesize);
        str[0]=0;
        rewind(fp);
        while((fgets(buf, 4096, fp))!=NULL){
            strcat(str, buf);
        }
        fclose(fp);
        p = str;
        if(p != NULL){
            write(cfd, p, strlen(p));
        }
 
    }
    // 关闭文件描述符
    close(cfd);
    close(lfd);
    return 0;
}