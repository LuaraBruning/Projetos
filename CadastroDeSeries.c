#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//ESTRUTURA----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    struct atualizacao{
        int temporadas_totais;
        int temporada_atual;
        int episodio_atual;
    };

    struct series{
        char titulo[100];
        int ano;
        char genero[50];
        int duracao;
        float nota;
        struct atualizacao programa //Estrutura "atualizacao" dentro da estrutura "series".
    };

//FUNCOES------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//<1>  INCLUIR NOVA SERIE......................................................................................................................................................................................
void incluir_serie(){

    FILE *file;
    file = fopen("arquivo.txt", "ab+");
    /*A funcao 'fopen()' abre o arquivo solicitado.
    "ab+" se refere ao modo que o arquivo sera aberto, neste caso abre o arquivo para leitura e acrescimo
    de dados; se nao existir, cria-o; se já existir, acrescenta os novos dados no fim do arquivo.*/

    struct series *novaserie;

    novaserie = (struct series *) malloc (sizeof(struct series));
    /*Alocacao de memoria - a funcao 'malloc()' reserva espaco de memoria antes
    de ler o arquivo caso aconteca de entrarem dados muito grandes.*/

    printf("\n                              Titulo da serie: ");
    scanf ("%[^\t\n]s", &novaserie->titulo);
    printf("\n                              Ano: ");
    scanf ("%d", &novaserie->ano);
    printf("\n                              Genero: ");
    scanf ("%s", &novaserie->genero);
    printf("\n                              Duracao em minutos: ");
    scanf ("%d", &novaserie->duracao);
    printf("\n                              Temporadas disponiveis: ");
    scanf ("%d", &novaserie->programa.temporadas_totais);
    printf("\n                              Temporada que esta sendo vista: ");
    scanf ("%d", &novaserie->programa.temporada_atual);
    printf("\n                              Ultimo episodio assistido: ");
    scanf ("%d", &novaserie->programa.episodio_atual);
    printf("\n                              Nota: ");
    scanf ("%f", &novaserie->nota);

    fwrite(novaserie, sizeof(struct series), 1, file);
    //A funcao 'fwrite()' escreve no arquivo os dados inseridos.

    printf("\n\n\n                              SERIE CADASTRADA COM SUCESSO!");
    fclose(file);
    //A funcao 'fclose()' fecha o arquivo manipulado.

    printf("\n\n                            <<<<Precione qualquer tecla para acessar o menu principal novamente>>>>");
 }

//<2>  LISTAR SERIES CADASTRADAS...............................................................................................................................................................................
void listar_serie(){

    FILE *file;
    file = fopen("arquivo.txt", "ab+");
    /*'fopen' -> Funcao que abre o arquivo solicitado.
    "ab+" se refere ao modo que o arquivo sera aberto, neste caso abre o arquivo para leitura e acrescimo
    de dados; se nao existir, cria-o; se ja existir, acrescenta os novos dados no fim do arquivo.*/

    struct series dados;
    int cont = 1;
    while (1==1) {
        if (fread(&dados, sizeof(dados), 1, file)!=1){
            //A funcao 'fread()' permite a leitura de um bloco de bytes em arquivos.
            break;
        }
        printf("\n                              %s", dados.titulo);
        printf("\n                              %d", dados.ano);
        printf("\n\n                            Nota: %.1f", dados.nota);
        printf("\n                              Seriado de %s", dados.genero);
        printf("\n                              Episodios de %d minutos", dados.duracao);
        printf("\n                              %d temporadas disponiveis", dados.programa.temporadas_totais);
        printf("\n                              Ultimo assistido: <S%dE%d> Episodio %d da Temporada %d", dados.programa.temporada_atual, dados.programa.episodio_atual, dados.programa.episodio_atual, dados.programa.temporada_atual);
        printf("\n\n                            Codigo: %03d", cont++);
        printf("\n\n                            --------------------------------------------------------------------------------");
    }
    fclose(file);
    //A funcao 'fclose()' fecha o arquivo manipulado.

    printf("\n                              <<<<Precione qualquer tecla para acessar o menu principal novamente>>>>");
}

