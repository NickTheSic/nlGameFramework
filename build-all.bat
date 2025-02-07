FOR /R "projects" %%i IN (*) DO (
    build.bat win %%~ni
    build.bat web %%~ni
    )
