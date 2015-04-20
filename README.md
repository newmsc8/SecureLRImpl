# SecureLRImpl

How to run this code:

In the main folder (the folder this file is located) compile all the codes:

./linreg_compile.sh all

Then run the offline stage:

./linreg_run.sh pre

Since this protocol has two players, in one tab run:

./linreg_run.sh alice

and then in another tab run:

./linreg_run.sh bob

Finally to test run:

./linreg_run.sh test

Now go to Bin/Linreg/ folder and compare "output" and "trunc_out" files to see the initial output and post-truncation output


