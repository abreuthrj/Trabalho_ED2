# Trabalho de ED2
## Parte 1
Para rodar o código por linha de comando, digitar no repositorio:
* Windows:
    ```
    g++ *.cpp -I .\ -o Trab.exe -finput-charset=utf-8 //compilar e gerar arquivo executavel
   .\Trab.exe // executar o arquivo
   ```

* Linux ou OSX:
  * Usando g++:
  ```
   g++ -std=c++11  -o trab *.cpp # compila e gera executavel
   ./trab # executa o arquivo
  ```
  * Usando cmake:
  ```
  mkdir build && cd build
  cmake ..
  make
  ./trab
  ```
