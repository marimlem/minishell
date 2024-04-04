#!/usr/bin/env bash

./minishell << EOF
hallo welt
< h
<< h
> h
>> h
h<o
h>o
h | h < o
h | > i
ech'o' "d d dd"'e'|>>a cat
a << b > c | f "ggg"
a "bb ><>||"| d"e"f
"e"f
"a"'b'c'd'e'f'
"a"b'c'd"e">>"e".md
"abcd'efghij'"<'<o'
"> o"
$a
"$ "
".$a."
exit
EOF