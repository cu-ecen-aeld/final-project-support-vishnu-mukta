// Tester code for assignment 5 part 1
// File:	aesdsocket.c
// Author:	Mukta Darekar
// Reference: https://docs.oracle.com/cd/E19620-01/805-4041/sockets-47146/index.html
//			  https://github.com/stockrt/queue.h/blob/master/sample.c
//			  https://github.com/cu-ecen-aeld/aesd-lectures/blob/master/lecture9/timer_thread.c

// Pre-processor directives
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <syslog.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/queue.h>
#include <pthread.h>
#include <sys/time.h>

// macro definition 
#define TOTAL_MSG	3	
#define ERROR		1
#define SUCCESS		0
#define MYPORT		9000
#define DEF_FILEPATH	"/var/socketdata"
#define IMG_FILEPATH	"/var/test.jpg"
#define BUFFER_LEN	200

typedef struct
{
    int fd;
    int acceptedfd;
    bool thread_complete_success;
    bool complete_status_flag;

}func_data;


int sockfd;
int exit_on_signal=0;


//Function:	static void signal_handler(int signo)
//Inputs:	signo - Signal number
static void signal_handler(int signo)
{
	if(signo == SIGINT || signo==SIGTERM) 
	{			
		shutdown(sockfd, SHUT_RDWR);

		exit_on_signal = true;
	}
}

uint8_t cmd_index=0;

char cmd_table[3][12] = { "capture\n", "get bytes\n", "send image\n"};
char cmd_size[3] = { 7, 9, 10};

char *verifysocket(char *buff, int searchfd, int *send_bytes)
{
	char *str = (char*)malloc(12);
	int bytes=0, ret=0;
	int img_fd;
	
	
    syslog(LOG_DEBUG, "buff: %s\n", buff);
    syslog(LOG_DEBUG, "cmd_index: %d\n", cmd_index);
	
	if((strncasecmp(buff, &cmd_table[cmd_index][0], cmd_size[cmd_index])) == 0)
	{
    	syslog(LOG_DEBUG, "compare successful\n");
		switch(cmd_index)
		{
			case 0:
				while(1)
				{
					sleep(1);
					lseek(searchfd, 0, SEEK_SET);
    				read(searchfd, &str[0], 4); 
					syslog(LOG_INFO, "str:'%s'\n", str);
    				
    				if((strncasecmp(str, "done", 4)) == 0) 
    				{
						syslog(LOG_INFO, "done\n");
    					str[4] = '\n';
    					cmd_index=1;
						*send_bytes = 5;
    					break;
    				}
				}
			break;
			
			case 1:
				//open jpg file
				img_fd = open(IMG_FILEPATH, O_RDONLY, 0764);
				if (img_fd == -1)	
				{//if error
					syslog(LOG_ERR, "can't open or create file '%s'\n", IMG_FILEPATH);
					exit_on_signal = true;
					cmd_index=0;
					break;
				}
				bytes = lseek(img_fd, 0, SEEK_END);
    			syslog(LOG_DEBUG, "bytes: %d\n", bytes);
				str[0] = (char)((bytes & 0xFF000000) >> 24);
				str[1] = (char)((bytes & 0x00FF0000) >> 16);
				str[2] = (char)((bytes & 0x0000FF00) >> 8);
				str[3] = (char)(bytes & 0x000000FF);
    			syslog(LOG_DEBUG, "str[0]: %x\n", str[0]);
    			syslog(LOG_DEBUG, "str[1]: %x\n", str[1]);
    			syslog(LOG_DEBUG, "str[2]: %x\n", str[2]);
    			syslog(LOG_DEBUG, "str[3]: %x\n", str[3]);
				cmd_index=0;
				*send_bytes = 4;	
			break;
			
			case 2:
				//open jpg file
				img_fd = open(IMG_FILEPATH, O_RDONLY, 0764);
				if (img_fd == -1)	
				{//if error
					syslog(LOG_ERR, "can't open or create file '%s'\n", IMG_FILEPATH);
					exit_on_signal = true;
					cmd_index=0;
					break;
				}
				bytes = lseek(img_fd, 0, SEEK_END);
				
    			str = (char*)malloc(bytes+1);
    			
    			ret = read(img_fd, &str[0], bytes); 
    			if(ret != bytes)
    			{
					syslog(LOG_ERR, "unable to read image properly");
					cmd_index=0;
					break;
    			}
    			str[bytes] = '\n';
    			cmd_index=0;    
    					
				*send_bytes = bytes+1;			
			break;
			
			default:
    					cmd_index=0;
			break;
		}
	}
	return str;
}


