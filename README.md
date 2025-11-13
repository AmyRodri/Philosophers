# 🍽️ Philosophers  

> `philosophers` é uma simulação em C do clássico problema dos [**filósofos comensais**](https://handersonbf.github.io/jantarDosFilosofos/), proposto por [**Edsger Dijkstra**](https://pt.wikipedia.org/wiki/Edsger_Dijkstra).  
> O projeto explora **threads**, **mutexes** e **sincronização** em sistemas concorrentes, garantindo que filósofos possam **comer, dormir e pensar** sem gerar **deadlocks** ou **condições de corrida**.
> ```bash
> ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
> ```
> O objetivo é desenvolver um programa capaz de gerenciar a concorrência de forma eficiente, respeitando os tempos de cada ação e evitando conflitos no acesso aos garfos (recursos compartilhados).  

![Banner](https://img.shields.io/badge/Project-philosophers-blueviolet) ![C](https://img.shields.io/badge/Language-C-red) ![License](https://img.shields.io/badge/License-MIT-green)

---

## 🎯 Objetivo  

O projeto `philosophers` tem como objetivo simular o clássico problema dos **filósofos comensais**, proposto por **Edsger Dijkstra**, que representa de forma abstrata os desafios da **concorrência** e **sincronização de processos** em sistemas computacionais.  

Na simulação, vários filósofos estão sentados em volta de uma mesa circular. Cada um alterna entre três estados: **pensar**, **comer** e **dormir**.  
Para comer, um filósofo precisa pegar **dois garfos**, um à sua esquerda e outro à sua direita — porém, como os garfos são compartilhados entre vizinhos, isso gera uma disputa por recursos que pode levar a **deadlocks** ou **condições de corrida**, se o acesso não for controlado corretamente.  

O objetivo principal é implementar uma solução que:  
- Utilize **threads** para representar cada filósofo;  
- Empregue **mutexes** para controlar o acesso aos garfos (recursos compartilhados);  
- Garanta que o programa funcione **sem deadlocks**, **sem data races** e respeitando o tempo de cada ação (`time_to_die`, `time_to_eat`, `time_to_sleep`);  
- Seja capaz de detectar quando um filósofo morre (caso ultrapasse o tempo sem comer) e encerrar a simulação de forma controlada.  

Em resumo, o projeto treina a habilidade de **pensar em paralelismo**, **gerenciar recursos limitados** e **prevenir problemas clássicos da programação concorrente**.

---

## 💻 Como usar  

#### 📦 Compilação com Makefile  

Para compilar o projeto, basta rodar no terminal:  

```bash
make
```
Isso irá compilar todos os arquivos e gerar o executável `philo`.

#### ♻️ Outros comandos úteis

`make re` — recompila o projeto do zero (executa fclean e depois all)

`make clean` — remove os arquivos objeto .o

`make fclean` — remove os arquivos objeto e o executável

#### ▶️ Execução

O programa recebe 4 ou 5 argumentos na seguinte ordem:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
Exemplo:
```bash
./philo 5 800 200 200
```

Esse comando cria 5 filósofos, cada um com:

`time_to_die` = 800ms — tempo máximo sem comer antes de morrer

`time_to_eat` = 200ms — tempo que o filósofo leva para comer

`time_to_sleep` = 200ms — tempo que o filósofo dorme após comer

Durante a execução, o programa exibirá na saída padrão o estado de cada filósofo:
```bash
0     1  is thinking
0     1  has taken a fork
0     1  has taken a fork
0     1  is eating
200   1  is sleeping
400   1  is thinking
```

Essas mensagens representam a linha do tempo das ações de cada filósofo (com timestamp e ID).

⚙️ Exemplo prático

Simulação com 4 filósofos:
```bash
./philo 4 410 200 200
```

Saída esperada (pode variar de execução para execução):
```bash
0     1  is thinking
0     2  is thinking
0     3  is thinking
1     4  has taken a fork
1     4  has taken a fork
1     4  is eating
201   4  is sleeping
202   1  has taken a fork
202   1  has taken a fork
202   1  is eating
...
```

---

## ⚙️ Funcionalidades  

O projeto `philosophers` simula o comportamento dos filósofos de forma **concorrente** e **sincronizada**, controlando cuidadosamente o acesso aos recursos (garfos).  
Abaixo estão as principais funcionalidades implementadas:  

---

#### 🍴 Criação dos Filósofos  
- Cada filósofo é representado por uma **thread independente**.  
- Todas as threads são criadas simultaneamente e começam a executar suas rotinas (comer, dormir, pensar).  

---

#### 🔒 Controle de Concorrência  
- O acesso aos garfos é protegido por **mutexes**, evitando que dois filósofos peguem o mesmo garfo ao mesmo tempo.  
- A sincronização garante que nenhum filósofo “roube” o garfo de outro enquanto ele está comendo.  

---

#### ⏱️ Gerenciamento de Tempo  
- Cada ação (comer, dormir, pensar) respeita um tempo definido pelos argumentos passados ao programa.  
- O tempo de simulação é controlado com precisão em milissegundos, garantindo que todos os filósofos sigam o mesmo ritmo.  

---

#### 💀 Detecção de Morte  
- Um monitor supervisiona o tempo desde a última refeição de cada filósofo.  
- Se algum ultrapassar o `time_to_die` sem comer, o programa encerra a simulação e exibe:  

```bash
800   3  died
```

### 🧮 Número Máximo de Refeições (opcional)

Quando o argumento `number_of_times_each_philosopher_must_eat` é fornecido, a simulação termina assim que todos os filósofos comerem o número especificado de vezes.

---

## 🧠 Conceitos Fundamentais  

O projeto `philosophers` é uma introdução prática aos **problemas clássicos de concorrência** em programação de baixo nível.  
Ele exige compreensão profunda de como múltiplas unidades de execução (threads ou processos) compartilham e disputam recursos.  
A seguir estão os principais conceitos abordados:  


#### 🧵 Threads  
- Permitem a execução **paralela** de múltiplas rotinas dentro do mesmo processo.  
- Cada filósofo é uma thread independente que executa sua rotina (`eat`, `sleep`, `think`).  
- O compartilhamento de memória entre threads torna o controle de acesso essencial.  


#### 🔒 Mutex (Mutual Exclusion)  
- É um **mecanismo de exclusão mútua** usado para impedir que duas threads acessem simultaneamente o mesmo recurso.  
- Cada garfo é protegido por um mutex, que deve ser **travado (lock)** antes do uso e **destravado (unlock)** após o uso.  
- Evita **condições de corrida** e garante consistência no comportamento do programa.  


#### ⏱️ Sincronização e Temporização  
- A sincronização garante que ações como “comer” e “dormir” ocorram no tempo correto e sem sobreposição indevida.  
- O tempo é controlado com funções como `gettimeofday()` e `usleep()`, mantendo precisão em milissegundos.  


#### 🧩 Deadlock  
- Ocorre quando todos os filósofos pegam um garfo e ficam esperando indefinidamente pelo outro.  
- O projeto deve ser implementado de modo a **evitar deadlocks**, garantindo que pelo menos um filósofo consiga comer sempre.  


#### ⚔️ Race Condition  
- Situação onde duas threads tentam acessar ou modificar a mesma variável simultaneamente, gerando resultados imprevisíveis.  
- Prevenido com o uso correto de **mutexes** e **seções críticas bem delimitadas**.  


#### 🧠 Monitoramento e Controle  
- Uma thread ou função dedicada monitora constantemente o estado de todos os filósofos.  
- Ela verifica se algum passou do `time_to_die` e, se sim, interrompe a simulação.  


#### 🧮 Filosofia de Projeto  
O projeto incentiva o uso de **design limpo e modular**, separando responsabilidades entre:  
- Gerenciamento de dados (`t_data` e `t_philo`);  
- Rotinas dos filósofos (`eat`, `sleep`, `think`);  
- Funções de sincronização e impressão (`print_state`, `safe_usleep`, etc).  


> Esses conceitos formam a base da **programação concorrente em C**, preparando o estudante para lidar com sistemas complexos que envolvem **multitarefa, sincronização e paralelismo real**.

---

## 📂 Arquivos

```bash
philosophers/
├── 📁 include/              # Headers (.h) do projeto
│   └── *.h
│
├── 📁 srcs/                 # Código-fonte principal
│   ├── eat.c                # Função responsável pelo ato de comer dos filósofos
│   ├── main.c               # Função principal (inicializa o programa)
│   ├── monitor.c            # Monitora o estado dos filósofos (morte, finalização, etc)
│   ├── runtime.c            # Lida com a execução das threads e o ciclo de vida
│   ├── setup.c              # Configuração inicial das estruturas e mutexes
│   ├── utils.c              # Funções utilitárias e auxiliares
│   └── validate.c           # Validação dos argumentos e entradas
│
├── ⚙️ .gitignore            # Arquivos/pastas ignorados pelo Git
├── 🧩 Makefile              # Script de compilação
└── 📘 README.md             # Documentação do projeto
```
---

## 💭 Considerações e Dicas  

Esse projeto foi um grande aprendizado sobre **programação concorrente**, **sincronização de threads**, **gerenciamento de tempo**, e principalmente sobre como **pensar de forma paralela e segura**.  

Durante o desenvolvimento, o maior desafio foi encontrar um equilíbrio entre **sincronização correta e performance**, evitando **deadlocks** e **condições de corrida** sem travar o programa.  
Testar diferentes abordagens para o controle dos garfos, a detecção de morte e o gerenciamento das ações de cada filósofo ajudou muito a entender como pequenas decisões influenciam o comportamento de todo o sistema.  

A parte de **monitoramento e tempo** também foi essencial para consolidar o entendimento sobre controle de concorrência.  
Ela me forçou a pensar em **como medir o tempo com precisão**, **interromper todas as threads de forma segura** e garantir que o programa responda rapidamente quando algo dá errado.  

---

### ⚙️ Dicas para quem for fazer o projeto:
- 🧩 **Entenda bem o problema teórico** antes de começar a codar — saber o que é um deadlock, race condition e starvation vai te poupar muito tempo.  
- 🔒 **Proteja tudo com mutexes**, mas só o necessário — mutex demais pode travar o programa, mutex de menos causa caos.  
- ⏱️ **Implemente um `ft_usleep` preciso** — o `usleep()` padrão pode gerar atrasos ou inconsistências no timing.  
- 🧵 **Use uma thread de monitoramento** para detectar mortes em tempo real e encerrar a simulação de forma limpa.  
- 💡 **Sincronize as mensagens de saída** com um mutex — isso evita que os `printfs` se embaralhem.  
- 🧮 **Teste com diferentes parâmetros**: use valores curtos (`./philo 3 200 100 100`) para debugar e longos (`./philo 5 800 200 200`) para observar estabilidade.  
- ⚔️ **Cuide da ordem de pegar os garfos** — alternar a ordem entre filósofos pares e ímpares ajuda a prevenir deadlocks.  
- 🔁 **Simule manualmente com poucos filósofos** (1 ou 2) pra entender a lógica básica antes de generalizar.  
- 🪶 **Mantenha o código modular e limpo** — dividir bem as funções (`init`, `routine`, `monitor`, `print_state`, etc.) facilita o debug e evita erros sutis.  

> ✨ *No fim, o Philosophers não é sobre threads — é sobre paciência. Porque enquanto eles comem, dormem e pensam… você enlouquece tentando sincronizar tudo.*


---

## 👩‍💻 Autoria

**✨ Amy Rodrigues ✨** 

🎓 Estudante de C e desenvolvimento de baixo nível na [42 São Paulo](https://www.42sp.org.br/)

🐧 Usuária de Linux | 💻 Fã de terminal | 🎯 Apaixonada por entender como tudo funciona por trás dos bastidores

---

## 📎 Licença

Este projeto foi desenvolvido como parte do currículo educacional da 42 São Paulo.

📘 **Uso permitido**:
- Pode ser utilizado como referência para estudos e aprendizado individual
- Pode servir de inspiração para seus próprios projetos

🚫 **Proibido**:
- Submeter cópias deste projeto como se fossem de sua autoria em avaliações da 42 ou outras instituições

Seja ético e contribua para uma comunidade de desenvolvedores mais honesta e colaborativa 🤝
