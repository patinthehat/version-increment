## version-increment ##
---


`version-increment` is a small utility written in c that allows for automation of increasing version numbers.
`version-increment` works with <a href="http://www.semver.org">semantic version</a> valid version strings.


Syntax:<br>

  `version-increment` [version-number] [index to increment] [increment by] - increments the specified field by specified amount.<br>
  - major is index 0
  - minor is index 1
  - patch is index 2


`version-increment` [version-number] [increment by] - increments patch level by specified number<br>
`version-increment` [version-number] - increments the patch level by 1<br>
Specifying the version number as "-" will cause `version-increment` to read <br> the version number from STDIN.<br/>
<br>

Some examples:<br>
	- `version-increment 1.0.0` outputs `1.0.1`<br>
	- `version-increment 2.0.0 0 1` outputs `3.0.0`<br>
	- `printf "1.2.3" | version-increment -` outputs `1.2.4`<br>


`version-increment` also supports reading and writing to files.

Examples:
	- `version-increment` test.txt
	if test.txt contains 1.2.0, the new contents of test.txt will be "1.2.1".


---

### Getting started ###
Once in the project folder, run `./build.sh` to compile the project.  
The compiled binary will be in `./build`.

You can also run `./build.sh install` and the script will attempt to 
install the binary into `/usr/bin`.

Finally, you can run `./build.sh archive` and the script will generate
 an archive ready for release in the `./build/` folder.


### Example Usage ###
An example of using this utility would be automatically increasing a version number on every build.

*Sample Makefile entry*

```Makefile
all: init myproject
	@echo "\n* Compiled all targets for $(THISPROJECT) project."
	@version-increment myproject-version.txt
	@exit 0

init:
	@version-increment myproject-version.txt
	@printf "#define VERSION = %s\n" `cat versiontest.txt` > version.h	
	@exit 0

```

Here, each time `make` or `make all` is run, the various programs will be built, and then the version number will be increased.
Assuming `version.h` is included in myproject.c, the version for myproject would be automatically updated upon every build.

---

### License ###

`version-increment` is licensed under the <a href="LICENSE">MIT</a> license.