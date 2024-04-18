
#!/usr/bin/env bash

./minishell << EOF
\$a
"$ "
".\$a."
" \$a"
/bin/echo $"HOME"\$USER
/bin/echo $"HOM"E\$USER
/bin/echo $"'HOM'E"\$USER
/bin/echo $'HOM'E\$USER
/bin/echo $"HOME"
/bin/echo $'HOME'
/bin/echo $
/bin/echo "$"
/bin/echo '$='
/bin/echo "$""$"
/bin/echo $"$"
/bin/echo $"42$"
/bin/echo "$"$
/bin/echo $'$'
/bin/echo '$'$
/bin/echo "$ "
/bin/echo '$ '
/bin/echo \$TESTNOTFOUND
/bin/echo \$HOME\$TESTNOTFOUND
/bin/echo \$TESTNOTFOUND\$HOME
/bin/echo \$TESTNOTFOUND\$HOME$
cd ..\$PWD
/bin/echo ""\$?""
/bin/echo " "\$?" "
/bin/echo \$?"42"
/bin/echo ''\$?''"42"
/bin/echo 'HELLO'\$?:''"42"
/bin/echo "\$?"
/bin/echo '\$?'
/bin/echo "'\$?'"
/bin/echo '"\$?"'
exit
EOF