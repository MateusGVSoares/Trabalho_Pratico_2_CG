# Lista 3 Computação Gráfica


# TODO
- Fazer o sistema de som -> Implementado >_<
- Fazer o parser para modelo .obj
- Impedir a nave de sair do sistema 
- Criar uma textura ou modelo de nave 


## Integrantes:

-   Mateus Soares   - Matrícula : 20223303314
-   Matheus Menezes - Matrícula : 20223003234
-   Laura Pianetti  - Matrícula : 20223002424
-   Adjailson       - Matrícula :
-   Lucas           - Matrícula :
-   Gustavo         - Matrícula :

## Bibliotecas Necessárias:

-   FreeGlut - sudo apt-get install freeglut3-dev
-   GLEW - sudo apt-get install libglew-dev
-   SOIL - sudo apt-get install libsoil-dev

## Como Compilar e Executar

-   No terminal, na pasta do projeto, dê o comando 'make run' para compilar e executar o projeto
-   Para apenas compilar o projeto, no terminal d&e o comando 'make all'
-   Para apenas executar o projeto, no terminal dê o comando './main', para executar o programa

## Teclas:

-   Utilize Z para aumentar a iluminação ambiente e X para diminuí-la
-   Utilize C para aumentar a iluminação difusa e V para diminuí-la
-   Utiliza B para aumentar a iluminação especular e N para diminuí-la

## Instruções Para Escrever o Script de Planetas

-   Escreva na primeira linha SISTEMA
-   Na segunda linha a quantidade total de planetas e luas
-   O resto será a descrição dos planetas, que deve seguir a seguinte ordem :

    -   1. A origem do planeta - Se este orbitar algum, está origem não importa
    -   2. O raio da esfera que representa o planeta
    -   3. O parâmetro a da órbita elíptica do planeta
    -   4. O parâmetro b da órbita elíptica do planeta
    -   5. A velocidade angular com que o planeta rotaciona em torno do próprio eixo
    -   6. A velocidade angular com que o planeta rotaciona na órbita
    -   7. Indica se o planeta emite luz ou não (1 - Emite / 0 - Não emite )
    -   8. !IMPORTANTE : Se o planeta emitir, passe 9 valores de ponto decimal que indicam, nesta ordem, as propriedades da luz emitida (Luz Ambiente | Luz Ambiente | Luz Especular)
    -   9. Quantidade de corpos que orbitam o planeta
    -   10. Indica se o planeta interage ou não com a luz (1 - Interage | 0 - Não interage)
    -   11. Arquivo do script de textura do planeta

-   Exemplo:
    
    SISTEMA

    3

    0.0,0.0,0.0;100.0;0;0 ;0.08;0.0; 1; 0.0,0.0,0.0; 1.0,1.0,1.0; 1.0,1.0,1.0; 1;1;assets/script/sun.tscp;
    
    0.0,0.0,0.0;40.0;300;280 ;2.0;0.1; 0;1;1;assets/script/earth.tscp;

    0.0,0.0,0.0;12.0;60;60 ;0.3;0.5; 0;0;1;assets/script/moon.tscp;
