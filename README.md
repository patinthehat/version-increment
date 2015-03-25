## version-increment ##
---


`version-increment` is a small utility written in c that allows for automation of increasing version numbers.
`version-increment` works with <a href="http://www.semver.org">semantic version</a> valid version strings.


Syntax:<br/>

  `version-increment` [version-number] [index to increment] [increment by] - increments the specified field by specified amount.<br/>
1. major is index 0<br/>
2. minor is index 1<br/>
3. patch is index 2<br/>



	`version-increment` [version-number] [increment by] - increments patch level by specified number<br/>
	`version-increment` [version-number]` - increments the patch level by 1<br/>
	Specifying the version number as "-" will cause `version-increment` to read <br/>
	  the version number from STDIN.<br/>
<br/>

Some examples:<br/>
	- `version-increment 1.0.0` outputs `1.0.1`<br/>
	- `version-increment 2.0.0 0 1` outputs `3.0.0`<br/>
	- `printf "1.2.3" | build/version-increment -` outputs `1.2.4`<br/>
---

### Getting started ###
Once in the project folder, run `./build.sh` to compile the project.  
The compiled binary will be in `./build`.

You can also run `./build.sh install` and the script will attempt to 
install the binary into `/usr/bin`.

Finally, you can run `./build.sh archive` and the script will generate
 an archive ready for release in the `./build/` folder.

---

### License ###

`version-increment` is licensed under the <a href="LICENSE">MIT</a> license.