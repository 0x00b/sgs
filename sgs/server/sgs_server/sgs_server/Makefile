# makefile for sgs
# author: lijun 
# date: 2018.1.10
#
#VPATH=.:src  #make find file in this directory,use : depart,or use vpath 

vpath %.h include/google/protobuf		# .h at include/google/protobuf
vpath %.h include/libev	# .h at 
vpath %.h libs					# .h at 
vpath %.h libs/json				# .h at 
vpath %.h zlib					# .h at 
#vpath %.c include/libev	# .h at 
vpath %.cpp libs				# .cpp at 

CC = gcc
CXX = g++

CFLAGS = -O0 -Wall
CXXFLAGS = -std=c++11 -g -O0 -fno-strict-aliasing -Wno-write-strings -frtti -fexceptions -Wall -DDEBUG
LIBS = -L./zlib -L./libs -lprotobuf -lstdc++

APP = sgs_server

inc = -I./ -Iinclude/google/protobuf -Iinclude/libev -Ilibs -Ilibs/json -Izlib # or use C_INCLUDE_PATH ,CPLUS_INCLUDE_PATH envir_path
#inc += -Isrc/src	 # +=

targ := $(shell ls|grep '\.cpp';ls libs|grep '\.cpp')
objs_:= $(patsubst %.c,%.o,$(targ))
objs := $(patsubst %.cpp,%.o,$(objs_))

$(APP):$(objs)
	$(CXX) $(CXXFLAGS) $(inc) -o $@ $(objs) $(LIBS) -lm

%.o:%.c
	$(CC) $(CFLAGS) $(inc) -c $^

%.o:%.cpp
	echo $(inc)
	$(CXX) $(CXXFLAGS) $(inc) -c $^


.PHONY:clean
clean:
	rm -f *.o $(APP) 
