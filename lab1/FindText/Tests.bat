@echo off

SET MyProgram="%~1"


REM ДОБАВИТЬ ТЕСТ С ПУСТОЙ СТРОКОЙ + ПУСТОЙ СТРОКОЙ

REM if input a word that is not in the text
%MyProgram% input2.txt "стоял" && goto err
echo test 1 passed

REM correct input
%MyProgram% input1.txt "вы" || goto err
echo test 2 passed

REM correct input
%MyProgram% input1.txt "Сергей Есенин" || goto err
echo test 3 passed

REM if text not specified, program must fail
%MyProgram% input1.txt && goto err
echo test 4 passed

REM if input no arguments
%MyProgram% && goto err
echo test 5 passed

REM if input file not specified, program must fail
%MyProgram% "Вы" && goto err
echo test 6 passed

REM Тесты прошли успешно
echo all tests passed
exit /B 0

REM ошибка
:err
echo Test failed
exit /B 1