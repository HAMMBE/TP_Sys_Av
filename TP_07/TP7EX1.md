# Mise en place d'un cgroup limitant la vitesse d'I/O disque pour un processus spécifique

## Étape 1 : Benchmark disque
Utilisez la commande dd pour réaliser deux tests consécutifs en générant deux fichiers de 2 Go chacun :
    
```
dd if=/dev/urandom of=test1.txt bs=1M count=2048
dd if=/dev/urandom of=test2.txt bs=1M count=2048
```

- if=/dev/urandom utilise un générateur de nombres aléatoires pour les données d'entrée.

- of=test1.txt spécifie le nom du fichier de sortie.

- bs=1M spécifie la taille de bloc.

- count=2048 spécifie le nombre de blocs à copier.


## Étape 2 : Mise en place du cgroup
Créez un cgroup nommé tp1_blkio qui porte sur le sous-système blkio :

```
sudo cgcreate -g blkio:tp1_blkio
```
Limitez la vitesse de lecture à 5 Mo/s en modifiant les paramètres appropriés dans le fichier /sys/fs/cgroup/blkio/tp1_blkio/blkio.throttle.read_bps_device :
```
sudo echo 5000000 > /sys/fs/cgroup/blkio/tp1_blkio/blkio.throttle.read_bps_device
```
## Étape 3 : Vérification de la contrainte

Utilisez la commande iotop pour observer les activités d'I/O en cours dans un terminal :

```
sudo iotop
```

Utilisez la commande dd à l'intérieur d'un autre terminal en utilisant cgexec pour exécuter la commande avec les contraintes du cgroup :
```
sudo cgexec -g blkio:tp1_blkio dd if=test1.txt of=/dev/null bs=1M
```
Vous devriez constater que la vitesse de lecture est maintenant limitée à 5 Mo/s, comme spécifié dans le cgroup. Si vous exécutez plusieurs instances de la commande dd en utilisant cgexec, vous devriez constater que la vitesse de lecture globale reste limitée à 5 Mo/s pour l'ensemble des instances.