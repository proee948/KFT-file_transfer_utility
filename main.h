#ifndef MAIN_H
#define MAIN_H

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/sendfile.h>

#define MAX_IP_LENGTH 128

struct info{char path[1024];};
struct name_and_ext{char name[128];char ext[8];};

void send_file(struct info);
struct info get_path(void);
char* extract_ip(void);
int start_tcp(void);
struct name_and_ext get_name_and_extension(struct info);


#ifndef RECEIVER_IP
#define RECEIVER_IP "bullshit" //this should be passed -D "_ip_"
#endif

#endif
