#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <dml/dml.h>


int main(int argc, char **argv) {

    puts("Alloc memory");
    uint64_t size = 512 * 4096;
    uint64_t *src = (uint64_t *) malloc(size); 
    uint64_t *dst = (uint64_t *) malloc(size); 

    puts("Initialize data");
    for(int i = 0; i < size / sizeof(uint64_t); ++i) {
        src[i] = i*i;
        dst[i] = 0; //load dst pages into memory to avoid page faults during DSA execution
    }

    puts("Create job");
    dml_path_t path = DML_PATH_HW;
    uint64_t job_size;
    dml_job_t *job_ptr;
    
    dml_get_job_size(path, &size);
    job_ptr = (dml_job_t *) malloc(size);
    dml_init_job(path, job_ptr);

    puts(" ... and set the neccessary fields");
    job_ptr->source_first_ptr      = src;
    job_ptr->source_length         = size;
    job_ptr->destination_first_ptr = dst;
    job_ptr->destination_first_ptr = size;
    job_ptr->operation             = DML_OP_MEM_MOVE;
    job_ptr->flags                |= DML_FLAG_COPY_ONLY;

    puts("Submit the job");
    dml_submit_job(job_ptr);

    //do async. work

    dml_status_t status = dml_wait_job(job_ptr, DML_WAIT_MODE_BUSY_POLL);

    if (DML_STATUS_OK != status) {
        printf("An error (%u) occurred during job execution.\n", status);
        dml_finalize_job(job_ptr);
        free(job_ptr);
        return 1;
    }
    status = dml_finalize_job(job_ptr);
    if (DML_STATUS_OK != status) {
        printf("An error (%u) occurred during job finalization.\n", status);
        free(job_ptr);
        return 1;
    } else {
        puts("No error occured");
    }
    free(job_ptr);




    puts("Check results");
    for(int i = 0; i < size / sizeof(uint64_t); ++i) {
        if(dst[i] != src[i]) {
            puts("Data were not copied correctly");
            return 1;
        }
    }

    puts("Everything went fine :)");

    free(src);
    free(dst);

    return 0;
}
