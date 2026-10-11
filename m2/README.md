# Trabalho M2 — Grafos: Coloração e Árvore Geradora Mínima (AGM)

Implementação completa em C++17 dos métodos exigidos para a M2 (Parte 1 e Parte 2), reutilizando a base de grafos da M1.

---

## Estrutura do Projeto M2

```
m2/
├── Makefile                          # Script de compilação e execução
├── README.md                         # Documentação completa e explicação dos algoritmos
├── docs/                             # PDFs dos enunciados e slides da M2
├── graph_examples/                   # Casos de teste nos formatos especificados (V A D P)
│   ├── coloring_s08_house.txt        # Grafo do slide S08 (Casa com diagonal - 5 vértices)
│   ├── coloring_s08_welsh.txt        # Grafo do slide S08 Welsh & Powell (5 vértices)
│   ├── coloring_cycle5.txt           # Ciclo C5 (ímpar, χ = 3)
│   ├── coloring_bipartite.txt        # Grafo bipartido completo K3,3 (χ = 2)
│   ├── coloring_petersen.txt         # Grafo de Petersen (10 vértices, χ = 3)
│   ├── coloring_medium.txt           # Grafo médio para benchmark de coloração (10 vértices)
│   ├── coloring_large.txt            # Grafo grande para benchmark (100 vértices, 600 arestas)
│   ├── coloring_huge.txt             # Grafo HUGE para estresse de coloração (3.000 vértices, 20.000 arestas)
│   ├── mst_s09_slide.txt             # Grafo do slide S09 (Exemplo de aula, custo total = 18)
│   ├── mst_s09_exercise.txt          # Grafo do exercício dos slides S09 (custo total = 17)
│   ├── mst_medium.txt                # Grafo médio ponderado (10 vértices, 14 arestas)
│   ├── mst_large.txt                 # Grafo grande ponderado (100 vértices, 600 arestas)
│   └── mst_huge.txt                  # Grafo HUGE ponderado (3.000 vértices, 20.000 arestas)
├── build/
│   └── main                          # Executável gerado
└── src/
    ├── main.cpp                      # Ponto de entrada com testes completos e suporte a CLI
    ├── graph/                        # Modelagem das estruturas de dados de grafos
    │   ├── edge.h                    # Representação de aresta
    │   ├── graph.h / graph.cpp       # Interface base polimórfica
    │   ├── list_graph.h / .cpp       # Lista de adjacência
    │   └── matrix_graph.h / .cpp     # Matriz de adjacência
    ├── io/
    │   └── graph_reader.h / .cpp     # Leitor do formato de arquivo (V A D P)
    └── algorithms/
        ├── coloring/                 # PARTE 1: Coloração de Grafos
        │   ├── coloring_result.h     # Struct de resultado (cores, tempo, atribuição)
        │   ├── brute_force.h / .cpp  # Força Bruta (testando 2, 3, ... cores)
        │   ├── welsh_powell.h / .cpp # Heurística Welsh & Powell
        │   ├── dsatur.h / .cpp       # Heurística DSATUR (Grau de Saturação)
        │   └── ordem_arbitraria.h / .cpp # Heurística sem critério de ordem (Ordem Arbitrária)
        └── mst/                      # PARTE 2: Árvore Geradora Mínima
            ├── mst_result.h          # Struct de resultado (arestas, peso total, tempo)
            ├── prim.h / .cpp         # Algoritmo de Prim
            └── kruskal.h / .cpp      # Algoritmo de Kruskal (com Union-Find / Disjoint-Set)
```

---

## Como Compilar e Executar

Dentro da pasta `m2/`:

```bash
# Compilar o projeto
make build

# Executar a bateria de demonstração completa
make run

# Limpar arquivos de build
make clean
```

### Execução de Arquivos Customizados via Linha de Comando:
```bash
# Executar apenas coloração em um grafo específico:
./build/main --color graph_examples/coloring_petersen.txt

# Executar apenas AGM em um grafo ponderado específico:
./build/main --mst graph_examples/mst_s09_slide.txt

# Detecção automática pelo cabeçalho (D e P):
./build/main graph_examples/mst_s09_slide.txt
```

---

## Parte 1: Coloração de Grafos

O problema consiste em atribuir uma cor a cada vértice de tal forma que dois vértices adjacentes (conectados por uma aresta) nunca compartilhem a mesma cor. O menor número de cores necessário é chamado de **número cromático** $\chi(G)$.

