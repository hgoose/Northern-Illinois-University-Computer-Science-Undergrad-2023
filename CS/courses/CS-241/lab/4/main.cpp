//
//  main.cpp
//
//  Created by Kurt McMahon on 2/5/24.
//

#include <iostream>

int compute_score(int[][4]);
void fill_grid(int[][4]);
void print_grid(int[][4]);

using std::cout;
using std::endl;

int main()
{
    int grid[4][4];
    int game1[4][4] = {{6, 6, 6, 6}, {6, 6, 6, 6},
                       {6, 6, 6, 6}, {6, 6, 6, 6}};
    int game2[4][4] = {{5, 5, 5, 5}, {3, 3, 3, 3},
                       {1, 1, 1, 1}, {5, 5, 5, 5}};

    print_grid(game1);
    cout << "Score = " << compute_score(game1)
         << endl << endl;

    print_grid(game2);
    cout << "Score = " << compute_score(game2)
         << endl << endl;

    srand(4);
    
    for (int i = 0; i < 8; i++)
    {
        fill_grid(grid);
        print_grid(grid);
        cout << "Score = " << compute_score(grid)
             << endl << endl;
    }
    
    return 0;
}

void fill_grid(int grid[][4])
{
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
            grid[r][c] = rand() % 6 + 1;
    }
}

void print_grid(int grid[][4])
{
    for (int r = 0; r < 4; r++)
    {
        cout << "-----------------\n|";
        
        for (int c = 0; c < 4; c++)
            cout << ' ' << grid[r][c] << " |";
        
        cout << endl;
    }

    cout << "-----------------\n\n";
}

    
