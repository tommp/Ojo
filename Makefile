program_EXECUTABLE := ojo

CC = gcc

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
current_path := $(abspath ../$(current_dir))



program_C_SRCS := $(wildcard src/*.c)
program_OBJS := ${program_C_SRCS:.c=.o}

OPENGL_LIB := GLESv2 EGL

program_INCLUDE_DIRS := $(current_path) $(current_path)/src/headers/ $(SDKSTAGE)/opt/vc/include/ $(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads $(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux ./libs/vgfont ./libs/ilclient
program_LIBRARY_DIRS := $(current_path)/src/lib/static $(SDKSTAGE)/opt/vc/lib/ ./libs/ilclient ./libs/vgfont
program_LIBRARIES := $(OPENGL_LIB) pthread rt m 

CCFLAGS += -pg -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DTARGET_POSIX -D_LINUX -fPIC -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -Wall -g -DHAVE_LIBOPENMAX=2 -DOMX -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -Wno-psabi
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

