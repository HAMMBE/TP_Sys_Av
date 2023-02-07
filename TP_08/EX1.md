1. Téléchargement de l'image Jenkins à partir du référentiel Docker.
- `docker pull jenkins/jenkins:alpine`

2. Lancement du conteneur pour fournir le service.
- `docker run -d -p 8080:8080 --name=tp_docker_1 jenkins/jenkins:alpine`

3. Vérification du bon fonctionnement du service.

4. Arrêt du conteneur lié.
- `docker stop tp_docker_jenkins`
