This is a "port" of GNU Chess 5.05 to OS/400. It contains only the source files
necessary to compile a runnable program object. The orignal code can be obtained
at https://ftp.gnu.org/gnu/chess/gnuchess-5.05.tar.gz.

## License.
The GNU Chess original license applies, which is the GPL version 2, or later.
This document is part of the GNU Chess AS/400 port, to be found on
[GitHub](https://github.com/PoC-dev/gnuchess-as400). Its content is subject to
the [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/) license,
also known as *Attribution-ShareAlike 4.0 International*.

## Compatibility.
The necessary C files have been treated with `indent`, and manually opimized to
nicely wrap into 80 characters. No further changes were necessary.

Because OS/400 lacks a proper shell, and common UNIX utilities, the *config.h*
had to be generated manually. The sources have been tested to compile in OS/400
V4R4, and later.

Unfortunately, this version can't be compiled for V3. The source code makes use
of 64 bit integer values, and teh C compiler for V3 doesn't understand `long
long int`.

Only minimal testing of the resulting program has been done. Especially
functions which open files might have hard coded paths which usually don't exist
in OS/400.

## Setup, terse.
- Create necessary objects, and upload:
```
ftp myas400 < ftpupload.txt
```
- Compile as per instructions in the REXX *make* script:
```
sbmjob cmd(strrexprc srcmbr(make) srcfile(gnuchess/qrexsrc)) job(cmplchess)
```
- Run it:
```
call pgm(gnuchess/gnuchess)
```

Usage instructions can be found online at
[www.gnu.org](https://www.gnu.org/software/chess/manual/). Many of the options
are valid for the older version.

----

2025-01-26 poc@pocnet.net
