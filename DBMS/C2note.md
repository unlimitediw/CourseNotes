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
  * Compiles the data definitions specified in DDL
  * Ideally 3 DDLs(internal/logical/external data model)
  * DDL compiler first parses the DDL definitions and checks their syntactical correctness.
  * DDL compiler then translates the data definitions to an internal format and generates errors if required
  * Upon successful compilation, DDL compiler registers the data definitions in the catalog.
* Database utilities

* Query Processor: assists in the execution of database queries such as retrieval, insertion, update or removal of data.
  * DML(data manipulation language) compiler
    * Procedural DML
      * DML explicitly specifies how to navigate in the database
      * record at a time DML
      * no query processor
    * Declarative DML
      * DML specifies what data should be retrieved or what changes should be made
      * set at a time DML
      * query processor
    * Impedance mismatch problem: 
      * e.g: mapping between OO(java) and relational(SQL) concepts
      * Solution: host language and DBMS with comparable data structures(JAVA - OODBMS, JS-mongoose), middleware to map the data structures from the DBMS to the host language and vice versa.
    * DML compiler starts by extracting the DML statements from the host language
    * DML compiler then collaborates with the query parser, query rewriter, query optimizer and query executor for executing the DML statements.
    * Errors are generated and reported if necessary
  * Query parser
    * Query Parser parses the query into an internal representation format
    * Query parser checks the query for syntactical and semantical correctness
  * Query rewriter
    * Query rewriter optimizes the query, independently of the current database state.
  * Query optimizer
    * Query optimizer optimizes the query based upon the current database state
    * Query optimizer comes up with various query execution plans and evaluates their cost in terms of estimated(# of I/O operations, CPU processing cost, execution time)
    * Estimates based on catalog information combined with statical inference
  * Query executor
    * Result of query optimization is a final execution plan
    * Query executor takes care of the actual execution by calling on the storage manager to retrieve the data requested.
* Storager Manager: governs physical file access and supervises the correct and efficient storage of data
  * Transaction Manager
  * Buffer Manager
  * Lock Manager
  * Recovery Manager

### Database
* raw data
* indices
* catalog

