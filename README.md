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
