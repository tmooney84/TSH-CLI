#!/bin/bash

echo "Starting tests.sh..."


# Build the project
make tsh || exit 1

echo ""
echo "------------------------------------------------------------------"
echo "------------------------------------------------------------------"

mkdir test_dir

echo "TSH/MY_ZSH TESTING"
echo ""
echo "1) Example Binary Commands (Linux)"
echo ""

# 	ls -l
echo "  a) ls -l command" 
./tsh <<EOF > test_dir/tsh_out.txt
ls -l
exit
EOF

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_out.txt > test_dir/tsh_out_clean.txt

ls -l > test_dir/bash_out.txt

if diff test_dir/tsh_out_clean.txt test_dir/bash_out.txt; then 
    echo "  Files match!"

else
    echo "  Files differ!"
    echo ""
    echo "-------tsh_out_clean.txt-------"
    cat test_dir/tsh_out_clean.txt
    echo ""
    echo ""
    echo "-------bash_out.txt------------"
    cat test_dir/bash_out.txt
fi

echo ""

# 	cat
echo "  b) cat <file> command"

echo "Hello World!" > test_dir/hello.txt

./tsh <<EOF > test_dir/tsh_out.txt
cat test_dir/hello.txt
exit
EOF

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_out.txt > test_dir/tsh_out_clean.txt

cat test_dir/hello.txt > test_dir/bash_out.txt

if diff test_dir/tsh_out_clean.txt test_dir/bash_out.txt; then 
    echo "  Files match!"

else
    echo "  Files differ!"
    echo ""
    echo "-------tsh_out_clean.txt-------"
    cat test_dir/tsh_out_clean.txt
    echo ""
    echo ""
    echo "-------bash_out.txt------------"
    cat test_dir/bash_out.txt
fi

echo""

# 	date
echo "  c) date command"

./tsh <<EOF > test_dir/tsh_out.txt
date
exit
EOF

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_out.txt > test_dir/tsh_out_clean.txt


date > test_dir/bash_out.txt

if diff test_dir/tsh_out_clean.txt test_dir/bash_out.txt; then 
    echo "  Files match!"

else
    echo "  Files differ!"
    echo ""
    echo "-------tsh_out_clean.txt-------"
    cat test_dir/tsh_out_clean.txt
    echo ""
    echo ""
    echo "-------bash_out.txt------------"
    cat test_dir/bash_out.txt
fi

echo ""
	
echo "2) Built-In Commands (Linux)"
echo ""

# 	cd
echo "  a) cd command"

./tsh <<EOF > test_dir/tsh_out.txt
cd test_dir
pwd
exit
EOF

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_out.txt > test_dir/tsh_out_clean.txt

cd test_dir
pwd > bash_out.txt
cd ..

if diff test_dir/tsh_out_clean.txt test_dir/bash_out.txt; then 
    echo "  Files match!"

else
    echo "  Files differ!"
    echo ""
    echo "-------tsh_out_clean.txt-------"
    cat test_dir/tsh_out_clean.txt
    echo ""
    echo ""
    echo "-------bash_out.txt------------"
    cat test_dir/bash_out.txt
fi

echo ""

# 	echo command 
echo "  b) echo command"

./tsh <<EOF > test_dir/tsh_out.txt
echo "Hello World!"
exit
EOF

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_out.txt > test_dir/tsh_out_clean.txt

echo "Hello World!" > test_dir/bash_echo.txt

if diff test_dir/tsh_out_clean.txt test_dir/bash_echo.txt; then 
    echo "  Files match!"

else
    echo "  Files differ!"
    echo ""
    echo "-------tsh_out_clean.txt-------"
    cat test_dir/tsh_out_clean.txt
    echo ""
    echo ""
    echo "-------bash_out.txt------------"
    cat test_dir/bash_echo.txt
fi

echo ""

#   export
echo "  c) export command"

./tsh <<EOF > test_dir/tsh_env_dump.txt
export TESTING=12345
env
exit
EOF

grep '^TESTING=' test_dir/tsh_env_dump.txt > test_dir/tsh_out.txt

