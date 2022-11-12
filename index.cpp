#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

using namespace std;

//*INICIO struct pre-existente
struct Arma
{
  int dano_minimo;
  int dano_maximo;
};
struct Jogador
{
  int nivel;
  int vida;
  Arma arma;
  int posicao[2];
};
struct Inimigo
{
  string nome;
  int vida;
  Arma arma;
};
//*FIM struct pre-existente

//*INICIO struct novas
struct Bloco
{
  bool bloqueado;
  bool pacifico;
  Inimigo *inimigo;
};
struct Mapa
{
  int altura, largura;
  Bloco **mapa;
};
struct Fase
{
  string nome;
  Mapa mapa;
  int contagem_inimigos = 5;
  Inimigo inimigos[5];
};
struct BlocoLivre
{
  Bloco *bloco;
  int altura, largura;
};
//*FIM struct novas

//*INICIO funcoes pre-existentes
template <typename T>
bool morreu(T personagem)
{
  if (personagem.vida < 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename Tata, typename Tdef>
Tdef ataque(Tata atacante, Tdef defensor)
{
  // 2 - 5
  int intervalo_dano = atacante.arma.dano_maximo - atacante.arma.dano_minimo + 1;
  int dano = atacante.arma.dano_minimo + rand() % intervalo_dano;

  defensor.vida = defensor.vida - dano;

  return defensor;
}

void jogar_fase(Jogador jog, Fase fase)
{
  cout << "Começou " << fase.nome << endl;
  for (int atual = 0; atual < 5; atual++)
  {
    while (!morreu(fase.inimigos[atual]))
    {
      jog = ataque(fase.inimigos[atual], jog);
      fase.inimigos[atual] = ataque(jog, fase.inimigos[atual]);

      cout << "O jogador atacou " << fase.inimigos[atual].nome << " e ele ficou com " << fase.inimigos[atual].vida << " de vida" << endl;
      cout << "O " << fase.inimigos[atual].nome << "atacou o jogador ao mesmo tempo e o deixou com " << jog.vida << " de vida" << endl;

      if (morreu(jog))
      {
        cout << "O jogador morreu, o jogo acabou";
        return;
      }
    }

    cout << fase.inimigos[atual].nome << " foi morto" << endl;
  }

  cout << "O jogador passou a fase";
}

void batalha(Jogador &jog, Inimigo inimigo)
{

  while (!morreu(inimigo))
  {
    jog = ataque(inimigo, jog);
    inimigo = ataque(jog, inimigo);

    cout << "O jogador atacou " << inimigo.nome << " e ele ficou com " << inimigo.vida << " de vida" << endl;
    cout << "O " << inimigo.nome << "atacou o jogador ao mesmo tempo e o deixou com " << jog.vida << " de vida" << endl;

    if (morreu(jog))
    {
      cout << "O jogador morreu, o jogo acabou";
      return;
    }
  }

  cout << "O jogador passou a fase\n";
}

Jogador criar_jogador()
{
  Arma aJ = {4, 10};

  Jogador jog = {1, 100, aJ};

  jog.posicao[0] = 0;
  jog.posicao[1] = 0;
  return jog;
}
//*FIM funcoes pre-existentes

//*INICIO funcoes novas
bool SorteioDe20Porcento();

void ExibirMapa(Mapa mapa, Jogador jogador);

BlocoLivre EncontrarBlocoLivre(Mapa mapa, bool pacifico)
{
  Bloco *bloco_sorteado;

  BlocoLivre bloco_livre;
  int altura_sorteada;
  int largura_sorteada;

  do
  {

    altura_sorteada = rand() % mapa.altura;
    largura_sorteada = rand() % mapa.largura;

    bloco_sorteado = &mapa.mapa[altura_sorteada][largura_sorteada];

  } while (bloco_sorteado->bloqueado || pacifico != bloco_sorteado->pacifico || bloco_sorteado->inimigo);

  bloco_livre = {bloco_sorteado, altura_sorteada, largura_sorteada};

  return bloco_livre;
}

Mapa CriarMapa(int altura, int largura)
{
  Mapa mapa;
  Mapa *pntr_mapa;

  pntr_mapa = &mapa;

  pntr_mapa->altura = altura;
  pntr_mapa->largura = largura;

  int contagem_pedras = 0;
  int contagem_pacificos = 0;

  pntr_mapa->mapa = new Bloco *[altura];

  Bloco *bloco_da_vez;
  for (int linha = 0; linha < altura; linha++)
  {
    pntr_mapa->mapa[linha] = new Bloco[largura];
    for (int coluna = 0; coluna < largura; coluna++)
    {
      bloco_da_vez = &pntr_mapa->mapa[linha][coluna];

      if (SorteioDe20Porcento())
      {
        contagem_pedras += 1;
        bloco_da_vez->bloqueado = true;
      }
      else
      {
        bloco_da_vez->bloqueado = false;
      }

      if (!SorteioDe20Porcento())
      {
        contagem_pacificos += 1;
        bloco_da_vez->pacifico = true;
      }
      else
      {
        bloco_da_vez->pacifico = false;
      }
    }
  }
  cout << "contagem pedra : " << contagem_pedras << " contagem pacificos: " << contagem_pacificos << endl;

  return mapa;
}

bool SorteioDe20Porcento()
{
  const int numero_sorteado = rand() % 100;

  if (numero_sorteado >= 0 && numero_sorteado <= 19)
  {
    return true;
  }
  else
  {
    return false;
  }
}

Fase CriarFase(int numInimigos, Inimigo *inimigos, int alturaMapa, int larguraMapa)
{
  Mapa mapa = CriarMapa(alturaMapa, larguraMapa);

  BlocoLivre bloco_livre;

  Arma aI = {1, 5};

  Inimigo goblin1 = {"Goblin", 20, aI};
  Inimigo goblin2 = {"Goblerto", 30, aI};
  Inimigo goblin3 = {"Gobo", 40, aI};
  Inimigo goblin4 = {"Goblinio", 50, aI};
  Inimigo chefao = {"Juca", 95, aI};

  Fase fase;
  fase.nome = "Fase 1";
  fase.inimigos[0] = goblin1;
  fase.inimigos[1] = goblin2;
  fase.inimigos[2] = goblin3;
  fase.inimigos[3] = goblin4;
  fase.inimigos[4] = chefao;

  for (int index_inimigo = 0; index_inimigo <= numInimigos; index_inimigo++)
  {

    bloco_livre = EncontrarBlocoLivre(mapa, false);
    bloco_livre.bloco->inimigo = &inimigos[index_inimigo];
  }

  fase.mapa = mapa;
  return fase;
}

void Movimentar(Jogador *jogador, Mapa mapa, char keyboard)
{

  int novo_valor_posicao;
  int index_posicao = 0;
  Bloco bloco_nova_posicao;

  switch (keyboard)
  {
  case 'W':
    index_posicao = 0;
    novo_valor_posicao = jogador->posicao[0] - 1;
    bloco_nova_posicao = mapa.mapa[jogador->posicao[0] - 1][jogador->posicao[1]];
    break;
  case 'S':

    index_posicao = 0;
    novo_valor_posicao = jogador->posicao[0] + 1;
    bloco_nova_posicao = mapa.mapa[jogador->posicao[0] + 1][jogador->posicao[1]];

    break;
  case 'D':

    index_posicao = 1;
    novo_valor_posicao = jogador->posicao[1] + 1;
    bloco_nova_posicao = mapa.mapa[jogador->posicao[0]][jogador->posicao[1] + 1];

    break;
  case 'A':

    index_posicao = 1;
    novo_valor_posicao = jogador->posicao[1] - 1;
    bloco_nova_posicao = mapa.mapa[jogador->posicao[0]][jogador->posicao[1] - 1];

    break;
  default:
    break;
  }

  if (novo_valor_posicao < 0 || novo_valor_posicao > 10 || bloco_nova_posicao.bloqueado)
  {
    return;
  }
  if (bloco_nova_posicao.inimigo)
  {
    batalha(*jogador, *bloco_nova_posicao.inimigo);
    char cont;
    cout << "...qualquer tecla para continuar ( vida jogador: " << jogador->vida << " )" << endl;
    cin >> cont;
  }

  jogador->posicao[index_posicao] = novo_valor_posicao;

  mapa.mapa[jogador->posicao[0]][jogador->posicao[1]].inimigo = NULL;
  return;
}

void ExibirMapa(Mapa mapa, Jogador jogador)
{

  for (int linha = 0; linha < mapa.altura; linha++)
  {
    for (int coluna = 0; coluna < mapa.largura; coluna++)
    {

      Bloco bloco = mapa.mapa[linha][coluna];

      if (linha == jogador.posicao[0] && coluna == jogador.posicao[1])
      {
        cout << "O";
        continue;
      }
      else
      {
        if (bloco.inimigo)
        {
          cout << "I";
        }
        else if (bloco.bloqueado)
        {
          cout << "X";
        }

        else
        {
          cout << "_";
        }
      }
    }

    cout << "\n";
  }
}

void PosicionarJogadorAleatorio(Fase fase, Jogador *jogador)
{
  BlocoLivre bloco_livre = EncontrarBlocoLivre(fase.mapa, true);
  bloco_livre.bloco->pacifico = false;
  jogador->posicao[0] = bloco_livre.altura;
  jogador->posicao[1] = bloco_livre.largura;
}

bool ExistemInimigos(Mapa mapa)
{
  bool existe_inimigo = false;
  for (int linha = 0; linha < mapa.altura; linha++)
  {
    for (int coluna = 0; coluna < mapa.largura; coluna++)
    {

      if (mapa.mapa[linha][coluna].inimigo)
      {
        existe_inimigo = true;
        break;
      }
    }
  }
  return existe_inimigo;
}

void jogo()
{
  srand(time(NULL));

  Jogador jogador = criar_jogador();
  Jogador *pntr_jogador = &jogador;

  Fase fase;
  Inimigo *pntr_inimigos = fase.inimigos;

  fase = CriarFase(fase.contagem_inimigos, pntr_inimigos, 10, 10);

  PosicionarJogadorAleatorio(fase, pntr_jogador);

  char keyboard;

  do
  {
    cout << "Aperte [I] para iniciar (mantenha o capslock ligado)";
    cin >> keyboard;

  } while (keyboard != 'I');

  bool jogador_vivo;
  do
  {

    system("clear");

    ExibirMapa(fase.mapa, jogador);

    char keyboard;
    cin >> keyboard;

    Movimentar(pntr_jogador, fase.mapa, keyboard);

  } while (ExistemInimigos(fase.mapa) || morreu(jogador));

  if (morreu(jogador))
  {
    cout << "\n\t===MORTO===";
  }
  else
  {
    cout << "\n\t===PARABENS===";
  }
}

template <typename Array, typename T>
void breadFirstTravesal(Array array[6][2], T startAt)
{

  cout << startAt;
  for (int neighbor : array[startAt])
  {
    if (neighbor == 0)
    {
      continue;
    }
    breadFirstTravesal(array, neighbor);
  }
}

void analisarColuna(Bloco array[10], int startAt)
{

  cout << array[startAt];

  for (int neighbor : array[startAt])
  {
    if ()
    {
      continue;
    }
    breadFirstTravesal(array, neighbor);
  }
}

void mapaBreadFirstTravesal(Mapa mapa, int player_line, int player_column, int enemy_line, int enemy_column, )
{
  Bloco first_block;

  Blocos *neighbors = new Bloco;

  for (int line = enemy_line; line < mapa.altura; line++)
  {
    for (int column = enemy_column; column < mapa.largura; column++)
    {

      first_block = mapa.mapa[line][column];

      for (int neighbors_count = 0; neighbors_count <= 4; neighbors_count++)
      {
        neighbors[neighbors_count] = mapa.mapa[left_one][]
      }

      cout << "[" << line << column << "] " << first_block.bloqueado << !!first_block.inimigo << " ";
    }
    cout << "\n";
  }
}

int main()
{
  srand(time(NULL));

  Jogador jogador = criar_jogador();
  Jogador *pntr_jogador = &jogador;

  Fase fase;
  Inimigo *pntr_inimigos = fase.inimigos;

  fase = CriarFase(fase.contagem_inimigos, pntr_inimigos, 10, 10);

  int array[6][2] = {{1, 2}, {3}, {4}, {5}, {}, {}};
  breadFirstTravesal(array, 0);
  cout << "\n";

  mapaBreadFirstTravesal(fase.mapa);

  //*jogar_fase(jogador, fase);
}