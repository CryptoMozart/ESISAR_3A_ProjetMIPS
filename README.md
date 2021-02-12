# ESISAR_3A_ProjetMIPS

Développement d’un emulateur MIPS

## Utilisation:

exécutez my_emul avec la commande `./my_emul_mips.`
Plusieurs choix s’offrent à vous:

## Pour exécuter un fichier txt contenant votre code MIPS
Pour cela rien de plus simple:

- mettez les fichiers à tester dans le dossier test/. Avec le format .txt
(La traduction en hexadécimal des instructions sera écrite dans le dossier
hexified)
- exécutez la commande ./my_emul_mips nom_de_votre_fichier.txt
- Enjoy

### Mode pas-à-pas

Vous pouvez également utiliser le mode pas-à-pas pour exécuter et voir le résultat
de chaque instruction.
- Donnez en option -pas suivi du nom du fichier à traiter (`./my_emul_mips
-pas nom_de_votre_fichier.txt`)
- Enjoy

### Mode interactif

Pour entrer dans le mode interactif, il suffi d’entrer la commande sans aucun
argument.
Vous pourrez alors entrer vos commandes les unes après les autres.

Notes pour écrire votre fichier:
Afin de rendre possible l’éxécution du code, il vous faudra réspecter la syntaxe
MIPS. C’est à dire:

- Mettre le nom des instructions en majuscule (ADD - ok / add - not ok)
- Donnez le nom des registres sous la forme suivante: $x avec x le numéro
de registre 0 <= x <= 31
- Pour les commentaires, utilisez le caractère ‘#’
- Séparez les registres par le caractère ‘,’ et les instructions des registres par
le caractère espace
- Écrivez une unique instruction par ligne
- Pour la syntaxe de chaque instruction vous pouvez vous référer au document
Annexe2-InstructionsMIPS.pdf
