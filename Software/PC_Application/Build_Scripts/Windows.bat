@REM Find Qt "bin" directory
@for /F "delims=" %%a in ('dir /B C:\Qt\5.15.*') do @set DETECTED_QT_VERSION=%%a%

@REM Select toolchain according to build target
@if "%1" == "32" (
	@set QT_BINARIES_PATH=C:\Qt\%DETECTED_QT_VERSION%\mingw81_32\bin
	@set "PATH=C:\Qt\Tools\mingw810_32\bin;C:\Qt\%DETECTED_QT_VERSION%\mingw81_32\bin;%PATH%"
) else if "%1" == "64" (
	@set QT_BINARIES_PATH=C:\Qt\%DETECTED_QT_VERSION%\mingw81_64\bin
	@set "PATH=C:\Qt\Tools\mingw810_64\bin;C:\Qt\%DETECTED_QT_VERSION%\mingw81_64\bin;%PATH%"
) else (
	@echo Please specify build target architecture bits. Put "32" or "64" as first command line argument.
	@goto End
)
@REM Make sure QT_BINARIES_PATH path is valid
@echo Detected Qt version : %DETECTED_QT_VERSION%, detected Qt binaries path : %QT_BINARIES_PATH%
@if not exist %QT_BINARIES_PATH%\qmake.exe (
	@echo Invalid Qt "bin" directory. Make sure Qt 5.15.x is installed in "C:\Qt" directory.
	@goto End
)

@set SOURCES_DIRECTORY=%CD%\..
@set BUILD_DIRECTORY=%TEMP%\Cyclope_Build_%1%_Bits
@set RELEASE_DIRECTORY=%TEMP%\Cyclope_Release_%1%_Bits

@REM Prepare directories
rmdir /Q /S %BUILD_DIRECTORY%
rmdir /Q /S %RELEASE_DIRECTORY%
mkdir %BUILD_DIRECTORY%
mkdir %RELEASE_DIRECTORY%
mkdir %RELEASE_DIRECTORY%\Cyclope

@REM Build application
cd %BUILD_DIRECTORY%
%QT_BINARIES_PATH%\qmake -spec win32-g++ %SOURCES_DIRECTORY%
mingw32-make.exe -j%NUMBER_OF_PROCESSORS%

@REM Copy relevant files to release path
copy %BUILD_DIRECTORY%\release\Cyclope.exe %RELEASE_DIRECTORY%\Cyclope

@REM Embed all needed libraries
cd %RELEASE_DIRECTORY%\Cyclope
@REM Do not use --release flag anymore with Qt 5.15.x (see QTBUG-84567)
%QT_BINARIES_PATH%\windeployqt --compiler-runtime Cyclope.exe

@REM Compress application to a ZIP archive
@set ARCHIVE_NAME=%USERPROFILE%\Desktop\Cyclope_%1%_Bits.zip
del %ARCHIVE_NAME%
powershell Compress-Archive -LiteralPath %RELEASE_DIRECTORY%\Cyclope -DestinationPath %ARCHIVE_NAME%

@REM Return to original directory
@cd %SOURCES_DIRECTORY%\Build_Scripts

:End
