for f in *.in; do
    ./dfs < "$f" > tmp.out
    diff -w tmp.out "${f%.in}.out" || {
        echo "WA on $f"
        exit
    }
    echo "AC $f"
done