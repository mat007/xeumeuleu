@echo off

md ..\lib\

xcopy /Y "..\out\libraries\xeumeuleu\vc71\release\xeumeuleu.lib" ..\lib\
xcopy /Y "..\out\libraries\xeumeuleu\vc71\debug\xeumeuleu_d.lib" ..\lib\

set INCLUDE_DIR=..\include\xeumeuleu
md %INCLUDE_DIR%

set SRC_DIR=..\src\libraries\xeumeuleu

xcopy /Y "%SRC_DIR%\xml.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\exception.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\xo*.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\xi*.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\encoding.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\grammar.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\start.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\end.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\content.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\cdata.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\attribute.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\list.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\name_list.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\visitor.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\caller*.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\name_caller*.h" %INCLUDE_DIR%
xcopy /Y "%SRC_DIR%\optional.h" %INCLUDE_DIR%
