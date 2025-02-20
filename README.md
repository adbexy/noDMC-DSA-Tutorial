# noDMC-DSA-Tutorial

This is the repository to the Tutorial "Unleashing the Intel Data Streaming Accelerator" given at noDMC@BTW2025.
For easy reprodicability we decided to deliver the code along side with a Docker-Container, which allows to simply recreate our tutorial setup.

## Setup 

To setup the contained Docker-Environment, the _Data Mover Library_ and the DSA-Devices on your system, please follow these steps

### Build Docker-Environment
0. Setup Docker or a compatible conteinerization platform on your test system.

1. Build the Docker container, using the `Dockerfile` in this repositories root directory. You may use the attached shell script.
    
    ```sudo ./docker_build.sh```

2. Launch the Docker container you built earlier. Make sure you mount this repository in `/home/user`. We have also included a shell script for your convenience:
    
    ```sudo ./docker_start.sh```
    
    Now you work inside a Docker container.

### Build the DML
3. Fetch the submodules of our repository (recursively) and build the DML library from inside the Docker container. The script `setup_DML.sh` would perform the entire setup for you. You may check it out and change the cmake flags to build the examples and text along with the libraries neccessary.
    
    ```./setup_DML.sh```

### Setup the DSA devices
4. Before we would be able to submit tasks to the DSA, we need to set it up. For setup we use the accel-cofig comand line client and our prepared config file. We prepared a script that combines deactivation of running DSA devices (as running devices cannot be reconfigured) and reconfiguration of them. 
    
    ```./code/config/load_dsa_config.sh code/config/3g2e_vary_prio.conf```

    It might be necessary to modify the script and configuration file, if your machine does not provide that many DSA devices.