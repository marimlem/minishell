#!/usr/bin/env bash

./minishell << EOF
hallo welt

<
<<
>
>>
<<<<
>>>>>>>
h <
h >
h <<
h >>
h <>
h >>>
h <<<<<
<<< h
>>>< h
h <>>> h
h >>|h
|||
|
||
h |
h ||
| h
|| h
| 
h | h |
exit
EOF