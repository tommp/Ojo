program_EXECUTABLE := ojo

CC = gcc

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
current_path := $(abspath ../$(current_dir))



program_C_SRCS := $(wildcard src/*.c)
program_OBJS := ${program_C_SRCS:.c=.o}


OPENGL_LIB := GL

program_INCLUDE_DIRS := $(current_path) $(current_path)/src/headers/
program_LIBRARY_DIRS := $(current_path)/src/lib/static
program_LIBRARIES := $(OPENGL_LIB) m 

CCFLAGS += -Wall -g -pg -march=armv7-a -mfpu=neon-vfpv4 -mfloat-abi=hard
CFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))


all: $(program_EXECUTABLE)

$(program_OBJS):%.o:%.c
	$(CC) $(CCFLAGS) -c $< -o $@ $(CFLAGS)

$(program_EXECUTABLE): $(program_OBJS)
	$(CC) $(CCFLAGS) $(CFLAGS) $(TARGET_ARCH) -o $(program_EXECUTABLE) $(program_OBJS) $(LDFLAGS)

clean:
	@- $(RM) $(program_EXECUTABLE)
	@- $(RM) $(program_OBJS)

distclean: clean

.PHONY: all clean distclean

