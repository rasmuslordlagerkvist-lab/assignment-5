programmet är skriven i c++ och utgör en slm (small language model) baserad på kgram, med option med pseudocount för "Laplace smoothing". 

hur projektet kompileras & raderas med makefile: 
* `make` - kompilerar: slm 
* `make clean` - raderar: slm 

användning: 
```bash
./slm -a p k filename o 
# eller 
./slm k filename o
```
där, 
* -a är en option.
* p är pseudocount, p > 0.
* Om -a p inte skrivs, sätts p = 0.
* k är längden på kgram, k > 0. 
* filename är en textfil. 
* o är längden man vill att output-texten ska ha, o > k > 0. 

exempel användning:
```bash
./slm -a 0.01 2 a_modest_proposal.txt 100 
./slm 3 moby_dick.txt 100
```

fallgrop för "bra genererad" text: om p > 0 och ett kgram inte fanns i träningstexten så väljs med stor sannolikhet nästa karaktär c, så att nästa kgram inte heller finns i träningstexten. detta orsakar att efter första kgram genererat som inte hittas i träningstexten, så blir med hög sannolikhet alla kommande kgram, dvs genereringen av texten "dåligt genererad". Lite kort beror det på sannolikheten att ett kgram med längd k bildar ett giltigt ord är (antal olika kgram observerade i träningstexten) / (antal kgram som går att skapa, utifrån observerade karaktärer i texten). när k är större, generellt blir sannolikheten att ett kgram med längd k bildar ett giltigt ord, snabbt mycket mindre.
