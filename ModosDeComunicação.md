**Modos de comunicação**
*OpenMP vs MPI*

OpenMP is a way to program on shared memory devices. This means that the parallelism occurs where every parallel thread has access to all of your data.

You can think of it as: parallelism can happen during execution of a specific for loop by splitting up the loop among the different threads.

MPI is a way to program on distributed memory devices. This means that the parallelism occurs where every parallel process is working in its own memory space in isolation from the others.


Because our project will have devices with independent memories the best comunication mode to implement is MPI.


*MPI vs Other Alternatives*

**WEBGRAFIA**:https://www.iottrends.tech/blog/how-to-cluster-raspberry-pi-4/
