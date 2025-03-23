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
    int shm_fd = shm_open(SHARED_MEMORY_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SHARED_MEMORY_SIZE);
    char *shared_memory = mmap(0, SHARED_MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_t *sem_parent = sem_open(SHARED_MEMORY_PARENT, O_CREAT, 0666, 0);
    sem_t *sem_child = sem_open(SHARED_MEMORY_CHILD, O_CREAT, 0666, 1);

    printf("Parent: Type your messages (type 'exit' to quit) %s\n");

    while(1) {
        sem_wait(sem_child);  
        
        printf("You: ");
        fgets(shared_memory, SHARED_MEMORY_SIZE, stdin);
        shared_memory[strcspn(shared_memory, "\n")] = 0; 

        sem_post(sem_parent); 
        
        if (strcmp(shared_memory, "exit") == 0) 
            break;
    }

    sem_close(sem_parent);
    sem_close(sem_child);
    sem_unlink(SHARED_MEMORY_PARENT);
    sem_unlink(SHARED_MEMORY_CHILD);
    shm_unlink(SHARED_MEMORY_NAME);
    return 0;
}
