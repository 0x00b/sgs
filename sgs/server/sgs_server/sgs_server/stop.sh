#/bin/bash

kill -9 `ps -ef|grep sgs_server |grep -v grep|awk '{print $2}'`


