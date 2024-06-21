# includes environment variables from the parent directory
include $(CURDIR)/../.env

# name of your application
APPLICATION = wsn-group-project

# If no BOARD is found in the environment, use this default:
BOARD ?= feather-nrf52840-sense

# This has to be the absolute path to the RIOT base directory:
# the enviroment variable RIOTBASE is defined in the .env file in the parent directory!
RIOTBASE ?= ${RIOTBASE}

# include SAUL to interact with onboard sensors and actuators
USEMODULE += saul

# include and auto-initialize all available sensors
USEMODULE += saul_default

# enable default networking devides in the platform
USEMODULE += netdev_default

# automatically initialize network interfaces for enabled devices
USEMODULE += auto_init_gnrc_netif

# enable single interface optimization.
# remove this if more than one interface is present
USEMODULE += gnrc_netif_single

USEMODULE += gnrc_netif_timestamp

# add minimal IPv6 support
USEMODULE += gnrc_ipv6_default

# enable ping support
USEMODULE += gnrc_icmpv6_echo

# add module to hex dump data
USEMODULE += od

# add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_cmds_default

# Enable the milliseconds timer.
USEMODULE += ztimer
USEMODULE += ztimer_msec

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# with ROLE=sender, the sender application is compiled
# with ROLE=receiver, the receiver application is compiled
# if nothing is specified, the shell is run
ifeq ($(ROLE), SENDER)
# do print
$(info Compiling sender application)
CFLAGS += -DSENDER
else ifeq ($(ROLE), RECEIVER)
$(info Compiling receiver application)
CFLAGS += -DRECEIVER
endif

CFLAGS += -DIP_ADDR=\"$(IP_ADDR)\"

include $(RIOTBASE)/Makefile.include
