@echo OFF

SET MyProgram="%~1"

REM correct input
%MyProgram% matrix1.txt || goto err
echo test 1 passed

REM input incorrect matrix
%MyProgram% matrix2.txt && goto err
echo test 2 passed

REM empty file
%MyProgram% matrix3.txt && goto err
echo test 3 passed

REM the determinant of the matrix is 0
%MyProgram% matrix4.txt || goto err
echo test 4 passed

REM the determinant of the matrix is 0
%MyProgram% matrix5.txt && goto err
echo test 5 passed

REM empty input
%MyProgram%  && goto err
echo test 6 passed

echo All tests passed
exit /B 0

:err
echo Test failed
exit /B 1

