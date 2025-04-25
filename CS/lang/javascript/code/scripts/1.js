var brackets = [
    [ [0, Infinity], 5 ],
];

function updateBrackets(lb,price) {
    let idx = 0;
    let max = brackets[0][0][0];
    let found = false;
    for (let i=0; i<brackets.length && !found; ++i) {
        let interval = brackets[i][0];
        if (interval[0] == lb) {
            found = true;
        }
        if (interval[0] < lb) {
            idx = i;
            max = interval[0];
        }
    }
    if (found) {
        console.log("already exists");
        return;
    }

    let tmp = brackets[idx][0][1];
    brackets[idx][0][1] = lb;
    brackets.splice(idx+1, 0, [[lb, tmp],price]);
}

updateBrackets(2,10);
updateBrackets(5,10);
updateBrackets(7,10);
console.log(brackets);
