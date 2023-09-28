
# ********************** Section for Macros (Variables) ********************** #
# Product file
NAME			= ircserv

# Enumeration of files
SRC				= main.cpp Server.cpp \
				  Client.cpp \
				  Channel.cpp \
				  Join.cpp \
				  debugMessage.cpp

# Message.cpp command/privmsg.cpp

# Check the platform
OS				= $(shell uname)

# Defination of macro constants

# Enumeration of directories
SRCDIR			= ./srcs
INCDIR			= ./includes
OBJDIR			= ./obj

# Aliases of commands
CXX				= c++
RM				= rm

# Command options (flags)
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98 -pedantic-errors -MMD -MP
INCLUDES		= -I$(INCDIR)
RMFLAGS			= -r
DEBUGCFLAGS		= -g -ggdb -fno-omit-frame-pointer
ifneq ($(OS), Darwin)
	DEBUGCFLAGS	+= -fstack-usage
endif
DEBUGLDFLAGS	= -fsanitize=address

# Redefination when the specific target
ifeq ($(MAKECMDGOALS), debug)
	ifneq ($(OS), Darwin)
		CPPFLAGS	+= $(DEBUGCFLAGS)
		LDFLAGS	+= $(DEBUGLDFLAGS)
	endif
	DEF		+= -D DEBUG_MODE=1
endif

# Macros to replace and/or integrate
SRCS			= $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(SRC:%.cpp=$(OBJDIR)/%.o)
DEPS			= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.d)))

# ********************* Section for targets and commands ********************* #

# Mandatory targets
.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	-$(RM) $(RMFLAGS) $(OBJDIR)

.PHONY: fclean
fclean: clean
	-$(RM) $(RMFLAGS) $(NAME)

.PHONY: re
re: fclean all

# Additional targets
.PHONY: debug
debug: fclean all

# Recipes
$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR):
	mkdir -p $@
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
$(OBJDIR)/%.o: $(SRCDIR)/command/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

# $(OBJDIR)/command/%.o: $(SRCDIR)/command/%.cpp | $(OBJDIR)/command
# 	mkdir -p $(OBJDIR)/command
#	$(CPP) $(DEF) $(INCLUDES) -o $@ -c $<


# Including and ignore .dep files when they are not found
-include $(DEPS)

# ******** ******** ******** ******** **** ******** ******** ******** ******** #
