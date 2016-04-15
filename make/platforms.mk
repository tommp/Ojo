WINDOW_SYSTEM := 1000
NO_WINDOW := 1000
SDL := 1001
RBP := 1002

ifneq ($(findstring sdl, $(MAKECMDGOALS)),)
WINDOW_SYSTEM = $(SDL)
endif

ifneq ($(findstring rbp, $(MAKECMDGOALS)),)
WINDOW_SYSTEM = $(RBP)
endif

sdl: all
rbp: all

.PHONY: sdl rbp