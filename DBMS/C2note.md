### Architecture and Clssification of DBMSs
* mongoose is a MongoDB object modeling tool designed to work in an asynchronous environment
* MongoDB is a DBMS
> Architecture of a DBMS

### D I A D
* Data Definition Language(DDL) statement 
* Interactive Query
* Applications
* Database Tools

### DBMS Interfaces

### DBMS
* Connection Manager: provides facilities to setup a database connection(locally or through a network)
  * verifies logon credentials and returns a connection handle
  * database connection can either run as single process or as thread within a process
* Security Manager: verifies whether a user has the right privileges
  * read versus write access
* DDL compiler
* Database utilities

* Query Processor
  * DML compiler
  * Query parser
  * Query rewriter
  * Query optimizer
  * Query executor

* Storager Manager
  * Transaction Manager
  * Buffer Manager
  * Lock Manager
  * Recovery Manager

### Database
* raw data
* indices
* catalog

