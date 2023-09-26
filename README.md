# IPC-Threads

Part 1:

We have a function which calculates the sum within the determined limits .

We declared a pipe to use it writing and reading the bounded sum.

When it is the child, we calculate the inner pipe and write.

When it is the parent, we read the bounded sum and calculate the sum.

Finally, we calculate the execution time.

Part 2:

We have a struct that have two member variables which are lower bound and upper bound which will represent the limits of each thread.

We have a function which calculates the sum within the determined limits and it contols the mutex in case we are using it.

After taking the number of threads and T from the user we divide x = threadsNum / T to get how many elements we will jump each thread.

Then we initialize an array of instances of the bound struct and create an array of threads.

We loop over the threads (i=0 till threadsnum-1)

We calculate the lower bound and the upper bound of the thread.

We create the thread and pass the function and the bounds to it.

Then we wait for the thread to terminate.

Finally, we calculate the execution time.

