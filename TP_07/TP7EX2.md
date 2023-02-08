# EX2

# Pour créer un cgroup nommé tp1_mem sur le sous-système memory, vous pouvez utiliser les commandes suivantes :

Le programme d'allocation de mémoire est disponnible dans le fichier [TP7EX2.c](./TP7EX2.c).

### Créer le cgroup tp1_mem :
```
sudo cgcreate -g memory:tp1_mem
```
### Limiter la consommation de mémoire à 50Mo
```
sudo echo 52428800 > /sys/fs/cgroup/memory/tp1_mem/memory.limit_in_bytes
```
Ces commandes utilisent cgcreate pour créer un cgroup nommé tp1_mem sur le sous-système memory, et echo pour écrire la limite de consommation de mémoire dans le fichier memory.limit_in_bytes. La limite est spécifiée en octets et correspond à 50Mo (50 * 1024 * 1024).

Utiliser la commande suivante dans un premier terminal :
```
htop
```
Utiliser la commande suivante dans un second terminal :
```
memconso
```

Pour voir la consommation de mémoire actuelle du cgroup, vous pouvez utiliser la commande suivante :
```
echo <pid> > /sys/fs/cgroup/memory/tp1_mem/tasks
```

