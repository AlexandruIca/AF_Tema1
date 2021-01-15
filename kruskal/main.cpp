#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <numeric>
#include <vector>

constexpr auto max_num_edges = 400'001;
constexpr auto max_num_nodes = 200'001;

struct edge
{
    int from = 0;
    int to = 0;
    int cost = 0;

    edge() noexcept = default;
    edge(edge const&) noexcept = default;
    edge(edge&&) noexcept = default;
    ~edge() noexcept = default;

    edge(int const f, int const t, int const c) noexcept
        : from{ f }
        , to{ t }
        , cost{ c }
    {
    }

    auto operator=(edge const&) noexcept -> edge& = default;
    auto operator=(edge&&) noexcept -> edge& = default;
};

std::array<int, max_num_nodes> g_group;

// intoarce grupa in care se afla nodul i
auto get_group(int const i) noexcept -> int
{
    // daca g_group[i] == i inseamna ca nodul a fost de la inceput in acea grupa, nu mai are rost sa caut
    if(g_group[i] == i) {
        return i;
    }

    // altfel, cauta in ce grupa e la 'vecin'
    g_group[i] = get_group(g_group[i]);

    return g_group[i];
}

// initial nodul i se afla intr-o anumita grupa k, daca in g_group[k] pun valoarea grupei lui j, atunci cand se va
// apela get_group nu se va opri la k, va continua si la grupa lui j, deci se face reuniune
auto make_union_for(int const i, int const j) noexcept -> void
{
    g_group[get_group(i)] = get_group(j);
}

auto main() noexcept -> int
{
    std::ifstream f{ "apm.in" };
    std::ofstream g{ "apm.out" };

    int n = 0;
    int m = 0;

    f >> n >> m;

    std::vector<edge> edges;
    std::vector<int> answer{};
    std::int64_t sum = 0;

    edges.reserve(max_num_edges);
    edges.emplace_back();

    for(int i = 1; i <= m; ++i) {
        int from = 0;
        int to = 0;
        int cost = 0;

        f >> from >> to >> cost;

        edges.emplace_back(from, to, cost);
    }

    // initial, fiecare nod este in grupa lui
    std::iota(g_group.begin() + 1, g_group.begin() + n + 1, 1);
    // sortez muchiile in ordine crescatoare dupa cost
    std::sort(edges.begin() + 1, edges.end(), [&](auto const& a, auto const& b) { return a.cost < b.cost; });

    // pentru fiecare muchi
    for(int i = 1; i <= m; ++i) {
        // daca nodurile nu fac parte din aceeasi grupa atunci nu se formeaza ciclu, se pastreaza proprietatea de arbore
        // deci pot sa adaug la solutie
        if(get_group(edges[i].from) != get_group(edges[i].to)) {
            sum += edges[i].cost;
            make_union_for(edges[i].from, edges[i].to);
            answer.push_back(i);
        }
    }

    g << sum << std::endl;
    g << n - 1 << std::endl;

    for(auto const idx : answer) {
        g << edges[idx].from << ' ' << edges[idx].to << std::endl;
    }
}
