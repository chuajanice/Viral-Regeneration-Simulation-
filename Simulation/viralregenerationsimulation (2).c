#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Count live neighbors
int countLiveNeighbors(int** grid, int rows, int cols, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int r = row + i, c = col + j;
            if (r >= 0 && r < rows && c >= 0 && c < cols)
                count += grid[r][c];
        }
    }
    return count;
}

// Display grid
void printGrid(int** grid, int rows, int cols) {
    system("clear");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf(grid[i][j] ? "O " : ". ");
        printf("\n");
    }
}

// Update grid state
void updateGrid(int** grid, int rows, int cols) {
    int** temp = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
        temp[i] = malloc(cols * sizeof(int));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) {
            int n = countLiveNeighbors(grid, rows, cols, i, j);
            if (grid[i][j])
                temp[i][j] = (n == 2 || n == 3);
            else
                temp[i][j] = (n == 3);
        }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = temp[i][j];

    for (int i = 0; i < rows; i++) free(temp[i]);
    free(temp);
}

// Delay time
int getSpeedDelay(char speed) {
    if (speed == 'f' || speed == 'F') return 1;
    if (speed == 'm' || speed == 'M') return 2;
    return 3;
}

int main() {
    int rows, cols, viruses;
    char speedChar;

    // Grid size
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    // Grid allocation
    int** grid = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
        grid[i] = calloc(cols, sizeof(int));

    // Initial cells
    printf("How many viruses? ");
    scanf("%d", &viruses);
    for (int i = 0; i < viruses; i++) {
        int r, c;
        printf("Enter position %d (row col): ", i + 1);
        scanf("%d %d", &r, &c);
        if (r >= 0 && r < rows && c >= 0 && c < cols)
            grid[r][c] = 1;
    }

    // Speed choice
    printf("Speed - Fast (F), Medium (M), Slow (S): ");
    scanf(" %c", &speedChar);
    int delay = getSpeedDelay(speedChar);

    // Simulation loop
    while (1) {
        printGrid(grid, rows, cols);
        updateGrid(grid, rows, cols);
        sleep(delay);
    }

    // Cleanup (unreachable)
    for (int i = 0; i < rows; i++) free(grid[i]);
    free(grid);

    return 0;
}
