@echo off
echo ================================================
echo          RUNNING ALL TESTS
echo ================================================

set SRC=src/BUYER.cpp src/CART.cpp src/USER.cpp src/PRODUCT.cpp src/PRODUCT_REPO.cpp src/BILL.cpp src/SELLER.cpp src/BILL_SERVICE.cpp src/AUTHORITY_SERVICE.cpp src/USER_ACCOUNT.cpp src/ConsoleHelper.cpp src/stringUtlis.cpp

set PASS=0
set FAIL=0

REM ── BILL_TEST ──────────────────────────────────────
echo.
echo [1/13] Running BILL_TEST...
g++ -std=c++17 test/BILL_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: BILL_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: BILL_TEST )

REM ── BILL_SERVICE_TEST ──────────────────────────────
echo.
echo [2/13] Running BILL_SERVICE_TEST...
g++ -std=c++17 test/BILL_SERVICE_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: BILL_SERVICE_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: BILL_SERVICE_TEST )

REM ── CART_TEST ──────────────────────────────────────
echo.
echo [3/13] Running CART_TEST...
g++ -std=c++17 test/CART_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: CART_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: CART_TEST )

REM ── PRODUCT_TEST ───────────────────────────────────
echo.
echo [4/13] Running PRODUCT_TEST...
g++ -std=c++17 test/PRODUCT_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: PRODUCT_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: PRODUCT_TEST )

REM ── PRODUCT_REPO_TEST ──────────────────────────────
echo.
echo [5/13] Running PRODUCT_REPO_TEST...
g++ -std=c++17 test/PRODUCT_REPO_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: PRODUCT_REPO_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: PRODUCT_REPO_TEST )

REM ── PRODUCT_SERVICE_TEST ───────────────────────────
echo.
echo [6/13] Running PRODUCT_SERVICE_TEST...
g++ -std=c++17 test/PRODUCT_SERVICE_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: PRODUCT_SERVICE_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: PRODUCT_SERVICE_TEST )

REM ── SELLER_TEST ────────────────────────────────────
echo.
echo [7/13] Running SELLER_TEST...
g++ -std=c++17 test/SELLER_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: SELLER_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: SELLER_TEST )

REM ── BUYER_TEST ─────────────────────────────────────
echo.
echo [8/13] Running BUYER_TEST...
g++ -std=c++17 test/BUYER_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: BUYER_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: BUYER_TEST )

REM ── ADMIN_TEST ─────────────────────────────────────
echo.
echo [9/13] Running ADMIN_TEST...
g++ -std=c++17 test/ADMIN_TEST.cpp %SRC% src/ADMIN.cpp -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: ADMIN_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: ADMIN_TEST )

REM ── USER_TEST ──────────────────────────────────────
echo.
echo [10/13] Running USER_TEST...
g++ -std=c++17 test/USER_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: USER_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: USER_TEST )

REM ── AUTHORITY_SERVICE_TEST ─────────────────────────
echo.
echo [11/13] Running AUTHORITY_SERVICE_TEST...
g++ -std=c++17 test/AUTHORITY_SERVICE_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: AUTHORITY_SERVICE_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: AUTHORITY_SERVICE_TEST )

REM ── USER_ACCOUNT_TEST ──────────────────────────────
echo.
echo [12/13] Running USER_ACCOUNT_TEST...
g++ -std=c++17 test/USER_ACCOUNT_TEST.cpp %SRC% -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: USER_ACCOUNT_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: USER_ACCOUNT_TEST )

REM ── SYSTEM_TEST ────────────────────────────────────
echo.
echo [13/13] Running SYSTEM_TEST...
g++ -std=c++17 test/SYSTEM_TEST.cpp %SRC% src/ADMIN.cpp src/SYSTEM.cpp -Iinclude -o test_run.exe 2>nul
if %errorlevel% == 0 (
    .\test_run.exe
    if %errorlevel% == 0 ( set /a PASS+=1 ) else ( set /a FAIL+=1 & echo FAILED: SYSTEM_TEST )
) else ( set /a FAIL+=1 & echo COMPILE ERROR: SYSTEM_TEST )


pause