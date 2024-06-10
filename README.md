 

valgrind --suppressions=supp.supp ./minishell

valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all ./minishell

valgrind --suppressions=supp.supp --leak-check=full --show-leak-kinds=all --trace-children=yes ./minishell


CTRL-SHIFT-O = go to functions in file
CTRL-TAB = switch between open windows