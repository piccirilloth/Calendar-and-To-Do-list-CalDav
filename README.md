# Calendar-and-To-Do-list-CalDav

## Come buildare questo progetto

Sono necessarie le librerie CURL, cURLpp e QT.<br/>
cURLpp è già presente all'interno del progetto

### Linux:
- Hai bisogno di installare la libreria CURL, a tale scopo esegui questo comando:
  - <code> sudo apt-get install libcurl4-openssl-dev </code>
- Per installare QT, esegui questo comando:
  - <code> sudo apt-get install qt5-default </code>

### MacOS
- CURL dovrebbe essere già installato nel sistema operativo, in caso contrario eseguire:
  - <code>ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null</code>
  - <code>brew install curl</code>
- Puoi installare QT dalla pagina web: https://www.qt.io/download
- Aggiungere nelle prime righe del file <code>CMakeList.txt</code> la riga <code>set(CMAKE_PREFIX_PATH "__QTDir__/__version__/clang_64/")</code>

### Windows
- Per installare CURL digitare i seguenti comandi:
  - <code>git clone https://github.com/curl/curl.git</code>
  - <code>cd curl</code>
  - <code>buildconf.bat</code>
  - <code>“__pathForVisualStudio__\vc\Auxiliary\Build\vcvarsall.bat” x64</code>
  - <code>nmake /f Makefile.vc mode=dll MACHINE=x64</code>
  - alla riga 123 del file <code>CMakeList.txt</code> modificare il path con <code>__CURLBuildPath__/builds/libcurl-vc-x64-release-dll-ipv6-sspschannel/include</code> 
  - alla riga 125 del file <code>CMakeList.txt</code> modificare il path con <code>__CURLBuildPath__/builds/libcurl-vc-x64-release-dll-ipv6-sspi-schannel-obj-lib/libcurl.lib</code>
- Puoi installare QT dalla pagina web: https://www.qt.io/download
- Impostare come compilatore <b>VisualStudio</b> su CLion
  
