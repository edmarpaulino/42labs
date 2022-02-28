#! /usr/bin/env bash

host='192.168.3.30:4242/'
# host='localhost:4242/'
array=('log' 'usr' 'bin' 'json' 'test' 'lib' 'etc')

for i in {0..1000};do
	num=$((i % 7))
	if (( $num == 0 ));then
		wget --method=GET -p ${host} -O /dev/null;
		wget --method=GET -p ${host}${array[num]} -O /dev/null;
	elif (( $num == 1 ));then
		wget --method=POST -p ${host} -O /dev/null;
		wget --method=POST -p ${host}${array[num]} -O /dev/null;
	elif (( $num == 2 ));then
		wget --method=PUT -p ${host} -O /dev/null;
		wget --method=PUT -p ${host}${array[num]} -O /dev/null;
	elif (( $num == 3 ));then
		wget --method=PATCH -p ${host} -O /dev/null;
		wget --method=PATCH -p ${host}${array[num]} -O /dev/null;
	elif (( $num == 4 ));then
		wget --method=DELETE -p ${host} -O /dev/null;
		wget --method=DELETE -p ${host}${array[num]} -O /dev/null;
	elif (( $num == 5 ));then
		wget --method=OPTIONS -p ${host} -O /dev/null;
		wget --method=OPTIONS -p ${host}${array[num]} -O /dev/null;
	else
		wget --method=HEAD -p ${host} -O /dev/null;
		wget --method=HEAD -p ${host}${array[num]} -O /dev/null;
	fi
done
