#include <deque>
#include <iostream>
#include <vector>

int dir_row[] = { -1, 0, 1, 0 };
int dir_col[] = { 0, 1, 0, -1 };

struct cell
{
    int row = 0;
    int col = 0;
    int cost = 0;

    cell(int const r, int const c, int const cst)
        : row{ r }
        , col{ c }
        , cost{ cst }
    {
    }
};

enum class cell_state
{
    occupied,
    empty
};

cell_state g_matrix[10001][10001];
std::deque<cell> g_cells{};
int g_num_rows = 0;
int g_num_cols = 0;

bool is_inside(int r, int c)
{
    return r >= 0 && r < g_num_rows && c >= 0 && c < g_num_cols;
}

auto solve() -> int
{
    int result = 0;

    while(!g_cells.empty()) {
        auto const current_cell = g_cells.front();
        g_cells.pop_front();
        result += current_cell.cost;

        for(int dir = 0; dir < 4; dir++) {
            int const new_r = current_cell.row + dir_row[dir];
            int const new_c = current_cell.col + dir_col[dir];

            if(is_inside(new_r, new_c) && g_matrix[new_r][new_c] == cell_state::empty) {
                g_matrix[new_r][new_c] = cell_state::occupied;
                g_cells.emplace_back(new_r, new_c, current_cell.cost + 1);
            }
        }
    }

    return result;
}

int main()
{
    int n = 0;
    int m = 0;
    int k = 0;

    std::cin >> n >> m >> k;

    g_num_rows = n;
    g_num_cols = m;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c = '\0';
            std::cin >> c;
            g_matrix[i][j] = (c == '.' ? cell_state::empty : cell_state::occupied);
        }
    }

    for(int i = 0; i < k; i++) {
        int a = 0;
        int b = 0;

        std::cin >> a >> b;

        g_matrix[a - 1][b - 1] = cell_state::occupied;
        g_cells.emplace_back(a - 1, b - 1, 0);
    }

    std::cout << solve();
}
