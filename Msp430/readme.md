# Como Compilar e Executar (Placa MSP430)

*No terminal (bash, shel, etc...)*

## Compilar

```<Caminho> -mmcu=msp430g2231 -Os <nomeArquivo>.c -o <nomeArquivo>.elf ``` 

ex:

```/home/gabriel/IOT/bin/msp430-elf-gcc -mmcu=msp430g2231 -Os blink.c -o blink.elf```

## Entrar na placa (com acesso total)

```sudo mspdebug rf2500```

## Na Placa (mspdebug)

(mspdebug)``` prog <nomeArquivo>.elf``` - Carregará o programa compilado no debugMSP 

(mspdebug)```run``` executará o programa recem carregado
