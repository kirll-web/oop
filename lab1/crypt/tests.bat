@echo OFF

SET MyProgram="%~1"

%MyProgram% "crypt" "text1.txt" "crypt1.txt" "2" || goto err
%MyProgram% "decrypt" "crypt1.txt" "decrypt1.txt" "2" || goto err
fc text1.txt decrypt1.txt > nul || goto err
echo test1 passed

%MyProgram% "crypt" "text2.txt" "crypt2.txt" "2" || goto err
%MyProgram% "decrypt" "crypt2.txt" "decrypt2.txt" "2" || goto err
fc text2.txt decrypt2.txt > nul || goto err
echo test2 passed

%MyProgram% "crypt" && goto err
echo test3 passed

%MyProgram% "crypt" "textasd2.txt" "crypt2.txt" "2" && goto err
echo test4 passed

%MyProgram% "crypt" "text2.txt" "crypasdt2.txt" "asd" && goto err
echo test5 passed

%MyProgram% "crypt" "text2.txt" "crypasdt2.txt" "256" && goto err
echo test6 passed

%MyProgram% && goto err
echo test7 passed

echo all tests passed
exit /B 0

:err
echo tests failed
exit /B1
