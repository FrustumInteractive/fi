#!/bin/sh

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  DIR="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
SCRIPTPATH="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

echo "Script path is: $SCRIPTPATH"

PATH=$PATH:$SCRIPTPATH/extern/Qt/4.8.6/bin:\
$SCRIPTPATH/extern/Mingw32/bin:\
$SCRIPTPATH/bin:\
$SCRIPTPATH/extern/MinGW/bin:\
$SCRIPTPATH/extern/MSVC/14/bin

green="\[\e[0;32m\]"
gold="\[\e[0;33m\]"
none="\[\e[m\]"

export PS1="[$green\u@\h $gold\w$none]\$ " 
LS_COLORS=$LS_COLORS:'di=1;36:fi=0:ex=1;32:*.bat=1;32:*.tar.gz=1;31' 
export LS_COLORS
export BASH_EMU=1

echo "alias ls=\"ls -F --color --show-control-chars\";rm shellinit" > shellinit
exec /bin/bash --init-file shellinit

