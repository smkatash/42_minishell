# **************************************************************************** #
#   REDIRS                                                                     #
# **************************************************************************** #

/bin/echo 1 >/dev/null | /usr/bin/grep 1

echo "exit_code ->$? user ->$USER home -> $HOME" 
echo "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<" 
echo 'exit_code ->$? user ->$USER home -> $HOME' 
exit 42 world 
export | sort | grep -v SHLVL | grep -v "declare -x _" | grep -v "PS.=" 
cat minishell.h | grep ");"$ 
export GHOST=123 | env | grep GHOST 
grep hi "<infile" <         ./test_files/infile
cat <"1""2""3""4""5" 
cat <"./test_files/infile" | echo hi 

cat <"./test_files/infile_big" | echo hi
Test  51: ❌ exit 42 world 
Test  14: ✅ echo '> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<' 
Test  15: ❌ echo "exit_code ->$? user ->$USER home -> $HOME"
Test  16: ❌ echo 'exit_code ->$? user ->$USER home -> $HOME' 
Test   1: ✅  
Test   2: ❌ $PWD 
mini exit code = 0
bash exit code = 126
mini error = ( Permission denied)
bash error = ( is a directory)
Test   3: ❌ $EMPTY 
mini error = ( Permission denied)
bash error = ()
Test   4: ❌ $EMPTY echo hi 
mini output = ()
bash output = (hi)
mini error = ( Permission denied)
bash error = ()
Test   5: ❌ ./test_files/invalid_permission 
mini exit code = 0
bash exit code = 126
Test   6: ❌ ./missing.out 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( No such file or directory)
Test   7: ❌ missing.out 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( command not found)
Test   8: ❌ "aaa" 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( command not found)
Test   9: ❌ test_files 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( command not found)
Test  10: ❌ ./test_files 
mini exit code = 0
bash exit code = 126
mini error = ( Permission denied)
bash error = ( is a directory)
Test  11: ❌ /test_files 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( No such file or directory)
Test  12: ❌ minishell.h 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( command not found)
Test  13: ❌ $ 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( command not found)
Test  14: ❌ $? 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( command not found)
Test  15: ❌ README.md 
mini exit code = 0
bash exit code = 127
mini error = ( Command not found)
bash error = ( command not found)

———————————— syntax
Test   1: ❌ | 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test   2: ❌ | echo oi 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test   3: ❌ | | 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test   4: ❌ | $ 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test   5: ❌ | > 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test   6: ❌ > 
mini exit code = 258
bash exit code = 2
mini error = ( parse error near`\n´)
bash error = ( syntax error near unexpected token `newline')
Test   7: ❌ >> 
mini exit code = 258
bash exit code = 2
mini error = ( parse error near`\n´)
bash error = ( syntax error near unexpected token `newline')
Test   8: ❌ >>> 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `>´)
bash error = ( syntax error near unexpected token `>')
Test   9: ❌ < 
mini exit code = 258
bash exit code = 2
mini error = ( parse error near`\n´)
bash error = ( syntax error near unexpected token `newline')
Test  10: ❌ << 
mini exit code = 258
bash exit code = 2
mini error = ( parse error near`\n´)
bash error = ( syntax error near unexpected token `newline')
Test  11: ❌ echo hi < 
mini exit code = 258
bash exit code = 2
mini error = ( parse error near`\n´)
bash error = ( syntax error near unexpected token `newline')
Test  12: ❌ cat    <| ls 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test  13: ❌ echo hi | > 
mini exit code = 258
bash exit code = 2
mini error = ( parse error near`\n´)
bash error = ( syntax error near unexpected token `newline')
Test  14: ❌ echo hi | > >> 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `>>´)
bash error = ( syntax error near unexpected token `>>')
Test  15: ❌ echo hi | < | 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test  16: ❌ echo hi |   | 
mini exit code = 258
bash exit code = 2
mini error = ( syntax error near unexpected token `|´)
bash error = ( syntax error near unexpected token `|')
Test  17: ❌ echo hi |  "|" 
mini error = ( Command not found)
bash error = ( command not found)
/17

Test 138: ❌ $PWD 
mini exit code = 1
bash exit code = 126