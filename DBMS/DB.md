> Learning outcome

* OLTP online transaction processing database
* Oracle database
* SQL language: DDL, DML, DCL and transaction control commands.
* Database programs using JDBC and ODBC.
* Database implementation, integrity and security.
* XML, JSON.
* Evaluate text search tech using Lucene in RDS.
* Hadoop.
* Datawarehouse database design.
* AWS RDS.
* Install database server in AWS EC2 instances.
* Build, deploy and maintain DB.

> AWS

* [EC2 Elastic Computing](https://blackboard.gwu.edu/bbcswebdav/pid-9274798-dt-content-rid-60722846_2/courses/41475_201901/ec2-ug.pdf)
* VPC Virtual Private Cloud [ug](https://blackboard.gwu.edu/bbcswebdav/pid-9274798-dt-content-rid-60722847_2/courses/41475_201901/vpc-ug.pdf) [ag](https://blackboard.gwu.edu/bbcswebdav/pid-9274798-dt-content-rid-60722849_2/courses/41475_201901/vpc-nag.pdf)
* [RDS Relational Database Service](https://blackboard.gwu.edu/bbcswebdav/pid-9274798-dt-content-rid-60722848_2/courses/41475_201901/rds-ug.pdf)
* [S3 Simple Storage Service](https://blackboard.gwu.edu/bbcswebdav/pid-9274798-dt-content-rid-60722850_2/courses/41475_201901/s3-user-guide.pdf)

> Application of DB Technology

* Storage and retrieval of taditional numeric and alphanumeric data in an inventory apploication.
* Multimedia applications(picture, audio, video)
* Biomtric applications(fingerprints, retina scans)
* Wearable applications(FitBit, Apple Watch)
* Geographical Information System(GIS) applications(Google Maps)
* Sensor applications(nuclear reactor)
* Big Data applications(Walmart)
* Internet of Things(IoT) applications(Telematics)

> Definitions

* Database is a collection of related data items within a specific business process or problem setting.
  * Has a target group of users and applications.
* A Database Management System(DBMS) is the software package used to define, create, use and maintain a database.
  * Consists of several software modules
* Combination of DBMS and database is called database system.

> VPC

> Data Model

* A conceptual data model provides a high-level description of the data items with their characteristics and relationships
  * Communication instrument between information architect and business user.
  * Should be implementation independent, user-friendly, and close to how the business user perceives the data.
  * Usually represented using an Enhanced-Entity Relationship(EER) model or an object-oriented model.

* Logical data model is a translation or mapping of the conceptual data model towards a specific implementation environment
  * Can be hierarchical, CODASYL, relational, object-oriented, extended relational, XML or NoSQL model

* Logical data model can be mapped to an internal data model that represents the data's physical storage details
  * Clearly describes which data is stored where, in what format, which indexes are provided to speed up retrieval
  * Highly DBMS specific
  
* External data model contains various subsets of the data items in the logical model, also called views, tailored toward the needs of specific applications or groups of users.

> Three Layer Architecture

* External Layer: views, external/logical mapping to next layer(logical data independence)
* Conceptual/Logical Layer: data items, logical/internal mapping to next layer(physical data independence)
* Internal Layer: Files, Disk and Cloud

> Catalog

* Heart of the DBMS
* Contains the data definitions, or metadata, of your database application
* Stores the definitions of the views, logical and internal data models, and synchronizes these three data models to make sure their consistency is guaranteed.

> Database Users(procedure)

* Information architect designs the conceptual data model.
* Database designer translates the conceptual data model into a logical and internal data model.
* Database administrator(DBA) is responsible for the implementation and monitoring of the database.
* Application developer develops database applications in a programming language such as Java or Python.
* Business user will run these applications to perform specific database operations.

> Database Languages

* Data Definition Language(DDL) is used by the DBA to express the database's external, logical and interal models.
  * Definitions are stored in the catalog.
* Data Manipulation Language(DML) is used to retrieve, insert, delete and modify data.
  * DML statements can be embedded in a programming language, or entered interactively through a front-end querying tool.
* Structuered Query Language(SQL) offers both DDL and DML statements for relational database systems.

> Advantages of Database Systems and Database Management

* Data Independence
* Database Modelling
* Managing Structured, Semi-Structured and Unstructured Data
* Managing Data Redundancy
* Specifying Integrity Rules
* Concurrency Control
* Backup and Recovery Facilities
* Data Security
* Performance Utilities

> Data Independence

* Data independence implies that changes in data definitions have minimal to no impact on the applications.
* Physical data independence implies that neither the applications, nor the views or logical data model must be changed when changes are made to the data storage specifications in the internal data model.
  * DBMS should provide interfaces between logical and internal data models
* Logical data independence implies that software applications are minimally affected by changes in the conceptual or logical data model
  * Views in the external data model will act as a protective shield
  * DBMS must provide interfaces between conceptual/logical and external layer
  
> Database Modelling

* A data model is an explicit representation of the data items together with their characteristics and relationships
* A conceptual data model should provide a formal and perfect mapping of the data requirements of the business process and is made in collaboration with the business user
  * translated into logical and internal data model.
* Important that a data model's assumptions and shortcomings are clearly documented

> Managing Sturctured, Semi Structured and Unstructured Data
* Structured data
  * can be described according to a formal logical data model
  * ability to express integrity rules and enforce correctness of data
  * also facilitates searching, processing and analyzing the data

* Unstructured data
  * no finer grained components in a file or series of characters that can be interpreted in a meaningful way by a DBMS or application.
  * Note: volume of unstructured data surpasses that of structured data.

* Semi-structured data
  * data which does have a certain structure, but the structure may be very irregular or highly volatile
 
> Managing Data Redundancy
* Duplication of data can be desired in distributed environments to improve data retrieval performance
* DBMS is now responsible for the management of the redundancy by providing synchronization facilities to safeguard data consistency
* Compared to the file approach, the DBMS guarantees correctness of the data without user intervention

> Specifying Integrity Rules
* Syntactical rules specify how the data should be represented and stored.
* Semantical rules focus on the semantical corretness or meaning of the data
* Integrity rules are specified as part of the conceptual/logical data model and stored in the catalog

> Concurrency Control
* DBMS has built in facilities to support concurrent or parallel execution of database programs.
* Database transaction: sequence of read/write operations considered to be an atomic unit in the sense that either all operations are executed or none at all.
* Read/write operations can be executed at the same time by the DBMS
* DBMS should avoid inconsistencies
* DBMS must support ACID(Atomicity, Consistency, Isolation, Durability) properties
  * Atomicity requires that a transaction should either be executed in its entirety or not all
  * Consistency assures that a transaction brings the database from one consistent state to another
  * Isolation ensures that the effect of concurrent transactions should be the same as if they would have been executed in isolation
  * Durability ensures that the databse changes made by a transaction declared can be made permanent under all circumstances.

> Backup and Recovery Facilities
* Backup and recovery facilities can be used to deal with the effect of loss of data due to hardware or network errors, or bugs in system or application software.
* Backup facilities can either perform a full or incremental backup.
* Recovery facilities allow to restore the data to a previous state after loss or damage occurred.

> Data Security
* Data security can be enforced by the DBMS.
* Some users have read access, whilst others have write access to the data(role-based functionality.
* Data access can be managed via logins and passwords assigned to users or user account.
* Each account has its own authorization rules that can be stored in the catalog.

> Performamnce Utilities
* Three KPIs of a DBMS:
  * response time denoting the time elapsed between issuing a database request and the successful termination thereof.
  * throughput rate representing the transactions a DBMS can process per unit of time
  * space utilization referring to the space utilized by the DBMS to store both raw data and metadata.
* DBMSs come with various types of utilities aimed at improving these KPIs