### 1. Força Bruta (`brute_force.cpp`)
- **Funcionamento**: Testa exaustivamente todas as combinações possíveis de cores. Começa testando se o grafo é $2$-colorível ($k=2$). Se não for viável, testa com $3$ cores ($k=3$), e assim por diante até encontrar a menor quantidade de cores que permita uma coloração válida.
- **Complexidade**: $O(k^V)$ — exponencial. Inviável para grafos grandes ($V > 20$), mas garante a solução matematicamente ótima para grafos pequenos.
- **Caso especial**: Se o grafo não possui arestas, $1$ cor é suficiente.

### 2. Welsh & Powell (`welsh_powell.cpp`)
- **Funcionamento**: Colore o grafo utilizando uma cor por vez, priorizando os vértices mais restritivos (com maior grau):
  1. Ordena os vértices em ordem decrescente de grau.
  2. Inicializa todos os vértices como sem cor.
  3. Enquanto houver vértices sem cor:
     - Define a próxima cor disponível $c$.
     - Itera sobre os vértices sem cor (na ordem decrescente de grau): caso nenhum vizinho possua a cor $c$, atribui $c$ ao vértice.
- **Complexidade**: $O(V \log V + V^2)$.

### 3. DSATUR (`dsatur.cpp`)
- **Funcionamento**: Baseia-se no **Grau de Saturação** de cada vértice, definido como a quantidade de cores distintas presentes entre os seus vizinhos:
  1. Ordena os vértices por grau decrescente e atribui a cor 0 ao vértice de maior grau.
  2. Enquanto houver vértices sem cor:
     - Escolhe o vértice com o maior grau de saturação.
     - Em caso de empate, escolhe o de maior grau no grafo original.
     - Atribui a menor cor não utilizada por nenhum vizinho adjacente.
     - Atualiza os graus de saturação dos vizinhos não coloridos.
- **Complexidade**: $O(V^2)$ ou $O(V \cdot \Delta)$, oferecendo uma das melhores aproximações de coloração conhecidas na literatura.

### 4. Sem Critério de Ordem / Ordem Arbitrária (`ordem_arbitraria.cpp`)
- **Funcionamento**: Itera sobre os vértices na sua ordem arbitrária/natural ($0, 1, \dots, V-1$) conforme especificado no enunciado ("*somente escolhendo em uma cor para cada vértice que não esteja em seus vizinhos em ordem arbitrária*"). Para cada vértice, descobre quais cores já foram atribuídas aos vizinhos e seleciona a primeira cor viável (menor índice inteiro $\ge 0$).
- **Complexidade**: $O(V + E)$ ou $O(V^2)$ no pior caso. É muito rápida, porém sensível à ordem de inserção dos vértices.

---

## Parte 2: Árvore Geradora Mínima (AGM)

Dado um grafo não orientado e ponderado $G$, a Árvore Geradora Mínima é um subgrafo que conecta todos os vértices sem formar ciclos, minimizando a soma dos pesos das arestas.

### 1. Algoritmo de Prim (`prim.cpp`)
- **Funcionamento**:
  1. Inicia um conjunto $S$ vazio de arestas para a solução.
  2. Inicia o conjunto de controle $Q$ com todos os vértices do grafo.
  3. Escolhe um vértice inicial arbitrário $A$ e o remove de $Q$.
  4. Enquanto $Q$ não estiver vazio:
     - Encontra a menor aresta $\{u, v\}$ tal que um vértice pertence a $Q$ e o outro pertence a $V \setminus Q$ (corte da árvore).
     - Adiciona $\{u, v\}$ a $S$.
     - Remove de $Q$ o vértice correspondente.
- **Estrutura utilizada**: Fila de prioridade (min-heap) para seleção da aresta mínima em tempo $O(E \log V)$.

### 2. Algoritmo de Kruskal (`kruskal.cpp`)
- **Funcionamento**:
  1. Inicia o conjunto de solução $S = \emptyset$.
  2. Inicia o conjunto de controle $Q$ com todas as arestas do grafo.
  3. Inicia uma floresta $F$ com cada vértice isolado em sua própria árvore (estrutura *Disjoint Set Union* / Union-Find).
  4. Ordena as arestas de $Q$ em ordem crescente de peso.
  5. Enquanto $Q$ não estiver vazio (e $|S| < V - 1$):
     - Seleciona e remove a menor aresta $\{u, v\}$ de $Q$.
     - Se $u$ e $v$ pertencem a árvores diferentes em $F$ (`find(u) != find(v)`):
       - Adiciona $\{u, v\}$ a $S$.
       - Une as árvores contendo $u$ e $v$ (`union(u, v)`).
- **Estrutura utilizada**: Union-Find com *path compression* e *union by rank* ($O(E \log E)$).

