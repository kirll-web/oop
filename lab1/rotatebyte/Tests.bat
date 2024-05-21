@echo OFF

SET MyProgram="%~1"

REM correct input
%MyProgram% 17 2 L || goto err
echo test 1 passed

REM correct input
%MyProgram% 5 2 R || goto err
echo test 2 passed

REM correct input
%MyProgram% 20 5 L || goto err
echo test 3 passed

REM  empty input
%MyProgram% 145 2 L || goto err
echo test 4 passed

REM  empty input
%MyProgram% 145 2 R || goto err
echo test 5 passed

REM correct input
%MyProgram% 21 3 R || goto err
echo test 6 passed

REM correct input
%MyProgram% 20 0 R || goto err
echo test 7 passed

REM  input letter instead of number
%MyProgram%  R R R  && goto err
echo test 8 passed

REM  not input L \ R
%MyProgram% 0 2 && goto err
echo test 9 passed

REM  incorrect input L \ R
%MyProgram% 0 2 S  && goto err
echo test 10 passed

REM  not input L \ R and number of bits
%MyProgram% 0  && goto err
echo test 11 passed

REM  empty input
%MyProgram% && goto err
echo test 12 passed

echo All tests passed
exit /B 0

:err
echo Test failed
exit /B 1

