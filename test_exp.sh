
#!/usr/bin/env bash

./minishell << EOF
\$a
"$ "
".\$a."
" \$a"
exit
EOF