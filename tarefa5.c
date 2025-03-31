#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ALUNOS 3
#define TAM_MAX 100


void create_file_from_input(char* file_name) {
    FILE *file = fopen(file_name, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    char nome[TAM_MAX], endereco[TAM_MAX], curso[TAM_MAX];

    for (int i = 0; i < NUM_ALUNOS; i++) {
        printf("Aluno %d\n", i + 1);

        printf("Nome: ");
        fgets(nome, TAM_MAX, stdin);
        
        printf("Endereco: ");
        fgets(endereco, TAM_MAX, stdin);
        
        printf("Curso: ");
        fgets(curso, TAM_MAX, stdin);

        fprintf(file, "%s%s%s", nome, endereco, curso);
    }

    fclose(file);
}

void process_file_1(const char* input_file, const char* output_file) {
    FILE *fin = fopen(input_file, "r");
    FILE *fout = fopen(output_file, "w");

    if (!fin || !fout) {
        printf("Erro ao abrir os arquivos!\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return;
    }

    char nome[TAM_MAX], endereco[TAM_MAX], curso[TAM_MAX];

    while (fgets(nome, TAM_MAX, fin) &&
           fgets(endereco, TAM_MAX, fin) &&
           fgets(curso, TAM_MAX, fin)) {
        
        // Remover a quebra de linha do fgets
        nome[strcspn(nome, "\n")] = '\0';
        endereco[strcspn(endereco, "\n")] = '\0';
        curso[strcspn(curso, "\n")] = '\0';

        // Gravar no novo arquivo com o indicador de tamanho
        fprintf(fout, "%02lu%s%02lu%s%02lu%s",
                strlen(nome), nome,
                strlen(endereco), endereco,
                strlen(curso), curso);
    }

    fclose(fin);
    fclose(fout);
}

void process_file_2(const char* input_file, const char* output_file) {
    FILE *fin = fopen(input_file, "r");
    FILE *fout = fopen(output_file, "w");

    if (!fin || !fout) {
        printf("Erro ao abrir os arquivos!\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return;
    }

    char buffer[20]; // Buffer auxiliar para armazenar os tamanhos
    while (fscanf(fin, "%2s", buffer) == 1) { // Lê o tamanho do nome
        int nome_tam = atoi(buffer);
        char nome[nome_tam + 1];
        fread(nome, 1, nome_tam, fin);
        nome[nome_tam] = '\0';

        fscanf(fin, "%2s", buffer); // Lê o tamanho da cidade
        int cidade_tam = atoi(buffer);
        char cidade[cidade_tam + 1];
        fread(cidade, 1, cidade_tam, fin);
        cidade[cidade_tam] = '\0';

        fscanf(fin, "%2s", buffer); // Lê o tamanho do curso
        int curso_tam = atoi(buffer);
        char curso[curso_tam + 1];
        fread(curso, 1, curso_tam, fin);
        curso[curso_tam] = '\0';

        // Exibe os registros na tela
        printf("Nome: %s | Cidade: %s | Curso: %s\n", nome, cidade, curso);

        // Grava no novo arquivo formatado com delimitadores
        fprintf(fout, "%s|%s|%s\n", nome, cidade, curso);
    }

    fclose(fin);
    fclose(fout);
}

void process_file_3(const char* input_file, const char* output_file) {
    FILE *fin = fopen(input_file, "r");
    FILE *fout = fopen(output_file, "w");

    if (!fin || !fout) {
        printf("Erro ao abrir os arquivos!\n");
        if (fin) fclose(fin);
        if (fout) fclose(fout);
        return;
    }

    char line[100]; // Buffer para armazenar uma linha inteira
    while (fgets(line, sizeof(line), fin)) {
        // Encontrar os delimitadores manualmente
        char *nome = line;
        char *cidade = NULL;
        char *curso = NULL;

        // Procurando o primeiro delimitador '|'
        cidade = memchr(nome, '|', strlen(nome));
        if (cidade) {
            *cidade = '\0'; // Substituir o delimitador por '\0'
            cidade++;
        }

        // Procurando o segundo delimitador '|'
        curso = memchr(cidade, '|', strlen(cidade));
        if (curso) {
            *curso = '\0'; // Substituir o delimitador por '\0'
            curso++;
        }

        // Exibe os registros na tela
        printf("Nome=%s | Endereco=%s | Curso=%s |\n", nome, cidade, curso);

        // Grava no novo arquivo formatado
        fprintf(fout, "Nome=%s | Endereco=%s | Curso=%s |\n", nome, cidade, curso);
    }

    fclose(fin);
    fclose(fout);
}





int main(){
	create_file_from_input("entrada.txt");
	process_file_1("entrada.txt","saida1.txt");
	process_file_2("saida1.txt","saida2.txt");
	process_file_3("saida2.txt","saida3.txt");
}
