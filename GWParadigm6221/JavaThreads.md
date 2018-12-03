### Multitasking and Multithreading
* Multitasking refers to a computer's ability to perform multiple jobs concurrently: more than one program are running concurrently, e.g UNIX.
* A thread is a single sequence of execution within a program.
* Multithreading refers to multiple threads of control within a single program: each program can run multiple threads of control within it.

### Concurrency vs Parallelism
* dependent or independet

### Threads and Processes
* An executing instance of a program is called a process. A thread is a subset of the process
* Threads share the address space of the process that created it, processes have their own address space.

### Threads Pros
* To maintain responsiveness of an application during a long running task
* To enable cancellation of separable tasks.
* Some problems are intrinsically parallel.
* To monitor status of some resource (DB)
* Some APIs and systems demand it: Swing.

### Application Thread
* When we execute an application:
  * The JVM creates a Thread object whose task is defined by the main() method.
  * It starts the thread
  * The thread executes the statement of the program one by one until method returns and the thread dies.

### Multiple Threads in an Application
* Each thread has its private run-time stack
* If two thread execute the same method, each will have its own copy if the local variables the methods uses
* However, all threads see the same dynamic memory(heap)
* Two different threads can act on the same object and same static fields concurrently

### Creating Threads
* There are two ways to create our own Thread object
  1. Subclassing the Thread class and instantiating a new object of that class
  2. Implementing the Runnable interface
  
