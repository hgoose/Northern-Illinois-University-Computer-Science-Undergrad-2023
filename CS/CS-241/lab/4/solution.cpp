int compute_score(int arr[][4]) {
    int score = 0;

    if (arr[0][0] % 2 == 0 && arr[0][3] % 2 == 0 && arr[3][0] % 2 == 0 && arr[3][3] % 2 == 0) {
        score+=20;
    }

    if (arr[0][0] % 2 != 0 && arr[0][3] % 2 != 0 && arr[3][0] % 2 != 0 && arr[3][3] % 2 != 0) {
        score+=20;
    }


    bool evendiag1 = 1;
    bool evendiag2 = 1;
    for (int i=0, j=3; i<4; ++i, --j) {

        if (arr[i][i] % 2 != 0)  {
            evendiag1 = 0;
        }
        if (arr[i][j] % 2 != 0) {
            evendiag2 =0;
        }
    }

    if (evendiag1 || evendiag2) {
        score+=20;

        if (evendiag1 && evendiag2) score+=20;

    }

    bool odddiag1 = 1;
    bool odddiag2 = 1;
    for (int i=0, j=3; i<4; ++i, --j) {

        if (arr[i][i] % 2 == 0)  {
            odddiag1 = 0;
        }
        if (arr[i][j] % 2 == 0) {
            odddiag2 = 0;
        }
    }

    if (odddiag1 || odddiag2) {
        score+=20;

        if (odddiag1 && odddiag2) score+=20;
    }

    for (int i = 0; i < 4; ++i) { // Iterate over rows
        bool isRowEven = true; // Assume the row is odd initially
        for (int j = 0; j < 4; ++j) { // Iterate over columns in the row
            if (arr[i][j] % 2 != 0) { // If an element is even
                isRowEven = false; // The row is not entirely odd
                break; // No need to check the rest of the row
            }
        }
        if (isRowEven) { // If the row was entirely odd
            score += 20; // Add 20 to the score
            break; // Since you only need one row to satisfy the condition, you can break here if the instructions imply so. Otherwise, remove this break if you need to check all rows.
        }
    }
    for (int i = 0; i < 4; ++i) { // Iterate over rows
        bool iscolumneven = true; // Assume the row is odd initially
        for (int j = 0; j < 4; ++j) { // Iterate over columns in the row
            if (arr[j][i] % 2 != 0) { // If an element is even
                iscolumneven = false; // The row is not entirely odd
                break; // No need to check the rest of the row
            }
        }
        if (iscolumneven) { // If the row was entirely odd
            score += 20; // Add 20 to the score
            break; // Since you only need one row to satisfy the condition, you can break here if the instructions imply so. Otherwise, remove this break if you need to check all rows.
        }
    }


    for (int i = 0; i < 4; ++i) { // Iterate over rows
        bool isRowOdd = true; // Assume the row is odd initially
        for (int j = 0; j < 4; ++j) { // Iterate over columns in the row
            if (arr[i][j] % 2 == 0) { // If an element is even
                isRowOdd = false; // The row is not entirely odd
                break; // No need to check the rest of the row
            }
        }
        if (isRowOdd) { // If the row was entirely odd
            score += 20; // Add 20 to the score
            break; // Since you only need one row to satisfy the condition, you can break here if the instructions imply so. Otherwise, remove this break if you need to check all rows.
        }
    }

    for (int i = 0; i < 4; ++i) { // Iterate over rows
        bool iscolumnodd = true; // Assume the row is odd initially
        for (int j = 0; j < 4; ++j) { // Iterate over columns in the row
            if (arr[j][i] % 2 == 0) { // If an element is even
                iscolumnodd = false; // The row is not entirely odd
                break; // No need to check the rest of the row
            }
        }
        if (iscolumnodd) { // If the row was entirely odd
            score += 20; // Add 20 to the score
            break; // Since you only need one row to satisfy the condition, you can break here if the instructions imply so. Otherwise, remove this break if you need to check all rows.
        }
    }


    int sum = 0;
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            sum+=arr[i][j];
        }
    }

    score+=sum;

    return score;

}

