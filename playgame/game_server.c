#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

void * handle_clnt(void * arg);
void send_msg(char * msg, int len);
void error_handling(char * msg);
void send_file(int sd,char* filename);
void recv_file(int sd,char* filenamd);
int clnt_cnt=0;
int clnt_socks[MAX_CLNT];
int cnt=0;
pthread_mutex_t mutx;

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	pthread_t t_id;
	if(argc!=2) {
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
						  
	pthread_mutex_init(&mutx, NULL);
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family=AF_INET; 
	serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_adr.sin_port=htons(atoi(argv[1]));
													
	if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
															
	while(1)
	{
		clnt_adr_sz=sizeof(clnt_adr);
		clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr,&clnt_adr_sz);
					
		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++]=clnt_sock;
		pthread_mutex_unlock(&mutx);
																												
		pthread_create(&t_id, NULL, handle_clnt, (void*)&clnt_sock);//\BD\BA\B7\B9\B5\E5 \BB\FD\BC\BA
		pthread_detach(t_id);
		printf("Connected client IP: %s \n", inet_ntoa(clnt_adr.sin_addr));
	}
	
	close(serv_sock);
	return 0;
}
	
void * handle_clnt(void * arg)
{
	int clnt_sock=*((int*)arg);
	int str_len=0, i;
	char *filemsg="file";	
	char msg[BUF_SIZE];

					
	while((str_len=read(clnt_sock, msg, sizeof(msg)))!=0){
		msg[str_len]=0;		
		if(strcmp(msg,"file_send")==0){	//file_sendŰ\BF\F6\B5带 \B9\DE\C0\B8\B8\E9 \C6\C4\C0\CF\C0\FC\BC\DB\C7ϱ\E2
			send_msg("te.png",-1);
		}
		else{			
			send_msg(msg, str_len);//\C0Ϲ\DD ä\C6ø޽\C3\C1\F6 \C0\FC\B4\DE
		}
}				
	pthread_mutex_lock(&mutx);
	for(i=0; i<clnt_cnt; i++)  //\BF\AC\B0\E1\C1\BE\B7\E1\B5\C8 Ŭ\B6\F3\C0̾\F0Ʈ \C1\A6\B0\C5
	{
		if(clnt_sock==clnt_socks[i])
		{
			while(i++<clnt_cnt-1)
				clnt_socks[i]=clnt_socks[i+1];
			break;
		}
	}
	clnt_cnt--;
	pthread_mutex_unlock(&mutx);
	close(clnt_sock);
	return NULL;
}
void send_msg(char * msg, int len)   
{
	int i;
	char sending[20]="file_sending";
	pthread_mutex_lock(&mutx);
	
	if(len==-1){
		
		for(i=0;i<clnt_cnt;i++){	
		write(clnt_socks[i],sending,strlen(sending));//Ŭ\B6\F3\C0̾\F0Ʈ\BF\A1\B0\D4 \C6\C4\C0Ϲ\DE\C0\BB \C1غ\F1\C7϶\F3\B0\ED \C0\FC\BC\DB
		sleep(1);//\BB\F3\B4\EB\B9\E6\C0\CC \C0о\EE\B5\E9\C0\CF \BDð\A3 \C1ֱ\E2
		send_file(clnt_socks[i],msg);//\C6\C4\C0\CF \BA\B8\B3\BB\B1\E2 \C7Լ\F6
		}
	}
	else{		
		for(i=0; i<clnt_cnt; i++){		
			write(clnt_socks[i], msg, len);	//\B0\A2 \BC\D2\C4Ͽ\A1 \BE\B2\B1\E2
		}
	}
	pthread_mutex_unlock(&mutx);
}
void recv_file(int sd,char* filename){

	int filesize=0;
	int bufsize;
	int nbyte;
	char buf[BUF_SIZE];
	FILE *file;
	
	file=fopen(filename,"wb");
	

	bufsize=BUF_SIZE;
	while(filesize!=0){
		if(filesize<BUF_SIZE)//\B3\B2\C0\BA \B5\A5\C0\CC\C5\CD \BB\E7\C0\CC\C1 \B9\F6\C6ۻ\E7\C0\CC\C1\EE \BA\B8\B4\D9 \C0\DB\C0\BB\B0\E6\BF\EC \B3\B2\BE\C6\C0ִ\C2 \BB\E7\C0\CC\C1\EE\C0\C7 \B5\A5\C0\CC\C5͸\B8 \C0б\E2\C0\A7\C7\D1 \C1\B6\B0ǹ\AE
			bufsize=filesize;
		nbyte=recv(sd,buf,bufsize,0);//\B9\F6\C6ۻ\E7\C0\CC\C1ŭ \B5\A5\C0\CC\C5\CD \BC\F6\BD\C5
		filesize=filesize-nbyte;//\C3\D1 \B5\A5\C0\CC\C5Ϳ\A1\BC\AD \B9\DE\C0\BA \B5\A5\C0\CC\C5\CD \BB\E7\C0\CC\C1 \BB\A9\B1\E2
		fwrite(buf,sizeof(char),nbyte,file);//\C6\C4\C0Ͽ\A1 \B5\A5\C0\CC\C5\CD \BE\B2\B1\E2
		nbyte=0;
	}
	fclose(file);
}
void send_file(int sd,char* filename){

	int fsize=0;
	int nsize=0;
	int fpsize=0;
	int BUFSIZE=40;	
	char buf[BUF_SIZE];	
	FILE *file=fopen(filename,"rb");
	fseek(file,0,SEEK_END);
	fsize=ftell(file);	//\C6\C4\C0\CF \BB\E7\C0\CC\C1\EE \C0\FA\C0\E5
	fseek(file,0,SEEK_SET);
	
	
	send(sd,&fsize,sizeof(fsize),0); //\C6\C4\C0\CF ũ\B1\E2 \C0\FC\BC\DB	

	
	while(nsize!=fsize){
		
		fpsize=fread(buf,1,BUFSIZE,file);//\B9\F6\C6\DB \BB\E7\C0\CC\C1ŭ \C6\C4\C0Ͽ\A1\BC\AD \C0б\E2
		nsize=nsize+fpsize;	//\C3\D1 \C0о\EE\B5\E9\C0\CE \BB\E7\C0\CC\C1\EE \C0\FA\C0\E5
		send(sd,buf,fpsize,0);//\C0о\EE\B5\E9\C0\CE \B5\A5\C0\CC\C5\CD \C0\FC\BC\DB
		sleep(0.5);	//\BB\F3\B4밡 \C0\D0\C0\BB \BDð\A3 \C1ֱ\E2
	}
	printf("done\n");//\BFϷ\E1 \B8޽\C3\C1\F6
	
	fclose(file);
}
void error_handling(char * msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}
