all:
	ln utils.h lab1/adversary/utils.h
	ln utils.h lab1/transmitter/utils.h
	ln utils.h lab2/master/utils.h
	ln utils.h lab2/slave/utils.h

clean:
	rm -f lab1/adversary/utils.h lab1/transmitter/utils.h lab2/master/utils.h lab2/slave/utils.h

# works for linux
# on windows those same commands work, at least for me :)