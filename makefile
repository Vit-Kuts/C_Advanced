all:course_project
course_project: main.o flags.o
	gcc -o course_project main.o flags.o

flags.o: flags.c
	gcc -c -o flags.o flags.c

main.o: main.c
	gcc -c -o main.o main.c

clean:
	del *.o
	del *.exe

clean_object:
	del *.o
