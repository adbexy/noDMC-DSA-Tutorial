
#include <cstdint>
#include <cstdlib>
#include <dml/dml.hpp>

#include <iostream>

#include "util/dml_helper.hpp"

int main(int argc, char **argv) {

    std::cout << "Alloc memory" << std::endl;
    //alloc memory
    size_t size = 512 * 4096;
    uint64_t *src = (uint64_t *) std::malloc(size); 
    uint64_t *dst = (uint64_t *) std::malloc(size); 

    std::cout << "Initialize data" << std::endl;

    for(int i = 0; i < size / sizeof(uint64_t); ++i) {
        src[i] = i*i;
        //dst[i] = 0; //load dst pages into memory to avoid page faults during DSA execution
    }

    std::cout << "Prepare dataviews" << std::endl;
    // memory regions for a DML operation have to be passed 
    // as dml::data_view objects
    dml::data_view src_view = dml::make_view(src, size / sizeof(uint64_t));
    dml::data_view dst_view = dml::make_view(dst, size / sizeof(uint64_t));

    std::cout << "Submit task for async. execution" << std::endl;
    // asynchronous execution of copy operation
    // path could be dml::software, dml::hardware, or dml::automatic
    auto handler = dml::submit<dml::hardware>(
            dml::mem_copy.block_on_fault(), src_view, dst_view);
    // dml::mem_copy.block_on_fault() -> page faults will be resolved on the accelerator
        
    // ... do other work  asynchronously

    std::cout << "Fetch completion record" << std::endl;
    // Wait for the DSA to finish the submitted task
    auto result = handler.get();

    std::cout << "Check for errors" << std::endl;
    if (result.status != dml::status_code::ok) {
        std::cout << 
                "ERROR: DML error occured! Status code: " << 
                status_code_to_string(result.status) << 
                std::endl; 
        return -1;
    } else std::cout << "No error occured"<< std::endl; 


    std::cout << "Check results" << std::endl;
    for(int i = 0; i < size / sizeof(uint64_t); ++i) {
        if(dst[i] != src[i]) {
            std::cout << "Data were not copied correctly" << std::endl;
            return 1;
        }
    }

    std::cout << "Everything went fine :)" << std::endl;

    std::free(src);
    std::free(dst);

    return 0;
}