//<3>  PESQUISAR SERIE.........................................................................................................................................................................................
void pesquisar_serie(){

    FILE *file;
    file = fopen("arquivo.txt", "ab+");
    /*'fopen' -> Funcao que abre o arquivo solicitado.
    "ab+" se refere ao modo que o arquivo sera aberto, neste caso Abre o arquivo para leitura e acréscimo
    de dados; se não existir, cria-o; se já existir, acrescenta os novos dados no fim do arquivo.*/

    struct series dados;

    char resp[50];
    printf("\n                              Digite o titulo da serie que deseja pesquisar: ");
    scanf("%[^\t\n]s", resp);

    /*Esse for converte tudo para minúsculo para assim depois poder comparar,
    caso o titulo da serie tenha sido inserido em letras maiusculas.*/
    for(int i = 0; resp[i]; i++){
        resp[i] = tolower(resp[i]);
        //A funcao 'tolower()' converte o caracter em minusculo.
    }
    while(fread(&dados,sizeof(struct series),1,file)){
         //A funcao 'fread()' permite a leitura de um bloco de bytes em arquivos.

        char busca[50];
        for(int i = 0; dados.titulo[i]; i++){
            busca[i] = tolower(dados.titulo[i]);
            //A funcao 'tolower()' converte o caracter em minusculo.
        }

        if(strstr(busca,resp)) {
            printf("\n\n                         --------------------------------------------------------------------------------");
            printf("\n                              %s", dados.titulo);
            printf("\n                              %d", dados.ano);
            printf("\n\n                              Nota: %.1f", dados.nota);
            printf("\n                              Seriado de %s", dados.genero);
            printf("\n                              Episodios de %d minutos", dados.duracao);
            printf("\n                              %d temporadas disponiveis", dados.programa.temporadas_totais);
            printf("\n                              Ultimo assistido: <S%dE%d> Episodio %d da Temporada %d", dados.programa.temporada_atual, dados.programa.episodio_atual, dados.programa.episodio_atual, dados.programa.temporada_atual);
        }
    }
    fclose(file);
    //A funcao 'fclose()' fecha o arquivo manipulado.
    printf("\n\n                         --------------------------------------------------------------------------------");
    printf("\n                            <<<<Precione qualquer tecla para acessar o menu principal novamente>>>>");
}

