# Jantar dos Filósofos MC504

Programa para visualizar o clássico problema do Jantar dos Filósofos.

![image](https://github.com/reyotak/MC504/assets/60493369/d255ff44-3af4-430d-ab61-695c3b5a8a53)

O problema sugerido por Dijkstra em 1965, é definido no LittleBookOfSemaphores como:

![image](https://github.com/reyotak/MC504/assets/60493369/a4ac6504-63d9-41fb-bd07-b6c54e8ced71)

O código filosofos.c segue esse loop. No entanto, ao invés de ter um loop infinito (while true), teremos um número finito de refeições disponíveis.

O programa possui 5 filósofos e 5 garfos.

## Instruções

Ao rodar o programa, será exibida a segunite mensagem:

![image](https://github.com/reyotak/MC504/assets/60493369/1f8fc3c6-ee73-4b51-851c-172a60fcf5b8)

Como exemplo, teremos um número de 10 refeições. Após isso, aparecerá a seguinte mensagem:

![image](https://github.com/reyotak/MC504/assets/60493369/d60b2325-f572-4ceb-8fe7-62ba3f7d66c9)

Colocaremos por exemplo um tempo de 2 segundos. A seguir:

![image](https://github.com/reyotak/MC504/assets/60493369/582dc0fe-f186-4d9e-84a2-e1bcd33ab87e)

Neste caso colocaremos 1 segundo. Após apertarmos "Enter" o programa começará a rodar.

## Estados dos Filósofos

Estado Pensando:
![image](https://github.com/reyotak/MC504/assets/60493369/21f3bac4-c595-4d27-a0fc-c03aa4255d0d)

Estado Segurando Garfo Esquerdo Apenas:
![image](https://github.com/reyotak/MC504/assets/60493369/7c6567a0-cc98-4632-9a46-2f8fa7686716)

Estado Segurando Garfo Direito Apenas:
![image](https://github.com/reyotak/MC504/assets/60493369/34d7488e-f900-4124-bc97-c0a54a777caf)

Estado Comendo:
![image](https://github.com/reyotak/MC504/assets/60493369/03684f44-f734-42ef-a60b-5096178ac5f0)

Toda vez que um filósofo fizer uma ação (pegar o garfo, soltar o garfo, pensar ou comer) será printada o estado da mesa:
![image](https://github.com/reyotak/MC504/assets/60493369/026297f3-3340-4e5e-a3c3-8e5f7b413f78)

Note que a mesa é circular. E portando o primeiro filósofo compartilha o garfo com o último.

## Lógica da Programa

Cada filósofo será representado por uma thread. A ação de cada thread segue a filosofia pensar -> pegar garfo -> comer -> soltar garfo -> pensar ... até que as refeições acabem.

Para controlarmos o número de refeições utilizaremos uma variável condicional counter. Ela contará quantas refeições foram feitas no total das threads.

Para evitarmos "Race conditions" dos garfos, cada garfo será um mutex.

Ao usarmos mutex, o problema do jantar do filósofo apresenta um impasse quando por exemplo todos os filosófos pegam o garfo esquerdo/direito ao mesmo tempo (Deadlock). Para resolvermos este impasse foi adicionada a segunites condições:

- O filósofo da posição par sempre pega inicialmente o garfo esquerdo. 
- O filósofo da posição impar sempre pega inicialmente o garfo direito.
- O filósofo solta primeiro o garfo esquerdo. 
