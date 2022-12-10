# Lista 3 Computação Gráfica

## Integrantes:

-   Mateus Soares   - Matrícula : 20223303314
-   Matheus Menezes - Matrícula : 20223003234
-   Laura Pianetti  - Matrícula : 20223002424
-   Adjailson       - Matrícula : 20223002120
-   Lucas           - Matrícula : 20223002540
-   Gustavo         - Matrícula : 20223003379

## Bibliotecas Necessárias:

-   FreeGlut - sudo apt-get install freeglut3-dev
-   GLEW - sudo apt-get install libglew-dev
-   SOIL - sudo apt-get install libsoil-dev
-   SDL_MIXER - sudo apt-get install libsdl2-mixer-dev	

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

    -   1. Fala se é um corpo esférico ou se irá especificar um modelo em vez de arquivo de textura (.obj)
    -   2. A origem do planeta - Se este orbitar algum, está origem não importa
    -   3. O raio da esfera que representa o planeta
    -   4. O parâmetro a da órbita elíptica do planeta
    -   5. O parâmetro b da órbita elíptica do planeta
    -   6. A velocidade angular com que o planeta rotaciona em torno do próprio eixo
    -   7. A velocidade angular com que o planeta rotaciona na órbita
    -   8. Indica se o planeta emite luz ou não (1 - Emite / 0 - Não emite )
    -   9. !IMPORTANTE : Se o planeta emitir, passe 9 valores de ponto decimal que indicam, nesta ordem, as propriedades da luz emitida (Luz Ambiente | Luz Ambiente | Luz Especular)
    -   10. Quantidade de corpos que orbitam o planeta
    -   11. Indica se o planeta interage ou não com a luz (1 - Interage | 0 - Não interage)
    -   12. Arquivo do script de textura do planeta ou arquivo de modelo .obj

-   Exemplo:
    
    SISTEMA

    3

    0;0.0,0.0,0.0;100.0;0;0 ;0.08;0.0; 1; 0.0,0.0,0.0; 1.0,1.0,1.0; 1.0,1.0,1.0; 1;1;assets/script/sun.tscp;
    
    0;0.0,0.0,0.0;40.0;300;280 ;2.0;0.1; 0;1;1;assets/script/earth.tscp;

    0;0.0,0.0,0.0;12.0;60;60 ;0.3;0.5; 0;0;1;assets/script/moon.tscp;
