Open linreg_run.sh with any editor. Set the number of rows, columns and columns of alice with ROW, COL and COLA respectively.

Add files x_file.txt and y_file.txt to this folder so that the input can read the data from.

In default files for "auto" data set are loaded for testing purposes. This data set has 398 rows and 7 columns. Alice has 3 and Bob has 4.

An R script is provided that explains how these files are created from the original csv files.

Some of the data sets and their x_file.txt , y_file.txt and beta_file.txt are provided under the a folder called "Data".

The rest used in our paper can be downloaded from this link: https://drive.google.com/file/d/0BwUgxpKu54_lX0dHdURVM3QwS1E/view?usp=sharing

First compile all c++ files:
./linreg_compile.sh all
Then, run all:
./linreg_run.sh all

After that compare values in beta_file.txt with sec_beta file available in the bin folder.

We use 50 iterations thus 100 multiplication protocols while computing the inversion.
First runtime is for computing X^T * T
the next 50 are for computing the trace of the resulting matrix
the next 50 are for computing the inverse
the next one is for multiplying the current matrix with X^T
and the last one is for multiplying the current matrix with Y.
The result matrix is beta values which are stored at sec_beta file in the bin folder.

We wait 2 seconds between running alice and bob. The only reason is that we want to run alice before bob and sometimes if we run them instantly after one another, constructor for alice could finish later than bobs which could cause issues.

In the include folder, in file protocol_message.hpp the maximum message size in bytes that we are able to send between alice and bob can be set. For large data sets this should be increased up to the desirable value (100GB should be enough for current data sets, default is set to 1GB).

This code is partly contains Bernardo David's code for secure linear algebra. We thank him for providing his useful code that we built our code on top of.
