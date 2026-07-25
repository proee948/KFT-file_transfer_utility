#include "main.h"

int main()
{
    struct info PASSED_INFO = get_path(); //extracted path of file
    //send_file(PASSED_INFO);
    get_name_and_extension(PASSED_INFO);
    
}

struct info get_path(void)
{
    struct info INFO = {0};
    FILE *STREAM = fopen("save.txt","r");
    if(STREAM == NULL){return INFO;}

    char *BUFFER;
    if ( (BUFFER = malloc(1024)) == NULL)
    {
        printf("malloc failed");
        return INFO;
    }    

    fseek(STREAM,0,SEEK_SET); //redundant
    char *P = BUFFER;

    int ch;
    char **ptr = &BUFFER; //ptr to dyn all arr BUFFER ptr 
    int count = 0;

    while( (ch = fgetc(STREAM)) != EOF && count < 1023)
    {
        **ptr = (char)ch;
        (*ptr)++;
        count++;
    }
    **ptr = '\0';
    strncpy(INFO.path, P, 1023);
    INFO.path[1023] = '\0';    
    //printf("BUFFER CONTENTS>>> %s",P);
    fclose(STREAM);
    free(P);
    return INFO;
}
int start_tcp(void)
{
    int c_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in adr = {
        .sin_family = AF_INET,
        .sin_port = htons(4444)
    };
    inet_pton(AF_INET, RECEIVER_IP, &adr.sin_addr);

    socklen_t len = sizeof(adr);
    
    if (connect(c_sockfd, (struct sockaddr *)&adr, len) == -1) {
        perror("Connect failed");
        close(c_sockfd);
        exit(EXIT_FAILURE);
    }
    printf("host connected\n");
    return c_sockfd;

}
void send_file(struct info PATH)
{
    int socket_fd = start_tcp();
    int file_descriptor_in = open(PATH.path,O_RDONLY); //open file


    //metadata//
    struct stat stat_data; 
    int check = stat(PATH.path,&stat_data);
    if(check == -1){perror("stat failed");}

    ///////////////////////////////////
    //metadata//
    //send metadata struct//
    send(socket_fd,&stat_data,sizeof(stat_data),0);
    //send metadata struct//

    //send bytes//
    ssize_t bytes_returned;
    off_t offset = 0;
    off_t *ptt = &offset;
    while( (bytes_returned = sendfile(socket_fd,file_descriptor_in,ptt,1024)) > 0)
    {
        ;
    }
    if(bytes_returned == -1)
        {
            perror("fail");
        }
    close(socket_fd);
    close(file_descriptor_in);
    //send bytes//
}
char* get_name_and_extension(struct info PATH)
{
    char *string;
    string = strrchr(PATH.path,'/') + 1;   
    
    char arr[100] = {'\0'};
    strcpy(arr,string);
    char *dot = strrchr(arr,'.');
    *dot = '\0';

    char* extension = strrchr(string,'.');

    printf("%s\n",extension);
    printf("%s\n",arr);
    
    /////////////////implement struct that will get passed as return type \
    //make it static so it isnt aborted after function ends

}
