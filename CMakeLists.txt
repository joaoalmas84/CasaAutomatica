cmake_minimum_required(VERSION 3.23)
project(oop_trabalho)

set(CMAKE_CXX_STANDARD 20)

add_executable(oop_trabalho main.cpp Zona.cpp Zona.h Propriedade.cpp Propriedade.h Sensor.cpp Sensor.h Regra.cpp Regra.h Processador.cpp Processador.h Terminal.h Terminal.cpp curses.h Aparelho.cpp Aparelho.h Habitacao.cpp Habitacao.h Comando.cpp Comando.h UI.cpp UI.h RegraBase.cpp RegraBase.h Regra_Igual.cpp Regra_Igual.h)

target_link_libraries(oop_trabalho PRIVATE "C:/Users/35193/OneDrive - ISEC/Ambiente de Trabalho/PDCurses-3.9/PDCurses-3.9/wincon/pdcurses.a")
