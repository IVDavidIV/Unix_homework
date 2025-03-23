#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>

#define SHARED_MEMORY_NAME "/chat_shm"
#define SHARED_MEMORY_PARENT "/sem_parent"
#define SHARED_MEMORY_CHILD "/sem_child"
#define SHARED_MEMORY_SIZE 256

int main() {
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_RDWR, 0666);
    char *shared_memory = mmap(0, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t *sem_parent = sem_open(SHARED_MEMORY_PARENT, 0);
    sem_t *sem_child = sem_open(SHARED_MEMORY_CHILD, 0);

    while(1) {
        sem_wait(sem_parent);

        if (strcmp(shared_memory, "exit") == 0)              
            break;

        printf("Child received your message: %s\n", shared_memory);
        sem_post(sem_child); 
    }

    sem_close(sem_parent);
    sem_close(sem_child);
    return 0;
}
