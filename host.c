#include "main.h"

int main()
{
    struct info PASSED_INFO = get_path(); //extracted path of file
    start_tcp();
    send_file(PASSED_INFO);
    
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
void start_tcp(void)
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

}
char* extract_ip(void)
{
    FILE *fp = popen("hostname -I","r");
    if (fp == NULL)
    {
        printf("popen failed");
        exit(EXIT_FAILURE);
    }

    static char IP[MAX_IP_LENGTH];
    while( (fgets(IP,MAX_IP_LENGTH,fp)) != NULL){;}
    //printf("%s",IP);  diagnostic//
    return IP;

    pclose(fp);
}
void send_file(struct info PATH)
{
    printf("%s",PATH.path);
    int file_descriptor_in = open(PATH.path,O_RDONLY);

    FILE *raw_p = fopen(PATH.path,"rb");
    char BUF[4096]; //match OS for efficiency
    size_t ctl;

    ///////////////implement protocol header here//////////

    ///////////////implement protocol header here//////////

    /////////////sends raw bytes of file////////////////
    while ( (ctl = fread(BUF,sizeof(char),1024,raw_p)) != 0)
    {
        send(file_descriptor_in,BUF,ctl,0); 
        memset(&BUF,0,sizeof(BUF));
    }
    close(file_descriptor_in);
    fclose(raw_p);
    /////////////sends raw bytes of file////////////////

    /*int ascii = file_descriptor + '0';
    write(1,&ascii,sizeof(ascii));
    write(1,"\n",1);*/ 
}
