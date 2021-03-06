// Project: AESD final project: Image transfer using socket communication
// File:	aesdsocket.c
// Author:	Mukta Darekar
// Reference: https://docs.oracle.com/cd/E19620-01/805-4041/sockets-47146/index.html
// Referred from: Tester code for assignment 5 part 1

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
#include <sys/wait.h>
#include <stdarg.h>

// macro definition 
#define TOTAL_MSG			3	
#define ERROR				1
#define SUCCESS				0
#define MYPORT				9000
#define DEF_FILEPATH		"/var/socketdata"
#define PGM_IMG_FILEPATH	"/var/test.pgm"
#define PPM_IMG_FILEPATH	"/var/test.ppm"
#define JPG_IMG_FILEPATH	"/var/test.jpg"
#define BUFFER_LEN			200
#define IMAGE_BUFFER_LEN	((320*240*3)+100)

// Commands for different image type capture
#define CAPTURE_RGB_JPG		0
#define CAPTURE_EDGE_JPG	1
#define CAPTURE_JPG			2
#define CAPTURE_RGB			3
#define CAPTURE_EDGE		4
#define CAPTURE				5

// Global variables
typedef struct
{
	int fd;
	int acceptedfd;
	bool complete_status_flag;

}func_data;

int sockfd;

int exit_on_signal=0;

uint8_t cmd_index=0;

char str[IMAGE_BUFFER_LEN] = {0};

//Commands
char img_table[6][18] = { "capture rgb jpg\n", "capture edge jpg\n", "capture jpg\n", "capture rgb\n", "capture edge\n", "capture\n"};
char img_size[6] = { 15, 16, 11, 11, 12, 7};
char cmd_table[3][12] = { "capture\n", "get bytes\n", "send image\n"};
char cmd_size[3] = { 7, 9, 10};

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

//Function:	bool do_exec(int image)
//Inputs:	image - image type to capture
//Outputs:	returns 1-success 0-failure
bool do_exec(int image)
{
	int status;
	pid_t pid, pid_comp;

	//capture image
	pid = fork();

	if (pid == -1)
	{
		return false;
	}	
	else if (pid == 0) 
	{
		if(image == CAPTURE_RGB_JPG || image == CAPTURE_RGB)
			execl("/usr/bin/capture", "/usr/bin/capture", "-p", (char *)NULL);
		else if(image == CAPTURE_EDGE_JPG || image == CAPTURE_EDGE)
			execl("/usr/bin/capture", "/usr/bin/capture", "-e", (char *)NULL);
		else
			execl("/usr/bin/capture", "/usr/bin/capture", (char *)NULL);
		perror("execl");
		exit (-1);
		return false; 
	}
	else if (pid > 0)
	{
		if (waitpid (pid, &status, 0) == -1)
			return false;

		else if (WIFEXITED (status))
		{
			if (WEXITSTATUS (status) != 0)
				return false;
		}
	}
	
	//compress image
	pid_comp = fork();

	if (pid_comp == -1)
	{
		return false;
	}	
	else if (pid_comp == 0) 
	{
		if(image == CAPTURE_RGB_JPG || image == CAPTURE_RGB)
			execl("/usr/bin/mogrify", "/usr/bin/mogrify", "-format", "jpg", "/var/test.ppm", (char *)NULL);
		else
			execl("/usr/bin/mogrify", "/usr/bin/mogrify", "-format", "jpg", "/var/test.pgm", (char *)NULL);
		perror("execl");
		exit (-1);
		return false; 
	}
	else if (pid_comp > 0)
	{
		if (waitpid (pid_comp, &status, 0) == -1)
			return false;

		else if (WIFEXITED (status))
		{
			if (WEXITSTATUS (status) != 0)
				return false;
		}
	}
	return true;
}

