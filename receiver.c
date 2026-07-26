#include "main.h"

int main()
{
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    int opt = 1; 
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(4444),
        .sin_addr.s_addr = INADDR_ANY
    };

    bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(listen_fd, 10);
    printf("Listening...\n");

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    int client_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("Error");
        close(listen_fd);
        return 1;
    }
    fetch_and_reconstruct(client_fd);

    close(client_fd);
    close(listen_fd);

    return 0;
}
void fetch_and_reconstruct(int inc_socket)
{
    //accept stat//
    struct stat received_stat;
    u_int64_t metadata_size = sizeof(struct stat); //sizeof incoming struct 
    recv(inc_socket,&received_stat,metadata_size,0);
    //accept stat//

    //accept name and extension//
    struct name_and_ext received_N_E;
    u_int64_t N_E_size = sizeof(struct name_and_ext);
    recv(inc_socket,&received_N_E,N_E_size,0);
    //accept name and extension//

    //accept bytes//
    strcat(received_N_E.name,received_N_E.ext); //full name and ext
    FILE* f = fopen(received_N_E.name,"wb"); //open file with correct name and ext

    uint8_t FINAL_BUFFER [1024];
    ssize_t ch = 0;

    while ( (ch = recv(inc_socket,FINAL_BUFFER,1024,0)) > 0 )
    {
        fwrite(FINAL_BUFFER,1,ch,f);
    }
    fclose(f);
}

