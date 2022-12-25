all:
	gcc ls.c -o ls
	gcc rm.c -o rm
	gcc date.c -o date
	gcc cat.c -o cat
	gcc mkdir.c -o mkdir
	gcc shell.c -o shell
	./shell
	make clean

# shell2:
# 	gcc ls.c -o ls
# 	gcc rm.c -o rm
# 	gcc date.c -o date
# 	gcc cat.c -o cat
# 	gcc mkdir.c -o mkdir
# 	gcc shell2.c -o shell2
# 	./shell2
# 	make clean

clean:
	rm -f ls rm date cat mkdir
	rm -f shell
#	rm -f shell2