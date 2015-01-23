This is what I saw when I build and run (./ake clean; ./ake):

	ceu learn_time.ceu
	bash cc learn_time.c -o learn_time
	./learn_time
one
dt 3000
two
dt 3000 <-- This is what I wasn't expecting to see.
three
dt 5000
four

This is with the fix Dr. Sant'anna added:
	ceu learn_time.ceu
	bash cc learn_time.c -o learn_time
	./learn_time
one
dt 3000ms
two
three
dt 5000ms
four
