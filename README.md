# Code d'exemple pour la caméra linéaire

Les fichiers contenus dans ce projet permettent de lire l'intensité de chaque
pixel de la caméra linéaire de Robopoly, puis de les afficher dans une fenêtre
dynamique sur un ordinateur à l'aide d'un script Python. 

Le dossier `camera` contient le code à mettre sur le microcontrôleur pour lire
la caméra. Celui-ci envoie les valeurs lues par UART à 9600bps. Les valeurs
d'intensité sont comprises entre 0 et 32, avec 32 la luminosité maximale. On
ajoute ensuite 48 à chaque valeur afin qu'elles correspondent à des caractères
ASCII (pour faciliter la transmission). 48 Correspond au code ASCII du
caractère '0'

Le fichier `cam.py` utilise matplotlib pour afficher un bar plot des valeurs lues par la caméra

Le dossier `matrix` contient une ébauche de code (encore non-fonctionnelle)
pour afficher le bar plot sur une matrice à leds
