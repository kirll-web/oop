@echo off

SET MyProgram="%~1"

REM if input a word that is not in the text
%MyProgram% in2.txt out.txt && goto err
echo test 1 passed
%MyProgram% out.txt && goto err
echo test 2 passed

%MyProgram% && err
echo test 3 passed

%MyProgram% in.txt out.txt || goto err
fc out.txt test.txt > nul || goto err
echo test 4 passed


echo all tests passed
exit /B 0
REM ошибка
:err
echo Test failed
exit /B 1


