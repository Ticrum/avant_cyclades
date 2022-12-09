out=avant_cyclades
src=$(shell find src/ -name "*.c")
header=$(shell find include -name "*.h")
obj=$(src:.c=.o)
lib=lib$(out).so
sta=lib$(out).a
libpath= -I ../include/
tempath=-L./objects/label/
rpath=-Wl, -rpath,/objects/label/
flag= -W -Wall -std=c11 -g -O3
link= -llapin -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lstdc++ -lm -ldl -lpthread -lopencv_imgproc -lopencv_objdetect -lopencv_video -lopencv_core -lavcall -lusb
user=$(shell printenv USER)

all: cc

cc: $(out)

$(out): $(obj)
	gcc $(obj) ../libcyclades.a -o $(out) $(libpath) $(flag) $(link)

instal: dy
	mkdir -p ~/.froot/lib ~/.froot/include
	cp $(lib) ~/.froot/lib
	cp $(header) ~/.froot/include

instalsta: sta
	mkdir -p ~/.froot/lib ~/.froot/include
	cp $(sta) ~/.froot/lib
	cp $(header) ~/.froot/include

expsta:
	export C_INCLUDE_PATH=/home/users/$(user)/.froot/include
	export LIBRARY_PATH=/home/users/$(user)/.froot/lib
	export CPLUS_INCLUDE_PATH=/home/users/$(user)/.froot/include

expdy:
	export LD_LIBRARY_PATH=/home/users/$(user)/.froot/lib
	export C_INCLUDE_PATH=/home/users/$(user)/.froot/include

dy: $(obj)
	gcc -shared -o $(lib) $(obj)

sta: $(obj)
	ar cr $(sta) $(obj)

cldy: cl
	rm -f ~/.froot/lib/$(lib)
	rm -f ~/.froot/$(header)

clsta: cl
	rm -f ~/.froot/lib/$(sta)
	rm -f ~/.froot/$(header)

cl:
	@rm -f $(out)
	@rm -f src/*~
	@rm -f include/*~
	@rm -f *~
	@rm -f vgcore*
	@rm -f $(obj)
	@rm -f $(lib)
	@rm -f $(sta)

.c.o:
	gcc -c $< $(libpath) -o $@ -fpic $(flag)

re: cl all

resta: cl sta

redy: cl dy

reinstal: cldy instal

reinstalsta: clsta instalsta
