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

    close(client_fd);
    close(listen_fd);

    return 0;
}
void fetch_and_reconstruct(int inc_socket)
{
    struct stat received_stat;
    u_int64_t metadata_size = sizeof(struct stat); //sizeof incoming struct 
    recv(inc_socket,&received_stat,metadata_size,0);

    //received_stat. fuck this shit
}
