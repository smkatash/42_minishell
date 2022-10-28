# **************************************************************************** #
#   REDIRS                                                                     #
# **************************************************************************** #

### SIMPLE ###
/bin/echo 42 > tmp_redir_out 42
cat tmp_redir_out
rm tmp_redir_out

/bin/echo "cat this text\n" > tmp_redir_out
cat <tmp_redir_out
rm tmp_redir_out

cat < /dev/null

cat | cat | ls
("" >tmp_std_outfile) && (ls | grep tmp_std_outfile)

/bin/echo 42 > /dev/null

/bin/echo 42 >> /dev/null

### OVERWRITE ###
/bin/echo 42 > /dev/null > /dev/null > /dev/null > /dev/null > tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out

/bin/echo 42 > tmp_redir_out > tmp_redir_out1 > tmp_redir_out2 > tmp_redir_out3
/bin/echo 0
cat tmp_redir_out
/bin/echo 1
cat tmp_redir_out1
/bin/echo 2
cat tmp_redir_out2
/bin/echo 3
cat tmp_redir_out3
rm tmp_redir_out tmp_redir_out1 tmp_redir_out2 tmp_redir_out3

/bin/echo 42 > /dev/null > tmp_redir_out
/bin/echo 2 >> /dev/null >> tmp_redir_out
cat tmp_redir_out
rm tmp_redir_out

### PERMISSION DENIED ###
touch tmp_redir_out_file1
chmod -r tmp_redir_out_file1
/bin/echo 1 > tmp_redir_out tmp_redir_out_file1

/bin/grep 1 < inputfile

/bin/grep 1 < NO_SUCH_FILE

/bin/grep 1 < inputfile < inputfile

/bin/grep 1 < NO_SUCH_FILE < inputfile

> tmp_std_outfile && echo 1

rm -f tmp_std_outfile

>tmp_std_outfile && ls | grep tmp_std_outfile

rm -f tmp_std_outfile


/bin/echo 1 >/dev/null | /bin/echo 2

/bin/echo >/dev/null 1 | /usr/bin/grep 1

/bin/echo >/dev/null 1 | /bin/echo 2

### HERE_DOC ###
cat << lim
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

<<lim cat
 "lim"
HELLO
42
 lim
testing your minishell
limm
lim

cat << lim
test
lim

cat << EOF
"EOF"
!! HELLO
@42 !!
 EOF\t\b\n
testing your minishell :)
limm
EOF

cat << hello
$USER
$NOVAR
$HOME
hello

cat << 'lim'
$USER
$NOVAR
$HOME
lim

cat << lim''
$USER
$NOVAR
$HOME
lim

cat << ''lim
$USER
$NOVAR
$HOME
lim

cat << 'lim'
$USER
$NOVAR
$HOME
lim

