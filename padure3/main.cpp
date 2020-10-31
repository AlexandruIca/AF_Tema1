#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <vector>

std::ifstream f{ "padure.in" };
std::ofstream g{ "padure.out" };

constexpr int g_max = 1'001;
constexpr int g_inf = 2e9;

class point
{
private:
    int m_i = 0;
    int m_j = 0;

public:
    point() noexcept = default;
    point(point const&) noexcept = default;
    point(point&&) noexcept = default;
    ~point() noexcept = default;

    point(int const r, int const c) noexcept
        : m_i{ r }
        , m_j{ c }
    {
    }

    auto operator=(point const&) noexcept -> point& = default;
    auto operator=(point&&) noexcept -> point& = default;

    constexpr auto i() const noexcept -> int
    {
        return m_i;
    }

    constexpr auto j() const noexcept -> int
    {
        return m_j;
    }
};

auto operator+(point const& a, point const& b) noexcept -> point
{
    return point{ a.i() + b.i(), a.j() + b.j() };
}

point g_start{};
point g_end{};

using matrix_t = std::array<std::array<int, g_max>, g_max>;

matrix_t g_matrix;
matrix_t g_cost;

int g_num_rows = 0;
int g_num_columns = 0;

auto read_graph() -> void
{
    int n = 0;
    int m = 0;
    int si = 0;
    int sj = 0;
    int ei = 0;
    int ej = 0;

    f >> n >> m >> si >> sj >> ei >> ej;

    g_start = point{ si, sj };
    g_end = point{ ei, ej };
    g_num_rows = n;
    g_num_columns = m;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            f >> g_matrix[i][j];
            g_cost[i][j] = g_inf;
        }
    }
}

auto is_inside(point const& p) noexcept -> bool
{
    return p.i() > 0 && p.i() <= g_num_rows && p.j() > 0 && p.j() <= g_num_columns;
}

template<typename T>
using remove_cvref_t = typename std::remove_reference<typename std::remove_cv<T>::type>::type;

template<typename T>
auto at(T&& m, point const& p) -> decltype(auto)
{
    static_assert(std::is_same<remove_cvref_t<T>, matrix_t>::value, "");
    return std::forward<T>(m)[p.i()][p.j()];
}

auto solve() -> void
{
    std::array<point, 4> const directions = { point{ -1, 0 }, point{ 0, 1 }, point{ 1, 0 }, point{ 0, -1 } };
    std::deque<point> queue{};

    queue.push_back(g_start);
    at(g_cost, g_start) = 0;

    while(!queue.empty()) {
        auto const p = queue.front();
        queue.pop_front();

        for(auto const& dir : directions) {
            auto const new_point = p + dir;

            if(!is_inside(new_point)) {
                continue;
            }

            if(at(g_matrix, new_point) != at(g_matrix, p) && at(g_cost, new_point) > at(g_cost, p) + 1) {
                at(g_cost, new_point) = at(g_cost, p) + 1;
                queue.push_back(new_point);
            }
            else if(at(g_matrix, new_point) == at(g_matrix, p) && at(g_cost, new_point) > at(g_cost, p)) {
                at(g_cost, new_point) = at(g_cost, p);
                queue.push_front(new_point);
            }
        }
    }
}

auto main() noexcept -> int
{
    read_graph();
    solve();
    g << at(g_cost, g_end);
}