void packetRWthread(func_data *func_args)
{
	bool status = true;

    int req_size=0;
    int size = BUFFER_LEN;    
    char *rebuffer = NULL;
    char *buffer = (char*)malloc(sizeof(char)*BUFFER_LEN);
	int nbytes = 0;
	ssize_t nr = 0;

	sigset_t mask;
    //Create signal set
    if (sigemptyset(&mask) == -1) 
	{
        syslog(LOG_ERR, "creating empty signal set failed");
		status = false;
    }
	//Add signal SIGINT into created empty set
    if (sigaddset(&mask, SIGINT) == -1) 
	{
        syslog(LOG_ERR, "Adding SIGINT failed");
		status = false;
    }
	//Add signal SIGTERM into created empty set
    if (sigaddset(&mask, SIGTERM) == -1) 
	{
        syslog(LOG_ERR, "Adding SIGTERM failed");
		status = false;
    } 
       
    
    while(1)
    {
    	nbytes = recv(func_args->acceptedfd, buffer+req_size, BUFFER_LEN, 0);
    	if(nbytes == -1)
    	{
		    syslog(LOG_ERR,"receive failed");
			status = false;
			break;
        }
        if (nbytes ==0)
        	break;
        
        req_size = req_size + nbytes;
        	
        if(size < (req_size+1))
        {
        	size += BUFFER_LEN;
        	rebuffer = realloc(buffer,sizeof(char)*size);
        	if(rebuffer == NULL)
        	{
		        syslog(LOG_ERR,"realloc failed");
				status = false;
				break;
		    }
		    buffer = rebuffer;
        }
       	
       	if(strchr(buffer,'\n') != NULL) 
       		break;    	
    }
    
    syslog(LOG_DEBUG, "Recv: %s\n", buffer);
    
    // Block signals to avoid partial write
    if (sigprocmask(SIG_BLOCK,&mask,NULL) == -1)
    {
        syslog(LOG_ERR,"sigprocmask failed");
		status = false;
    }	
	nr = write(func_args->fd, buffer, req_size);
	if (nr == -1)	
	{//if error
		syslog(LOG_ERR, "can't write received string in file '%s'", DEF_FILEPATH);
		status = false;
	}
    syslog(LOG_DEBUG, "nr: %ld\n", nr);
    // Block signals to avoid partial write
    if (sigprocmask(SIG_UNBLOCK,&mask,NULL) == -1)
    {
        syslog(LOG_ERR,"sigprocmask failed");
		status = false;
    }	
    
    lseek(func_args->fd, 0, SEEK_SET);
    
    req_size = 0;
    
    buffer = verifysocket(buffer, func_args->fd, &req_size);
    
    syslog(LOG_DEBUG, "req_size: %d\n", req_size);
    syslog(LOG_DEBUG, "buffer: %s\n", buffer);
    
	nbytes = send(func_args->acceptedfd, buffer, req_size, 0);
	if(nbytes != req_size)
	{
		syslog(LOG_ERR, "send failed");
		status = false;
	}
    
    if (status == true)
    {
		syslog(LOG_DEBUG, "Successful");
    }

    //status true
	func_args->thread_complete_success = status;
    func_args->complete_status_flag = true;

    free(buffer);
    free(rebuffer);
}


