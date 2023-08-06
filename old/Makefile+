# ********************** Section for Macros (Variables) ********************** #
# Product file
NAME            = ircserv

# Enumeration of files
SRC             = main.cpp server.cpp message.cpp
COMMAND_SRC     = privmsg.cpp

# Check the platform
OS              = $(shell uname)

# Enumeration of directories
SRCDIR          = ./src
INCDIR          = ./include
OBJDIR          = ./obj
COMMAND_DIR     = $(SRCDIR)/command

# Aliases of commands
CPP             = c++
RM              = rm

# Command options (flags)
CPPFLAGS        = -Wall -Wextra -Werror -std=c++98
INCLUDES        = -I$(INCDIR)
RMFLAGS         = -r
DEBUGCFLAGS     = -g -ggdb -fno-omit-frame-pointer
ifneq ($(OS), Darwin)
    DEBUGCFLAGS += -fstack-usage
endif
DEBUGLDFLAGS    = -fsanitize=address

# Redefination when the specific target
ifeq ($(MAKECMDGOALS), debug)
    ifneq ($(OS), Darwin)
        CPPFLAGS    += $(DEBUGCFLAGS)
        LDFLAGS += $(DEBUGLDFLAGS)
    endif
    DEF         += -D DEBUG_MODE=1
endif

# Macros to replace and/or integrate
SRCS            = $(addprefix $(SRCDIR)/, $(SRC)) $(addprefix $(COMMAND_DIR)/, $(COMMAND_SRC))
OBJS            = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
OBJS            += $(patsubst $(COMMAND_DIR)/%.cpp,$(OBJDIR)/command/%.o,$(COMMAND_SRC))
DEPS            = $(OBJS:.o=.d)

# ********************* Section for targets and commands ********************* #
# Phonies
.PHONY: all clean fclean re debug

# Mandatory targets
all: $(NAME)
clean:
	-$(RM) $(RMFLAGS) $(OBJDIR)
fclean: clean
	-$(RM) $(RMFLAGS) $(NAME)
re: fclean all

# Additional targets
debug: fclean all

# Recipes
$(NAME): $(OBJS)
	$(CPP) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CPP) $(CPPFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<

$(OBJDIR)/%.o: $(SRCDIR)/command/%.cpp | $(OBJDIR)
	@mkdir -p $(OBJDIR)/command
	$(CPP) $(CPPFLAGS) $(DEF) $(INCLUDES) -o $@ -c $<


$(OBJDIR):
	@mkdir -p $@

# Including and ignore .dep files when they are not found
-include $(DEPS)
