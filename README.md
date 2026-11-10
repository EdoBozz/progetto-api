# Progetto di Algoritmi e Principi dell'Informatica — Ottimizzazione dei Percorsi

**Politecnico di Milano | Laurea Triennale in Ingegneria Informatica | A.A. 2024/2025**

# Descrizione del progetto #

Il progetto è stato sviluppato nell'ambito del corso di **Algoritmi e Principi dell'Informatica** del Politecnico di Milano.

L'obiettivo consiste nella realizzazione di un programma in **linguaggio C** per la gestione di una rete di trasporto rappresentata attraverso una mappa esagonale.

Il sistema permette di modificare dinamicamente i costi di attraversamento, aggiungere o rimuovere collegamenti aerei e calcolare il percorso a costo minimo tra due punti della mappa.

# Funzionalità principali #

Il programma supporta quattro operazioni:

- **`init`** — Inizializza una mappa esagonale con un numero specificato di righe e colonne.
- **`change_cost`** — Modifica i costi di attraversamento degli esagoni all'interno di un determinato raggio.
- **`toggle_air_route`** — Aggiunge o rimuove collegamenti aerei direzionali tra due esagoni.
- **`travel_cost`** — Calcola il costo minimo necessario per raggiungere una destinazione a partire da un punto iniziale.

La rete di trasporto può essere modificata dinamicamente durante l'esecuzione del programma.

# Algoritmi e strutture dati #

L'implementazione utilizza diversi algoritmi e strutture dati:

- **Grafi e liste di adiacenza:** rappresentazione dei collegamenti tra gli esagoni della mappa.
- **Algoritmo di Dijkstra:** ricerca dei percorsi a costo minimo.
- **Min-heap:** gestione dei nodi durante l'esplorazione del grafo.
- **Tabelle hash:** gestione dei nodi visitati durante le operazioni di aggiornamento dei costi.
- **Allocazione dinamica della memoria:** gestione della mappa e delle strutture dati associate.

# Implementazione #

La mappa esagonale viene rappresentata mediante un grafo, nel quale ogni esagono corrisponde a un nodo e i collegamenti rappresentano i possibili spostamenti.

A ogni collegamento è associato un costo, che può variare durante l'esecuzione del programma.

Il sistema riceve i comandi tramite **standard input** e restituisce i risultati attraverso **standard output**.

# Tecnologie utilizzate #

- **Linguaggio:** C
- **Competenze:** algoritmi e strutture dati, teoria dei grafi, ricerca di percorsi minimi, gestione dinamica della memoria.

# Struttura del repository #

- `Progetto.c` — Codice sorgente del programma.
- `Specifica_2024_2025.pdf` — Specifica originale del progetto.

---

*Progetto universitario realizzato nell'ambito del corso di Laurea Triennale in Ingegneria Informatica presso il Politecnico di Milano.*
