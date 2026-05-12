# NanoTekSpice

## Compilation

```bash
make # compile l'entièretée du projet
```

## Lancement

```bash
./nanotekspice <chemin_vers_le_fichier_nts> # Lance le projet avec le fichier spécifié
```

## Commandes

- **simulate** - *simule une fois le courant qui passe dans le circuit.*
- **display** - *affiche l'état actuel des entrées/sorties.*
- **loop** - *execute les commandes simulate et display indéfiniment jusqu'à un `CTRL+C`.*
- **=** - *instancie l'input choisis à la valeur définie (valeur possible: `0` (éteint), `1` (allumé), `U` (non-définie); ex: `in_1=0`).*
- **exit** - *quitte le programme.*

## Composants

- **Special components** :
    - **input** - *simple input* (file: `ntsFiles/specialComponents/input_output.nts`)
    - **output** - *simple output* (file: `ntsFiles/specialComponents/input_output.nts`)
    - **clock** - *inverse l'input à chaques ticks.* (file: `ntsFiles/specialComponents/clock.nts`)
    - **false** - *initialise l'input à 0 (ne peut pas être modifié).* (file: `ntsFiles/specialComponents/false.nts`)
    - **true** - *initialise l'input à 1 (ne peut pas être modifié).* (file: `ntsFiles/specialComponents/true.nts`)
    - **logger** - *écrit le byte spécifié dans le fichier `log.bin`.* (file: `ntsFiles/specialComponents/logger.nts`)
_
- **Elementary components**
    - **and** - *porte ET* (file: `ntsFiles/elementaryComponents/and.nts`)
    - **or** - *porte OR* (file: `ntsFiles/elementaryComponents/or.nts`)
    - **xor** - *porte XOR* (file: `ntsFiles/elementaryComponents/xor.nts`)
    - **not** - *inverse l'input* (file: `ntsFiles/elementaryComponents/not.nts`)
_
- **Gates components** :
    - **4001** - *4 portes OR + NOT* (file: `ntsFiles/gatesComponents/4001_nor.nts`)
    - **4011** - *4 portes ET + NOT* (file: `ntsFiles/gatesComponents/4011_nand.nts`)
    - **4030** - *4 portes XOR* (file: `ntsFiles/gatesComponents/4030_xor.nts`)
    - **4069** - *6 NOT* (file: `ntsFiles/gatesComponents/4069_not.nts`)
    - **4071** - *4 portes OU* (file: `ntsFiles/gatesComponents/4071_or.nts`)
    - **4081** - *4 portes ET* (file: `ntsFiles/gatesComponents/4081_and.nts`)
_
- **Advanced components**
    - **2716** - *rom* (file: `ntsFiles/advancedComponents/2716_rom.nts`)
    - **4008** - *adder* (file: `ntsFiles/advancedComponents/4008_adder.nts`)
    - **4013** - *flip flop* (file: `ntsFiles/advancedComponents/4013_flipflop.nts`)
    - **4017** - *johnson* (file: `ntsFiles/advancedComponents/4017_johnson.nts`)
    - **4040** - *counter* (file: `ntsFiles/advancedComponents/4040_counter.nts`)
    - **4094** - *shift* (file: `ntsFiles/advancedComponents/4094_shift.nts`)
    - **4512** - *selector* (file: `ntsFiles/advancedComponents/4512_selector.nts`)
    - **4514** - *decoder* (file: `ntsFiles/advancedComponents/4514_decoder.nts`)
    - **4801** - *ram* (file: `ntsFiles/advancedComponents/4801_ram.nts`)