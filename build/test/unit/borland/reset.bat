:: run this file if sysid.inc or depends.inc breaks
@if exist ..\Makefiles echo. > ..\Makefiles\borland\sysid.inc
@if exist ..\..\Makefiles echo. > ..\..\Makefiles\borland\sysid.inc
@if exist ..\..\..\Makefiles echo. > ..\..\..\Makefiles\borland\sysid.inc
@if exist .\Makefile.inc echo. > borland\depends.inc
@if exist ..\Makefile.inc echo. > depends.inc
