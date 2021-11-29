**Modos de comunicação**
*OpenMP vs MPI*

OpenMP is a way to program on shared memory devices. This means that the parallelism occurs where every parallel thread has access to all of your data.

You can think of it as: parallelism can happen during execution of a specific for loop by splitting up the loop among the different threads.

MPI is a way to program on distributed memory devices. This means that the parallelism occurs where every parallel process is working in its own memory space in isolation from the others.


Because our project will have devices with independent memories the best comunication mode to implement is MPI.


**MPI**
O uso de MPI levanta questões de escalabilidade, dado o espaço de estados do processo de verificação crescer exponencialmente com o número de processos considerados.

A abordagem considerada para a verificação de programas MPI é baseada em tipos de sessão multi-participante. A ideia base passa por especificar o protocolo de comunicação a ser respeitado por um conjunto de participantes que comunicam entre si trocando mensagens. 

A partir de um protocolo expresso desta forma, é possível extrair por sua vez o protocolo local de cada um dos participantes, segundo uma noção de projecção de comportamentos. Se para cada participante (processo) no programa MPI se verificar a aderência ao protocolo local respectivo, são garantidas propriedades como a ausência de condições de impasse e a segurança de tipos. A verificação desta aderência é feita sobre programas C que usam MPI, usando a ferramenta VCC da Microsoft Research.
A partir de um protocolo expresso nessa linguagem. é gerado um header C que exprime o tipo num formato compatível com a ferramenta VCC.

**WEBGRAFIA**:
1. https://www.iottrends.tech/blog/how-to-cluster-raspberry-pi-4/
2. https://repositorio.ul.pt/handle/10451/10051?locale=en

