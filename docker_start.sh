#!/bin/bash
sudo docker run -it \
    --name noDMC_Tutorial \
    --rm \
    --privileged \
    --cap-add=sys_nice \
    --mount type=bind,src=.,target=/home/user \
    no_dmc