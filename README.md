# ThaleX Graphics Engine

ThaleX Graphics Engine é uma engine gráfica em desenvolvimento usando C++ e OpenGL. O objetivo da ThaleX é fornecer uma base sólida para criar gráficos 3D de alto desempenho e flexíveis. Esta engine faz uso de bibliotecas como GLFW para gerenciamento de janelas, GLM para matemática vetorial e matriz, e GLAD para carregamento de extensões OpenGL.

## Recursos

- **Renderização:**
  - Suporte básico para renderização de objetos 3D.
  - Configuração inicial para adicionar novas técnicas de renderização.

- **Câmera:**
  - Movimento básico da câmera com controles para ajustes de visualização.
  - Planejamento para melhorias no movimento e na configuração da câmera.

## Instalação

Para começar a usar o ThaleX Graphics Engine, você precisa ter o [CMake](https://cmake.org/install/) e as dependências necessárias instaladas. Siga as etapas abaixo:

1. Clone o repositório:
   ```sh
   git clone https://github.com/usuario/thalex-graphics-engine.git
   cd thalex-graphics-engine
   ```

2. Crie um diretório de construção e navegue até ele:
   ```sh
   mkdir build
   cd build
   ```

3. Execute o CMake para gerar os arquivos de construção:
   ```sh
   cmake ..
   ```

4. Compile o projeto:
   ```sh
   make
   ```

5. Execute o aplicativo:
   ```sh
   ./bin/app
   ```

## Uso

Após a construção, você pode executar o aplicativo localizado em `./bin/app`. A engine atualmente suporta a renderização básica de objetos 3D e possui funcionalidades preliminares para controle de câmera.

## ToDo

## Contribuição

Contribuições são bem-vindas! Se você quiser ajudar a melhorar a ThaleX Graphics Engine, por favor, faça um fork do repositório e envie um pull request com suas melhorias ou correções.

## Contato

Para mais informações ou perguntas, você pode entrar em contato com [thaleshend@gmail.com](mailto:thaleshend@gmail.com).