echo "TESTING=12345" > test_dir/actual.txt

if diff test_dir/tsh_out.txt test_dir/actual.txt; then 
    echo "  Files match...Export working correctly!"

else
    echo "  Files differ...Export not working correctly!"
    echo ""
    echo "-------tsh_out.txt-------"
    cat test_dir/tsh_out.txt
    echo ""
    echo ""
    echo "-------acutal.txt------------"
    cat test_dir/actual.txt

    echo "***UNABLE TO TEST unset command CORRECTLY >>> unset TEST RESULTS INVALID!"
fi

echo ""

# 	unset
echo "  d) unset command"

./tsh <<EOF > test_dir/tsh_env_dump.txt
export TESTING=12345
unset TESTING
env
exit
EOF

grep '^TESTING=' test_dir/tsh_env_dump.txt > test_dir/tsh_out.txt

echo "TESTING=12345" > test_dir/actual.txt

if diff test_dir/tsh_out.txt test_dir/actual.txt > /dev/null; then 
    echo "  Files match...Unset not working correctly!"
    echo ""
    echo "-------tsh_out.txt-------"
    cat test_dir/tsh_out.txt
    echo ""
    echo ""
    echo "-------acutal.txt------------"
    cat test_dir/actual.txt
else
    echo "  Files differ...Unset working correctly!"
fi

echo ""

#   env
echo "  e) env command"

./tsh <<EOF > test_dir/tsh_env.txt
env
exit
EOF

env > test_dir/actual_env.txt

grep -v '^_=' test_dir/tsh_env.txt | sort > test_dir/tsh_env.txt
grep -v '^_=' test_dir/actual_env.txt | sort > test_dir/actual_env.txt

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_env.txt > test_dir/tsh_env_clean.txt

if diff -q test_dir/tsh_env_clean.txt test_dir/actual_env.txt; then 
    echo "  Files match...Env working correctly!"

else
    echo "  Files differ...Env not working correctly!"
    echo ""
    echo "-------tsh_env_clean.txt-------"
    cat test_dir/tsh_env_clean.txt
    echo ""
    echo ""
    echo "-------acutal_env.txt------------"
    cat test_dir/actual_env.txt
fi

echo ""

# 	exit
echo "  f) exit command"

./tsh <<EOF > /dev/null

exit
EOF

if [ $? -eq 0 ]; then
    echo "  Exit working correctly (status 0)"
else
    echo "  Exit returned a non-zero status $?"
fi

echo ""

# 	pwd
echo "  g) pwd command"

./tsh <<EOF > test_dir/tsh_out.txt
pwd
exit
EOF

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_out.txt > test_dir/tsh_out_clean.txt


pwd > test_dir/bash_out.txt

if diff test_dir/tsh_out_clean.txt test_dir/bash_out.txt; then 
    echo "  Files match... pwd working correctly!"

else
    echo "  Files differ!"
    echo ""
    echo "-------tsh_out_clean.txt-------"
    cat test_dir/tsh_out_clean.txt
    echo ""
    echo ""
    echo "-------bash_out.txt------------"
    cat test_dir/bash_out.txt
fi

echo ""

# 	which
echo "  h) which command"

./tsh <<EOF > test_dir/tsh_out.txt
which cat
exit
EOF

sed 's/\[TSH: [^]]*]> //g; s/^[[:space:]]*//; s/[[:space:]]*$//' \
    test_dir/tsh_out.txt > test_dir/tsh_out_clean.txt


which cat > test_dir/bash_out.txt

if diff test_dir/tsh_out_clean.txt test_dir/bash_out.txt; then 
    echo "  Files match... which working correctly!"

else
    echo "  Files differ!"
    echo ""
    echo "-------tsh_out_clean.txt-------"
    cat test_dir/tsh_out_clean.txt
    echo ""
    echo ""
    echo "-------bash_out.txt------------"
    cat test_dir/bash_out.txt
fi

echo ""

rm -rf test_dir
rm tsh tsh.o utils.o builtin_cmds.o 
