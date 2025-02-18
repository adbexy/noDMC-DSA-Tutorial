#!/bin/sh

if [ $(whoami) != "root" ]; then
	echo "not run as root. might be a mistake on your side!";
	exit;
fi

accel-config disable-device dsa0
accel-config disable-device dsa1
accel-config disable-device dsa2
accel-config disable-device dsa3
accel-config disable-device dsa4
accel-config disable-device dsa5
accel-config disable-device dsa6
accel-config disable-device dsa7

accel-config load-config -c $1 -e

# change access rights of the work queues to allow access for every user
chmod 666 /dev/dsa/*

