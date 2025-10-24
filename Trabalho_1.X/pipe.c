#include "pipe.h"
#include "sync.h"
#include "mem.h"
#include <xc.h>

void create_pipe(pipe_t *p)
{
    p->pipe_data = (char *)SRAMalloc(PIPE_MAX_SIZE); // Aloca dinamicamente o buffer do pipe
    p->pipe_pos_read    = 0;
    p->pipe_pos_write   = 0;

    if (p->pipe_data == NULL) {
        return;
    }

    // Inicializa os sem?foros de controle do pipe
    sem_init(&p->pipe_sem_read, 0);
    sem_init(&p->pipe_sem_write, PIPE_MAX_SIZE);
}


void read_pipe(pipe_t *p, char *buffer)
{
    di();
    
    if (p->pipe_data == NULL) {
        ei();
        return;
    }

    // Testa o sem?foro de leitura
    sem_wait(&p->pipe_sem_read);
    
    *buffer = p->pipe_data[p->pipe_pos_read];
    p->pipe_pos_read = (p->pipe_pos_read + 1) % PIPE_MAX_SIZE;
    
    // Libera o sem?foro da escrita
    sem_post(&p->pipe_sem_write);
    
    ei();
}


void write_pipe(pipe_t *p, char buffer)
{
    di();
    
    if (p->pipe_data == NULL) {
        ei();
        return;
    }

    // Testa o sem?foro de escrita
    sem_wait(&p->pipe_sem_write);
    
    p->pipe_data[p->pipe_pos_write] = buffer;
    p->pipe_pos_write = (p->pipe_pos_write + 1) % PIPE_MAX_SIZE;
    
    // Libera o sem?foro da leitura
    sem_post(&p->pipe_sem_read);
    
    ei();    
}

