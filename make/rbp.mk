
RBP2_LIB := openmaxil bcm_host vcos vchiq_arm
program_LIBRARIES += $(RBP_LIB)
CFLAGS += -DWINDOW_SYSTEM=$(RBP)