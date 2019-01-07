# JVM

> Class Loader
* Loading Java classes during runtime dynamically to the JVM (CL is part of JAR, Java Runtime Env)
1. An application or system class loader loads our own files in the classpath.
2. Extension class loaders load classes that are an extension of the standard core Java classes.
3. A bootstrap or primordial class loader is the parent of all other. (bootstrap class loader is written in native code, not Java)
* Delegation Model, Unique Classes, Visibility.


> JVM Memory
* Method Area: logical part of heap area, static fields and structures.
* Heap: runtime data area, memory for all class instances and arrays are allocated. (also has non heap memory)
* JVM Stacks: store stack frames (pushes or pops frames)
* PC(program counter) Registers: contains the address of the instruction currently being executed in its associated thread.
* Native Method Stacks: similar to JVM Stack and executing native (non-Java) methods.

> Execution Engine, Native Method Interface and Native Method Libraries

