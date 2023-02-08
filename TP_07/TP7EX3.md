# EX3


# Pour nettoyer les cgroups créés précédemment en sauvegardant la configuration pour un usage ultérieur.

Utiliser la commande cgsnapshot pour sauvegarder la configuration des groupes.
```
cgsnapshot <directory_name>
```
Utiliser les commandes cgdelete et lscgroup pour supprimer les groupes et vérifier leur suppression effective.
```
cgdelete <group_name>
lscgroup
```
Rendre la configuration permanente en utilisant les fichiers /etc/cgconfig.conf et /etc/cgrules.conf.
```
nano /etc/cgconfig.conf
nano /etc/cgrules.conf
```
Puis vider le cache mémoire avant de vérifier la prise en compte:

```
sync; echo 3 > /proc/sys/vm/drop_caches
```