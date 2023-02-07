
# I – Proposer un service d’infrastructure via conteneur

1. Téléchargez l'image networkboot/dhcpd depuis le hub Docker en utilisant la commande suivante:

        docker pull networkboot/dhcpd

2. Créer un fichier dhcpd.conf contenant le configuration d'exemple.

3. Lancer le conteneurs avec la commande :

        docker run --network=host --name=dhcpd -v /path/to/dhcpd.conf:/data/dhcpd.conf -d networkboot/dhcpd

4.  Pour vérifier que le service est disponible, on peux utiliser la commande ip addr show.

# II – Proposer une stack applicative « wordpress »

1. Créer le fichier [compose.yaml](./compose.yaml) provenant de dockerhub

2. Lancer la commande dans le répetoire contenant  [compose.yaml](./compose.yaml) : 
        
        docker-compose up -d

3. Verifier l'état du conteneur créé avec la commande :

        docker ps

4. Puis verifier l'affichage de wordpress : http://localhost:80

5. On peux ensuite supprimer le conteneur et la base de donnée  avec la commande : 
    
        docker compose down --volumes