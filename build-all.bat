:: This does not work how I want it to.
:: More research needs to be done before this does what I want
:: The idea is to loop through all the 'projects' and build them.  This happens to build a lot more than I want

:: FOR /R "projects" %%i IN (*) DO (
::     build.bat win %%~ni
::     build.bat web %%~ni
::     )
:: 