<a name="menu"></a>
Java Threads:
1. [Java Threads Introduction](#introduction)
2. [Create Java Threads](#create)
3. [Introduction to Amazon Simple Storage Service](#s3)
4. [Introduction to Amazon Redshift](#redshift)
5. [Intro to Amazon Machine Learning](#introml)
6. [Build a Machine Learning Model](#buildml)
7. [AWS SageMaker Overview](#viewsegmaker)
8. [AWS SageMaker](#segmaker)
9. [Build a Serverless Real-Time Data Processing APP](#app)

<a name="introduction"></a>
> Introduction to Java Threads
[Back to Menu](#menu)
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



<a name="create"></a>
> How to create threads in Java by extending Thread class
[Back to Menu](#menu)

### Creating Threads
* There are two ways to create our own Thread object
 1. Subclassing the Thread class and instantiating a new object of that class
 2. Implementing the Runnable interface
* In both cases the run() method should be implemented.
* Implementing extend Thread:
```
class MyClass extends Thread {
 // In IDEA, click Generate -> Override Method -> run():void to generate the run()
 public void run() {
  for(int i = 0; i < 10; i++){
   System.out.println(Threading.currentThread().getID() + "Value " + i)
  }
  // Set the running time concurrency
  try{
   Thread.sleep(1000);
  } catch (InterruptedException e) {
   e.printStackTrace();
  }
}

public class Demo {
 public static void main(String[] args) {
  MyClass myClass = new MyClass();
  MyClass myClass1 = new MyClass();
  // .start() will lets you create the thread and if you just use the run() in MyClass there is no diff with normal class
  myClass.start();
  myClass1.start();
 }
}
'''
