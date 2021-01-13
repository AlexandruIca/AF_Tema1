#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

std::ifstream f{ "ctc.in" };
std::ofstream g{ "ctc.out" };

std::array<std::vector<int>, 100'001> g_graph{};          // graful normal
std::array<std::vector<int>, 100'001> g_graph_t{};        // graful transpus
std::array<bool, 100'001> g_visited{};                    // aici tin nodurile vizitate
std::array<int, 100'001> g_ctc_index{};                   // aici tin "grupul" din care face parte fiecare nod
std::vector<int> g_dfs_rev{};                             // aici tin nodurile in ordinea in care le-am parcurs in DFS
std::unordered_map<int, std::vector<int>> g_components{}; // aici tin toate componentele cerute de problema(tare conexe)
int g_num_nodes = 0;

auto read_graph() -> void
{
    int n = 0;
    int m = 0;

    f >> n >> m;

    g_num_nodes = n;

    for(int i = 0; i < m; ++i) {
        int x = 0;
        int y = 0;

        f >> x >> y;

        g_graph[x].push_back(y);
        g_graph_t[y].push_back(x); // transpus
    }
}

// dfs pentru graful normal
auto dfs(int const i) -> void
{
    if(g_visited[i]) {
        return;
    }

    g_visited[i] = true;

    for(auto const node : g_graph[i]) {
        dfs(node);
    }

    g_dfs_rev.push_back(i); // pun nodurile in ordinea "inversa"(vreau ca nodul din care pornesc sa fie ultimul adaugat)
}

// dfs pentru graful transpus
auto dfs_t(int const i, int const index) -> void
{
    // daca nodul apartine deja unui grup, pas
    if(g_ctc_index[i] != 0) {
        return;
    }

    g_ctc_index[i] = index;           // marcheaza ca nodul i apartine unui grup
    g_components[index].push_back(i); // de asemenea retine nodurile pentru grupul 'index'

    for(auto const node : g_graph_t[i]) {
        // toti vecinii apartin grpului 'index'
        dfs_t(node, index);
    }
}

auto main() noexcept -> int
{
    g_dfs_rev.reserve(g_graph.size());
    read_graph();

    int num_comp = 0;

    for(int i = 1; i <= g_num_nodes; ++i) {
        dfs(i);
    }

    // incepe practic de la radacina din dfs-ul normal, parcurge toti vecinii si marcheaza grupurile
    for(auto it = g_dfs_rev.rbegin(); it != g_dfs_rev.rend(); ++it) {
        int const el = *it;

        if(g_ctc_index[el] == 0) {
            dfs_t(el, ++num_comp);
        }
    }

    g << num_comp << '\n';

    // afiseaza componentele in sine
    for(auto const& p : g_components) {
        for(int const e : p.second) {
            g << e << ' ';
        }

        g << '\n';
    }
}
