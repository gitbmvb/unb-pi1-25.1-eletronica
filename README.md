# 🚀 [PI1-25.1] Eletrônica

Este repositório contém o desenvolvimento do sistema eletrônico realizado pelo **Grupo 1** na disciplina de Projeto Integrador de Engenharia 1 (PI1), sob orientação do Prof. Ricardo Ajax Dias Kosloski. O objetivo é fornecer códigos e documentação para todos os componentes eletrônicos do projeto, incluindo base de lançamento e foguete experimental.

## 📑 Sumário

- [📊 Diagramas](#diagramas)
- [📁 Estrutura do Projeto](#estrutura-do-projeto)
- [▶️ Como Executar](#como-executar)
- [👥 Autores](#autores)

## 📊 Diagramas

- [Diagrama de Blocos da Base](docs/img/blocos_base.png)
- [Esquemático da Base](docs/img/esquematico_base_julho.png)
- [Diagrama de Blocos do Foguete](docs/img/blocos_foguete.png)
- [Esquemático do Foguete](docs/img/esquematico_foguete.png)

## 📁 Estrutura do Projeto

O projeto está organizado na seguinte estrutura de pastas:

```
.
├── docs
│   ├── img
├── src
│   ├── base
│   │   ├── main.ino
│   │   └── ...
│   ├── foguete
│   │   ├── foguete.ino
│   ├── tests
│   │   └── ...
├── README.md
```

- A pasta `docs` contém a documentação do projeto, incluindo diagramas e imagens.
- A pasta `src` contém o código-fonte em **Arduino** (`.ino`), organizado em subpastas para a base e o foguete.
- O arquivo `README.md` contém informações gerais sobre o projeto.

## ▶️ Como Executar

Para executar o projeto:

1. ⚙️ Certifique-se de que todas as dependências estão instaladas na IDE Arduino.
2. 🔌 Conecte os componentes eletrônicos conforme os diagramas esquemáticos.
3. 💾 Abra o arquivo `main.ino` da base ou do foguete na IDE Arduino.
4. ⬆️ Faça o upload do código para a placa (Arduino/Raspberry Pi Pico/ESP32, conforme o projeto).
5. 🖥️ Utilize o Monitor Serial para acompanhar o funcionamento.

Consulte a documentação específica de cada componente para mais detalhes sobre execução e testes.

## 👥 Autores

<div align="center">
   <table style="margin-left: auto; margin-right: auto;">
        <tr>
            <td align="center">
                <a href="https://github.com/Bercacos">
                    <img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/187900968?v=4" width="150px;"/>
                    <h5 class="text-center">Bernardo Broetto<br>241010950</h5>
                </a>
            </td>
            <td align="center">
                <a href="https://github.com/gitbmvb">
                    <img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/30751876?v=4" width="150px;"/>
                    <h5 class="text-center">Bruno Martins <br>211039297</h5>
                </a>
            </td>
            <td align="center">
                <a href="https://github.com/HouNst7">
                    <img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/171448629?v=4" width="150px;"/>
                    <h5 class="text-center">Elias Sobrinho <br>241011706</h5>
                </a>
            </td>
            <td align="center">
                <a href="https://github.com/ian-dcg">
                    <img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/78445038?v=4" width="150px;"/>
                    <h5 class="text-center">Ian da Costa <br>190125829</h5>
                </a>
            </td>
            <td align="center">
                <a href="https://github.com/murilopbs">
                    <img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/62524293?v=4" width="150px;"/>
                    <h5 class="text-center">Murilo Perazzo <br>190129221</h5>
                </a>
            </td>
    </table>
</div>