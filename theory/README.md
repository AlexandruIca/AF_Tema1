# General

## Drum
- Secventa de varfuri, intre oricare 2 varfuri exista un arc
- Drum simplu: nu contine un arc de mai multe ori
- Drum elementar: nu contine un varf de mai multe ori

## Circuit
- Drum simplu cu capetele identice
- Circuit elementar: drumul asociat e elementar

## Lant
- Secventa de varfuri cu propr. ca oricare 2 vf. consecutive sunt adiacente

## Lant vs Drum
- La lant nu conteaza orientarea arcelor, conteaza doar ca oricare 2 noduri consecutive exista o muchie cu acele extremitati
- La drum trebuie sa pot sa merg efectiv prin noduri

## Drum Eulerian
- Trece prin fiecare muchie exact odata

## Drum Hamiltonian
- Trece prin fiecare varf exact odata

## Graf Partial
- Un graf care are aceleasi varfuri cu graful "mare", si multimea muchiilor e inclusa in cea a grafului "mare"

## Subgraf
- Un graf care are multimea varfurilor inclusa in cea a grafului "mare", si multimea muchiilor e inclusa in cea a
grafului "mare"
- Un graf G1 se numeste subgraf indus de G daca multimea varfurilor e inclusa in cea a lui G, iar toate muchiile din G
au extremitatile in multimea varfurilor G1

## Graf Transpus
- Matricea de adiacență transpusă
- Folosit de exemplu pentru aflarea componentelor tare conexe

## BFS
- Complexitate: O(V + E) sau O(n + m)
- Se poate folosi pt. drumul cel mai scurt intr-un graf neponderat

## Sortare Topologica
- Complexitate: O(V + E)
- Pentru detectare de cicluri: parcurg stiva generata, pentru fiecare nod tin un index pe care il incrementez in loop,
la final daca parcurg sortarea topologica si daca index-ul unui parinte nu apare primul atunci exista ciclu

## Nod/Muchie critica
- Daca s-ar scoate graful nu ar mai fi conex

## Muchii de Intoarcere
- Leaga un fiu cu un stramos de-al lui in arbore, nu pot fi critice

## Arbori Partiali
- Orice graf neorientat conex contine un arbore partial

## Arbori Partiali de Cost Minim
- Prim & Kruskal
- Nu sunt unici, dar mai multi arbori partiali de cost minim au acelasi cost
- Folositori la probleme de clustering

## Kruskal
- Complexitate pentru liste de adiacenta(pentru matrice de adiacenta: Prim):
  * Sortare: O(m log m) = O(m log n)
  * n * reuniune: O(n^2)
  * Per total: O(m log n + n^2)
- Ordonez muchiile crescator dupa cost
- O muchie de la `a` la `b` nu formeaza ciclu daca `grupa[a] != grupa[b]`
- Pentru a vedea ce grupa are un nod:
```python
def get_group(node):
    if group[node] == node:
        return node

    group[node] = get_group[group[node]]
    return group[node]
``` 
- Pentru a adauga o muchie de la `a` la `b` se reuneste grupa lui `a` cu `b`:
```python
def union(a, b):
    group[get_group(a)] = get_group(b)
```
- Pentru fiecare muchie, daca nu formeaza ciclu cu graful deja format, adaug la APCM
- Ma opresc la n-1 muchii

## Prim
- Complexitate:
  * Search: O(V^2)
  * Heap: O((V + E) log V)
  * Fibonacci heap: O(E + (V log V))
- Pornesc de la un nod care formeaza arborele si adaug noduri vecine cu cost minim
- Pot sa tin nodurile vecine intr-un heap sortat dupa distante
- Ceva de genul:
```python
start_node = 1
queue = [start_node]
distance.fill(inf)
parent.fill(0)
distance[start_node] = 0

while not queue.empty():
    node = queue.extract_min()
    add_to_tree(node)
    
    for neighbor in graph[node]:
       queue.append(neighbor)
```

