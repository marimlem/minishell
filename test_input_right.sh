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

exit
EOF