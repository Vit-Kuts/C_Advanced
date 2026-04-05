all:course_project
course_project: main.o flags.o calculate.o root.o integral.o test.o
	gcc -o course_project main.o flags.o calculate.o root.o integral.o test.o

flags.o: flags.c
	gcc -c -o flags.o flags.c

calculate.o: calculate.c
	gcc -c -o calculate.o calculate.c

integral.o: integral.c
	gcc -c -o integral.o integral.c

root.o: root.c
	gcc -c -o root.o root.c

test.o: test.c
	gcc -c -o test.o test.c

main.o: main.c
	gcc -c -o main.o main.c

clean:
	del *.o
	del *.exe

clean_object:
	del *.o