## Drum Minim
- Pentru un graf care nu e ponderat: BFS
- Un arbore partial de cost minim nu este neaparat un arbore de distante minime
- De la un nod la toate celelalte: Dijkstra
  * Daca avem muchii cu cost negativ: Bellman-Ford
  * Pentru cost negativ, NU se poate aduna o constanta la fiecare cost, dupa aplicand Dijkstra
- Intre orice pereche de noduri: Floyd Warshall
- Pentru un DAG:
  * Parcurg varfurile in ordinea data de sortarea topologica
  * Relaxez pentru fiecare varf arcele care ies din el
  * ```python
    for node in top_sort():
        for neighbor in graph[node]:
            if distance[node] + cost(node, neighbor) < distance[neighbor]:
                distance[neighbor] = distance[node] + cost(node, neighbor)
    ```
  * Complexitate: O(M + N)
- Pentru drum minim intre toate perechile de varfuri(pot fi costuri negative dar nu cicluri de cost negativ):
  * Floyd-Warshall: Complexitate O(n^3)
  * Pentru k = 1..=n se calculeaza costul minim de la i la j avand varfuri intermediare doar din multimea {1, 2, ..., k}
  * Ceva de genul:
  ```python
  distance[i][j] = weight[i][j]
  parent[i][j] = i if ij in edges else 0

  for k in 1..=n:
      for i in 1..=n:
          for j in 1..=n:
              if distance[i][j] > distance[i][k] + distance[k][j]:
                  distance[i][j] = distance[i][k] + distance[k][j]
                  parent[i][j] = parent[k][j]
  ```
  * Pentru a vedea si drumul:
  ```python
  def path(i, j):
      if i != j:
          path(i, parent[i][j])
      print(j)
  ```
  * Daca A = matrice de adiacenta atunci a_ij^k din A^k reprezinta numarul de drumuri distincte de lungime k de la i la j(nu neaparat elementare)

## Inchidere Tranzitiva
- Roy-Warshall: complexitate O(n^3)
- Graf NEPONDERAT
- Ceva de genul:
```python
d = # matrice de adiacenta
# Ca la Floyd-Warshall
for k:
  for i:
    for j:
      d[i][j] = d[i][j] or (d[i][k] and d[k][j])
```

## Flux
- Orice retea admite cel putin un flux, cel vid

## Flux Maxim
- Ford-Fulkerson: complexitate O(mL) sau O(nmC), C = capacitate
- Edmonds-Karp - o varianta de Ford-Fulkerson

## Edmonds-Karp
- Complexitate: O(n m^2)
- Ceva de genul:
```python
def bfs():
    nodes = [start_node] # queue

    while not nodes.empty():
        current = nodes.pop()

        for neighbor in graph[current]:
            if parent[neighbor] == 0 and capacity[current][neighbor] > 0:
                parent[neighbor] = current
                nodes.push(neighbor)

    return parent[graph.count()]
```
Folosit asa:
```python
capacity[i][j] = capcity # Input
capacity[j][i] = 0 # graful rezidual

while bfs() != 0:
    for neighbor in graph[-1]:
        min_capacity = capacity[neighbor][graph.count()]
        min_capacity = min(min_capacity, capacity[parent[i]][i] for i = neighbor, i != start_node, i = parent[i])

        capacity[parent[i]][i] -= min_capacity
        capacity[i][parent[i]] += min_capacity # rezidual

        flow += min_capacity

    parent.fill(0)
```

## Graf Bipartit
- Teorema Konig:
  * Graful G este bipartit <=> toate ciclurile elementare din G sunt pare
  * Algoritm pentru a testa daca un graf este bipartit:
    - Coloram cu 2 culori un arbore partial al sau printr-o parcurgere(coloram orice vecin j nevizitat al varfului curent i cu o culoare diferita de cea a lui i)
    - Testam daca celelalte muchii de la i la vecini j deja vizitati au extremitatile i si j colorate diferit

## Cuplaj
- Multime M inclusa in multimea muchiilor grafului in care oricare 2 muchii nu sunt adiacente
- Cuplaj de cardinal maxim: cat mai multe muchii

