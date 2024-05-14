# Desafio OxeBots, Equipe 1

## Descrição do Projeto

O desafio consiste em desenvolver um simulador 2D na linguagem de programação C++, que deve incluir, no mínimo, um robô e uma bola, sendo essencial que o robô interaja com a bola.

Considerando que o simulador é primariamente uma ferramenta de validação, torna-se necessária a comunicação com um módulo externo, que enviará os comandos para o/os robôs, para isso, será necessário o uso do protocolo de comunicação protobuf.

## Dependências

- SDL2
- protobuf
- make

## Instalação

No Ubuntu, você pode instalar as dependências necessárias executando o comando abaixo:

``` sh
sudo apt-get install libsdl2-dev protobuf-compiler make libprotobuf-dev
```

## Como compilar

Para compilar o projeto, basta executar o comando `make` no terminal.

## Como executar

Para executar o projeto, basta executar o comando `make run` no terminal.

No VSCode, você pode executar o projeto através da extensão `ms-vscode.makefile-tools`.

> VS Marketplace Link: [https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.makefile-tools)

## Processo de Desenvolvimento

### Pesquisa

Após compreender as exigências do projeto, conduzimos uma pesquisa sobre as tecnologias e ferramentas necessárias. Além disso, revisamos conceitos de classes em C++ e programação orientada a objetos.

Buscamos exemplos de simuladores 2D para utilizarmos como base, estudamos o funcionamento do SDL e procuramos por outros projetos que utilizassem essa biblioteca. Também revisamos os conceitos de programação necessários para a realização do desafio e investigamos maneiras de tornar o projeto compatível tanto com Windows quanto com Linux. Além disso, buscamos material para compreender o que é um protobuf e como ele funciona.

### Material de Apoio:

- Exemplo de projeto: Bots2D: [Bots2D: Building a robot 2D simulator from scratch in C++](https://www.artfulbytes.com/bots2d-blogpost)
- Tutorial de configuração do SDL: [https://youtu.be/H08t6gD1Y1E?si=qEVLzV1xthIzJLfd](https://youtu.be/H08t6gD1Y1E?si=qEVLzV1xthIzJLfd)
- Wiki do SDL: https:[https://wiki.libsdl.org/SDL2/FrontPage](https://wiki.libsdl.org/SDL2/FrontPage)
- Projetos com SDL: [C++/SDL2 RPG Physics Based 2D Platformer for Beginners Tutorial](https://www.youtube.com/watch?v=KsG6dJlLBDw&list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS), [Making a Game With C++ and SDL2](https://www.youtube.com/watch?v=iEn0ozP-jxc)
- Exemplo de projeto IEEE Very Small Size Soccer: [https://youtu.be/YU4e1UFWLeY?si=-I7xb6xXNY1ujLUS](https://youtu.be/YU4e1UFWLeY?si=-I7xb6xXNY1ujLUS)
- Desenvolvimento de um robô: [https://periodicos.ufersa.edu.br/ecop/article/view/7890](https://periodicos.ufersa.edu.br/ecop/article/view/7890)
- Material sobre a função inet_addr (winsock2.h)::[função inet_addr (winsock2.h)](https://learn.microsoft.com/pt-br/windows/win32/api/winsock2/nf-winsock2-inet_addr)

### Desenvolvimento

- Arquitetura do projeto
- Criar uma janela e um loop
- Criação das classes Ball, Robot, Field, Interactions, Score
- Implementação das mecânicas:
- Robot:
- - Movimento
- - Colisão
- - Controle
- Ball:
- - Movimento
- - Colisão
- Interactions:
- - Robô pega a bola
- - Robô lança a bola
- Score:
- - Marcar gol
- - Atualizar placar
- - Voltar às posições iniciais
- Comunicação:
- - Protocolo
- - Envio de comandos
- Segunda janela com representação gráfica dos controles dos robôs
