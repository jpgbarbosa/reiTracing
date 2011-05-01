############################################################################
#
#       Project		OpenGL demo make file with GNU gcc $Revision: 1.00 $ 
#	    
#       Author		W.B.Langdon at MUN 10 May 2007
#
############################################################################

NAME 	= glDrawPixels
OBJS 	= glDrawPixels.o

LIBS 	= -lm 
#LIBS 	= -lm -lC
CC 	= g++
#CC 	= cc
COMPILE = $(CC) -c $(CFLAGS)
#CFLAGS 	= -O5
CFLAGS 	= -g
LINK 	= $(CC) -o 
GL_LIBS = -lglu32 -lglut32 -lopengl32


$(NAME):$(OBJS) 
	$(LINK) $(NAME) $(LDFLAGS) $(OBJS) $(LIBS) $(GL_LIBS) 

#C++ source files

glDrawPixels.o:	glDrawPixels.cpp
	$(COMPILE) glDrawPixels.cpp