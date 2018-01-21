#anydbm

anydbm is a front-end for DBM-style databases that use **simple string values as keys** to access records containing strings. It uses the **whichdb** module to identify **dbhash**, **gdbm**, and **dbm** databases, then opens them with the appropriate module. It is used as a backend for shelve, which knows how to store objects using pickle.

##Creating a New Database
The storage format for new databases is selected by looking for each of these modules in order:

	dbhash
	gdbm
	dbm
	dumbdbm
The **open()** function takes flags to control how the database file is managed. To create a new database when necessary, use **'c'**. To always create a new database, use **'n'**.

	import anydbm
	
	db = anydbm.open('/tmp/example.db', 'n')
	db['key'] = 'value'
	db['today'] = 'Sunday'
	db['author'] = 'Doug'
	db.close()
	
In this example, the file is always re-initialized. To see what type of database was created, we can use **whichdb**.

	import whichdb
	print whichdb.whichdb('/tmp/example.db')

Your results may vary, depending on what modules are installed on your system.

	$ python anydbm_whichdb.py
	dbhash

## Opening an Existing Database

To open an existing database, use flags of either **'r'** (for read-only) or **'w'** (for read-write). You don’t need to worry about the format, because existing databases are automatically given to **whichdb** to identify. If a file can be identified, the appropriate module is used to open it.

	import anydbm

	db = anydbm.open('/tmp/example.db', 'r')
	try:
	    print 'keys():', db.keys()
	    for k, v in db.iteritems():
	        print 'iterating:', k, v
	    print 'db["author"] =', db['author']
	finally:
	    db.close()
Once open, **db** is a dictionary-like object, with support for the usual methods:

	$ python anydbm_existing.py
	
	keys(): ['author', 'key', 'today']
	iterating: author Doug
	iterating: key value
	iterating: today Sunday
	db["author"] = Doug
	
##Error Cases

The keys of the database need to be **strings**.

	import anydbm
	
	db = anydbm.open('/tmp/example.db', 'w')
	try:
	    db[1] = 'one'
	except TypeError, err:
	    print '%s: %s' % (err.__class__.__name__, err)
	finally:
	    db.close()
Passing another type results in a **TypeError**.

	$ python anydbm_intkeys.py
	
	TypeError: Integer keys only allowed for Recno and Queue DB's
Values must be strings or **None**.

	import anydbm
	
	db = anydbm.open('/tmp/example.db', 'w')
	try:
	    db['one'] = 1
	except TypeError, err:
	    print '%s: %s' % (err.__class__.__name__, err)
	finally:
	    db.close()

A similar *TypeError* is raised if a value is not a **string**.

	$ python anydbm_intvalue.py
	
	TypeError: Data values must be of type string or None.