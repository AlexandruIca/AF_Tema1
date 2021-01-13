#include <array>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int num_rows = 3;
constexpr int num_columns = 3;

using board_t = std::array<std::array<char, num_columns>, num_rows>;

enum class result
{
    lose = -1,
    draw = 0,
    win = 1,
    invalid = 2
};

auto result_to_str(result const r) -> std::string
{
    switch(r) {
    case result::lose:
        return "lose";
    case result::draw:
        return "draw";
    case result::win:
        return "win";
    default:
    case result::invalid:
        return "invalid";
    }
}

auto opposite(result const r) noexcept -> result
{
    switch(r) {
    case result::lose:
        return result::win;
    case result::draw:
        return result::draw;
    case result::win:
        return result::lose;
    default:
    case result::invalid:
        return result::invalid;
    }
}

struct array_hasher
{
    std::size_t operator()(board_t const& a) const
    {
        std::size_t h = 0;

        for(auto e : a) {
            // for(auto cell : e) {
            h ^= std::hash<int>{}(e[0]) + 0x9e3779b9 + (h << 6) + (h >> 2);
            //}
        }
        return h;
    }
};

board_t g_board;
std::unordered_map<board_t, result, array_hasher> g_cache; // cache pentru a retine configuratiile pt matrice

// intoarce true daca jucatorul 'who' a castigat
auto has_won(char const who) noexcept -> bool
{
    for(std::size_t i = 0; i < num_rows; ++i) {
        if(g_board[i][0] == who && g_board[i][1] == who && g_board[i][2] == who) {
            return true;
        }
        if(g_board[0][i] == who && g_board[1][i] == who && g_board[2][i] == who) {
            return true;
        }
    }

    if(g_board[0][0] == who && g_board[1][1] == who && g_board[2][2] == who) {
        return true;
    }
    if(g_board[0][2] == who && g_board[1][1] == who && g_board[2][0] == who) {
        return true;
    }

    return false;
}

auto solve(char const player) -> result
{
    /*
    if(g_cache.find(g_board) != g_cache.end()) {
        return g_cache[g_board];
    }
    */

    int num_wins = 0;
    int num_draws = 0;
    int num_empty = 0;

    // incerc sa joc cu 'player'
    for(std::size_t i = 0; i < num_rows; ++i) {
        for(std::size_t j = 0; j < num_columns; ++j) {
            if(g_board[i][j] != '.') {
                continue;
            }

            ++num_empty;
            g_board[i][j] = player;

            if(has_won(player)) {
                ++num_wins;
            }
            else {
                auto const r = (player == 'X' ? solve('0') : solve('X'));

                // a pierde '0' inseamna a castiga 'X' si invers
                // egalitate ramane egalitate
                if(r == result::draw) {
                    ++num_draws;
                }
                else if(r == result::lose) {
                    ++num_wins;
                }
            }

            g_board[i][j] = '.';
        }
    }

    if(num_empty == 0) {
        return result::draw;
    }
    if(num_wins > 0) {
        // return g_cache[g_board] = result::win;
        return result::win;
    }
    if(num_draws > 0) {
        // return g_cache[g_board] = result::draw;
        return result::draw;
    }

    // return g_cache[g_board] = result::lose;
    return result::lose;
}

auto main() noexcept -> int
{
    std::ifstream f{ "xsizero.in" };
    std::ofstream g{ "xsizero.out" };

    std::size_t board_index = 0;
    std::string lines[num_rows];

    for(std::size_t i = 0; i < num_rows; ++i) {
        lines[i].reserve(num_columns);
    }

    while(std::getline(f, lines[0], '\n')) {
        std::getline(f, lines[1], '\n');
        std::getline(f, lines[2], '\n');

        int num_x = 0;
        int num_z = 0;

        for(std::size_t i = 0; i < num_rows; ++i) {
            for(std::size_t j = 0; j < num_columns; ++j) {
                g_board[i][j] = lines[i][j];

                if(g_board[i][j] == 'X') {
                    ++num_x;
                }
                else if(g_board[i][j] == '0') {
                    ++num_z;
                }
            }
        }

        for(std::size_t i = 0; i < num_rows; ++i) {
            lines[i].clear();
        }

        ++board_index;

        auto state = result::invalid;

        // e randul lui 0
        if(num_x - num_z == 1) {
            state = opposite(solve('0'));
        }
        else if(num_x == num_z) {
            state = solve('X');
        }

        g << "Testul #" << board_index << ": " << result_to_str(state) << std::endl;
    }
}
