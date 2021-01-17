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

## Graf Partial
- Un graf care are aceleasi varfuri cu graful "mare", si multimea muchiilor e inclusa in cea a grafului "mare"

## Subgraf
- Un graf care are multimea varfurilor inclusa in cea a grafului "mare", si multimea muchiilor e inclusa in cea a
grafului "mare"
- Un graf G1 se numeste subgraf indus de G daca multimea varfurilor e inclusa in cea a lui G, iar toate muchiile din G
au extremitatile in multimea varfurilor G1

## Graf Bipartit
- Un graf G = (V, E) care se poate imparti in:
```
V = V1 + V2(reuniune)
V1 & V2 = none(intersectie)
|e & V1| = |e & V2| = 1 forall e in E
```

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

# Probleme

## Nodurile Comune Lanturilor Optime Intre X si Y
<!-- Graf -->
- 2 bfs-uri, unul pornind de la X, celalat de la Y, tinand distantele in 2 vectori(dist\_start, dist\_end)
- Un nod se afla sigur intr-un lant optim daca:
```
dist_start[nod] + dist_end[nod] == dist_start[Y]
```
- Tin nodurile aflate la distanta i intr-un vector `level`
- Cand pe `level[i]` am doar un nod acela sigur e comun tuturor drumurilor

## Determinarea Componentelor Tare Conexe
<!-- ctc -->
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
