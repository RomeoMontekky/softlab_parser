@echo off

set TEST_COMMAND=..\bin\softlab_parser.exe

set SUCCESSFUL_TESTS=0
set FAILED_TESTS=0

call :run_one_test error_no_input_file
for %%f in (*.in) do ( call :run_one_test %%~nf )

echo ---------------------------------------
echo Successful tests - %SUCCESSFUL_TESTS%, Failed tests - %FAILED_TESTS%
goto :eof

:run_one_test
%TEST_COMMAND% %1.in %1.out> %1_log.out 2>&1
echo n | comp %1_log.out %1_log.exp > NUL 2> NUL

if ERRORLEVEL 1 (
   echo %1 ... Fail & set /a FAILED_TESTS=%FAILED_TESTS%+1 & goto :eof
) else (
   del %1_log.out

   if exist %1.out (
      echo n | comp %1.out %1.exp > NUL 2> NUL
      if ERRORLEVEL 1 (echo %1 ... Fail & set /a FAILED_TESTS=%FAILED_TESTS%+1 & goto :eof)
      del %1.out
   )
)

echo %1 ... OK & set /a SUCCESSFUL_TESTS=%SUCCESSFUL_TESTS%+1

goto :eof

