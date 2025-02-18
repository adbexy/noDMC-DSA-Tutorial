FROM debian:12 as base

# disable requests for user input of the following code
ENV DEBIAN_FRONTEND=noninteractive

# add testing packages (for linux-cpupower)
RUN echo "deb http://deb.debian.org/debian/ testing non-free contrib main" \
	>> /etc/apt/sources.list
# update apt-get packet lists, only strictly necessary for cpu-power,
# which uses the testing package repos
RUN apt-get update

# gcc and g++
RUN apt-get install -y gcc-12 g++-12
# cmake for compiling
RUN apt-get install -y cmake git 
# NUMA configuration
RUN apt-get install -y numactl libnuma-dev
# for configuring DSA
RUN apt-get install -y accel-config
# for plotting
RUN apt-get install -y python3-seaborn

# to change cpu governor
RUN apt-get install -y linux-cpupower

# install modprobe, used by cpupower as installed by linux-cpupower
RUN apt-get install -y kmod

# delete apt-get packet lists
RUN rm -rf /var/lib/apt-get/lists/*

# create shortcuts/links to the executables
RUN rm -f /usr/bin/g++ /usr/bin/gcc
RUN ln --symbolic /usr/bin/g++-12 /usr/bin/g++
RUN ln --symbolic /usr/bin/gcc-12 /usr/bin/gcc

# create working directory to bind volumes
RUN mkdir /home/user
WORKDIR /home/user
# makes caching after this impossible
#ADD . ./

WORKDIR /home/user