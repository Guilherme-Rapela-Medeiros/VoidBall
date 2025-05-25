# VoidBall

O projeto desenvolvido pelo nosso grupo foi o void-ball, que é uma mistura dos jogos arcanoid com space invaders.

No jogo o usuário controla uma 🛸nave que fica na parte inferior da tela, de onde começa atirando uma bola para cima e podendo atirar raios contra a nave inimiga.
O objetivo é derrotar o NPC, que estará na parte 🔝superior da tela.
O NPC se movimentará para a esquerda⬅️ e para a direita➡️ enquanto tenta acertar a 🛸nave (o usuário) com seus raios.
O NPC inimigo começará com 3 pontos de vida❤️, e a cada fase que o usuário passar, ficará mais difícil derrotá-lo.

# Elementos estáticos do jogo 

Contadores de vida: No canto superior esquerdo da tela temos o contador de vidas inimiga em vermelho, enquanto que no canto inferior esquerdo, temos o contador de vidas do jogador em verde.

Bola: Próximo ao centro da tela temos a bola atirada no começo do jogo, que o jogador tem que rebater no intuito de subtrair o inimigo de suas vidas.

Indicador de nível: No canto superior direito da tela se encontra o indicador de nível em branco.

# Elementos móveis do jogo 

Jogador: O jogador é a barra azul que se encontra na parte inferior da tela, podendo se movimentar da esquerda para direita no intuito de desviar dos raios inimigos e rebater a bola branca na tela, o jogador também pode disparar raios verdes no inimigo. 

Inimigo: O inimigo é a barra vermelha que está posicionada no topo da tela, se movimentando na horizontal, atirando raios laranjas no jogador.

# Fim do jogo 

  Quando o jogo acabar, seja pelo jogador ficar sem vidas ou por chegar ao nível 100, será apresentada uma tela de Game Over, onde o jogador pode escolher 3 letras para designar sua pontuação, após inserir as 3 letras e pressionar "enter" o jogo apresenta as maiores pontuações e a opção de voltar a jogar pressionando a tecla "R".

# Instruções de Compilação 

1 - É necessário ter instada a biblioteca raylib no computador. 

2 - Abrir o terminal e digitar o comando:
“gcc VoidBall.c -o VoidBall.exe -lraylib -lopengl32 -lgdi32 -lwinmm”
Para assim criar o arquivo .exe.

3 - Por fim executar o arquivo .exe com o comando:
./VoidBall.exe


##Membros: 

Demetrius Souza - dspj@cesar.school - Demetriussou

Guilherme Rapela Medeiros - grm2@cesar.school - Guilherme-Rapela-Medeiros

José Veloso - jvgv@cesar.school - vitor-veloso
