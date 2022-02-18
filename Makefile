knight: knight.c
	gcc knight.c -Wall -Werror -o knight

clean:
	rm -f knight *~ core output.txt
