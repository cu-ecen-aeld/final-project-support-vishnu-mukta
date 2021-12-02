/*
 * File name: display_image.c - Receives image from socket and displays on LCD
 * Author: Vishnu Dodballapur
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <signal.h>
#include <syslog.h>
#include <string.h>
#include "gpio.h"
#include "lcd.h"

#define PGM_BYTES_CHUNK     (256)
#define PGM_SIZE            (76800)
#define PPM_SIZE			(76800 * 3)

uint8_t pgm_buff[PGM_BYTES_CHUNK] = { 0 };


int main(int argc, char* argv[]) {
    
    int socket_fd, test_pgm_fd;
    struct addrinfo hints;
    struct addrinfo* res;
    int send_bytes = 0, recv_bytes = 0, pgm_write_bytes;
    uint8_t recv_buff[15] = { 0 };
    uint8_t stdin_buff[20] = { 0 };
    uint8_t stdin_buff_len = 0;
    uint32_t pgm_len = 0;
    //uint8_t* pgm_buff;
    uint32_t pgm_bytes_recvd = 0, pgm_bytes_to_recv = 0;
    //pid_t pid;
    //int status, exit_status;
    uint8_t color_buff[3];
    int i, j;
    int image_type=0;

    if (argc != 2) {
        printf("Incorrect number of arguments.\nUsage:\ndisplay_image [ server ip address ] \n");
        exit(-1);
    }

    openlog(NULL, 0, LOG_USER);
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], "9000", &hints, &res) != 0 ) {
        syslog(LOG_ERR, "getaddrinfo");
        perror("getaddrinfo");
        exit(-1);
    }


    //Init LCD module
    if (LCD_Init()) {
        printf("Error in LCD_Init()\n");
        return 1;
    }

    //Init LCD module
    if (LCD_SetOrientation()) {
        printf("Error in LCD_SendOrientation()\n");
        return 1;
    }

    //Init LCD module
    if (LCD_SetBorders(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1)) {
        printf("Error in LCD_SetBorders()\n");
        return 1;
    }

    while (1) {
        printf("Enter command from below:\n");
        printf("1. <capture>          : to capture and send greyscale image\n");
        printf("2. <capture jpg>      : to capture and send greyscale compressed image\n");
        printf("3. <capture edge>     : to capture and send edge detection image\n");
        printf("4. <capture edge jpg> : to capture and send edge detection compressed image\n");
        printf("5. <capture rgb>      : to capture and send color image\n");
        printf("6. <capture rgb jpg>  : to capture and send color compressed image\n");
        printf("7. <exit>             : to exit the program\n");
        stdin_buff_len = read(STDIN_FILENO, &stdin_buff[0], 20);
        if (stdin_buff_len < 0) {
            syslog(LOG_ERR, "read");
            perror("read");
            exit(-1);
        }
        printf("stdin_buff: %s", (char *)stdin_buff);
        printf("stdin_buff_len: %d\n", stdin_buff_len);

        pgm_bytes_recvd = 0;


        if (!strncmp("exit\n", (char *)stdin_buff, stdin_buff_len)) {
        	image_type=0;
            break;
        }
        else if (strncmp("capture\n", (char *)stdin_buff, stdin_buff_len) == 0) {
        	image_type=0;
            //continue;
        }
        else if (strncmp("capture jpg\n", (char *)stdin_buff, stdin_buff_len) == 0) {
        	image_type=1;
            //continue;
        }
        else if (strncmp("capture edge\n", (char *)stdin_buff, stdin_buff_len) == 0) {
        	image_type=0;
            //continue;
        }
        else if (strncmp("capture edge jpg\n", (char *)stdin_buff, stdin_buff_len) == 0) {
        	image_type=1;
            //continue;
        }
        else if (strncmp("capture rgb\n", (char *)stdin_buff, stdin_buff_len) == 0) {
        	image_type=2;
            //continue;
        }
        else if (strncmp("capture rgb jpg\n", (char *)stdin_buff, stdin_buff_len) == 0) {
        	image_type=1;
            //continue;
        }
        else
        	continue;

        socket_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (socket_fd < 0) {
            syslog(LOG_ERR, "socket");
            perror("socket");
            exit(-1);
        }

        if (connect(socket_fd, res->ai_addr, res->ai_addrlen) == -1) {
            syslog(LOG_ERR, "connect");
            perror("connect");
            exit(-1);
        }
        //printf("Connected!\n");

        send_bytes = send(socket_fd, &stdin_buff[0], stdin_buff_len, 0);
        if (send_bytes < 0) {
            syslog(LOG_ERR, "send");
            perror("send");
            exit(-1);
        }

        //printf("Bytes sent: %d\n", send_bytes);

        recv_bytes = recv(socket_fd, &recv_buff[0], 5, 0);
        if (recv_bytes < 0) {
            syslog(LOG_ERR, "recv");
            perror("recv");
            exit(-1);
        }

        //printf("Bytes recvd: %d\n", recv_bytes);
        //printf("Message received from socket server: %s\n", (char *)recv_buff);

        send_bytes = send(socket_fd, "get bytes\n", 10, 0);
        if (send_bytes < 0) {
            syslog(LOG_ERR, "send");
            perror("send");
            exit(-1);
        }

        //printf("Bytes sent: %d\n", send_bytes);

        recv_bytes = recv(socket_fd, &recv_buff[0], sizeof(uint32_t), 0);
        if (recv_bytes < 0) {
            syslog(LOG_ERR, "recv");
            perror("recv");
            exit(-1);
        }

        //printf("Bytes recvd: %d\n", recv_bytes);
        pgm_len = *((uint32_t *)(&recv_buff[0]));
        pgm_len = ntohl(pgm_len);

        //printf("pgm_len: %d\n", pgm_len);


        send_bytes = send(socket_fd, "send image\n", 11, 0);
        if (send_bytes < 0) {
            syslog(LOG_ERR, "send");
            perror("send");
            exit(-1);
        }

		if(image_type==2)
        	test_pgm_fd = open("/root/pgm_image.ppm", O_CREAT | O_RDWR | O_TRUNC, 0774);
		else if(image_type==1)
        	test_pgm_fd = open("/root/pgm_image.jpg", O_CREAT | O_RDWR | O_TRUNC, 0774);
		else if(image_type==0)
        	test_pgm_fd = open("/root/pgm_image.pgm", O_CREAT | O_RDWR | O_TRUNC, 0774);
        	
        if (test_pgm_fd < 0) {
            syslog(LOG_ERR, "open");
            perror("open");
            exit(-1);
        }

        while (pgm_bytes_recvd < pgm_len) {
            if (pgm_bytes_recvd + PGM_BYTES_CHUNK > pgm_len) {
                pgm_bytes_to_recv = pgm_len - pgm_bytes_recvd;
            }
            else {
                pgm_bytes_to_recv = PGM_BYTES_CHUNK;
            }

            recv_bytes = recv(socket_fd, &pgm_buff[0], pgm_bytes_to_recv, 0);
            if (recv_bytes < 0) {
                syslog(LOG_ERR, "recv");
                perror("recv");
                exit(-1);
            }

            pgm_write_bytes = write(test_pgm_fd, &pgm_buff[0], recv_bytes);
            if (pgm_write_bytes < 0) {
                syslog(LOG_ERR, "recv");
                perror("recv");
                exit(-1);
            }

            pgm_bytes_recvd += recv_bytes;

            //printf("pgm_bytes_recvd: %d\n", pgm_bytes_recvd);
            //printf("pgm_write_bytes: %d\n", pgm_write_bytes);
        }

        //printf("pgm of %d bytes length received\n", pgm_bytes_recvd);

        /*close(test_pgm_fd);

        pid = fork();
        if (pid == -1) {
            syslog(LOG_ERR, "fork");
            perror("fork");
            exit(-1);
        }
        else if (pid == 0) {
            execl("/usr/bin/mogrify", "/usr/bin/mogrify", "-write", "../foo.pgm", "-format", "pgm", "test_pgm.pgm", (char *)NULL);
            exit(-1);
        }
        else {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                exit_status = WEXITSTATUS(status);
                if (exit_status != 0) {
                    printf("Something went wrong in execl\n");
                    exit(-1);
                }
            }
        }
        printf("Converted image!\n");*/
        

        

        //printf("Entering program...\n");
    
        


        //Reading test file
        
        /*test_pgm_fd = open("/root/test.pgm", O_RDONLY);
        if (test_pgm_fd < 0) {
            perror("open");
            exit(-1);
        }*/
        
        if (image_type == 0) {
        	lseek(test_pgm_fd, pgm_len - PGM_SIZE, SEEK_SET);
        }
        else if (image_type == 2) {
        	lseek(test_pgm_fd, pgm_len - PPM_SIZE, SEEK_SET);
        }

        printf("Drawing pixels...\n");
        for (j = 0; j < LCD_HEIGHT; j++) {
            for (i = 0; i < LCD_WIDTH; i++) {
            	if (image_type == 0) {
		            if ((read(test_pgm_fd, &color_buff[0], 1)) == -1) {
		                perror("read");
		                exit(-1);
		            }
		            LCD_WritePGMPixel(i, j, color_buff[0]);
                }
                else if (image_type == 2) {
                	if ((read(test_pgm_fd, &color_buff[0], 3)) == -1) {
                		perror("read");
                		exit(-1);
                	}
                	LCD_WritePPMPixel(i, j, color_buff);
                }
            }
        }
        
        printf("Image display successful!\n");
        
        close(test_pgm_fd);
        memset(recv_buff, 0, 15);
        memset(stdin_buff, 0, 10);
        close(socket_fd);
    }
    printf("Exiting...\n");
    //DeInit LCD module
    //if (LCD_DeInit()) {
    //    printf("Error in LCD_DeInit()\n");
    //    return 1;
    //}
    
    return 0;
}
