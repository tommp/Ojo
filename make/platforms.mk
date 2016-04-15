WINDOW_SYSTEM := 1000
NO_WINDOW := 1000
DISPMANX := 1001
RBP := 1002

ifneq ($(findstring sdl, $(MAKECMDGOALS)),)
WINDOW_SYSTEM = $(SDL)
endif

ifneq ($(findstring dsx, $(MAKECMDGOALS)),)
WINDOW_SYSTEM = $(DISPMANX)
endif

sdl: all
dsx: all

.PHONY: sdl rbp