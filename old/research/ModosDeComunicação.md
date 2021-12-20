**Modos de comunicação**
*OpenMP vs MPI*

OpenMP é uma forma de programar em dispositivos de memória compartilhada. Isto significa que o paralelismo ocorre onde cada processo paralelo tem acesso a todos os seus dados.

O paralelismo pode acontecer durante a execução de um loop *for* específico, dividindo-se o loop entre as diferentes threads.

MPI é uma forma de programar em dispositivos de memória distribuída. Isso significa que o paralelismo ocorre onde cada processo paralelo está trabalhando em seu próprio espaço de memória, isolado dos restantes.

Como o nosso projeto terá dispositivos com memórias independentes, o melhor modo de comunicação a ser implementado é o MPI.


**MPI**
O uso de MPI levanta questões de escalabilidade, dado o espaço de estados do processo de verificação crescer exponencialmente com o número de processos considerados.

A abordagem considerada para a verificação de programas MPI é baseada em tipos de sessão multi-participante. A ideia base passa por especificar o protocolo de comunicação a ser respeitado por um conjunto de participantes que comunicam entre si trocando mensagens. 

A partir de um protocolo expresso desta forma, é possível extrair por sua vez o protocolo local de cada um dos participantes, segundo uma noção de projecção de comportamentos. Se para cada participante (processo) no programa MPI se verificar a aderência ao protocolo local respectivo, são garantidas propriedades como a ausência de condições de impasse e a segurança de tipos. A verificação desta aderência é feita sobre programas C que usam MPI, usando a ferramenta VCC da Microsoft Research.
A partir de um protocolo expresso nessa linguagem é gerado um header C que exprime o tipo num formato compatível com a ferramenta VCC.



**Protocolos**
Neste site, fala-se e mostra exemplos de como o MPI funciona com protocolos.
https://www.di.fc.ul.pt/~vv/papers/martins.santos.etal_especificacao-verificacao-MPI.pdf

**WEBGRAFIA**:
1. https://www.iottrends.tech/blog/how-to-cluster-raspberry-pi-4/
2. https://repositorio.ul.pt/handle/10451/10051?locale=en
3. https://www.di.fc.ul.pt/~vv/papers/martins.santos.etal_especificacao-verificacao-MPI.pdf
