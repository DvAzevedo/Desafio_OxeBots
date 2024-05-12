# Desafio OxeBots, Equipe 1

## Descrição do Projeto

O desafio consiste em desenvolver um simulador 2D na linguagem de programação C++, que deve incluir, no mínimo, um robô e uma bola, sendo essencial que o robô interaja com a bola.

Considerando que o simulador é primariamente uma ferramenta de validação, torna-se necessária a comunicação com um módulo externo, que enviará os comandos para o/os robôs, para isso, será necessário o uso do protocolo de comunicação protobuf.

## Dependências

- SDL2
- protobuf
- make
- ncurses

## Instalação

No Ubuntu, você pode instalar as dependências necessárias executando o comando abaixo:

``` sh
sudo apt-get install libsdl2-dev protobuf-compiler ncurses-bin ncurses-base ncurses-term make
```

## Como compilar

Para compilar o projeto, basta executar o comando `make` no terminal.

## Como executar

Para executar o projeto, basta executar o comando `make run` no terminal.

No VSCode, você pode executar o projeto através da extensão `ms-vscode.makefile-tools`.

> VS Marketplace Link: [https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools)