———————————— redirects
Test   1: ✅ grep hi <./test_files/infile 
Test   2: ✅ grep hi "<infile" <         ./test_files/infile 
Test   3: ✅ echo hi < ./test_files/infile bye bye 
Test   4: ✅ grep hi <./test_files/infile_big <./test_files/infile 
Test   5: ✅ echo <"./test_files/infile" "bonjour       42" 
Test   6: ✅ cat <"./test_files/file name with spaces" 
Test   7: ✅ cat <./test_files/infile_big ./test_files/infile 
Test   8: ✅ cat <"1""2""3""4""5" 
Test   9: ✅ echo <"./test_files/infile" <missing <"./test_files/infile" 
Test  10: ✅ echo <missing <"./test_files/infile" <missing 
Test  11: ✅ cat <"./test_files/infile" 
Test  12: ✅ echo <"./test_files/infile_big" | cat <"./test_files/infile" 
Test  13: ✅ echo <"./test_files/infile_big" | cat "./test_files/infile" 
Test  14: ✅ echo <"./test_files/infile_big" | echo <"./test_files/infile" 
Test  15: ✅ echo hi | cat <"./test_files/infile" 
Test  16: ✅ echo hi | cat "./test_files/infile" 
Test  17: ❌ cat <"./test_files/infile" | echo hi 
mini error = ()
bash error = ( Broken pipe)
Test  18: ✅ cat <"./test_files/infile" | grep hello 
Test  19: ✅  
Test  20: ✅ cat <missing 
Test  21: ✅ cat <missing | cat 
Test  22: ✅ cat <missing | echo oi 
Test  23: ✅ cat <missing | cat <"./test_files/infile" 
Test  24: ✅ echo <123 <456 hi | echo 42 
Test  25: ✅ ls >./outfiles/outfile01 
Test  26: ✅ ls >         ./outfiles/outfile01 
Test  27: ✅ echo hi >         ./outfiles/outfile01 bye 
Test  28: ✅ ls >./outfiles/outfile01 >./outfiles/outfile02 
Test  29: ✅ ls >./outfiles/outfile01 >./test_files/invalid_permission 
Test  30: ✅ ls >"./outfiles/outfile with spaces" 
Test  31: ✅ ls >"./outfiles/outfile""1""2""3""4""5" 
Test  32: ✅ ls >"./outfiles/outfile01" >./test_files/invalid_permission >"./outfiles/outfile02" 
Test  33: ✅ ls >./test_files/invalid_permission >"./outfiles/outfile01" >./test_files/invalid_permission 
Test  34: ✅ cat <"./test_files/infile" >"./outfiles/outfile01" 
Test  35: ✅ echo hi >./outfiles/outfile01 | echo bye 
Test  36: ✅ echo hi >./outfiles/outfile01 >./outfiles/outfile02 | echo bye 
Test  37: ✅ echo hi | echo >./outfiles/outfile01 bye 
Test  38: ✅ echo hi | echo bye >./outfiles/outfile01 >./outfiles/outfile02 
Test  39: ✅ echo hi >./outfiles/outfile01 | echo bye >./outfiles/outfile02 
Test  40: ✅ echo hi >./outfiles/outfile01 >./test_files/invalid_permission | echo bye 
Test  41: ✅ echo hi >./test_files/invalid_permission | echo bye 
Test  42: ✅ echo hi >./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
Test  43: ✅ echo hi | echo bye >./test_files/invalid_permission 
Test  44: ✅ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission 
Test  45: ✅ echo hi | echo bye >./test_files/invalid_permission >./outfiles/outfile01 
Test  46: ✅ cat <"./test_files/infile" >./test_files/invalid_permission 
Test  47: ✅ cat >./test_files/invalid_permission <"./test_files/infile" 
Test  48: ✅ cat <missing >./outfiles/outfile01 
Test  49: ✅ cat >./outfiles/outfile01 <missing 
Test  50: ✅ cat <missing >./test_files/invalid_permission 
Test  51: ✅ cat >./test_files/invalid_permission <missing 
Test  52: ✅ cat >./outfiles/outfile01 <missing >./test_files/invalid_permission 
Test  53: ✅ ls >>./outfiles/outfile01 
Test  54: ✅ ls >>      ./outfiles/outfile01 
Test  55: ✅ ls >>./outfiles/outfile01 >./outfiles/outfile01 
Test  56: ✅ ls >./outfiles/outfile01 >>./outfiles/outfile01 
Test  57: ✅ ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02 
Test  58: ✅ ls >>./outfiles/outfile01 >>./outfiles/outfile02 
Test  59: ✅ ls >>./test_files/invalid_permission 
Test  60: ✅ ls >>./test_files/invalid_permission >>./outfiles/outfile01 
Test  61: ✅ ls >>./outfiles/outfile01 >>./test_files/invalid_permission 
Test  62: ✅ ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02 
Test  63: ✅ ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02 
Test  64: ✅ ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing 
Test  65: ✅ echo hi >>./outfiles/outfile01 | echo bye 
Test  66: ✅ echo hi >>./outfiles/outfile01 >>./outfiles/outfile02 | echo bye 
Test  67: ✅ echo hi | echo >>./outfiles/outfile01 bye 
Test  68: ✅ echo hi | echo bye >>./outfiles/outfile01 >>./outfiles/outfile02 
Test  69: ✅ echo hi >>./outfiles/outfile01 | echo bye >>./outfiles/outfile02 
Test  70: ✅ echo hi >>./test_files/invalid_permission | echo bye 
Test  71: ✅ echo hi >>./test_files/invalid_permission >./outfiles/outfile01 | echo bye 
Test  72: ✅ echo hi | echo bye >>./test_files/invalid_permission 
Test  73: ✅ echo hi | echo >>./outfiles/outfile01 bye >./test_files/invalid_permission 
Test  74: ✅ cat <minishell.h>./outfiles/outfile 
Test  75: ✅ cat <minishell.h|ls 