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
  * Loading utility
  * Reorganization utility
  * Performance monitoring utilities
  * User management utilities
  * Backup and recovery utility

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
    * Supervises execution of database transactions: a database transaction is a sequence of read/write operations considered to be an atomic unit.
    * Creates a schedule with interleaved read/write operations
    * Guarantees ACID(Atomicity, Consistency, Isolation, Durability) properties
    * Commit a transaction upon successful execution and Rollback a transaction upon unsuccessful execution
  * Buffer Manager
    * Manages buffer memory of the DBMS and intelligently caches data in the buffer
    * Needs to adopt smart replacement strategy in case buffer is full
    * Buffer manager needs to interact with lock manager
  * Lock Manager
    * Lock manager provides concurrency control which ensures data integrity at all time.
    * Read and write locks.
    * Resposible for assigning, releasing, and recording locks in the catalog
    * Makes use of a locking protocol which describes the locking rules, and a lock table with the lock information.
  * Recovery Manager
    * Supervises the correct execution of database transactions
    * Keeps track of all database operations in a log file
    * Will be called upon to undo actions of aborted transactions or during crash recovery.
    

### Database
* raw data
* indices
* catalog

### Categorization of DBMSs
* Based on data model
  * Hierarchical DBMSs (e.g [IMS](https://www.ibm.com/support/knowledgecenter/en/SSMKHH_10.0.0/com.ibm.etools.mft.doc/ac66140_.htm) )
    * adopt a tree like data model
    * DML is procedural and record oriented
    * no query processor(logical and internal data model intertwined)
  * Network DBMSs
    * use a network data model
    * [CODASYL](https://en.wikipedia.org/wiki/CODASYL) DBMS
    * DML is procedural and record oriented
    * no query processor(logical and internal data model intertwined)
    * (computer associates)[CA-IDMS](https://en.wikipedia.org/wiki/IDMS)
  * Relational DBMSs(e.g MySQL, Oracle DBMS, IBM DB2, MicrosoftSQL)
    * use the relational data model
    * currently the most popular in industry
    * SQL(declarative and set oriented)
    * query processor
    * strict separation between the logical and internal data model
  * Object-Oriented DBMSs(OODBMS)(e.g db4o)
    * based upon the OO data model
    * no impedance mismatch in combination with OO host language
    * complex
  * Object-Relational DBMSs(ORDBMS)(e.g Oracle DBMS, DB2, MicrosoftSQL)
    * extended relational DBMS(ERDBMS)
    * use a relational model extended with OO concepts
    * DML is SQL(declarative and set oriented)
  * XML DBMS
    * use XML data model to store data
    * native XML DBMS map the tree structure of an XML document to a physical storage structure
    * XML-enabled DBMS(Oracle DBMS, DB2)
  * NoSQL DBMSs(e.g Apache Hadoop, MongoDB, Neo4j)
    * targeted at storing big and unstructured data
    * can be classified into key-value stores, column oriented databases and graph databses
    * focus on scalability and the ability to cope with irregular or highly volatile data srtuctures.
* Based on degree of simultaneous access
  * Single user versus multi user systems
* Based on architecture
  * Centralized DBMS architecutre
    * data is maintained on a centralized server
  * Client server DBMS architecture
    * active clients request services from passive servers
    * fat server versus fat client variant
  * n-tier DBMS architecture
    * client with GUI functionality, application server with applications, databse server with DBMS and database, and web server for web based access
  * Cloud DBMS architecutre(AWS Redshift, Apache Cassandra, Google BigTable)
    * DBMS and database are hosted by a third party cloud provider
  * Federated DBMS
    * provides a uniform interface to multiple underlying data sources
    * hides the underlying storage details to facilitate data access.
  * in-memory DBMS(e.g HANA)
    * stores all data in internal memory instead of slower external storage
    * often used for real time purposes
* Based on usage
  * On-line transaction processing(OLTP)
    * focus on managing operational or transactional data
    * database server must be able to process lots of simple transactions per unit of time
    * DBMS must have good support for processing a high volume of short, simple queries
  * On-line analytical processing(OLAP)
    * focus on using operational data for tactical or strategical decision making
    * limited number of users formulates complex queries
    * DBMS should support efficient processing of complex queries which often come in smaller volumes.
  * Big Data & Analyticcs
    * NoSQL databases
    * focus on more flexible, or even schema-less, database structures
    * store unstructued information such as emails, text documents, etc.
  * Multimedia
    * Multimedia DBMS provide storage of multimedia data such as text, images, audio, video...
    * should also provide content-based query facilities.
  * Spatial applicaition
    * spatial DBMSs support storage and querying of spatial data(both 2D or 3D)
    * Geographical information systems(GIS)
  * Sensoring
    * sensor DBMS manage sensor data such as biometric data from wearables or telematics data
  * Mobile
    * Mobile DBMSs run on smartphones, tablets or other mobile devices
    * should always be online, have a small footprint and be able to deal with limit processing power, storage and battery life
  * Open source
    * MySQL
