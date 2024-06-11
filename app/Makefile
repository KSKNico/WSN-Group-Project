# includes environment variables from the parent directory
include $(CURDIR)/../.env

# name of your application
APPLICATION = wsn-group-project

# If no BOARD is found in the environment, use this default:
BOARD ?= feather-nrf52840-sense

# This has to be the absolute path to the RIOT base directory:
# the enviroment variable RIOTBASE is defined in the .env file in the parent directory!
RIOTBASE ?= ${RIOTBASE}

# add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_cmds_default

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