## Cuplaj Maxim in Graf Bipartit
- Reducerea la flux maxim:
  * Complexitate: O(n m)
  * Se adauga 2 noduri s si t, unul inainte de prima partitie, al doilea la final
  * Se transforma muchiile in graful bipartit in arce(directie)
  * Asociez fiecarui arc capacitatea 1
  * Calculez fluxul maxim

## Teorema lui Euler
- Un graf G e eulerian <=> orice varf din G e par
- G are un lant eulerian <=> G are cel mult 2 varfuri de grad impar

## Graf Eulerian
- Algoritmul lui Hierholzer pt a determina ciclu eulerian:
  * Complexitate: O(m)
  * Pornesc cu un ciclu eulerian, aleg un nod, ii adaug muchiile incidente care nu se gasesc in ciclu, repeta
  * Daca sirul contine toate muchiile, graful e eulerian

# Probleme

## Nodurile Comune Lanturilor Optime Intre X si Y
<!-- Graf -->
- Complexitate: O(V + E)
- 2 bfs-uri, unul pornind de la X, celalat de la Y, tinand distantele in 2 vectori(dist\_start, dist\_end)
- Un nod se afla sigur intr-un lant optim daca:
```
dist_start[nod] + dist_end[nod] == dist_start[Y]
```
- Tin nodurile aflate la distanta i intr-un vector `level`
- Cand pe `level[i]` am doar un nod acela sigur e comun tuturor drumurilor

## Determinarea Componentelor Tare Conexe
<!-- ctc -->
- Complexitate: O(V + E)
- Tin si graful normal si cel transpus
- Fac dfs pe cel normal, tin dfs-ul intr-un vector `lista`
- Parcurg `lista` in ordine inversa, facand dfs pe graful transpus:
```python
group: Dict[int, int] = {}

def dfs_t(node, index):
    if node in group and group[node] != 0:
        return

    group[node] = index
    # Daca am nevoie si de componente in sine
    components[index].append(node)

    for neighbor in graph[node]:
        dfs_t(neighbor, index)

for el in lista.reverse():
    if el in group and group[el] == 0:
        dfs_t(el, num_components + 1)
        num_components += 1
```

## Determinarea Punctelor/Muchiilor Critice
- Complexitate: O(V + E)
- Ceva de genul:
```python
def dfs(node):
    visited[node] = True
    min_level[node] = level[node]

    for neighbor in graph[node]:
        if not visited[neighbor]:
            level[neighbor] = level[node] + 1
            dfs(neighbor)
            min_level[node] = min(min_level[node], min_level[neighbor])

            if min_level[neighbor] > min_level[node]:
                # Muchie critica
        else:
            if level[neighbor] < level[node] - 1:
                # Muchie de intoarcere
                min_level[node] = min(min_level[node], min_level[neighbor])
```
- Pentru puncte critice:
  * Daca e radacina si are cel putin 2 fii
  * Are cel putin un fiu j cu `min_level[j] >= level[i]`

## Bellman-Ford
- Complexitate: O(EV)
- Functioneaza pe graf cu costuri nu neaparat pozitive
- Ceva de genul:
```python
for i in range(nr_varfuri):
    for edge in muchii:
        if distance[edge.from] + edge.cost < distance[edge.to]:
            distance[edge.to] = distance[edge.from] + edge.cost
```
- Pentru a detecta cicluri negative:
```python
# la fel ca inainte
if distance[edge.from] + edge.cost < distance[edge.to]:
    # nodul face parte dintr-un ciclu negativ
```

## Dijkstra
- Complexitate: O((E + V)log(V)) in varianta cu heap
- Ceva de genul:
```python
nodes := priority_queue()

while not nodes.empty():
    current = nodes.pop()

    for neighbor in graph[current]:
        if distance[current] + neighbor.weight < distance[neighbor]:
            distance[neighbor] = distance[current] + neighbor.weight

            if not visited[current]:
                visited[current] = True
                nodes.push(current)
```
