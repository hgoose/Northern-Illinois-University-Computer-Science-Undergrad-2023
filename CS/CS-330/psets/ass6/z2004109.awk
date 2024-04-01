# Z2004109.awk created by Nate Warner z2004109
# The report counts the number of times a word occurs in the input file.

BEGIN {
    count = 0
}

{
    for (i=1; i<=NF; i++) {
        gsub(/[^a-zA-Z0-9]+$/, "", $i) # Remove punctuation from end of word
        gsub(/^[^a-zA-Z0-9]+/, "", $i) # Remove punctuation from start of word

        wordlist[tolower($i)] += 1
        ++count
    }
}

END {

    printf "%15s %7s\n", "Word", "Count"
    printf "------------------------\n"

    for (x in wordlist) {
        if (length(x) >= 5 && wordlist[x] >= 3) {
            printf "%15s %3d\n", x, wordlist[x]
        }
    }

    printf "------------------------\n"
    printf "%s: %d\n", "Number of words", count

}