int main(int argc, char* argv[])
{

    openlog(NULL, LOG_CONS, LOG_USER);

	struct sockaddr_in saddr;
	bool exit_on_error = false;
	int opt=1;
	int acceptedfd;
	int fd; 
    socklen_t len;
    int ret = 0;
    func_data funcdata;
            
	syslog(LOG_INFO, "aesdsocket code started\n");
	
	// check if deamon needs to be started
    if ((argc == 2) && (strcmp("-d", argv[1])==0)) 
	{
		// start deamon
        pid_t pid = fork();
        if (pid == -1) 
		{
            syslog(LOG_ERR, "failed to fork");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
		{
            exit(EXIT_SUCCESS);
        }

		syslog(LOG_INFO, "fork successful\n");
	
        pid_t sid = setsid();		
		if (sid == -1) 
		{
			syslog(LOG_ERR, "failed to setsid");
			exit(EXIT_FAILURE);
		}
		umask(0);
		syslog(LOG_INFO, "SID: %d\n", sid);

		if (chdir("/") == -1) 
		{
			syslog(LOG_ERR, "failed to change dir");
			exit(EXIT_FAILURE);
		}
		syslog(LOG_INFO, "chdir successful\n");

		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		
		syslog(LOG_INFO, "daemon created\n");
    }
    
	// Set signal handler for SIGINT
	if(signal(SIGINT, signal_handler) == SIG_ERR)
	{
		syslog(LOG_ERR, "Cannot handle SIGINT!\n");
		exit_on_error = true;
		goto EXITING;
	}

	// Set signal handler for SIGTERM
	if(signal(SIGTERM, signal_handler) == SIG_ERR)
	{
		syslog(LOG_ERR, "Cannot handle SIGTERM!\n");
		exit_on_error = true;
		goto EXITING;
	}
    
	//create socket
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		syslog(LOG_ERR, "socket creation failed\n");
		exit_on_error = true;
		goto EXITING;
	}
	syslog(LOG_INFO, "socket created\n");
	
	//reuse socket
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) == -1)
	{
		syslog(LOG_ERR, "setsocketopt failed\n");
		exit_on_error = true;
		goto EXITING;
	}
	syslog(LOG_INFO, "socket created\n");
	saddr.sin_family = PF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(MYPORT);

	//bind socket at port number 9000
	ret = bind(sockfd, (struct sockaddr *) &saddr, sizeof(struct sockaddr_in));
	if (ret == -1)
	{
		syslog(LOG_ERR, "socket binding failed\n");
		exit_on_error = true;
		goto EXITING;
	}
	syslog(LOG_INFO, "bind successful\n");
    
    //start listening at port 9000
	ret = listen(sockfd, 10);
	if (ret == -1)
	{
		syslog(LOG_ERR, "socket listening failed\n");
		exit_on_error = true;
		goto EXITING;
	}
	syslog(LOG_INFO, "listening\n");

	//create or open file to store received packets
	fd = open(DEF_FILEPATH, O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0764);
	if (fd == -1)	
	{//if error
		syslog(LOG_ERR, "can't open or create file '%s'\n", DEF_FILEPATH);
		exit_on_error = true;
		goto EXITING;
	}
    len = sizeof(struct sockaddr);
		
	//accept connection
	acceptedfd = accept(sockfd, (struct sockaddr *) &saddr, &len);
			
	if (acceptedfd == -1)
	{
		syslog(LOG_ERR, "socket accepting failed\n");
		exit_on_error = true;
		goto EXITING;
	}
	syslog(LOG_DEBUG, "Accepted connection from '%s'\n", inet_ntoa((struct in_addr)saddr.sin_addr));
		
    while(exit_on_signal==0) 
    {		
		funcdata.fd = fd;
		funcdata.acceptedfd = acceptedfd;
		funcdata.thread_complete_success = true;
		funcdata.complete_status_flag = true;
		
		packetRWthread(&funcdata);
		
		if(exit_on_signal || exit_on_error || funcdata.thread_complete_success==false)
			break;
	}

	syslog(LOG_DEBUG, "Closing connection from '%s'\n", inet_ntoa((struct in_addr)saddr.sin_addr));
    close(acceptedfd);

EXITING:

	if (exit_on_error && exit_on_signal==false)
		syslog(LOG_DEBUG, "exiting on failure\n");
	else
		syslog(LOG_DEBUG, "exiting on signal\n");

	//if(acceptedfd)
	//	close(acceptedfd);

	if(sockfd)
		close(sockfd);

	if(fd)	
	{
		close(fd);
		remove(DEF_FILEPATH);
	}

	closelog();
	
	if (exit_on_error && exit_on_signal==false)
		return 1;
	else
		return 0;
		
}





