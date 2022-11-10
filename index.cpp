#include <iostream>
#include <string>
#include <time.h>
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
  int *posicao;
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
  cout << "Começou " << fase.nome << endl
       << endl;

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

    cout << fase.inimigos[atual].nome << " foi morto" << endl
         << endl;
  }

  cout << "O jogador passou a fase";
}

Jogador criar_jogador()
{
  Arma aJ = {4, 10};

  int posicao_jogador[2] = {0, 0};
  int *pntr_posicao_jogador = posicao_jogador;

  Jogador jog = {1, 100, aJ, pntr_posicao_jogador};

  return jog;
}
//*FIM funcoes pre-existentes

//*INICIO funcoes novas
bool SorteioDe20Porcento();

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
  for (int linha = 0; linha < altura; linha++)
  {
    pntr_mapa->mapa[linha] = new Bloco[largura];
    for (int coluna = 0; coluna < largura; coluna++)
    {
      if (SorteioDe20Porcento())
      {
        contagem_pedras += 1;
        pntr_mapa->mapa[linha][coluna].bloqueado = true;
      }
      else
      {
        pntr_mapa->mapa[linha][coluna].bloqueado = false;
      }

      if (!SorteioDe20Porcento())
      {
        contagem_pacificos += 1;
        pntr_mapa->mapa[linha][coluna].pacifico = true;
      }
      else
      {
        pntr_mapa->mapa[linha][coluna].pacifico = false;
      }
    }
  }
  cout << "contagem pedra : " << contagem_pedras << " contagem pacificos: " << contagem_pacificos;

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

  Mapa *pntr_mapa = &mapa;

  Bloco *bloco_sorteado = new Bloco;

  int altura_sorteada;
  int largura_sorteada;

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

  for (int index_inimigo = 0; index_inimigo < numInimigos; index_inimigo++)
  {
    do
    {

      altura_sorteada = rand() % pntr_mapa->altura;
      largura_sorteada = rand() % pntr_mapa->largura;

      bloco_sorteado = &pntr_mapa->mapa[altura_sorteada][largura_sorteada];

    } while (!bloco_sorteado->bloqueado && bloco_sorteado->pacifico && !bloco_sorteado->inimigo);

    bloco_sorteado->inimigo = &inimigos[index_inimigo];
  }

  return fase;
}

int main()
{
  srand(time(NULL));

  Jogador jogador = criar_jogador();

  Fase fase;
  Inimigo *pntr_inimigos = fase.inimigos;

  fase = CriarFase(sizeof(fase.contagem_inimigos) + 1, pntr_inimigos, 10, 10);

  char keyboard;

  keyboard = getchar();

  //*jogar_fase(jogador, fase);
}