//<4>  EDITAR SERIE ESPECIFICA.................................................................................................................................................................................
void editar_serie(){

    FILE *file;
    file = fopen("arquivo.txt", "rb+");
    /*'fopen' -> Funcao que abre o arquivo solicitado.
    "rb+" se refere ao modo que o arquivo sera aberto, neste caso abre o arquivo para leitura
    e gravacao; se nao existir, cria-o; se já existir, acrescenta os novos dados no inicio
    deste arquivo, sobregravando os ja existentes.*/

    struct series dados;

    int cod;
    printf("\n                              Digite o codigo da serie que deseja editar: ");
    scanf("%d", &cod);

     if(fseek(file, (cod-1)*sizeof(struct series), SEEK_SET)!=0){
        /*A função ‘fseek()’ faz procuras e acessos randomicos em arquivos, ou seja,
        move a posicao corrente de leitura ou escrita no arquivo de um valor
        especificado, a partir de um ponto especificado.*/

        printf("                            Item nao encontrado!");
        return;
    }

    if (fread(&dados, sizeof(struct series), 1, file)!=1){
       //A funcao 'fread()' permite a leitura de um bloco de bytes em arquivos.

        printf("\n\t                            Erro na abertura do item!");
        getch();
        system("cls");
        return;
    }

    system("cls");

    printf("                            %c----------------------------------------------------------------------------%c\n",201,187);
    printf("                            | ");printf("\t\t\t      CADASTRO DE NOVA SERIE   ");printf("\t\t\t      |\n");
    printf("                            %c----------------------------------------------------------------------------%c\n",200,188);

    printf("\n\n                            >>>DADOS ANTIGOS<<< ");

    printf("\n\n\n                              Titulo: %s", dados.titulo);
    printf("\n\n                            Ano: %d", dados.ano);
    printf("\n\n                            Genero: %s", dados.genero);
    printf("\n\n                            Duracao: %d", dados.duracao);
    printf("\n\n                            Temporadas disponiveis: %d", dados.programa.temporadas_totais);
    printf("\n\n                            Temporada atual: %d", dados.programa.temporada_atual);
    printf("\n\n                            Episodio atual: %d", dados.programa.episodio_atual);
    printf("\n\n                            Nota: %.1f", dados.nota);
    fflush(stdin);


    printf("\n\n\n\n\n                              >>>DADOS NOVOS<<<");

    printf("\n\n\n                              Titulo: ");
    scanf("%[^\t\n]s", &dados.titulo);
    printf("\n                              Ano: ");
    scanf("%d", &dados.ano);
    printf("\n                              Genero: ");
    scanf("%s", &dados.genero);
    printf("\n                              Duracao: ");
    scanf("%d", &dados.duracao);
    printf("\n                              Temporadas disponiveis: ");
    scanf("%d", &dados.programa.temporadas_totais);
    printf("\n                              Temporada atual: ");
    scanf("%d", &dados.programa.temporada_atual);
    printf("\n                              Episodio atual: ");
    scanf("%d", &dados.programa.episodio_atual);
    printf("\n                              Nota: ");
    scanf("%f", &dados.nota);



    fseek(file, -(long) sizeof(struct series), SEEK_CUR);
    /*A função ‘fseek()’ faz procuras e acessos randomicos em arquivos, ou seja,
    move a posicao corrente de leitura ou escrita no arquivo de um valor
    especificado, a partir de um ponto especificado, neste caso o '-(long)'
    faz com que o novo registro seja gravado em cima do anterior*/

    fwrite(&dados, sizeof(struct series), 1, file);
    //A funcao 'fwrite()' escreve no arquivo os dados inseridos.

    fflush(file);
    printf("\n\n\n                              RESULTADO ALTERADO COM SUCESSO!\n");

    fclose(file);
    //A funcao 'fclose()' fecha o arquivo manipulado.

    printf("\n                              <<<<Precione qualquer tecla para acessar o menu principal novamente>>>>");

}

