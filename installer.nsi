!define VERSION "1.0.3"
!include "MUI2.nsh"
Outfile "qgit-installer.exe"
Name "QGit"
LicenseData COPYING.rtf
InstallDir "$PROGRAMFILES64\QGit"

;!define MUI_LICENSEPAGE_CHECKBOX
#!define MUI_LICENSEPAGE_RADIOBUTTONS

!define MUI_FINISHPAGE_RUN "$INSTDIR\p4merge.exe"

; Page license
; Page directory
; Page instfiles
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "COPYING.rtf"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
; UninstPage uninstConfirm
; UninstPage instfiles
#!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
#!insertmacro MUI_UNPAGE_FINISH


!insertmacro MUI_LANGUAGE English


Section

    SetOutPath "$INSTDIR"

    #CreateDirectory "$INSTDIR"
    File qgit.txt
    WriteUninstaller "$INSTDIR\uninstall.exe"

    CreateDirectory "$SMPROGRAMS\QGit"
    CreateShortcut /NoWorkingDir "$SMPROGRAMS\qgit\QGit.lnk" "$INSTDIR\qgit.txt"
    CreateShortcut /NoWorkingDir "$SMPROGRAMS\qgit\Uninstall QGit.lnk" "$INSTDIR\uninstall.exe"

SectionEnd



Section "Uninstall"

    Delete "$INSTDIR\qgit.txt"
    Delete "$INSTDIR\uninstall.exe"
    RMDir /r "$SMPROGRAMS\QGit"


    RMDir "$INSTDIR"         # not unsafe if I've manually cleared the files

SectionEnd