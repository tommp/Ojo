
DISPMANX_LIB := openmaxil bcm_host vcos vchiq_arm
program_LIBRARIES += $(DISPMANX_LIB)
CFLAGS += -DWINDOW_SYSTEM=$(DISPMANX)