//<5>  EXCLUIR SERIE ESPECIFICA................................................................................................................................................................................
void excluir_serie(){

    FILE *file;
    file = fopen("arquivo.txt", "ab+");
    FILE *newFile;
    newFile = fopen("novo_arquivo.txt", "ab+");
    /*'fopen' -> Funcao que abre o arquivo solicitado.
    "ab+" se refere ao modo que o arquivo sera aberto, neste caso abre o arquivo para leitura e acrescimo
    de dados; se nao existir, cria-o; se já existir, acrescenta os novos dados no fim do arquivo.*/

    struct series dados;

    int contador = 0;
    int novoContador = 0;

    char resp[50];
    printf("\n                              Digite o titulo da serie que deseja excluir: ");
    scanf("%[^\t\n]s", resp);

    for(int i = 0; resp[i]; i++){
        resp[i] = tolower(resp[i]);
        //A funcao 'tolower()' converte o caracter em minusculo.
    }
        while(1==1){
            fseek(file, contador* sizeof(struct series),SEEK_SET);
            /*A função ‘fseek()’ faz procuras e acessos randomicos em arquivos, ou seja,
            move a posicao corrente de leitura ou escrita no arquivo de um valor
            especificado, a partir de um ponto especificado.*/

            if(fread(&dados,sizeof(struct series), 1, file)!=1){
              //A funcao 'fread()' permite a leitura de um bloco de bytes em arquivos.

                break;
            }
            char busca[50];
            for(int i = 0; dados.titulo[i]; i++){
            busca[i] = tolower(dados.titulo[i]);
                       //A funcao 'tolower()' converte o caracter em minusculo.

            }
            if(!strstr(busca,resp)){
                fseek(file, novoContador* sizeof(struct series), SEEK_SET);
                /*A função ‘fseek()’ faz procuras e acessos randomicos em arquivos, ou seja,
                move a posicao corrente de leitura ou escrita no arquivo de um valor
                especificado, a partir de um ponto especificado.*/

                if(fwrite(&dados, sizeof(struct series), 1, newFile)!= 1){
                   printf("                         Erro na copia do item");
                }
                novoContador++;
            }
            contador++;
        }
    fclose(file);
    //A funcao 'fclose()' fecha o arquivo antigo manipulado.

    fclose(newFile);
    //A funcao 'fclose()' fecha o novo arquivo manipulado.

    remove("arquivo.txt");
    //A funcao 'remove()' deleta o arquivo antigo manipulado.

    rename ("novo_arquivo.txt", "arquivo.txt");
    //A funcao 'rename()' renomeia o novo arquivo manipulado.

    printf("\n\n\n\n                            A SERIE FOI EXCLUIDA COM SUCESSO!");
    printf("\n\n\n                              <<<<Precione qualquer tecla para acessar o menu principal novamente>>>>");
}

//<6>  EXCLUIR TODAS AS SERIES.................................................................................................................................................................................
void excluir_todas_series(){

    remove("arquivo.txt");
    //A funcao 'remove()' deleta o arquivo manipulado.

    printf("\n                              O ARQUIVO DE TODAS AS SERIES FOI EXCLUIDO COM SUCESSO!");
    printf("\n\n                            <<<<Precione qualquer tecla para acessar o menu principal novamente>>>>");
}