//Function:	void verifysocket(char *buff, int searchfd, int *send_bytes)
//Inputs:	*buff - socket buffer passed to verify commands received
//			searchfd - fd of file in which to search commands - removed functionality
//          *send_bytes - returns numbers of bytes to be sent
void verifysocket(char *buff, int searchfd, int *send_bytes)
{
	int bytes=0, ret=0;
	int img_fd;
	static int image_type=0;
	int i=0;

	syslog(LOG_DEBUG, "buff: %s\n", buff);
	syslog(LOG_DEBUG, "cmd_index: %d\n", cmd_index);

	memset(&str[0], 0, IMAGE_BUFFER_LEN);
	syslog(LOG_DEBUG, "memset");

	if((strncasecmp(&buff[0], &cmd_table[cmd_index][0], cmd_size[cmd_index])) == 0)
	{
		syslog(LOG_DEBUG, "compare successful\n");
		switch(cmd_index)
		{
			case 0:	//capture and compress image
				for (i=0; i<6; i++)
				{
					if((strncasecmp(buff, &img_table[i][0], img_size[i])) == 0)
					{
						image_type = i;
						break;
					}
				}
					
				if(do_exec(image_type) == true)
				{
					str[0] = 'd';
					str[1] = 'o';
					str[2] = 'n';
					str[3] = 'e';
					str[4] = '\n';
					syslog(LOG_INFO, "done\n");
					cmd_index=1;
					*send_bytes = 5;
				}
			break;
			
			case 1: //Send size of image file in bytes
				//open image file
				if(image_type == CAPTURE_RGB)
					img_fd = open(PPM_IMG_FILEPATH, O_RDONLY, 0764);
				else if(image_type == CAPTURE_RGB_JPG || image_type == CAPTURE_EDGE_JPG || image_type == CAPTURE_JPG)			
					img_fd = open(JPG_IMG_FILEPATH, O_RDONLY, 0764);
				else			
					img_fd = open(PGM_IMG_FILEPATH, O_RDONLY, 0764);
				
				if (img_fd == -1)	
				{//if error
					syslog(LOG_ERR, "can't open or create image file \n");
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
				syslog(LOG_DEBUG, "str[0]: 0x%x\n", str[0]);
				syslog(LOG_DEBUG, "str[1]: 0x%x\n", str[1]);
				syslog(LOG_DEBUG, "str[2]: 0x%x\n", str[2]);
				syslog(LOG_DEBUG, "str[3]: 0x%x\n", str[3]);
				cmd_index=2;
				*send_bytes = 4;	
				close(img_fd);
			break;
			
			case 2: //Send image data
				//open image file
				if(image_type == CAPTURE_RGB)
					img_fd = open(PPM_IMG_FILEPATH, O_RDONLY, 0764);
				else if(image_type == CAPTURE_RGB_JPG || image_type == CAPTURE_EDGE_JPG || image_type == CAPTURE_JPG)			
					img_fd = open(JPG_IMG_FILEPATH, O_RDONLY, 0764);
				else			
					img_fd = open(PGM_IMG_FILEPATH, O_RDONLY, 0764);

				if (img_fd == -1)	
				{//if error
					syslog(LOG_ERR, "can't open or create image file \n");
					exit_on_signal = true;
					cmd_index=0;
					break;
				}
				bytes = lseek(img_fd, 0, SEEK_END);
				syslog(LOG_DEBUG, "image size: 0x%x\n", bytes);

				lseek(img_fd, 0, SEEK_SET);

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
				close(img_fd);		
			break;
			
			default:
				cmd_index=0;
			break;
		}
	}
}

//Function:	void packetReadWrite(func_data *func_args)
//Inputs:	*func_args - function arguments structure
void packetReadWrite(func_data *func_args)
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
    
	verifysocket(buffer, func_args->fd, &req_size);

	syslog(LOG_DEBUG, "req_size: %d\n", req_size);
	syslog(LOG_DEBUG, "str buffer: %s\n", &str[0]);

	nbytes = send(func_args->acceptedfd, &str[0], req_size, 0);
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
	func_args->complete_status_flag = status;

	free(buffer);
	free(rebuffer);
}

//Function:	int main(int argc, char* argv[])
//Inputs:	argc - number of arguments, argv[] - arguments
int main(int argc, char* argv[])
{
	openlog(NULL, LOG_CONS, LOG_USER);

	struct sockaddr_in saddr;
	bool exit_on_error = false;
	int opt=1;
	int acceptedfd;
	int fd; 
	socklen_t len;
	int ret = 0, i = 0;
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
	
	//stay in loop till any signal received	
	while(exit_on_signal==0) 
	{
		if(exit_on_signal || exit_on_error)
			break;

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

		funcdata.fd = fd;
		funcdata.acceptedfd = acceptedfd;
		funcdata.complete_status_flag = true;

		//Stay in loop to complete one whole image transfer
		for(i=0; i<3; i++)
		{
			packetReadWrite(&funcdata);

			if(exit_on_signal || exit_on_error)
				break;
		}

		syslog(LOG_DEBUG, "Closing connection from '%s'\n", inet_ntoa((struct in_addr)saddr.sin_addr));
		close(acceptedfd);
		//close connection and then go on to accept again for every new image transfer
	}

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





