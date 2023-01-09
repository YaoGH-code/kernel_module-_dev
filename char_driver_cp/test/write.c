#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>

#define DATA_NUM 32

int main(int argc, char *argv[]){
	int fd,i;
	int r_len, w_len;
	fd_set fdset;
	char buf[DATA_NUM] = "Hello/world!";
	fd = open("/dev/ychar_dev", O_RDWR);
	if (fd==-1){
		perror("open file error.");
		return -1;
	}
	else {
		printf("open succeed");		
	}
	w_len = write(fd, buf, DATA_NUM);
	if(w_len==-1){
		perror("write error.\n");
		return -1;
	}
	printf("write lenght is: %d\n", w_len);
	close(fd);
	return 0;
}