//<0>  SAIR....................................................................................................................................................................................................
void sair(){
    int opcao;
    opcao='0';
    /*Enquanto a opcao for diferente de zero o programa ira continuar,
    no momento em que o usuario entrar com o inteiro 0 o programa sera finalizado.*/

    printf("\t\t\t\t                            Luara Bruning\n");
    printf("\t\t\t                              LPG0002 (TADS) 2018/1\n\n\n");

}
//MAIN---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(){

    int opcao;
    while(opcao!='0'){
    /*Enquanto a opcao for diferente de zero o programa ira continuar,
    no momento em que o usuario entrar com o inteiro 0 o programa sera finalizado.

      Apresentacao das opcoes do MENU*/
      printf("\n\n\n\n                          %c----------------------------------------------------------------------------%c\n",201,187);
      printf("                          | ");printf("\t\t\t     ATULIZACAO DE SERIES");printf("\t\t\t       |\n");
      printf("                          %c----------------------------------------------------------------------------%c\n",200,188);
      printf("\n                                                          %c            %c",201,187);
      printf("\n                                                           %c----------%c",260,260);
      printf("\n                                                           |   MENU   |");
      printf("\n                                                           %c----------%c",260,260);
      printf("\n                                                          %c            %c\n",200,188);
      printf("                                              %c------------------------------------%c\n",201,187);
      printf("                                              | <1>  Incluir nova serie            |\n");
      printf("                                              |------------------------------------|\n");
      printf("                                              | <2>  Listar series cadastradas     |\n");
      printf("                                              |------------------------------------|\n");
      printf("                                              | <3>  Pesquisar serie               |\n");
      printf("                                              |------------------------------------|\n");
      printf("                                              | <4>  Editar serie especifica       |\n");
      printf("                                              |------------------------------------|\n");
      printf("                                              | <5>  Excluir serie especifica      |\n");
      printf("                                              |------------------------------------|\n");
      printf("                                              | <6>  Excluir todas as series       |\n");
      printf("                                              |------------------------------------|\n");
      printf("                                              | <0>  Sair                          |\n");
      printf("                                              %c------------------------------------%c",200,188);
      printf("\n\n");
      /*De acordo com a tabela ASCII eh possivel usando '%c' e, identificando o respectivo codigo desejado,
      inserirmos determinados simbolos no 'printf'.*/

      fflush(stdin);
      opcao= getch();//Le a opcao que o usuario seleciona

      switch(opcao){
      /*De acordo com o numero do menu que o usuario escolher o 'case' correspondente
      sera executado, onde logo em seguida a funçao sera chamada.*/

        case '1'://INCLUIR AS SERIES
            fflush(stdin);//Limpa a tela
              system("cls");
              printf("                          %c----------------------------------------------------------------------------%c\n",201,187);
              printf("                          | ");printf("\t\t\t      CADASTRO DE NOVA SERIE   ");printf("\t\t\t       |\n");
              printf("                          %c----------------------------------------------------------------------------%c\n",200,188);
              incluir_serie();//Chamando a função para o usuário inserir os dados.
         getch();
         system("cls");
        break;

        case '2'://LISTAR AS SERIES
            fflush(stdin);
              system ("cls");
              printf("                          %c----------------------------------------------------------------------------%c\n",201,187);
              printf("                          | ");printf("\t\t\t     SERIES CADASTRADAS");printf("\t\t\t               |\n");
              printf("                          %c----------------------------------------------------------------------------%c\n",200,188);
              listar_serie();//Chamando a função para listar os dados cadastrados.
         getch();
         system("cls");
        break;

        case '3'://PESQUISAR DETERMINADA SERIE
            fflush(stdin);
              system ("cls");
              printf("                          %c----------------------------------------------------------------------------%c\n",201,187);
              printf("                          | ");printf("\t\t\t     PESQUISAR SERIE CADASTRADA ");printf("\t\t       |\n");
              printf("                          %c----------------------------------------------------------------------------%c\n",200,188);
              pesquisar_serie();//Chamando a função para o usuario pesquisar a serie desejada.
         getch();
         system("cls");
        break;

        case '4'://EDITAR DETERMINADA SERIE
            fflush(stdin);
              system ("cls");
              printf("                          %c----------------------------------------------------------------------------%c\n",201,187);
              printf("                          | ");printf("\t\t\t     EDITAR SERIE CADASTRADA ");printf("\t\t\t       |\n");
              printf("                          %c----------------------------------------------------------------------------%c\n",200,188);
              editar_serie();//Chamando a função para o usuario editar a serie desejada.
         getch();
         system("cls");
        break;

        case '5'://EXCLUIR DETERMINADA SERIE
            fflush(stdin);
              system ("cls");
              printf("                          %c----------------------------------------------------------------------------%c\n",201,187);
              printf("                          | ");printf("\t\t\t     EXCLUIR SERIE CADASTRADA ");printf("\t\t\t       |\n");
              printf("                          %c----------------------------------------------------------------------------%c\n",200,188);
              excluir_serie();//Chamando a função para o usuario excluir a serie desejada.
         getch();
         system("cls");
        break;

        case '6'://EXCLUI O ARQUIVO
            fflush(stdin);
              system ("cls");
              printf("                          %c----------------------------------------------------------------------------%c\n",201,187);
              printf("                          | ");printf("\t\t\tEXCLUIR TODAS AS SERIES CADASTRADAS      ");printf("\t      |\n");
              printf("                          %c----------------------------------------------------------------------------%c\n",200,188);
              excluir_todas_series();//Chamando a função para excluir o arquivos com todas as series.
         getch();
         system("cls");
        break;

        case '0'://ENCERRA O PROGRAMA
            sair();//Chamando a função para sair do programa
        break;

        default://CASO O USUARIO DIGITE UMA OPCAO INEXISTENTE NO MENU
              system("cls");//Limpa a tela.
        break;
      }
    }
}
