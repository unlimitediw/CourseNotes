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
