#include "nl_lib.h"
#include "private/nl_gl.h"

typedef struct myvd myvd;
struct myvd 
{
    int unused;
};

typedef struct my_batch my_batch;
struct my_batch
{
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int max_vertice_count;
    unsigned int current_vertice_count;

    myvd*  vertices;
};

void init_batch(my_batch* batch, unsigned int count)
{   
    const unsigned int vertice_count = count * 4;
    const unsigned int indice_count  = count * 6;

    const size_t vertice_data = vertice_count * sizeof(myvd);
    const size_t indice_data  = indice_count  * sizeof(unsigned int);

    batch->vertices = (myvd*)memory_allocate(vertice_data);
}

void free_batch(my_batch* batch)
{
    memory_free(batch->vertices);
}

static my_batch batch = {0};

void app_specific_init(void)
{
    init_batch(&batch, 3);
}

void app_specific_update(double dt)
{
    (void)dt;
}

void app_specific_cleanup()
{
    free_batch(&batch);
}