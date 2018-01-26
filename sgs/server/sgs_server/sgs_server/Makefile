# makefile for sgs
# author: lijun 
# date: 2018.1.10
#
#VPATH=.:src  #make find file in this directory,use : depart,or use vpath 

vpath %.h include/libev	# .h at 
vpath %.h libs					# .h at 
vpath %.h libs/json				# .h at 
vpath %.h zlib					# .h at 
vpath %.h mysqlutil				# .h at 
vpath %.h libgamelogic			# .h at 
vpath %.h libgamelogic/sgslogic			# .h at 
vpath %.h jsonproto			# .h at 
#vpath %.c include/libev	# .h at 
vpath %.cpp libs				# .cpp at 
vpath %.cpp mysqlutil			# .cpp at 
vpath %.cpp libgamelogic			# .cpp at 
vpath %.cpp libgamelogic/sgslogic	# .cpp at 

CC = gcc
CXX = g++

CFLAGS = -O0 -Wall
CXXFLAGS = -std=c++11 -g -O0 -fno-strict-aliasing -Wno-write-strings -frtti -fexceptions -Wall -DDEBUG
LIBS = -L./zlib -L./libs -lev -lstdc++ -lmysqlclient

APP = sgs_server

inc = -I./ -Iinclude/libev -Ilibs -Ilibs/json -Izlib -Imysqlutil -Ijsonproto# or use C_INCLUDE_PATH ,CPLUS_INCLUDE_PATH envir_path
#inc += -Isrc/src	 # +=

targ := $(shell ls|grep '\.cpp';ls libs|grep '\.cpp';ls mysqlutil|grep '\.cpp';ls libgamelogic|grep '\.cpp';ls libgamelogic/sgslogic|grep '\.cpp')
objs_c:= $(patsubst %.c,%.o,$(targ))
objs_cc:= $(patsubst %.cc,%.o,$(objs_c))
objs := $(patsubst %.cpp,%.o,$(objs_cc))

$(APP):$(objs)
	$(CXX) $(CXXFLAGS) $(inc) -o $@ $(objs) $(LIBS) -lm

%.o:%.c
	$(CC) $(CFLAGS) $(inc) -c $^

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(inc) -c $^


.PHONY:clean clean_obj
clean:
	rm -f *.o $(APP) 

clean_obj:
	rm -f *.o