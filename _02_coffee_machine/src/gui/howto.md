# QT App project
- Installare QT5
- Scrivere il codice sorgente
- QMake & compile

# Compile
Per creare una configurazione:
`qmake -project` or `qmake-qt5 -project`

Per creare un `Makefile`:
`qmake *.pro`

Per poter compilare correttamente ho aggiunto delle flags
nel file `.pro`, quindi la seguente riga

`QT += gui declarative widgets`

## Depends
- libserial (aur)
